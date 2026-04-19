//---------------------------------------------------------------------------

#pragma hdrstop

#include <System.SysUtils.hpp>

#include <windows.h>

#include <GdiPlus.h>

#include <iterator>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Calc.h"
#include "IObserver.h"

using Gdiplus::GraphicsPath;
using Gdiplus::FontFamily;
using Gdiplus::FontStyle;
using Gdiplus::StringFormat;
using Gdiplus::StringAlignment;

using std::begin;
using std::end;
using std::advance;

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace AreaPrj {

void Calc::DoAddObserverToModel( IObserver& Observer )
{
    geo_.AddObserver( Observer );
}
//---------------------------------------------------------------------------

template<typename It>
inline bool IsMove( It Curr, It End )
{
    return
        Curr != End &&
        ( *Curr & Gdiplus::PathPointTypePathTypeMask ) ==
        Gdiplus::PathPointTypeStart;
}

template<typename It>
inline bool IsClosed( It Curr, It End )
{
    return
        Curr != End &&
        ( *Curr & Gdiplus::PathPointTypeCloseSubpath ) &&
        !( *Curr & Gdiplus::PathPointTypePathMarker );
}

template<typename It>
inline bool IsMarker( It Curr, It End )
{
    return Curr != End &&
           ( *Curr & Gdiplus::PathPointTypePathMarker );
}

template<typename It>
inline bool IsLine( It Curr, It End )
{
    if ( Curr != End ) {
        switch ( *Curr & static_cast<BYTE>( Gdiplus::PathPointTypePathTypeMask ) ) {
            case Gdiplus::PathPointTypeLine:
            case Gdiplus::PathPointTypeBezier:
                return true;
            default:
                break;
        }
    }
    return false;
}

template<typename TIt, typename PIt>
inline void Adv( TIt& Pi, PIt& Ti )
{
    advance( Pi, 1 );
    advance( Ti, 1 );
}

// Ogni tanto capita che una glyph abbia i ring "invertiti" (cio�
// quello esterno in uno interno e viceversa). La strategia �
// di cercare il ring interno con l'area pi� grande e scambiarlo
// con quello esterno se questi � pi� grande
void FixGlyph( IModel::PolygonType& Polygon )
{
    namespace bg = boost::geometry;

    bg::correct( Polygon );

    if ( !Polygon.inners().empty() ) {
        auto ItMax = std::max_element(
            begin( Polygon.inners() ), end( Polygon.inners() ),
            []( auto const & Lhs, auto const & Rhs ) {
                return fabs( bg::area( Lhs ) ) < fabs( bg::area( Rhs ) );
            }
        );

        if ( fabs( bg::area( *ItMax ) ) > fabs( bg::area( Polygon.outer() ) ) ) {
            std::swap( *ItMax, Polygon.outer() );
            bg::correct( Polygon );
        }
    }
}

enum class RingTerminator { Closed, Marker };

template<typename TIt, typename PIt, typename Ring>
inline RingTerminator ReadRing( TIt& ti, PIt& pi, TIt te, Ring& R, bool IsOuter )
{
    R.emplace_back( pi->X, pi->Y );
    Adv( ti, pi );

    if ( !IsLine( ti, te ) ) {
        throw Exception(
            IsOuter
              ? _D( "'line' expected: outer ring not closed" )
              : _D( "'line' expected: inner ring not closed" )
        );
    }
    R.emplace_back( pi->X, pi->Y );
    Adv( ti, pi );

    while ( IsLine( ti, te ) && !IsMarker( ti, te ) && !IsClosed( ti, te ) ) {
        R.emplace_back( pi->X, pi->Y );
        Adv( ti, pi );
    }

    if ( IsClosed( ti, te ) ) {
        R.emplace_back( pi->X, pi->Y );
        return RingTerminator::Closed;
    }
    if ( IsMarker( ti, te ) ) {
        R.emplace_back( pi->X, pi->Y );
        return RingTerminator::Marker;
    }

    throw Exception(
        IsOuter
          ? _D( "outer ring not properly closed" )
          : _D( "inner ring not properly closed" )
    );
}

void Calc::DoSetText( String Val, String FontName, double FontSize,
                      bool Bold, bool Italic )
{
    // Usando GDI+, converte il testo in primitive grafiche
    // (poligoni/ring) e le scrive nel modello

    // Crea il path dal testo
    GraphicsPath GPath;

    GPath.StartFigure();

    FontFamily fontFamily( FontName.c_str() );
    StringFormat sf;
//    sf.SetAlignment( StringAlignment::StringAlignmentCenter );
//    sf.SetLineAlignment( StringAlignment::StringAlignmentCenter );

    GPath.AddString(
        Val.c_str(), -1,
        &fontFamily,
        Bold ?
          Italic ?
            FontStyle::FontStyleBoldItalic
          :
            FontStyle::FontStyleBold
        :
          Italic ?
            FontStyle::FontStyleItalic
          :
            FontStyle::FontStyleRegular,
        FontSize,
        Gdiplus::PointF( 0, 0 ),
        &sf
    );
    GPath.CloseFigure();

    // estrae i segmenti di linea dal path
    auto const Cnt = GPath.GetPointCount();

    using PointCnt = std::vector<Gdiplus::PointF>;
    using TypeCnt = std::vector<BYTE>;

    PointCnt Pts( Cnt );
    GPath.GetPathPoints( Pts.data(), Pts.size() );

    TypeCnt Tps( Cnt );
    GPath.GetPathTypes( Tps.data(), Tps.size() );

    // GDI+  -->  boost::geometry

    namespace bg = boost::geometry;

    IModel::PolygonCont Polygons;

    auto ti = begin( Tps );
    auto te = end( Tps );
    auto pi = begin( Pts );
    auto pe = end( Pts );

    for ( ; pi != pe ; ) {
        if ( !IsMove( ti, te ) ) {
            throw Exception( _D( "Starting 'move' expected for outer ring" ) );
        }

        IModel::PolygonType Polygon;
        auto term = ReadRing( ti, pi, te, Polygon.outer(), true );

        while ( term == RingTerminator::Closed ) {
            Adv( ti, pi );
            if ( !IsMove( ti, te ) ) {
                throw Exception( _D( "Starting 'move' expected for inner ring" ) );
            }
            Polygon.inners().push_back({});
            term = ReadRing( ti, pi, te, Polygon.inners().back(), false );
        }

        FixGlyph( Polygon );
        Polygons.push_back( Polygon );
        Adv( ti, pi );
    }
    geo_.SetPolygons( std::move( Polygons ) );
}

} // End of namespace AreaPrj
