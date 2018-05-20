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

__fastcall ServerThread::ServerThread( bool CreateSuspended )
	: TThread( CreateSuspended )
{
	FreeOnTerminate = true;
}

// ---------------------------------------------------------------------------
void __fastcall ServerThread::Execute( )
{
	// ---- Place thread code here ----
	server_ = new Server( );
	if ( !server_->Init( ) )
	{
		MessageBoxW( NULL, L"Ошибка запуска сервера", L"Error", MB_OK );
		return;
	}
	if ( !server_->RecieveFile( ) )
	{
		MessageBoxW( NULL, L"Ошибка приема файла", L"Error", MB_OK );
		return;
	}
	delete server_;
}
// ---------------------------------------------------------------------------
