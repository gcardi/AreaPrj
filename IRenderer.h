#ifndef IRendererH
#define IRendererH

namespace Vcl::Graphics {
class TCanvas;
}

namespace AreaPrj {

class IModel;

class IRenderer {
public:
    void PrepareRendering( IModel const & Model, int OfsX, int OfsY ) {
        DoPrepareRendering( Model, OfsX, OfsY );
    }
    void Render( Vcl::Graphics::TCanvas& Canvas ) const { DoRender( Canvas ); }
    String GetName() const { return DoGetName(); }
    bool GetFilled() const { return filled_; }
    void SetFilled( bool Val ) { filled_ = Val; }
    virtual ~IRenderer() = default;
protected:
    virtual String DoGetName() const = 0;
    virtual void DoPrepareRendering( IModel const & Model, int OfsX, int OfsY ) = 0;
    virtual void DoRender( Vcl::Graphics::TCanvas& Canvas ) const = 0;
private:
    bool filled_ {};
};

} // End of namespace AreaPrj


#endif
