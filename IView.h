#ifndef IViewH
#define IViewH

#include <System.hpp>

namespace AreaPrj {

class IModel;

class IView {
public:
    //void Reset();

    String GetText() const;
    void SetText( String Val );
    String GetFontName() const;
    void SetFontName( String Val );
    double GetTextSize() const;
    void SetTextSize( double Val );
    bool GetBold() const;
    void SetBold( bool Val );
    bool GetItalic() const;
    void SetItalic( bool Val );
protected:
};

} // End of namespace AreaPrj

#endif

