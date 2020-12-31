//---------------------------------------------------------------------------

#ifndef GDIRendererH
#define GDIRendererH

#include <SystemTypes.h>

#include <vector>

#include "IRenderer.h"

namespace AreaPrj {

class GDIRenderer : public IRenderer {
public:
    static constexpr LPCTSTR GetDescription() { return _D( "GDI" ); }
protected:
    virtual String DoGetName() const override { return GetDescription(); }
    virtual void DoPrepareRendering( IModel const & Model ) override;
    virtual void DoRender( Vcl::Graphics::TCanvas& Canvas ) const override;
private:
    using Polygon = std::vector<System::Types::TPoint>;
    using PolygonCont = std::vector<Polygon>;

    PolygonCont polygons_;
};

} // End of namespace AreaPrj

//---------------------------------------------------------------------------
#endif
