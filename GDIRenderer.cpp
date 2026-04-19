//---------------------------------------------------------------------------

#pragma hdrstop

#include <algorithm>

#include <Vcl.Graphics.hpp>

#include "IModel.h"
#include "GDIRenderer.h"
#include "Utils.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace AreaPrj {

void GDIRenderer::DoPrepareRendering( IModel const & Model, int OfsX, int OfsY )
{
    auto& Polygons = Model.GetPolygons();

    PolygonCont GdiPolygons;

    for ( auto const & Pol : Polygons ) {
        PolygonGroup Group;
        Group.push_back( ToGDIPolygon<Ring>( Pol.outer(), OfsX, OfsY ) );
        for ( auto const & RingInner : Pol.inners() ) {
            Group.push_back( ToGDIPolygon<Ring>( RingInner, OfsX, OfsY ) );
        }
        GdiPolygons.push_back( std::move( Group ) );
    }

    polygons_ = std::move( GdiPolygons );
}
//---------------------------------------------------------------------------

void GDIRenderer::DoRender( Vcl::Graphics::TCanvas& Canvas ) const
{
    if ( GetFilled() ) {
        Canvas.Pen->Style = psSolid;
        Canvas.Pen->Color = clBlack;
        Canvas.Brush->Style = bsSolid;
        Canvas.Brush->Color = static_cast<TColor>( RGB( 200, 220, 255 ) );
        SetPolyFillMode( Canvas.Handle, ALTERNATE );
        for ( auto const & Group : polygons_ ) {
            std::vector<TPoint> AllPoints;
            std::vector<int> Counts;
            for ( auto const & Ring : Group ) {
                if ( Ring.size() < 2 ) continue;
                AllPoints.insert( AllPoints.end(), Ring.begin(), Ring.end() );
                Counts.push_back( static_cast<int>( Ring.size() ) );
            }
            if ( !Counts.empty() ) {
                ::PolyPolygon(
                    Canvas.Handle, AllPoints.data(),
                    Counts.data(), static_cast<int>( Counts.size() )
                );
            }
        }
    }
    else {
        for ( auto const & Group : polygons_ ) {
            for ( auto const & Ring : Group ) {
                if ( Ring.size() < 2 ) continue;
                Canvas.Polyline( Ring.data(), Ring.size() - 1 );
            }
        }
    }
}
//---------------------------------------------------------------------------

} // End of namespace AreaPrj

