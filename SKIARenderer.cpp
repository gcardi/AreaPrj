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
        PolygonGroup Group;
        Group.push_back( ToGDIPolygon<Ring>( Pol.outer(), OfsX, OfsY ) );
        for ( auto const & RingInner : Pol.inners() ) {
            Group.push_back( ToGDIPolygon<Ring>( RingInner, OfsX, OfsY ) );
        }
        SkiaPolygons.push_back( std::move( Group ) );
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
            bool const Filled = GetFilled();

            _di_ISkPaint LFillPaint;
            if ( Filled ) {
                LFillPaint = SkPaint( TSkPaintStyle::Fill );
                LFillPaint->AntiAlias = true;
                LFillPaint->Color = 0xFFC8DCFF; // RGB(200,220,255)
            }

            auto LPaint = SkPaint( TSkPaintStyle::Stroke );
            LPaint->AntiAlias = true;
            LPaint->Color = 0xFF000000;
            LPaint->StrokeWidth = 1;

            for ( auto const & Group : polygons_ ) {
                if ( Filled ) {
                    auto LPathBuilder =
                        SkPathBuilder( TSkPathFillType::EvenOdd );
                    for ( auto const & Ring : Group ) {
                        if ( Ring.size() < 2 ) continue;
                        LPathBuilder->MoveTo( Ring[0].X, Ring[0].Y );
                        for ( std::size_t i = 1; i < Ring.size(); ++i ) {
                            LPathBuilder->LineTo( Ring[i].X, Ring[i].Y );
                        }
                        LPathBuilder->Close();
                    }
                    auto LPath = LPathBuilder->Detach();
                    ACanvas->DrawPath( LPath, LFillPaint );
                    ACanvas->DrawPath( LPath, LPaint );
                }
                else {
                    for ( auto const & Ring : Group ) {
                        if ( Ring.size() < 2 ) continue;
                        auto LPathBuilder = SkPathBuilder();
                        LPathBuilder->MoveTo( Ring[0].X, Ring[0].Y );
                        for ( std::size_t i = 1; i < Ring.size(); ++i ) {
                            LPathBuilder->LineTo( Ring[i].X, Ring[i].Y );
                        }
                        LPathBuilder->Close();
                        ACanvas->DrawPath( LPathBuilder->Detach(), LPaint );
                    }
                }
            }
        }, true );

    Canvas.Draw( ClipRect.Left, ClipRect.Top, Bmp.get() );
}
//---------------------------------------------------------------------------

} // End of namespace AreaPrj
