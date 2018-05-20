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
	return true;
}

// ---------------------------------------------------------------------------
bool Server::Accept( )
{
	// Ожидаем подключения клиента к серверу
	connectSocket_ = accept( listenSocket_, NULL, NULL );
	if ( connectSocket_ == INVALID_SOCKET )
	{
		int err = WSAGetLastError( );
		closesocket( listenSocket_ );
		WSACleanup( );
		return false;
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
