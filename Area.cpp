//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

#include <GdiPlus.h>

//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("FormMain.cpp", frmMain);
//---------------------------------------------------------------------------
class GdiPlusSessionManager {
public:
    GdiPlusSessionManager() {
        Gdiplus::GdiplusStartup( &gdiplusToken_, &gdiplusStartupInput_, NULL );
    }
    ~GdiPlusSessionManager() {
        try {
            Gdiplus::GdiplusShutdown( gdiplusToken_ );
        }
        catch ( ... ) {
        }
    }
    GdiPlusSessionManager( GdiPlusSessionManager const & ) = delete;
    GdiPlusSessionManager& operator=( GdiPlusSessionManager const & ) = delete;
private:
    Gdiplus::GdiplusStartupInput gdiplusStartupInput_;
    ULONG_PTR gdiplusToken_;
} GdiPlusSession;

//---------------------------------------------------------------------------

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
         Application->Initialize();
         Application->MainFormOnTaskBar = true;
         Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
