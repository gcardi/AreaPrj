//---------------------------------------------------------------------------

#pragma hdrstop

#include <System.SysUtils.hpp>

#include <random>
#include <future>
#include <vector>
#include <numeric>
#include <iterator>
#include <utility>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>

#include "IModel.h"

#include "StochasticMTAreaCalc.h"

using std::mt19937;
using std::uniform_real_distribution;
using std::accumulate;
using std::begin;
using std::end;

using boost::geometry::envelope;

using boost::geometry::model::box;
using boost::geometry::area;

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace AreaPrj {

String StochasticMTAreaCalc::DoGetDescription() const
{
    return Format(
        _D( "\'%s\' with %.0n random points using %u tasks" ),
        ARRAYOFCONST((
            GetName(),
            static_cast<long double>( pointCount_ ),
            taskCount_
        ))
    );
}

double StochasticMTAreaCalc::DoCompute( IModel const & Model ) const
{
    box<IModel::PointType> BoundingBox;
    auto const & Polygons = Model.GetPolygons();
    envelope( Polygons, BoundingBox );
    std::vector<std::future<size_t>> Tasks;
    for ( size_t n = 0 ; n < taskCount_ ; ++n ) {
        Tasks.push_back(
            std::async(
                std::launch::async,
                [&]( std::random_device::result_type seed, size_t PtCnt ) -> size_t {
                    auto const & Polygons = Model.GetPolygons();
                    mt19937 Generator( seed );
                    uniform_real_distribution<> DisX(
                        BoundingBox.min_corner().x(),
                        BoundingBox.max_corner().x()
                    );

                    uniform_real_distribution<> DisY(
                        BoundingBox.min_corner().y(),
                        BoundingBox.max_corner().y()
                    );

                    size_t HitCnt {};

                    for ( size_t n = 0 ; n < PtCnt ; ++n ) {
                        if ( Model.HitTest( DisX( Generator ), DisY( Generator ) ) ) {
                            ++HitCnt;
                        }
                    }
                    return HitCnt;
                },
                rd_(),
                pointCount_ / taskCount_
            )
        );
    }
    return
        static_cast<double>(
            accumulate<decltype( begin( Tasks ) ), size_t>(
                begin( Tasks ), end( Tasks ), {},
                []( size_t Val, auto& fut ) {
                    return Val + fut.get();
                }
            )
        ) /
        pointCount_ * area( BoundingBox );
}

} // End of namespace AreaPrj
