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

#include <memory>

#include "IController.h"
#include "IRenderer.h"
#include "IAreaCalculator.h"
#include "IModel.h"

#include "IObserver.h"
#include "IView.h"

#include "Calc.h"

// Classe necessaria per ingannare l'IDE di Embarcadero a cui non piace
// la multipla ereditarietà a livello di classi derivate da TObject
class TMIfrmMain : public TForm, public AreaPrj::IView, public AreaPrj::IObserver {
public:
    template<typename...A>
    TMIfrmMain( A&&... Args ) : TForm( std::forward<A>( Args )... ) {}
};

class TfrmMain : public TMIfrmMain
{
__published:	// IDE-managed Components
    TPaintBox *paintboxViewport;
    TPanel *pnlViewport;
    TEdit *edtText;
    TLabel *Label1;
    TComboBox *comboboxFontName;
    TLabel *Label3;
    TEdit *edtTextSize;
    TLabel *Label4;
    TLabel *lblHitTest;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *lblWidth;
    TLabel *Label8;
    TLabel *lblHeight;
    TComboBox *comboboxRenderer;
    TLabel *Label7;
    TCheckBox *checkboxBold;
    TCheckBox *checkboxItalic;
    TPanel *Panel1;
    TPanel *Panel2;
    TActionList *ActionList1;
    TAction *actArea;
    TButton *Button1;
    TComboBox *comboboxAreaMethod;
    TLabel *Label2;
    TLabel *lblCoords;
    TLabel *lblBoundingBox;
    void __fastcall paintboxViewportPaint(TObject *Sender);
    void __fastcall TextChanged(TObject *Sender);
    void __fastcall edtTextSizeKeyPress(TObject *Sender, System::WideChar &Key);
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

public:		// User declarations
    __fastcall TfrmMain( TComponent* Owner ) override;

    AreaPrj::IController& GetController() { return concreteCalc_; }
    AreaPrj::IController const & GetController() const { return concreteCalc_; }

protected:
    // IObserver
    virtual void DoNotify() override { Render(); }

    // IView
    virtual String DoGetText() const override;
    virtual void DoSetText( String Val ) override;
    virtual String DoGetFontName() const override;
    virtual void DoSetFontName( String Val ) override;
    virtual double DoGetTextSize() const override;
    virtual void DoSetTextSize( double Val ) override;
    virtual bool DoGetBold() const override;
    virtual void DoSetBold( bool Val ) override;
    virtual bool DoGetItalic() const override;
    virtual void DoSetItalic( bool Val ) override;
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

