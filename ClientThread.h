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
		std::string  ipaddr,
		bool         CreateSuspended );

	Client * client_;

	std::wstring sourceFile_;
	std::string ipaddr_;
} ;
// ---------------------------------------------------------------------------
#endif
