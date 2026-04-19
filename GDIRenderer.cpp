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
        GdiPolygons.push_back( ToGDIPolygon<Polygon>( Pol.outer(), OfsX, OfsY ) );
        for ( auto const & RingInner : Pol.inners() ) {
            GdiPolygons.push_back( ToGDIPolygon<Polygon>( RingInner, OfsX, OfsY ) );
        }
    }

    polygons_ = std::move( GdiPolygons );
}
//---------------------------------------------------------------------------

void GDIRenderer::DoRender( Vcl::Graphics::TCanvas& Canvas ) const
{
    for ( auto const & Polygon : polygons_ ) {
        if ( Polygon.size() < 2 ) continue;
        Canvas.Polyline( Polygon.data(), Polygon.size() - 1 );
    }
}
//---------------------------------------------------------------------------

} // End of namespace AreaPrj

