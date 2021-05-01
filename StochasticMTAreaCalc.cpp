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
        _D( "\'%s\' con %.0n di punti casuali suddiviso in %u task" ),
        ARRAYOFCONST((
            GetName(),
            static_cast<long double>( GetPointCount() ),
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
                    return HitTest( Model, BoundingBox, PtCnt, seed );
                },
                rd_(),
                GetPointCount() / taskCount_
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
        GetPointCount() * area( BoundingBox );
}

} // End of namespace AreaPrj
