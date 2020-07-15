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

#include "Calc.h"
#include "IRenderer.h"
#include "VCLView.h"
#include "IAreaCalculator.h"
#include "IModel.h"

class TfrmMain : public TForm
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
    __fastcall TfrmMain(TComponent* Owner);

    // To access IView and IObserver methods use (*this)-> in place of this->
    auto operator->() { return &gui_; }
    auto operator->() const { return &gui_; }

private:	// User declarations
    using IntfImpl = AreaPrj::VCLView<TfrmMain>;

    friend IntfImpl;

    AreaPrj::Calc calc_;       // Concrete Controller
    IntfImpl gui_{ *this };    // Concrete view (proxy)
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
    AreaPrj::IModel const & GetModel() const { return calc_.GetModel(); }
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

