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
    SL->Sorted = true;
    SL->Duplicates = System::Types::dupIgnore;
    SL->CaseSensitive = false;

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
        static int WINAPI Proc( LOGFONT const * Elfe, TEXTMETRIC const * /*Tme*/,
                                DWORD FontType, LPARAM LParam )
        {
            if ( FontType & ( TRUETYPE_FONTTYPE | DEVICE_FONTTYPE ) ) {
                String const FontName{ Elfe->lfFaceName };
                if ( !FontName.IsEmpty() && FontName[1] != _D( '@' ) ) {
                    auto SL = reinterpret_cast<TStringList*>( LParam );
                    SL->Add( FontName );
                }
            }
            return TRUE;
        }
    };

    ::EnumFontFamiliesEx(
        DC.get(), &LFont, &EnumFontFamExProc::Proc,
        reinterpret_cast<LONG_PTR>( SL.get() ), {}
    );

    return SL;
}

} // End of namespace AreaPrj

