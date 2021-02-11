//---------------------------------------------------------------------------

#ifndef CursorH
#define CursorH

/*! RAII class to manage screen cursor lifetime */
class TCursorManager
{
public:
    TCursorManager( TCursor Cursor = crHourGlass );
    ~TCursorManager();
    TCursorManager( TCursorManager const & Cursor ) = delete;
    TCursorManager& operator=( TCursorManager const & Cursor ) = delete;
    TCursor Set( TCursor Cursor );
    void Restore();
private:
    TCursor oldCursor_;
    bool restored_ {};
};


//---------------------------------------------------------------------------
#endif
