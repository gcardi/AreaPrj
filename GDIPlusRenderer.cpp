//---------------------------------------------------------------------------

#pragma hdrstop

#include <algorithm>

#include <Vcl.Graphics.hpp>

#include "IModel.h"
#include "GDIPlusRenderer.h"
#include "Utils.h"

using std::transform;

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace AreaPrj {

void GDIPlusRenderer::DoPrepareRendering( IModel const & Model )
{
    auto& Polygons = Model.GetPolygons();
    PolygonCont GdiPolygons;
    for ( auto const & Pol : Polygons ) {
        GdiPolygons.push_back( ToGDIPolygon<Polygon>( Pol.outer() ) );
        for ( auto const & RingInner : Pol.inners() ) {
            GdiPolygons.push_back( ToGDIPolygon<Polygon>( RingInner ) );
        }
    }
    polygons_ = std::move( GdiPolygons );
}
//---------------------------------------------------------------------------

void GDIPlusRenderer::DoRender( Vcl::Graphics::TCanvas& Canvas ) const
{
    Gdiplus::Graphics g( Canvas.Handle );
    Gdiplus::Pen MPen( Gdiplus::Color( 0xFF, 0, 0, 0 ) );
    g.SetSmoothingMode( Gdiplus::SmoothingModeAntiAlias );
    for ( auto const & Polygon : polygons_ ) {
        g.DrawPolygon( &MPen, Polygon.data(), Polygon.size() );
    }
}
//---------------------------------------------------------------------------

} // End of namespace AreaPrj
