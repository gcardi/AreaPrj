//---------------------------------------------------------------------------

#ifndef CalcH
#define CalcH

#include "Geometrie.h"

#include "IController.h"

namespace AreaPrj {

class Calc : public IController
{
public:
protected:
    virtual void DoAddObserverToModel( IObserver& Observer ) override;
    virtual IModel const & DoGetModel() const override { return geo_; }
    virtual void DoSetText( String Text, String FontName, double FontSize,
                            double DX, double DY, bool Bold, bool Italic ) override;
private:
    Geometrie geo_;  // Model
};

} // End of namespace AreaPrj

#endif
