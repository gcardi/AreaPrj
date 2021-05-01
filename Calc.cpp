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

void Calc::DoSetText( String Val, String FontName, double FontSize,
                      double DX, double DY, bool Bold, bool Italic )
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
        Gdiplus::Point( DX, DY ),
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

    /*
        // Dot language (for graphviz)
        //
        // Use http://magjac.com/graphviz-visual-editor/ to see the graph
        // (paste following code to the left pane)

        digraph finite_state_machine {
            rankdir=LR;
            size="8,5"
            node [shape = none]; START;
            node [shape = doublecircle]; EXIT;
            node [shape = circle];
            // MV = IsMove( ti, te )
            // LN = IsLine( ti, te )
            // CL = IsClosed( ti, te )
            // MK = IsMarker( ti, te )
            START -> O1
            O1 -> EXIT [label = "EOF"];
            O1 -> O2 [label = "MV (A)"];
            O1 -> EXIT [label = "!MV (E1)"];
            O2 -> O3 [label = "LN (B)"];
            O2 -> EXIT [label = "!LN (E2)"];
            O3 -> O3 [label = "|1| LN (B)"];
            O3 -> I1 [label = "|2| CL (B)"];
            O3 -> O1 [label = "MK (C)"];
            O3 -> EXIT [label = "!MK (E3)"];
            I1 -> I2 [label = "MV (D)"];
            I1 -> EXIT [label = "!MV (E4)"];
            I2 -> I3 [label = "LN (F)"];
            I2 -> EXIT [label = "!LN (E5)"];
            I3 -> I3 [label = "LN (F)"];
            I3 -> I1 [label = "CL (F)"];
            I3 -> O1 [label = "MK (G)"];
            I3 -> EXIT [label = "!MK (E6)"];
        }
    */

    for ( ; pi != pe ; ) {
        // O1
        if ( IsMove( ti, te ) ) {
            // (A)
            IModel::PolygonType Polygon;
            Polygon.outer().emplace_back( pi->X, pi->Y );
            Adv( ti, pi );
            // O2
            if ( IsLine( ti, te ) ) {
                // (B)
                Polygon.outer().emplace_back( pi->X, pi->Y );
                Adv( ti, pi );
                // O3
                while ( IsLine( ti, te ) ) {
                    if ( IsMarker( ti, te ) || IsClosed( ti, te ) ) {
                        break;
                    }
                    // (B)
                    Polygon.outer().emplace_back( pi->X, pi->Y );
                    Adv( ti, pi );
                }
                if ( IsClosed( ti, te ) ) {
                    // (B) (Adv implicito)
                    Polygon.outer().emplace_back( pi->X, pi->Y );
                    do {
                        Adv( ti, pi );
                        // I1
                        if ( IsMove( ti, te ) ) {
                            // (D)
                            Polygon.inners().push_back({});
                            Polygon.inners().back().emplace_back( pi->X, pi->Y );
                            Adv( ti, pi );
                            // I2
                            if ( IsLine( ti, te ) ) {
                                // (F)
                                Polygon.inners().back().emplace_back(
                                    pi->X, pi->Y
                                );
                                Adv( ti, pi );
                                // I3
                                while ( IsLine( ti, te ) ) {
                                    if ( IsMarker( ti, te ) || IsClosed( ti, te ) ) {
                                        break;
                                    }
                                    // (F)
                                    Polygon.inners().back().emplace_back(
                                        pi->X, pi->Y
                                    );
                                    Adv( ti, pi );
                                }
                                if ( IsClosed( ti, te ) ) {
                                    // (F) (Adv implicito)
                                    Polygon.inners().back().emplace_back(
                                        pi->X, pi->Y
                                    );
                                    // Adv( ti, pi );
                                    // goto I1
                                }
                                else if ( IsMarker( ti, te ) ) {
                                    // (G) (Adv implicito)
                                    Polygon.inners().back().emplace_back(
                                        pi->X, pi->Y
                                    );
                                    FixGlyph( Polygon );
                                    Polygons.push_back( Polygon );
                                    // goto O1
                                    break;
                                }
                                else {
                                    // E6
                                    throw Exception(
                                        _D( "inner ring not properly closed" )
                                    );
                                }
                            }
                            else {
                                // E5
                                throw Exception(
                                    _D( "'line' expected: inner ring not closed" )
                                );
                            }
                        }
                        else {
                            // E4
                            throw Exception(
                                _D( "Starting 'move' expected for inner ring" )
                            );
                        }
                    }
                    while ( !IsMarker( ti, te ) );
                }
                else if ( IsMarker( ti, te ) ) {
                    // (C) (Adv implicito)
                    Polygon.outer().emplace_back( pi->X, pi->Y );
                    FixGlyph( Polygon );
                    Polygons.push_back( Polygon );
                    // goto O1
                }
                else {
                    // E3
                    throw Exception( _D( "outer ring not properly closed" ) );
                }
            }
            else {
                // E2
                throw Exception(
                    _D( "'line' expected: outer ring not closed" )
                );
            }
        }
		else
		{
            // (E1)
			throw Exception( _D( "Starting 'move' expected for outer ring" ) );
		}
		Adv( ti, pi );
	}
    geo_.SetPolygons( std::move( Polygons ) );
}

} // End of namespace AreaPrj
