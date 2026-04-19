//---------------------------------------------------------------------------

#ifndef GDIPlusRendererH
#define GDIPlusRendererH

#include <GdiPlus.h>

#include <SystemTypes.h>

#include <vector>

#include "IRenderer.h"

namespace AreaPrj {

class GDIPlusRenderer : public IRenderer {
public:
    static constexpr LPCTSTR GetDescription() { return _D( "GDI+" ); }
protected:
    virtual String DoGetName() const override { return GetDescription(); }
    virtual void DoPrepareRendering( IModel const & Model, int OfsX, int OfsY ) override;
    virtual void DoRender( Vcl::Graphics::TCanvas& Canvas ) const override;
private:
    using Ring = std::vector<Gdiplus::PointF>;
    using PolygonGroup = std::vector<Ring>;
    using PolygonCont = std::vector<PolygonGroup>;

    PolygonCont polygons_;
};

} // End of namespace AreaPrj

//---------------------------------------------------------------------------
#endif
