//---------------------------------------------------------------------------

#ifndef GeometrieH
#define GeometrieH

#include <utility>

#include <boost/geometry.hpp>

#include "Observable.h"
#include "IModel.h"

namespace AreaPrj {

class Geometrie : public IModel, public Observable {
public:
protected:
    virtual PolygonCont const & DoGetPolygons() const override {
        return polygons_;
    }
    virtual void DoSetPolygons( PolygonCont const & Items ) override {
        AssignPolygons( Items );
    }
    virtual bool DoHitTest( CoordType X, CoordType Y ) const override {
        return boost::geometry::within( PointType{ X, Y }, polygons_ );
    }
private:
    PolygonCont polygons_;

    template<typename PC>
    void AssignPolygons( PC&& Items ) {
        polygons_ = std::forward<PC>( Items );
        NotifyObservers();
    }
};

} // End of namespace AreaPrj

#endif
