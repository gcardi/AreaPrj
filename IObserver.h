#ifndef IObserverH
#define IObserverH

namespace AreaPrj {

class IObserver {
public:
    void Notify() { DoNotify(); }
protected:
    virtual void DoNotify() = 0;
};

} // End of namespace AreaPrj

#endif


