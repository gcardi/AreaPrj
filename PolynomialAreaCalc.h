//---------------------------------------------------------------------------

#ifndef PolynomialAreaCalcH
#define PolynomialAreaCalcH

#include "IModel.h"
#include "IAreaCalculator.h"

namespace AreaPrj {

class PolynomialAreaCalc : public IAreaCalculator {
public:
    static constexpr LPCTSTR GetName() { return _T( "polinomiale" ); }
protected:
    virtual double DoCompute( IModel const & Model ) const override;
    virtual String DoGetDescription() const override { return GetName(); }
private:
};

} // End of namespace AreaPrj

//---------------------------------------------------------------------------
#endif
