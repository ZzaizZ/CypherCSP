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
	__fastcall ServerThread(
		std::wstring destinationPath,
		std::wstring port,
		bool         CreateSuspended );

	Server * server_;

	std::wstring destinationPath_;
	std::wstring port_;
} ;
// ---------------------------------------------------------------------------
#endif
