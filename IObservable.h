#ifndef IObservableH
#define IObservableH

#include <System.hpp>

namespace AreaPrj {

class IObserver;

class IObservable {
public:
public:
    virtual ~IObservable() = default;
    void AddObserver( IObserver& Item ) { DoAddObserver( Item ); }
    //void RemoveObserver( IObserver& Item ); // YAGNI - https://it.wikipedia.org/wiki/You_aren%27t_gonna_need_it
    void NotifyObservers() { DoNotifyObservers(); }
protected:
    virtual void DoAddObserver( IObserver& Item ) = 0;
    virtual void DoNotifyObservers() = 0;
};

} // End of namespace AreaPrjPrj

#endif
