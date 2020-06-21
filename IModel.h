#ifndef IModelH
#define IModelH

#include <System.hpp>

#include <boost/geometry.hpp>

namespace AreaPrj {

class IModel {
public:
    using CoordType = double;
    using PointType = boost::geometry::model::d2::point_xy<CoordType>;
    using PolygonType = boost::geometry::model::polygon<PointType>;
    using PolygonCont = boost::geometry::model::multi_polygon<PolygonType>;

    PolygonCont const & GetPolygons() const { return DoGetPolygons(); }
    void SetPolygons( PolygonCont const & Items ) { DoSetPolygons( Items ); }
    bool HitTest( CoordType X, CoordType Y ) const { return DoHitTest( X, Y ); }
protected:
    virtual PolygonCont const & DoGetPolygons() const = 0;
    virtual void DoSetPolygons( PolygonCont const & Items ) = 0;
    virtual bool DoHitTest( CoordType X, CoordType Y ) const = 0;
};

} // End of namespace AreaPrj

#endif

