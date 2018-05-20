// ---------------------------------------------------------------------------

#ifndef ServerH
#define ServerH
// ---------------------------------------------------------------------------
#include "Communication.h"
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
using namespace std;

class Server : public Communication
{
public:
	Server( std::wstring port );
	bool Init( );
	bool Listen( );
	bool Accept( );
	bool CleanUp( );

private:

	SOCKET listenSocket_;

	std::wstring port_;

} ;
#endif
