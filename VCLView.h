
//---------------------------------------------------------------------------

#ifndef VCLViewH
#define VCLViewH

#include "IObserver.h"
//#include "IView.h"

namespace AreaPrj {

// Questa classe � necessaria perch� per limiti del framework VCL
// non � possibile avere la multipla ereditariet� sul un discendete di TForm
// Quindi, la form principale "aggrega"
template<typename T>
class VCLView : public IObserver/*, public IView*/ {
public:
	VCLView( T& GUI ) : gui_{ GUI } {}
protected:
	virtual void DoNotify() override {	gui_.Render();}
private:
	T& gui_;
};

} // End of namespace AreaPrj

//---------------------------------------------------------------------------
#endif
