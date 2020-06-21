//---------------------------------------------------------------------------

#pragma hdrstop

#include <windows.h>

#include <memory>

#include "Utils.h"

using std::unique_ptr;
using std::make_unique;

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace AreaPrj {

unique_ptr<TStringList> RetrieveFontList()
{
    auto SL = make_unique<TStringList>();
    LOGFONT LFont {};

    class DCMngr {
    public:
        DCMngr() : dc_( ::GetDC( {} ) ) { Win32Check( dc_ != HDC{} ); }
        ~DCMngr() { ::ReleaseDC( {}, dc_ ); }
        HDC get() const { return dc_; }
    private:
        HDC dc_;
    } DC;

    LFont.lfCharSet = DEFAULT_CHARSET;

    struct EnumFontFamExProc {
        static int WINAPI Proc( LOGFONT const * Elfe, TEXTMETRIC const * Tme,
                                DWORD FontType, LPARAM LParam )
        {
            if ( FontType & TRUETYPE_FONTTYPE ) {
                auto SL = reinterpret_cast<TStringList*>( LParam );
                String const FontName{ Elfe->lfFaceName };
                if ( !SL->Count ||
                     (
                       !SameText( FontName, SL->Strings[SL->Count-1] ) &&
                       !FontName.IsEmpty() && FontName[1] != _T( '@' )
                     )
                ) {
                    SL->Append( FontName );
                }
            }
            return TRUE;
        }
    };

    ::EnumFontFamiliesEx(
        DC.get(), &LFont, &EnumFontFamExProc::Proc,
        reinterpret_cast<LONG_PTR>( SL.get() ), {}
    );

    SL->Sort();

    return SL;
}

} // End of namespace AreaPrj

