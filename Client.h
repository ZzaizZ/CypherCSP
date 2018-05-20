// ---------------------------------------------------------------------------

#ifndef ClientH
#define ClientH
// ---------------------------------------------------------------------------
#include "communication.h"
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
using namespace std;

// ---------------------------------------------------------------------------
class Client : public Communication
{
public:
	Client(
		std::wstring ipaddr,
		std::wstring port );
	bool Init( );
	bool Connect( );
	bool CleanUp( );

private:

	struct addrinfoW * ptr_;

	std::wstring ipaddr_;
	std::wstring port_;
} ;

#endif
