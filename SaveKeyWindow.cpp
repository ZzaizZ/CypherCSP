//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SaveKeyWindow.h"

#include "ProviderCryptography.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	tedPassPhrase->PasswordChar = L'*';
	tedApprovePassPhrase->PasswordChar = L'*';
    keySaveDialog->Filter = "Файлы симметричного ключа (*.symkey)|*.SYMKEY|Все файлы (*.*)|*.*";
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnSaveKeyClick(TObject *Sender)
{
	ProviderCryptography *crypt = new ProviderCryptography( PROV_GOST_2012_256 );
	if ( !keySaveDialog->Execute( ) )
	{
		return;
	}
	UnicodeString uPass = tedPassPhrase->Text;
	UnicodeString uPassApprove = tedApprovePassPhrase->Text;
	if (uPass == uPassApprove) {
		std::string password( AnsiString( uPass ).c_str( ) );
		crypt->GenerateKey( ( char * )password.c_str( ) );
		crypt->SaveKey( (keySaveDialog->FileName + ".symkey").c_str( ) );
        delete crypt;
        this->Close();
	}
	else
	{
		MessageBoxW( NULL, L"Введённые пароли не совпадают", L"Error",
			MB_OK );
	}
    delete crypt;
}
//---------------------------------------------------------------------------
