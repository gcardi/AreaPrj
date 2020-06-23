#ifndef IViewH
#define IViewH

#include <System.hpp>

namespace AreaPrj {

//class IModel;

class IView {
public:
    String GetText() const { return GetText(); }
    void SetText( String Val ) { SetText( Val ); }
    String GetFontName() const { return DoGetFontName(); }
    void SetFontName( String Val ) { DoSetFontName( Val ); }
    double GetTextSize() const { return DoGetTextSize(); }
    void SetTextSize( double Val ) { DoSetTextSize( Val ); }
    bool GetBold() const { return DoGetBold(); }
    void SetBold( bool Val ) { DoSetBold( Val ); }
    bool GetItalic() const { return DoGetItalic(); }
    void SetItalic( bool Val ) { DoSetItalic( Val ); }
    void Pan( int Dx, int Dy ) { DoPan( Dx, Dy ); }
protected:
    virtual String DoGetText() const = 0;
    virtual void DoSetText( String Val ) = 0;
    virtual String DoGetFontName() const = 0;
    virtual void DoSetFontName( String Val ) = 0;
    virtual double DoGetTextSize() const = 0;
    virtual void DoSetTextSize( double Val ) = 0;
    virtual bool DoGetBold() const = 0;
    virtual void DoSetBold( bool Val ) = 0;
    virtual bool DoGetItalic() const = 0;
    virtual void DoSetItalic( bool Val ) = 0;
    virtual void DoPan( int Dx, int Dy ) = 0;
};

} // End of namespace AreaPrj

#endif

