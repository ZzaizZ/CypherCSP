// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GenerateKeyPairWindow.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 * Form3;

// ---------------------------------------------------------------------------
__fastcall TForm3::TForm3( TComponent * Owner ) : TForm( Owner )
{
	keyGenerateDialog->Filter =
		"Файлы открытого ключа (*.pubkey)|*.PUB|Все файлы (*.*)|*.*";
	this->Position = poDesktopCenter;
}

// ---------------------------------------------------------------------------
void __fastcall TForm3::btnGenerateClick( TObject * Sender )
{
	ProviderCryptography * crypt =
		new ProviderCryptography( PROV_GOST_2012_256 );
	if ( !keyGenerateDialog->Execute( ) )
	{
		return;
	}
	std::wstring containerName = tedContainerName->Text.w_str();
	std::wstring pkPath = keyGenerateDialog->FileName.w_str();
	pkPath.append(L".pubkey");
	crypt->GenKeyPair( containerName.c_str(), pkPath.c_str() );
	delete crypt;
	this->Close( );
	// delete crypt;
}
// ---------------------------------------------------------------------------
