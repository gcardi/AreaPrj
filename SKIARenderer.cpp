//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <memory>

#include <Vcl.Graphics.hpp>
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>

#include "IModel.h"
#include "SKIARenderer.h"
#include "Utils.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace AreaPrj {

void SKIARenderer::DoPrepareRendering( IModel const & Model, int OfsX, int OfsY )
{
    auto& Polygons = Model.GetPolygons();
    PolygonCont SkiaPolygons;
    for ( auto const & Pol : Polygons ) {
        SkiaPolygons.push_back( ToGDIPolygon<Polygon>( Pol.outer(), OfsX, OfsY ) );
        for ( auto const & RingInner : Pol.inners() ) {
            SkiaPolygons.push_back( ToGDIPolygon<Polygon>( RingInner, OfsX, OfsY ) );
        }
    }
    polygons_ = std::move( SkiaPolygons );
}
//---------------------------------------------------------------------------

void SKIARenderer::DoRender( Vcl::Graphics::TCanvas& Canvas ) const
{
    auto const ClipRect = Canvas.ClipRect;
    int const W = ClipRect.Width();
    int const H = ClipRect.Height();
    if ( W <= 0 || H <= 0 ) return;

    auto Bmp = std::make_unique<Vcl::Graphics::TBitmap>();
    Bmp->PixelFormat = pf32bit;
    Bmp->SetSize( W, H );

    using namespace System::Skia;

    Vcl::Skia::SkiaDraw( Bmp.get(),
        [this]( const _di_ISkCanvas ACanvas ) {
            auto LPaint = SkPaint( TSkPaintStyle::Stroke );
            LPaint->AntiAlias = true;
            LPaint->Color = 0xFF000000;
            LPaint->StrokeWidth = 1;

            for ( auto const & Polygon : polygons_ ) {
                if ( Polygon.size() < 2 ) continue;
                auto LPathBuilder = SkPathBuilder();
                LPathBuilder->MoveTo( Polygon[0].X, Polygon[0].Y );
                for ( std::size_t i = 1; i < Polygon.size(); ++i ) {
                    LPathBuilder->LineTo( Polygon[i].X, Polygon[i].Y );
                }
                LPathBuilder->Close();
                ACanvas->DrawPath( LPathBuilder->Detach(), LPaint );
            }
        }, true );

    Canvas.Draw( ClipRect.Left, ClipRect.Top, Bmp.get() );
}
//---------------------------------------------------------------------------

} // End of namespace AreaPrj
