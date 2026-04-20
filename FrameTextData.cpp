//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <algorithm>

#include "Utils.h"
#include "FrameTextData.h"

using std::max;

using AreaPrj::InvariantFmt;
using AreaPrj::RetrieveFontList;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmeTextData *frmeTextData;
//---------------------------------------------------------------------------

__fastcall TfrmeTextData::TfrmeTextData(TComponent* Owner)
    : TFrame(Owner)
{
    comboboxFontName->Items->Assign( RetrieveFontList().get() );
    comboboxFontName->ItemIndex =
        max( comboboxFontName->Items->IndexOf( Font->Name ), 0 );
    //GetController().AddObserverToModel( *this );

}
//---------------------------------------------------------------------------

String TfrmeTextData::DoGetText() const
{
    return edtText->Text;
}
//---------------------------------------------------------------------------

void TfrmeTextData::DoSetText( String Val )
{
    if ( Val != edtText->Text ) {
        edtText->Text = Val;
        NotifyObservers();
    }
}
//---------------------------------------------------------------------------

String TfrmeTextData::DoGetFontName() const
{
    return comboboxFontName->Text;
}
//---------------------------------------------------------------------------

void TfrmeTextData::DoSetFontName( String Val )
{
    if ( Val != comboboxFontName->Text ) {
        comboboxFontName->Text = Val;
        NotifyObservers();
    }
}
//---------------------------------------------------------------------------

double TfrmeTextData::DoGetTextSize() const
{
    return StrToFloat( edtTextSize->Text, InvariantFmt() );
}
//---------------------------------------------------------------------------

void TfrmeTextData::DoSetTextSize( double Val )
{
    if ( StrToFloat( edtTextSize->Text, InvariantFmt() ) != Val ) {
        edtTextSize->Text = Format(
            _D( "%g" ),
            ARRAYOFCONST(( static_cast<long double>( Val ) )),
            InvariantFmt()
        );
        NotifyObservers();
    }
}
//---------------------------------------------------------------------------

bool TfrmeTextData::DoGetBold() const
{
    return checkboxBold->Checked;
}
//---------------------------------------------------------------------------

void TfrmeTextData::DoSetBold( bool Val )
{
    if ( checkboxBold->Checked != Val ) {
        checkboxBold->Checked = Val;
        //UpdateModel();
        NotifyObservers();
    }
}
//---------------------------------------------------------------------------

bool TfrmeTextData::DoGetItalic() const
{
    return checkboxItalic->Checked;
}
//---------------------------------------------------------------------------

void TfrmeTextData::DoSetItalic( bool Val )
{
    if ( checkboxItalic->Checked != Val ) {
        checkboxItalic->Checked = Val;
        //UpdateModel();
        NotifyObservers();
    }
}
//---------------------------------------------------------------------------

void TfrmeTextData::NotifyObservers()
{
}
//---------------------------------------------------------------------------

