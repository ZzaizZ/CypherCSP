// ---------------------------------------------------------------------------

#ifndef ServerThreadH
#define ServerThreadH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "Server.h"

// ---------------------------------------------------------------------------
class ServerThread : public TThread
{
private:
protected:
	void __fastcall Execute( );

public:
	__fastcall ServerThread( bool CreateSuspended );

	Server * server_;
} ;
// ---------------------------------------------------------------------------
#endif
