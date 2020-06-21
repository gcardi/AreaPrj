//---------------------------------------------------------------------------

#ifndef ObservableH
#define ObservableH

#include <vector>
#include <functional>

#include "IObservable.h"

namespace AreaPrj {

class Observable : public IObservable {
public:
protected:
    virtual void DoAddObserver( IObserver& Item ) override;
    virtual void DoNotifyObservers() override;
private:
    std::vector<std::reference_wrapper<IObserver>> observers_;
};

} // End of namespace AreaPrjPrj

//---------------------------------------------------------------------------
#endif
