//---------------------------------------------------------------------------

#ifndef FrameTextDataH
#define FrameTextDataH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "IFontProperties.h"
#include "Observable.h"

//---------------------------------------------------------------------------

class TfrmeTextData : public TFrame
                    , public AreaPrj::IFontProperties
                    //, public AreaPrj::Observable
{
__published:	// IDE-managed Components
    TEdit *edtText;
    TCheckBox *checkboxItalic;
    TCheckBox *checkboxBold;
    TEdit *edtTextSize;
    TComboBox *comboboxFontName;
    TLabel *Label3;
    TLabel *Label1;
    TLabel *Label4;
private:	// User declarations
    // IFontProperties
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

    void NotifyObservers();

    INTFOBJECT_IMPL_IUNKNOWN(TFrame)

    // IObservable
    //virtual void DoAddObserver( IObserver& Item ) override;
    //virtual void DoNotifyObservers() override;
public:		// User declarations
    __fastcall TfrmeTextData(TComponent* Owner) override;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmeTextData *frmeTextData;
//---------------------------------------------------------------------------
#endif
