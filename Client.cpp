// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Client.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

Client::Client( ) : Communication( )
{
	connectSocket_ = INVALID_SOCKET;
	result_ = NULL;
	ptr_ = NULL;
}

// ---------------------------------------------------------------------------
bool Client::Init( std::string ipaddr )
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

	iResult = getaddrinfo( ipaddr.c_str( ), DEFAULT_PORT, &hints_, &result_ );
	if ( iResult != 0 )
	{
		MessageBoxW( NULL, L"Ошибка функции getaddrinfo", L"Error", MB_OK );
		WSACleanup( );
		return false;
	}

	for ( ptr_ = result_; ptr_ != NULL; ptr_ = ptr_->ai_next )
	{
		connectSocket_ = socket( ptr_->ai_family, ptr_->ai_socktype,
			ptr_->ai_protocol );
		if ( connectSocket_ == INVALID_SOCKET )
		{
			MessageBoxW( NULL, L"Ошибка создания сокета", L"Error", MB_OK );
			WSACleanup( );
			return false;
		}

		// Пытаемся подключиться к серверу
		iResult = connect( connectSocket_, ptr_->ai_addr,
			( int )ptr_->ai_addrlen );
		if ( iResult == SOCKET_ERROR )
		{
			MessageBoxW( NULL, L"Ошибка подключения к серверу", L"Error",
			MB_OK );
			closesocket( connectSocket_ );
			connectSocket_ = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo( result_ );

	if ( connectSocket_ == INVALID_SOCKET )
	{
		WSACleanup( );
		return false;
	}
	return true;
}
