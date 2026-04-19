//---------------------------------------------------------------------------

#ifndef Direct2DRendererH
#define Direct2DRendererH

#include <SystemTypes.h>

#include <vector>

#include "IRenderer.h"

namespace AreaPrj {

class Direct2DRenderer : public IRenderer {
public:
    static constexpr LPCTSTR GetDescription() { return _D( "Direct2D" ); }
protected:
    virtual String DoGetName() const override { return GetDescription(); }
    virtual void DoPrepareRendering( IModel const & Model, int OfsX, int OfsY ) override;
    virtual void DoRender( Vcl::Graphics::TCanvas& Canvas ) const override;
private:
    using Ring = std::vector<System::Types::TPointF>;
    using PolygonGroup = std::vector<Ring>;
    using PolygonCont = std::vector<PolygonGroup>;

    PolygonCont polygons_;
};

} // End of namespace AreaPrj

//---------------------------------------------------------------------------
#endif
