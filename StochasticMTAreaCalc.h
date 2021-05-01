//---------------------------------------------------------------------------

#ifndef StochasticMTAreaCalcH
#define StochasticMTAreaCalcH

#include "IModel.h"
#include "StochasticAreaCalc.h"

#include <random>

namespace AreaPrj {

class StochasticMTAreaCalc : public StochasticAreaCalc {
public:
    StochasticMTAreaCalc( size_t PointCount, size_t TaskCount )
      : StochasticAreaCalc( PointCount ), taskCount_{ TaskCount } {}
    static constexpr LPCTSTR GetName() { return _D( "stocastico parallelo" ); }
protected:
    virtual double DoCompute( IModel const & Model ) const override;
    virtual String DoGetDescription() const override;
private:
    size_t taskCount_;
};

} // End of namespace AreaPrj

//---------------------------------------------------------------------------
#endif
