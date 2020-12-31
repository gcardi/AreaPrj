//---------------------------------------------------------------------------

#ifndef StochasticAreaCalcH
#define StochasticAreaCalcH

#include "IModel.h"
#include "IAreaCalculator.h"

#include <random>

namespace AreaPrj {

class StochasticAreaCalc : public IAreaCalculator {
public:
    StochasticAreaCalc( size_t PointCount ) : pointCount_{ PointCount } {}
    static constexpr LPCTSTR GetName() { return _D( "stocastico" ); }
protected:
    virtual double DoCompute( IModel const & Model ) const override;
    virtual String DoGetDescription() const override;
private:
    // Will be used to obtain a seed for the random number engine
    std::random_device mutable rd_;
    size_t pointCount_;
};

} // End of namespace AreaPrj

//---------------------------------------------------------------------------
#endif



