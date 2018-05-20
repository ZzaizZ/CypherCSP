// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#include "SaveKeyWindow.h"
#include "include/WinCryptEx.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmainForm * mainForm;

// ---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm( TComponent * Owner ) : TForm( Owner )
{
	algorithmComboBox->ItemIndex = 0;
    checkCryptoProvider(0);
	crypt = new ProviderCryptography( PROV_GOST_2012_256 );
	passwordEdit->PasswordChar = L'*';
	//this->Height = 210;
	this->Position = poDesktopCenter;
	keyOpenDialog->Filter = "Файлы симметричного ключа (*.symkey)|*.SYMKEY|Все файлы (*.*)|*.*";
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::chooseKeyCheckBoxClick( TObject * Sender )
{
	if ( chooseKeyCheckBox->Checked )
	{
		passwordEdit->Enabled = false;
		encryptButton->Enabled = true;
		decryptButton->Enabled = true;
	}
	else
	{
		passwordEdit->Enabled = true;
		if ( passwordEdit->Text.IsEmpty( ) )
		{
			encryptButton->Enabled = false;
			decryptButton->Enabled = false;
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::saveKeyButtonClick( TObject * Sender )
{
	TForm2 *save = new TForm2(Owner);
	save->Show();
}

// ---------------------------------------------------------------------------"
void __fastcall TmainForm::passwordEditChange( TObject * Sender )
{
	if ( !passwordEdit->Text.IsEmpty( ) )
	{
		encryptButton->Enabled = true;
		decryptButton->Enabled = true;
		saveKeyButton->Enabled = true;
	}
	else
	{
		encryptButton->Enabled = false;
		decryptButton->Enabled = false;
		saveKeyButton->Enabled = false;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::encryptButtonClick( TObject * Sender )
{

	if ( !inputOpenDialog->Execute( ) )
	{
		return;
	}
	if ( !outputOpenDialog->Execute( ) )
	{
		return;
	}
	if ( chooseKeyCheckBox->Checked )
	{
		if ( !keyOpenDialog->Execute( ) )
		{
			return;
		}
		crypt->GenerateKey( keyOpenDialog->FileName.c_str( ) );
		crypt->EncryptFile( inputOpenDialog->FileName.c_str( ),
			outputOpenDialog->FileName.c_str( ) );
	}
	else
	{
		UnicodeString unicodeLine = passwordEdit->Text;
		std::string password( AnsiString( unicodeLine ).c_str( ) );
		crypt->GenerateKey( ( char * )password.c_str( ) );
		crypt->EncryptFile( inputOpenDialog->FileName.c_str( ),
			outputOpenDialog->FileName.c_str( ) );
	}

}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::decryptButtonClick( TObject * Sender )
{

	if ( !inputOpenDialog->Execute( ) )
	{
		return;
	}
	if ( !outputOpenDialog->Execute( ) )
	{
		return;
	}
	if ( chooseKeyCheckBox->Checked )
	{
		if ( !keyOpenDialog->Execute( ) )
		{
			return;
		}
		crypt->GenerateKey( keyOpenDialog->FileName.c_str( ) );
		crypt->DecryptFile( inputOpenDialog->FileName.c_str( ),
			outputOpenDialog->FileName.c_str( ) );
	}
	else
	{
		UnicodeString unicodeLine = passwordEdit->Text;
		std::string password( AnsiString( unicodeLine ).c_str( ) );
		crypt->GenerateKey( ( char * ) password.c_str( ) );
		crypt->DecryptFile( inputOpenDialog->FileName.c_str( ),
			outputOpenDialog->FileName.c_str( ) );
	}

}
// ---------------------------------------------------------------------------
bool TmainForm::checkCryptoProvider(int index)
{
    if (algorithmComboBox->ItemIndex == index) { // На первой позиции - КриптоПРО крипропровайдер
		// делаем тестовое создание контекста криптопровайдера
		// если создаётся ок, то работа будет дальше, иначе интерфейс неактивен
		HCRYPTPROV hCryptProvider_;
		if ( !CryptAcquireContext( &hCryptProvider_, NULL, NULL, 80,
			CRYPT_VERIFYCONTEXT ) )
		{
			MessageBoxW( NULL, L"Ошибка инициализации криптопровайдера. Возможно, не установлена КриптоПРО 4.", L"Error",
				MB_OK );
			saveKeyButton->Enabled = false;
			chooseKeyCheckBox->Enabled = false;
			passwordEdit->Enabled = false;
		}
	}
}
// ---------------------------------------------------------------------------
void __fastcall TmainForm::algorithmComboBoxChange(TObject *Sender)
{
    checkCryptoProvider(0);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::btnGenerateKeyPairClick(TObject *Sender)
{
	wchar_t *containerName = L"MyContainerName"; // имя создаваемого контейнера
	wchar_t *pkPath = L"E:\\MyContainerName.pub"; // путь сохранения открытого ключа
	crypt->GenKeyPair(containerName, pkPath);
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::btnLoadKeyPairClick(TObject *Sender)
{
	crypt->LoadKeyPair(L"KC1_test");
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::btnLoadResponderKeyClick(TObject *Sender)
{
	crypt->ExportPublicKeyToFile(L"321.pub");
}
//---------------------------------------------------------------------------

