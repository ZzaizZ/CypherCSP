// ---------------------------------------------------------------------------

#ifndef ClientThreadH
#define ClientThreadH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "Client.h"

// ---------------------------------------------------------------------------
class ClientThread : public TThread
{
private:
protected:
	void __fastcall Execute( );

public:
	__fastcall ClientThread(
		std::wstring sourceFile,
		std::wstring ipaddr,
		std::wstring port,
		bool         CreateSuspended );

	Client * client_;

	std::wstring sourceFile_;
	std::wstring ipaddr_;
	std::wstring port_;
} ;
// ---------------------------------------------------------------------------
#endif
