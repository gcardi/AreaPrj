//---------------------------------------------------------------------------

#ifndef FormMainH
#define FormMainH

//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>

#include "anafestica/PersistFormVCL.h"
#include "anafestica/CfgRegistrySingleton.h"
#include <Vcl.ComCtrls.hpp>
#include "FrameTextData.h"

#include <memory>

#include "IController.h"
#include "IRenderer.h"
#include "IAreaCalculator.h"
#include "IModel.h"

#include "IObserver.h"
#include "IView.h"

#include "Calc.h"

// This class is needed to fool the Embarcadero's IDE which doesn't like
// multiple inheritance at the level of TObject derived classes
class TMIfrmMain : public TForm, public AreaPrj::IView, public AreaPrj::IObserver {
public:
    template<typename...A>
    TMIfrmMain( A&&... Args ) : TForm( std::forward<A>( Args )... ) {}
protected:
    INTFOBJECT_IMPL_IUNKNOWN(TForm)
};

class TfrmMain : public TMIfrmMain
{
__published:	// IDE-managed Components
    TPaintBox *paintboxViewport;
    TPanel *pnlViewport;
    TLabel *lblHitTest;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *lblWidth;
    TLabel *Label8;
    TLabel *lblHeight;
    TComboBox *comboboxRenderer;
    TLabel *Label7;
    TPanel *Panel1;
    TPanel *Panel2;
    TActionList *ActionList1;
    TAction *actArea;
    TButton *Button1;
    TComboBox *comboboxAreaMethod;
    TLabel *Label2;
    TLabel *lblCoords;
    TLabel *lblBoundingBox;
    TCheckBox *checkboxFillArea;
    TPageControl *pagecontrolProperties;
    TTabSheet *tbshtText;
    TfrmeTextData *frmeTextData1;
    void __fastcall paintboxViewportPaint(TObject *Sender);
    void __fastcall paintboxViewportMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall pnlViewportResize(TObject *Sender);
    void __fastcall paintboxViewportMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall paintboxViewportMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall comboboxRendererChange(TObject *Sender);
    void __fastcall actAreaExecute(TObject *Sender);
    void __fastcall actAreaUpdate(TObject *Sender);
    void __fastcall comboboxAreaMethodChange(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall paintboxViewportMouseLeave(TObject *Sender);
    void __fastcall checkboxFillAreaClick(TObject *Sender);

public:		// User declarations
    __fastcall TfrmMain( TComponent* Owner ) override;

    AreaPrj::IController& GetController() { return concreteCalc_; }
    AreaPrj::IController const & GetController() const { return concreteCalc_; }

protected:
    // IObserver
    virtual void DoNotify() override { Render(); }

    // IView
    virtual void DoPan( int Dx, int Dy ) override;
    virtual AreaPrj::IModel const & DoGetModel() const override;

private:	// User declarations
    AreaPrj::Calc concreteCalc_; // Concrete controller
    std::unique_ptr<AreaPrj::IRenderer> renderer_ { MakeRender() };
    bool inputDataValid_{ false };
    bool dragging_ {};
    int startX_ {};
    int startY_ {};
    int ofsX_ {};
    int ofsY_ {};
    int oldOfsX_ {};
    int oldOfsY_ {};
    std::unique_ptr<AreaPrj::IAreaCalculator> areaCalc_ { MakeAreaCalculator() };

    bool HitTest( int X, int Y ) const;
    double GetThickness() const;
    void SetThickness( double Val );

    void ShowArea( double Val );
    void UpdateModel();
    bool IsInputDataValid() const { return inputDataValid_; }
    static std::unique_ptr<TStringList> GetRendererNameList();
    std::unique_ptr<AreaPrj::IRenderer> MakeRender() const;
    void InvalidateViewport();
    static std::unique_ptr<TStringList> GetAreaMethodNameList();
    std::unique_ptr<AreaPrj::IAreaCalculator> MakeAreaCalculator() const;
    void CancelTextDrag();
    void Render();
    void UpdateBoundingBoxValues();
    void ClearBoundingBoxValues();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif

