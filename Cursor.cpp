//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Cursor.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

__fastcall TCursorManager::TCursorManager( TCursor Cursor )
    : restored_( false ), oldCursor_( Set( Cursor ) )
{
}
//---------------------------------------------------------------------------

__fastcall TCursorManager::~TCursorManager()
{
    if ( !restored_ )
        Restore();
}
//---------------------------------------------------------------------------

TCursor __fastcall TCursorManager::Set( TCursor Cursor )
{
    TCursor const CurrentCursor( Screen->Cursor );
    Screen->Cursor = Cursor;
    restored_ = false;
    return CurrentCursor;
}
//---------------------------------------------------------------------------

void __fastcall TCursorManager::Restore()
{
    Screen->Cursor = oldCursor_;
    restored_ = false;
}
//---------------------------------------------------------------------------

