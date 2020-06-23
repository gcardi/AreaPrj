
//---------------------------------------------------------------------------

#ifndef VCLViewH
#define VCLViewH

#include "IObserver.h"
#include "IView.h"

namespace AreaPrj {

// Questa classe è necessaria perché per limiti del framework VCL
// non è possibile avere la multipla ereditarietà sul un discendete di TForm
// Quindi, la form principale "aggrega" questa classe per esporla come
// istanza di una classe implementata su un gruppo di interfacce pure

template<typename T>
class VCLView : public IObserver, public IView {
public:
    VCLView( T& GUI ) : gui_{ GUI } {}
protected:
    // IObserver
    virtual void DoNotify() override { gui_.Render(); }

    // IView
    virtual String DoGetText() const override { return gui_.GetInputText(); }
    virtual void DoSetText( String Val ) override { gui_.SetInputText( Val ); }
    virtual String DoGetFontName() const override { return gui_.GetInputTextFontName(); }
    virtual void DoSetFontName( String Val ) override { gui_.SetInputTextFontName( Val ); }
    virtual double DoGetTextSize() const override { return gui_.GetInputTextFontSize(); }
    virtual void DoSetTextSize( double Val ) override { gui_.SetInputTextFontSize( Val ); }
    virtual bool DoGetBold() const override { return gui_.GetInputTextBold(); }
    virtual void DoSetBold( bool Val ) override { gui_.SetInputTextBold( Val ); }
    virtual bool DoGetItalic() const override { return gui_.GetInputTextItalic(); }
    virtual void DoSetItalic( bool Val ) override { gui_.SetInputTextItalic( Val ); }
    virtual void DoPan( int Dx, int Dy ) override { gui_.ViewportPan( Dx, Dy ); }
private:
    T& gui_;
};

} // End of namespace AreaPrj

//---------------------------------------------------------------------------
#endif
