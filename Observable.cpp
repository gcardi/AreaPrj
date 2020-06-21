//---------------------------------------------------------------------------

#pragma hdrstop

#include "IObserver.h"
#include "Observable.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace AreaPrj {

void Observable::DoAddObserver( IObserver& Item )
{
    observers_.push_back( Item );
}
//---------------------------------------------------------------------------

void Observable::DoNotifyObservers()
{
    for ( auto Item : observers_ ) {
        Item.get().Notify();
    }
}
//---------------------------------------------------------------------------

} // End of namespace AreaPrj




