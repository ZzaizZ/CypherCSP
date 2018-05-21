// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ServerThread.h"
#pragma package(smart_init)
// ---------------------------------------------------------------------------

// Important: Methods and properties of objects in VCL can only be
// used in a method called using Synchronize, for example:
//
// Synchronize(&UpdateCaption);
//
// where UpdateCaption could look like:
//
// void __fastcall ServerThread::UpdateCaption()
// {
// Form1->Caption = "Updated in a thread";
// }
// ---------------------------------------------------------------------------

__fastcall ServerThread::ServerThread(
	std::wstring destinationPath,
	std::wstring port,
	bool         CreateSuspended ) : TThread(
	             CreateSuspended )
{
	FreeOnTerminate = true;
	destinationPath_ = destinationPath;
	port_ = port;
}

// ---------------------------------------------------------------------------
void __fastcall ServerThread::Execute( )
{
	// ---- Place thread code here ----
	server_ = new Server( port_ );
	if ( !server_->Init( ) )
	{
		MessageBoxW( NULL, L"Ошибка запуска сервера", L"Error", MB_OK );
		return;
	}
	if ( !server_->Listen( ) )
	{
		MessageBoxW( NULL, L"Ошибка прослушивания порта", L"Error", MB_OK );
		return;
	}
	while ( !Terminated )
	{
		if ( !server_->Accept( ) )
		{
			MessageBoxW( NULL, L"Ошибка подключения клиента", L"Error", MB_OK );
			break;
		}
		if ( !server_->RecieveFile( destinationPath_ ) )
		{
			MessageBoxW( NULL, L"Ошибка приема файла", L"Error", MB_OK );
			break;
		}
	}
	server_->CleanUp( );
	delete server_;
}
// ---------------------------------------------------------------------------
