//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GenerateKeyPairWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
    keyGenerateDialog->Filter = "Файлы открытого ключа (*.pub)|*.PUB|Все файлы (*.*)|*.*";
	this->Position = poDesktopCenter;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::btnGenerateClick(TObject *Sender)
{
    ProviderCryptography *crypt = new ProviderCryptography( PROV_GOST_2012_256 );
	if ( !keyGenerateDialog->Execute( ) )
	{
		return;
	}
	wchar_t *containerName = tedContainerName->Text.c_str();
	wchar_t *pkPath = (keyGenerateDialog->FileName+".pub").c_str( );
	crypt->GenKeyPair(containerName, pkPath);
	delete crypt;
	this->Close();
    delete crypt;
}
//---------------------------------------------------------------------------
