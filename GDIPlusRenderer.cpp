//---------------------------------------------------------------------------

#pragma hdrstop

#include <algorithm>

#include <Vcl.Graphics.hpp>

#include "IModel.h"
#include "GDIPlusRenderer.h"
#include "Utils.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace AreaPrj {

void GDIPlusRenderer::DoPrepareRendering( IModel const & Model, int OfsX, int OfsY )
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

void GDIPlusRenderer::DoRender( Vcl::Graphics::TCanvas& Canvas ) const
{
    Gdiplus::Graphics g( Canvas.Handle );
    Gdiplus::Pen MPen( Gdiplus::Color( 0xFF, 0, 0, 0 ) );
    g.SetSmoothingMode( Gdiplus::SmoothingModeAntiAlias );
    if ( GetFilled() ) {
        Gdiplus::SolidBrush MBrush( Gdiplus::Color( 0xFF, 200, 220, 255 ) );
        for ( auto const & Group : polygons_ ) {
            Gdiplus::GraphicsPath Path( Gdiplus::FillModeAlternate );
            for ( auto const & Ring : Group ) {
                if ( Ring.size() < 2 ) continue;
                Path.AddPolygon( Ring.data(), Ring.size() );
            }
            g.FillPath( &MBrush, &Path );
            g.DrawPath( &MPen, &Path );
        }
    }
    else {
        for ( auto const & Group : polygons_ ) {
            for ( auto const & Ring : Group ) {
                g.DrawPolygon( &MPen, Ring.data(), Ring.size() );
            }
        }
    }
}
//---------------------------------------------------------------------------

} // End of namespace AreaPrj
