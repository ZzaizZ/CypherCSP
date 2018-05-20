// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ClientThread.h"
#pragma package(smart_init)
// ---------------------------------------------------------------------------

// Important: Methods and properties of objects in VCL can only be
// used in a method called using Synchronize, for example:
//
// Synchronize(&UpdateCaption);
//
// where UpdateCaption could look like:
//
// void __fastcall ClientThread::UpdateCaption()
// {
// Form1->Caption = "Updated in a thread";
// }
// ---------------------------------------------------------------------------

__fastcall ClientThread::ClientThread(
	std::wstring sourceFile,
	std::string  ipaddr,
	bool         CreateSuspended ) : TThread(
	             CreateSuspended )
{
	FreeOnTerminate = true;
	sourceFile_ = sourceFile;
	ipaddr_ = ipaddr;
}

// ---------------------------------------------------------------------------
void __fastcall ClientThread::Execute( )
{
	// ---- Place thread code here ----
	client_ = new Client( );
	if ( !client_->Init( ipaddr_ ) )
	{
		MessageBoxW( NULL,
			L"Ошибка подключения к серверу, убедитесь что он запущен или доступен",
			L"Error", MB_OK );
		return;
	}
	if ( !client_->SendFile( sourceFile_ ) )
	{
		MessageBoxW( NULL, L"Ошибка отправки файла", L"Error", MB_OK );
		return;
	}
	MessageBoxW( NULL, L"Файл передан", L"Информация", MB_OK );
	delete client_;

}
// ---------------------------------------------------------------------------
