//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GenerateKeys.h"
#include "ProviderCryptography.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
    keyGenerateDialog->Filter =
		"Файл открытого ключа (*.pubkey)|*.PUB|Все файлы (*.*)|*.*";
	this->Position = poDesktopCenter;
	save = new TForm2( Owner );
}
//---------------------------------------------------------------------------
void __fastcall TForm4::btnGenerateKeysClick(TObject *Sender)
{
    ProviderCryptography * crypt =
		new ProviderCryptography( PROV_GOST_2012_256 );
	if ( !keyGenerateDialog->Execute( ) )
	{
		return;
	}
	crypt->GenKeyPair( tedContainerName->Text.c_str(), (keyGenerateDialog->FileName+".pubkey").c_str() );
	delete crypt;
	if (cbGenSessionKey->Checked)
		save->Show( );
	this->Close( );
}
//---------------------------------------------------------------------------
