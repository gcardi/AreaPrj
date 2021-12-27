#ifndef IObserverH
#define IObserverH

#include <System.hpp>  // <-- for IUnknown

namespace AreaPrj {

class IObserver : public IUnknown {
public:
    // These three stupid methods are needed to get rid of even more stupid
    // warnings from the Embarcadero clang compilers that claim that the
    // classes that a form derives from and that have an 'I' at the beginning
    // of their name themselves have to derive from IUnknown.
    //
    // [bcc(32c|64) Warning]: Interface 'IObserver' does not derive
    // from IUnknown. (Interfaces should derive from IUnknown)
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject) override { return {}; }
    virtual ULONG   STDMETHODCALLTYPE AddRef() override { return {}; }
    virtual ULONG   STDMETHODCALLTYPE Release() override { return {}; }

    void Notify() { DoNotify(); }
protected:
    virtual void DoNotify() = 0;
};

} // End of namespace AreaPrj

#endif


