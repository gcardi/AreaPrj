//---------------------------------------------------------------------------

#ifndef UtilsH
#define UtilsH

#include <System.Classes.hpp>

#include <algorithm>
#include <iterator>
#include <memory>

namespace AreaPrj {

extern std::unique_ptr<TStringList> RetrieveFontList();

// Helper per convertire un Ring di boost.geomerty in un vector di punti GDI
template<typename R, typename T>
R ToGDIPolygon( T const & Ring, double OfsX = 0, double OfsY = 0 )
{
    R GDIPoly;

    GDIPoly.reserve( Ring.size() );

    std::transform(
        std::begin( Ring ), end( Ring ),
        std::back_inserter( GDIPoly ),
        [OfsX, OfsY]( auto & Pt ) {
            return typename R::value_type( Pt.x() + OfsX, Pt.y() + OfsY );
        }
    );
    return GDIPoly;
}

extern TFormatSettings const & InvariantFmt();

} // End of namespace AreaPrj

//---------------------------------------------------------------------------
#endif
