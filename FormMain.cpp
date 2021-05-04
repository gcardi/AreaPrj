//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <iterator>
#include <utility>
#include <memory>
#include <algorithm>
#include <vector>
#include <thread>

#include <boost/geometry.hpp>
//#include <boost/geometry/geometries/geometries.hpp>

#include "GDIRenderer.h"
#include "GDIPlusRenderer.h"
#include "Utils.h"
#include "PolynomialAreaCalc.h"
#include "StochasticAreaCalc.h"
#include "Cursor.h"
#include "FormMain.h"
#include "StochasticMTAreaCalc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;

//---------------------------------------------------------------------------

using std::begin;
using std::end;
using std::back_inserter;
using std::make_unique;
using std::max;
using std::thread;

using AreaPrj::IRenderer;
using AreaPrj::RetrieveFontList;
using AreaPrj::GDIRenderer;
using AreaPrj::GDIPlusRenderer;
using AreaPrj::PolynomialAreaCalc;
using AreaPrj::StochasticAreaCalc;
using AreaPrj::StochasticMTAreaCalc;

using boost::geometry::envelope;
using boost::geometry::model::box;

//---------------------------------------------------------------------------

// Questa funzione (mai chiamata) serve a verificare che la classe TfrmMain,
// che ha più di una base, implementi tutte le funzioni virtuali delle classi
// da cui deriva. Alcune delle basi di TfrmMain sono classi astratte prive
// di dati (che qui fungono da interfacce). Il meccanismo di creazione della
// istanza assegnata al puntatore frmMain presente in Area.cpp è siffatto:
//
//  Application->CreateForm(__classid(TfrmMain), &frmMain);
//
// Putroppo questi non produce errori se i metodi puri virtuali non sono tutti
// implementati in TfrmMain. Per ovviare a questo inconveniente si crea una
// funzione, che non verrà mai chiamata e che quindi non consuma risorse,
// per innescare il meccanismo di verifica intrinseco nel C++ che pretente
// che tutte le funzioni pure virtuali ereditate da una classe concreta siano
// implementate.
namespace ValidCtrl {
void Test() {
    new ::TfrmMain( nullptr );
}
}

__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TMIfrmMain(Owner)
{
    pnlViewport->ControlStyle = pnlViewport->ControlStyle << csOpaque;

    comboboxFontName->Items->Assign( RetrieveFontList().get() );
    comboboxFontName->ItemIndex =
        max( comboboxFontName->Items->IndexOf( Font->Name ), 0 );
    GetController().AddObserverToModel( *this );

    comboboxAreaMethod->Items->Assign( GetAreaMethodNameList().get() );
    comboboxAreaMethod->ItemIndex = 0;

    comboboxRenderer->Items->Assign( GetRendererNameList().get() );
    comboboxRenderer->ItemIndex = 0;

    UpdateModel();
}
//---------------------------------------------------------------------------

std::unique_ptr<TStringList> TfrmMain::GetAreaMethodNameList()
{
    auto SL = make_unique<TStringList>();
    SL->Append( PolynomialAreaCalc::GetName() );
    SL->Append( StochasticAreaCalc::GetName() );

    // Se la CPU ha più di un thread hardware allora vale la pena
    // di aggiungere anche il calcolatore stochastico multi-thread
    if ( thread::hardware_concurrency() > 1 ) {
        SL->Append( StochasticMTAreaCalc::GetName() );
    }

    return SL;
}
//---------------------------------------------------------------------------

// Factory method
std::unique_ptr<AreaPrj::IAreaCalculator> TfrmMain::MakeAreaCalculator() const
{
    constexpr size_t StochsticPtCount = 1000000;
    switch ( comboboxAreaMethod->ItemIndex ) {
        case 1:
            return make_unique<StochasticAreaCalc>( StochsticPtCount );
        case 2:
            return make_unique<StochasticMTAreaCalc>(
                StochsticPtCount, thread::hardware_concurrency()
            );
        default:
            return make_unique<PolynomialAreaCalc>();
    }
}
//---------------------------------------------------------------------------

std::unique_ptr<TStringList> TfrmMain::GetRendererNameList()
{
    auto SL = make_unique<TStringList>();
    SL->Append( GDIRenderer::GetDescription() );
    SL->Append( GDIPlusRenderer::GetDescription() );
    return SL;
}
//---------------------------------------------------------------------------

// Factory method
std::unique_ptr<IRenderer> TfrmMain::MakeRender() const
{
    switch ( comboboxRenderer->ItemIndex ) {
        case 1:
            return make_unique<GDIPlusRenderer>();
        default:
            return make_unique<GDIRenderer>();
    }
}
//---------------------------------------------------------------------------

void TfrmMain::InvalidateViewport()
{
    paintboxViewport->Invalidate();
}
//---------------------------------------------------------------------------

void TfrmMain::Render()
{
    renderer_->PrepareRendering( GetModel() );
    InvalidateViewport();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::paintboxViewportPaint( TObject *Sender )
{
    auto& PaintBox = static_cast<TPaintBox&>( *Sender );
    auto& PBCanvas = *PaintBox.Canvas;
    if ( IsInputDataValid() ) {
        renderer_->Render( PBCanvas );
    }
    else {
        auto Rect = PaintBox.ClientRect;
        String Txt = _D( "Invalid" );
        auto TextFmt =
            TTextFormat() << tfVerticalCenter << tfCenter << tfSingleLine;
        PBCanvas.Font->Size = 48;
        PBCanvas.TextRect( Rect, Txt, TextFmt );
    }
}
//---------------------------------------------------------------------------

String TfrmMain::DoGetText() const
{
    return edtText->Text;
}
//---------------------------------------------------------------------------

void TfrmMain::DoSetText( String Val )
{
    if ( Val != edtText->Text ) {
        edtText->Text = Val;
        UpdateModel();
    }
}
//---------------------------------------------------------------------------

String TfrmMain::DoGetFontName() const
{
    return comboboxFontName->Text;
}
//---------------------------------------------------------------------------

void TfrmMain::DoSetFontName( String Val )
{
    if ( Val != comboboxFontName->Text ) {
        comboboxFontName->Text = Val;
        UpdateModel();
    }
}
//---------------------------------------------------------------------------

double TfrmMain::DoGetTextSize() const
{
    return edtTextSize->Text.ToDouble();
}
//---------------------------------------------------------------------------

void TfrmMain::DoSetTextSize( double Val )
{
    if ( edtTextSize->Text.ToDouble() != Val ) {
        edtTextSize->Text =
            Format( _D( "%g" ), ARRAYOFCONST(( static_cast<long double>( Val ) )) );
        UpdateModel();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::TextChanged(TObject *Sender)
{
    UpdateModel();
}
//---------------------------------------------------------------------------


void TfrmMain::UpdateModel()
{
    auto TextSize = StrToFloatDef( edtTextSize->Text, -1.0 );
    // Validate Input Data
    inputDataValid_ = TextSize < 1000.0 && TextSize > 0.0;
    if ( IsInputDataValid() ) {
        GetController().SetText(
            IView::GetText(), // Iview:: per risolvere l'ambiguità con Vcl::Controls::TControl
            GetFontName(), TextSize, ofsX_, ofsY_, GetBold(), GetItalic()
        );
        UpdateBoundingBoxValues();
    }
    else {
        InvalidateViewport();
        ClearBoundingBoxValues();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edtTextSizeKeyPress(TObject *Sender, System::WideChar &Key)
{
    switch ( Key ) {
        case VK_RETURN:
            UpdateModel();
            Key = 0;
            break;
        default:
            break;
    }
}
//---------------------------------------------------------------------------

bool TfrmMain::HitTest( int X, int Y ) const
{
    return GetModel().HitTest( X, Y );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::paintboxViewportMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    dragging_ = false;
    if ( IsInputDataValid() && HitTest( X, Y ) ) {
        oldOfsX_ = ofsX_;
        oldOfsY_ = ofsY_;
        startX_ = X - ofsX_;
        startY_ = Y - ofsY_;
        dragging_ = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::paintboxViewportMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
    if ( dragging_ ) {
        ofsX_ = X - startX_;
        ofsY_ = Y - startY_;
        UpdateModel();
    }
    else {
        paintboxViewport->Cursor = HitTest( X, Y ) ? crHandPoint : crCross;
    }

    lblHitTest->Caption =
        IsInputDataValid() ?
          HitTest( X, Y ) ?
            _D( "in" )
          :
            _D( "out" )
        : _D( "-" );
    lblCoords->Caption =
    #if ( __CODEGEARC__ >= 0x0750 )
        Format( _D( "(%d,%d)" ), X, Y );
    #else
        Format( _D( "(%d,%d)" ), ARRAYOFCONST(( X, Y )) );
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::paintboxViewportMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    dragging_ = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pnlViewportResize(TObject *Sender)
{
    lblWidth->Caption = paintboxViewport->ClientWidth;
    lblHeight->Caption = paintboxViewport->ClientHeight;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::comboboxRendererChange(TObject *Sender)
{
    renderer_ = std::move( MakeRender() );
    renderer_->PrepareRendering( GetModel() );
    InvalidateViewport();
}
//---------------------------------------------------------------------------

bool TfrmMain::DoGetBold() const
{
    return checkboxBold->Checked;
}
//---------------------------------------------------------------------------

void TfrmMain::DoSetBold( bool Val )
{
    if ( checkboxBold->Checked != Val ) {
        checkboxBold->Checked = Val;
        UpdateModel();
    }
}
//---------------------------------------------------------------------------

bool TfrmMain::DoGetItalic() const
{
    return checkboxItalic->Checked;
}
//---------------------------------------------------------------------------

void TfrmMain::DoSetItalic( bool Val )
{
    if ( checkboxItalic->Checked != Val ) {
        checkboxItalic->Checked = Val;
        UpdateModel();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actAreaExecute(TObject *Sender)
{
    TCursorManager CursorManager;
    ShowMessage(
        Format(
            _D( "L'area calcolata con il metodo %s è %f u²"  ),
            ARRAYOFCONST((
                areaCalc_->GetDescription(),
                static_cast<long double>(
                    areaCalc_->Compute( GetModel() )
                )
            ))
        )
    );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::actAreaUpdate(TObject *Sender)
{
    auto& Act = static_cast<TAction&>( *Sender );
    Act.Enabled = areaCalc_ && IsInputDataValid();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::comboboxAreaMethodChange(TObject *Sender)
{
    areaCalc_ = std::move( MakeAreaCalculator() );
}
//---------------------------------------------------------------------------

void TfrmMain::CancelTextDrag()
{
    ofsX_ = oldOfsX_;
    ofsY_ = oldOfsY_;
    dragging_ = false;
    UpdateModel();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
    switch ( Key ) {
        case VK_ESCAPE:
            if ( dragging_ ) {
                CancelTextDrag();
            }
            break;
        default:
            break;
    }
}
//---------------------------------------------------------------------------

void TfrmMain::DoPan( int Dx, int Dy )
{
    if ( !dragging_ ) {
        ofsX_ += Dx;
        ofsY_ += Dy;
        UpdateModel();
    }
}
//---------------------------------------------------------------------------

AreaPrj::IModel const & TfrmMain::DoGetModel() const
{
    return GetController().GetModel();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::paintboxViewportMouseLeave(TObject *Sender)
{
    lblCoords->Caption = {};
}
//---------------------------------------------------------------------------

void TfrmMain::UpdateBoundingBoxValues()
{
    if ( !IView::GetText().IsEmpty() ) {
        box<AreaPrj::IModel::PointType> BoundingBox;
        envelope( GetModel().GetPolygons(), BoundingBox );
        lblBoundingBox->Caption =
            Format(
                _D( "BB - W:%.1f H:%.1f" ),
                ARRAYOFCONST((
                    BoundingBox.max_corner().x() - BoundingBox.min_corner().x(),
                    BoundingBox.max_corner().y() - BoundingBox.min_corner().y()
                ))
            );
    }
    else {
        ClearBoundingBoxValues();
    }
}
//---------------------------------------------------------------------------

void TfrmMain::ClearBoundingBoxValues()
{
    lblBoundingBox->Caption = {};
}
//---------------------------------------------------------------------------

