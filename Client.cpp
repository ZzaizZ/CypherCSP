// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Client.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

Client::Client(
	std::wstring ipaddr,
	std::wstring port ) : Communication( )
{
	connectSocket_ = INVALID_SOCKET;
	result_ = NULL;
	ptr_ = NULL;
	ipaddr_ = ipaddr;
	port_ = port;
}

// ---------------------------------------------------------------------------
bool Client::Init( )
{
	int iResult;
	iResult = WSAStartup( REQ_WINSOCK_VER, &wsaData_ );
	if ( iResult != 0 )
	{
		return false;
	}

	ZeroMemory( & hints_, sizeof( hints_ ) );
	hints_.ai_family = AF_INET;
	hints_.ai_socktype = SOCK_STREAM;
	hints_.ai_protocol = IPPROTO_TCP;

	iResult = GetAddrInfoW( ipaddr_.c_str( ), port_.c_str( ), &hints_,
		&result_ );
	if ( iResult != 0 )
	{
		WSACleanup( );
		return false;
	}
	return true;

}

// ---------------------------------------------------------------------------
bool Client::Connect( )
{
	int iResult;
	for ( ptr_ = result_; ptr_ != NULL; ptr_ = ptr_->ai_next )
	{
		connectSocket_ = socket( ptr_->ai_family, ptr_->ai_socktype,
			ptr_->ai_protocol );
		if ( connectSocket_ == INVALID_SOCKET )
		{
			return false;
		}

		// ѕытаемс€ подключитьс€ к серверу
		iResult = connect( connectSocket_, ptr_->ai_addr,
			( int )ptr_->ai_addrlen );
		if ( iResult == SOCKET_ERROR )
		{
			closesocket( connectSocket_ );
			connectSocket_ = INVALID_SOCKET;
			continue;
		}
		break;
	}
	return true;
}

// ---------------------------------------------------------------------------
bool Client::CleanUp( )
{
	FreeAddrInfoW( result_ );

	if ( connectSocket_ == INVALID_SOCKET )
	{
		WSACleanup( );
		return false;
	}
	return true;
}
