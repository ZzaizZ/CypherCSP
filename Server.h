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
	Server( );
	bool Init( );

private:

	SOCKET listenSocket_;

} ;
#endif
