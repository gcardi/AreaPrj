//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <algorithm>
#include <memory>

#include <Vcl.Graphics.hpp>
#include <Vcl.Direct2D.hpp>
#include <Winapi.D2D1.hpp>

#include "IModel.h"
#include "Direct2DRenderer.h"
#include "Utils.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

using Winapi::D2d1::D2D1PointF;
using Winapi::D2d1::_di_ID2D1SolidColorBrush;
using Winapi::D2d1::_di_ID2D1PathGeometry;
using Winapi::D2d1::_di_ID2D1GeometrySink;
using Winapi::D2d1::_di_ID2D1Geometry;
using Winapi::D2d1::_di_ID2D1Brush;
using Winapi::D2d1::_di_ID2D1StrokeStyle;

namespace AreaPrj {

void Direct2DRenderer::DoPrepareRendering( IModel const & Model, int OfsX, int OfsY )
{
    auto& Polygons = Model.GetPolygons();
    PolygonCont D2DPolygons;
    for ( auto const & Pol : Polygons ) {
        PolygonGroup Group;
        Group.push_back( ToGDIPolygon<Ring>( Pol.outer(), OfsX, OfsY ) );
        for ( auto const & RingInner : Pol.inners() ) {
            Group.push_back( ToGDIPolygon<Ring>( RingInner, OfsX, OfsY ) );
        }
        D2DPolygons.push_back( std::move( Group ) );
    }
    polygons_ = std::move( D2DPolygons );
}
//---------------------------------------------------------------------------

void Direct2DRenderer::DoRender( Vcl::Graphics::TCanvas& Canvas ) const
{
    if ( !TDirect2DCanvas::Supported() ) return;

    auto const ClipRect = Canvas.ClipRect;
    int const W = ClipRect.Width();
    int const H = ClipRect.Height();
    if ( W <= 0 || H <= 0 ) return;

    std::unique_ptr<TDirect2DCanvas> D2DC(
        new TDirect2DCanvas( &Canvas, ClipRect )
    );
    D2DC->BeginDraw();

    D2D1_COLOR_F WhiteColor = { 1.0f, 1.0f, 1.0f, 1.0f };
    D2DC->RenderTarget->Clear( WhiteColor );
    D2DC->RenderTarget->SetAntialiasMode( D2D1_ANTIALIAS_MODE_PER_PRIMITIVE );

    // Create stroke brush (black)
    _di_ID2D1SolidColorBrush StrokeBrush;
    D2D1_COLOR_F BlackColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    D2DC->RenderTarget->CreateSolidColorBrush( BlackColor, nullptr, StrokeBrush );

    // Create fill brush (light blue)
    _di_ID2D1SolidColorBrush FillBrush;
    if ( GetFilled() ) {
        D2D1_COLOR_F FillColor = { 200.0f/255, 220.0f/255, 255.0f/255, 1.0f };
        D2DC->RenderTarget->CreateSolidColorBrush( FillColor, nullptr, FillBrush );
    }

    auto Factory = Vcl::Direct2d::D2DFactory();

    for ( auto const & Group : polygons_ ) {
        _di_ID2D1PathGeometry Geometry;
        Factory->CreatePathGeometry( Geometry );

        _di_ID2D1GeometrySink Sink;
        Geometry->Open( Sink );
        Sink->SetFillMode( D2D1_FILL_MODE_ALTERNATE );

        for ( auto const & Ring : Group ) {
            if ( Ring.size() < 2 ) continue;
            Sink->BeginFigure(
                D2D1PointF( Ring[0].X, Ring[0].Y ),
                GetFilled() ? D2D1_FIGURE_BEGIN_FILLED
                            : D2D1_FIGURE_BEGIN_HOLLOW
            );
            for ( std::size_t i = 1; i < Ring.size(); ++i ) {
                Sink->AddLine( D2D1PointF( Ring[i].X, Ring[i].Y ) );
            }
            Sink->EndFigure( D2D1_FIGURE_END_CLOSED );
        }
        Sink->Close();

        _di_ID2D1Geometry BaseGeom( Geometry );
        if ( GetFilled() && FillBrush ) {
            _di_ID2D1Brush FBrush( FillBrush );
            D2DC->RenderTarget->FillGeometry( BaseGeom, FBrush, nullptr );
        }
        _di_ID2D1Brush SBrush( StrokeBrush );
        D2DC->RenderTarget->DrawGeometry( BaseGeom, SBrush, 1.0f, nullptr );
    }

    D2DC->EndDraw();
}
//---------------------------------------------------------------------------

} // End of namespace AreaPrj
