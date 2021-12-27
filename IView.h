#ifndef IViewH
#define IViewH

#include <System.hpp>

 namespace AreaPrj {

class IModel;

class IView : public IUnknown {
public:
    // These three stupid methods are needed to get rid of even more stupid
    // warnings from the Embarcadero clang compilers that claim that the
    // classes that a form derives from and that have an 'I' at the beginning
    // of their name themselves have to derive from IUnknown.
    //
    // [bcc(32c|64) Warning]: Interface 'IView' does not derive
    // from IUnknown. (Interfaces should derive from IUnknown)
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject) override { return {}; }
    virtual ULONG   STDMETHODCALLTYPE AddRef() override { return {}; }
    virtual ULONG   STDMETHODCALLTYPE Release() override { return {}; }

    /** \brief Legge il testo dell'interfaccia utente
      * \return La stringa contenente il testo
      *
      * Recupera il testo inserito nell'interfaccia utente per il quale
      * calcolare l'area
      */
    String GetText() const { return DoGetText(); }

    /** \brief Assegna il testo nell'interfaccia utente
      * \param Val La stringa contenente il testo
      *
      * Questo metodo consente di modificare il valore relativo al testo
      * di cui calcolare l'area presente sull'interfaccia utente
      */
    void SetText( String Val ) { DoSetText( Val ); }

    String GetFontName() const { return DoGetFontName(); }
    void SetFontName( String Val ) { DoSetFontName( Val ); }
    double GetTextSize() const { return DoGetTextSize(); }
    void SetTextSize( double Val ) { DoSetTextSize( Val ); }
    bool GetBold() const { return DoGetBold(); }
    void SetBold( bool Val ) { DoSetBold( Val ); }
    bool GetItalic() const { return DoGetItalic(); }
    void SetItalic( bool Val ) { DoSetItalic( Val ); }

    /** \brief Applica uno spostamento alla visualizzazione dell'intero testo
      * \param Dx Spostamento orizzontale espresso in pixel
      * \param Dy Spostamento verticale espresso in pixel
      *
      * Questo metodo permette al visualizzatore grafico di disegnare il testo
      * con uno spostamento relativo rispetto all'origine che si trova in alto
      * a sinistra
      */
    void Pan( int Dx, int Dy ) { DoPan( Dx, Dy ); }

    /** \brief Ritorna un riferimento costante al Modello
      * \return Il riferimento al modello
      *
      * Ritorna un riferimento al Modello che espone metodi per il recupero
      * di tutte le informazioni necessarie alla visualizzazione ed all'interazione
      * con l'utente
      */
    IModel const & GetModel() const { return DoGetModel(); }
protected:
    virtual String DoGetText() const = 0;
    virtual void DoSetText( String Val ) = 0;
    virtual String DoGetFontName() const = 0;
    virtual void DoSetFontName( String Val ) = 0;
    virtual double DoGetTextSize() const = 0;
    virtual void DoSetTextSize( double Val ) = 0;
    virtual bool DoGetBold() const = 0;
    virtual void DoSetBold( bool Val ) = 0;
    virtual bool DoGetItalic() const = 0;
    virtual void DoSetItalic( bool Val ) = 0;
    virtual void DoPan( int Dx, int Dy ) = 0;
    virtual IModel const & DoGetModel() const = 0;
};

} // End of namespace AreaPrj

#endif

