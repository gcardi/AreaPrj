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
    size_t GetPointCount() const { return pointCount_; }

    template<typename BB>
    static auto HitTest( IModel const & Model, BB const & BoundingBox,
                         size_t PointCount, unsigned int Seed )
    {
        std::uniform_real_distribution<> DisX(
            BoundingBox.min_corner().x(),
            BoundingBox.max_corner().x()
        );

        std::uniform_real_distribution<> DisY(
            BoundingBox.min_corner().y(),
            BoundingBox.max_corner().y()
        );

        std::mt19937 Generator( Seed );

        size_t HitCnt {};

        for ( size_t n = 0 ; n < PointCount ; ++n ) {
            if ( Model.HitTest( DisX( Generator ), DisY( Generator ) ) ) {
                ++HitCnt;
            }
        }

        return HitCnt;
    }

protected:
    std::random_device mutable rd_;

    virtual double DoCompute( IModel const & Model ) const override;
    virtual String DoGetDescription() const override;
private:
    size_t pointCount_;
};

} // End of namespace AreaPrj

//---------------------------------------------------------------------------
#endif

