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

class TFormForm : public TForm, public AreaPrj::IView, public AreaPrj::IObserver {
public:
	template<typename...A>
	TFormForm( A&&... Args ) : TForm( std::forward<A>( Args )... ) {}
};

class TfrmMain : public TFormForm
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

public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner) override;

	AreaPrj::IController& GetController() { return concreteCalc_; }
	AreaPrj::IController const & GetController() const { return concreteCalc_; }

protected:
	// IObserver
    virtual void DoNotify() override { Render(); }

    // IView
    virtual String DoGetText() const override { return GetInputText(); }
    virtual void DoSetText( String Val ) override { SetInputText( Val ); }
    virtual String DoGetFontName() const override { return GetInputTextFontName(); }
    virtual void DoSetFontName( String Val ) override { SetInputTextFontName( Val ); }
    virtual double DoGetTextSize() const override { return GetInputTextFontSize(); }
    virtual void DoSetTextSize( double Val ) override { SetInputTextFontSize( Val ); }
    virtual bool DoGetBold() const override { return GetInputTextBold(); }
    virtual void DoSetBold( bool Val ) override { SetInputTextBold( Val ); }
    virtual bool DoGetItalic() const override { return GetInputTextItalic(); }
    virtual void DoSetItalic( bool Val ) override { SetInputTextItalic( Val ); }
    virtual void DoPan( int Dx, int Dy ) override { ViewportPan( Dx, Dy ); }
    virtual AreaPrj::IModel const & DoGetModel() const override { return GetModel(); }

private:	// User declarations
//    using IntfImpl = AreaPrj::VCLView<TfrmMain>;

//    friend IntfImpl;

	AreaPrj::Calc concreteCalc_; // Concrete controller
	std::unique_ptr<AreaPrj::IRenderer> renderer_ { MakeRender() };
	bool dataValid_{ false };
	bool dragging_ {};
    int startX_ {};
    int startY_ {};
    int ofsX_ {};
    int ofsY_ {};
    int oldOfsX_ {};
    int oldOfsY_ {};
    std::unique_ptr<AreaPrj::IAreaCalculator> areaCalc_ { MakeAreaCalculator() };

    String GetInputText() const;
    void SetInputText( String Val );
    String GetInputTextFontName() const;
    void SetInputTextFontName( String Val );
    double GetInputTextFontSize() const;
    void SetInputTextFontSize( double Val );
    bool GetInputTextBold() const;
    void SetInputTextBold( bool Val );
    bool GetInputTextItalic() const;
    void SetInputTextItalic( bool Val );
    void ViewportPan( int Dx, int Dy );
    bool HitTest( int X, int Y ) const;
    AreaPrj::IModel const & GetModel() const { return GetController().GetModel(); }
    double GetThickness() const;
    void SetThickness( double Val );

    void ShowArea( double Val );
    void UpdateModel();
    bool IsDataValid() const { return dataValid_; }
    static std::unique_ptr<TStringList> GetRendererNameList();
    std::unique_ptr<AreaPrj::IRenderer> MakeRender() const;
    void InvalidateViewport();
    static std::unique_ptr<TStringList> GetAreaMethodNameList();
    std::unique_ptr<AreaPrj::IAreaCalculator> MakeAreaCalculator() const;
    void CancelTextDrag();

    // Usata dalla parte IView di IntfImpl
    void Render();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif

