//---------------------------------------------------------------------------

#ifndef StochasticMTAreaCalcH
#define StochasticMTAreaCalcH

#include "IModel.h"
#include "IAreaCalculator.h"

#include <random>

namespace AreaPrj {

class StochasticMTAreaCalc : public IAreaCalculator {
public:
    StochasticMTAreaCalc( size_t PointCount, size_t TaskCount )
        : pointCount_{ PointCount }, taskCount_{ TaskCount } {}
    static constexpr LPCTSTR GetName() { return _T( "stocastico parallelo" ); }
protected:
    virtual double DoCompute( IModel const & Model ) const override;
    virtual String DoGetDescription() const override;
private:
    // Will be used to obtain a seed for the random number engine
    std::random_device mutable rd_;
    size_t pointCount_;
    size_t taskCount_;
};

} // End of namespace AreaPrj

//---------------------------------------------------------------------------
#endif
