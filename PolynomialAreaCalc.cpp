//---------------------------------------------------------------------------

#pragma hdrstop

#include <boost/geometry.hpp>

#include "PolynomialAreaCalc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace AreaPrj {

double PolynomialAreaCalc::DoCompute( IModel const & Model ) const
{
    return boost::geometry::area( Model.GetPolygons() );
}

} // End of namespace AreaPrj

