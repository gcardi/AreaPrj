//---------------------------------------------------------------------------

#pragma hdrstop

#include <System.SysUtils.hpp>

#include <random>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>

#include "IModel.h"
#include "StochasticAreaCalc.h"

using std::mt19937;
using std::uniform_real_distribution;

using boost::geometry::envelope;

using boost::geometry::model::box;
using boost::geometry::area;

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace AreaPrj {

String StochasticAreaCalc::DoGetDescription() const
{
    return Format(
        _D( "\'%s\' con %.0n di punti casuali" ),
        ARRAYOFCONST((
            GetName(),
            static_cast<long double>( pointCount_ )
        ))
    );
}

double StochasticAreaCalc::DoCompute( IModel const & Model ) const
{
    //Standard mersenne_twister_engine seeded with rd()
    mt19937 Generator( rd_() );

    box<IModel::PointType> BoundingBox;

    auto const & Polygons = Model.GetPolygons();

    envelope( Polygons, BoundingBox );

    uniform_real_distribution<> DisX(
        BoundingBox.min_corner().x(),
        BoundingBox.max_corner().x()
    );

    uniform_real_distribution<> DisY(
        BoundingBox.min_corner().y(),
        BoundingBox.max_corner().y()
    );

    size_t HitCnt {};

    for ( size_t n = 0 ; n < pointCount_ ; ++n ) {
        if ( Model.HitTest( DisX( Generator ), DisY( Generator ) ) ) {
            ++HitCnt;
        }
    }

    return static_cast<double>( HitCnt ) / pointCount_ * area( BoundingBox );
}

} // End of namespace AreaPrj

