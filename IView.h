#ifndef IViewH
#define IViewH

#include <System.hpp>

 namespace AreaPrj {

class IModel;

class IView : public IInterface {
public:
/*
    // These three stupid methods are needed to get rid of even more stupid
    // warnings from the Embarcadero clang compilers that claim that the
    // classes that a form derives from and that have an 'I' at the beginning
    // of their name themselves have to derive from IUnknown.
    //
    // [bcc(32c|64) Warning]: Interface 'IView' does not derive
    // from IUnknown. (Interfaces should derive from IUnknown)
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject) override { return {}; }
    virtual ULONG   STDMETHODCALLTYPE AddRef() override { return {}; }
    virtual ULONG   STDMETHODCALLTYPE Release() override { return {}; }
*/
    void Pan( int Dx, int Dy ) { DoPan( Dx, Dy ); }
    IModel const & GetModel() const { return DoGetModel(); }
protected:
    virtual void DoPan( int Dx, int Dy ) = 0;
    virtual IModel const & DoGetModel() const = 0;
};

} // End of namespace AreaPrj

#endif

