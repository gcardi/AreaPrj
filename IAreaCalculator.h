#ifndef IAreaCalculatorH
#define IAreaCalculatorH

#include "IModel.h"

namespace AreaPrj {

class IAreaCalculator {
public:
    double Compute( IModel const & Model ) const {
        return DoCompute( Model );
    }
    String GetDescription() const { return DoGetDescription(); }
protected:
    virtual double DoCompute( IModel const & Model ) const = 0;
    virtual String DoGetDescription() const = 0;
};

} // End of namespace AreaPrj

#endif