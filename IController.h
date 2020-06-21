#ifndef IControllerH
#define IControllerH

#include <System.hpp>
#include <Vcl.Graphics.hpp>

namespace AreaPrj {

class IModel;

class IController {
public:
    IModel const & GetModel() const { return DoGetModel(); }
    void SetText( String Text, String FontName, double FontSize,
                  double DX, double DY, bool Bold, bool Italic ) {
        DoSetText( Text, FontName, FontSize, DX, DY, Bold, Italic );
    }
protected:
    virtual IModel const & DoGetModel() const = 0;
    virtual void DoSetText( String Text, String FontName, double FontSize,
                            double DX, double DY, bool Bold, bool Italic ) = 0;
};

} // End of namespace AreaPrj

#endif

