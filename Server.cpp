// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Server.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma comment (lib, "Ws2_32.lib")

Server::Server( std::wstring port ) : Communication( )
{
	listenSocket_ = INVALID_SOCKET;
	port_ = port;
}

// ---------------------------------------------------------------------------
bool Server::Init( )
{

	int iResult;
	// Инициализация Winsock
	iResult = WSAStartup( REQ_WINSOCK_VER, &wsaData_ );
	if ( iResult != 0 )
	{
		return false;
	}

	ZeroMemory( & hints_, sizeof( hints_ ) );
	hints_.ai_family = AF_INET;
	hints_.ai_socktype = SOCK_STREAM;
	hints_.ai_protocol = IPPROTO_TCP;
	hints_.ai_flags = AI_PASSIVE;

	// Получаем исходный IP адрес сервера и порт
	iResult = GetAddrInfoW( NULL, port_.c_str( ), &hints_, &result_ );
	if ( iResult != 0 )
	{
		WSACleanup( );
		return false;
	}
	return true;

}

// ---------------------------------------------------------------------------
bool Server::Listen( )
{
	int iResult;
	// Создаем прослушивающий сокет для сервера
	listenSocket_ = socket( result_->ai_family, result_->ai_socktype,
		result_->ai_protocol );
	if ( listenSocket_ == INVALID_SOCKET )
	{
		FreeAddrInfoW( result_ );
		WSACleanup( );
		return false;
	}

	// Привязываем сокет и IP адрес
	iResult = ::bind( listenSocket_, result_->ai_addr,
		( int )result_->ai_addrlen );
	if ( iResult == SOCKET_ERROR )
	{
		FreeAddrInfoW( result_ );
		closesocket( listenSocket_ );
		WSACleanup( );
		return false;
	}

	FreeAddrInfoW( result_ );

	iResult = ::listen( listenSocket_, 2 );
	if ( iResult == SOCKET_ERROR )
	{
		closesocket( listenSocket_ );
		WSACleanup( );
		return false;
	}
	// Инициализация набора активных сокетов
	FD_ZERO( & active_fd_set );
	FD_SET( listenSocket_, & active_fd_set );
	return true;
}

// ---------------------------------------------------------------------------
bool Server::Accept( std::wstring destinationPath )
{

	/* Block until input arrives on one or more active sockets. */
	timeval tv;
	tv.tv_sec = 2;
	tv.tv_usec = 0;
	read_fd_set = active_fd_set;
	if ( select( 0, &read_fd_set, NULL, NULL, &tv ) < 0 )
	{
		int err = WSAGetLastError( );
		MessageBoxW( NULL, L"Ошибка select", L"Error", MB_OK );
		return false;
	}

	/* Service all the sockets with input pending. */
	for ( int i = 0; i < read_fd_set.fd_count; ++i )
	{
		if ( FD_ISSET( listenSocket_, &read_fd_set ) )
		{
			/* Connection request on original socket. */
			connectSocket_ = accept( listenSocket_, NULL, NULL );
			if ( connectSocket_ == INVALID_SOCKET )
			{
				int err = WSAGetLastError( );
				closesocket( listenSocket_ );
				WSACleanup( );
				return false;
			}
			FD_SET( connectSocket_, & active_fd_set );
			return true;
		}
		else
		{
			if ( FD_ISSET( connectSocket_, &read_fd_set ) )
			{
				// Запускается функция приема и после должен очиститься fd_setd
				if ( RecieveFile( destinationPath ) )
				{
					FD_CLR( connectSocket_, & active_fd_set );
				}
				return true;
			}
		}
	}

	return true;
}

// ---------------------------------------------------------------------------
bool Server::CleanUp( )
{
	// Нет необходимости в дальнейшей прослушке порта
	closesocket( listenSocket_ );
	closesocket( connectSocket_ );
	WSACleanup( );
	return true;
}

// ---------------------------------------------------------------------------
bool Server::Shutdown( )
{
	int iResult;
	iResult = shutdown( connectSocket_, SD_BOTH );
	if ( iResult == SOCKET_ERROR )
	{
		closesocket( connectSocket_ );
		WSACleanup( );
		return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
