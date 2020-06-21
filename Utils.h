//---------------------------------------------------------------------------

#ifndef UtilsH
#define UtilsH

#include <System.Classes.hpp>

#include <memory>

namespace AreaPrj {

extern std::unique_ptr<TStringList> RetrieveFontList();

// Helper per convertire un Ring di boost.geomerty in un vector di punti GDI
template<typename R, typename T>
R ToGDIPolygon( T const & Ring )
{
    R GDIPoly;

    GDIPoly.reserve( Ring.size() );

    transform(
        begin( Ring ), end( Ring ),
        back_inserter( GDIPoly ),
        []( auto & Pt ) {
            return typename R::value_type( Pt.x(), Pt.y() );
        }
    );
    return GDIPoly;
}

} // End of namespace AreaPrj

//---------------------------------------------------------------------------
#endif
