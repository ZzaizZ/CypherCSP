// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#include "SaveKeyWindow.h"
#include "GenerateKeyPairWindow.h"
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
	keyOpenDialog->Filter = "����� ������������� ����� (*.symkey)|*.SYMKEY|��� ����� (*.*)|*.*";
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
    if (algorithmComboBox->ItemIndex == index) { // �� ������ ������� - ��������� ���������������
		// ������ �������� �������� ��������� ����������������
		// ���� �������� ��, �� ������ ����� ������, ����� ��������� ���������
		HCRYPTPROV hCryptProvider_;
		if ( !CryptAcquireContext( &hCryptProvider_, NULL, NULL, 80,
			CRYPT_VERIFYCONTEXT ) )
		{
			MessageBoxW( NULL, L"������ ������������� ����������������. ��������, �� ����������� ��������� 4.", L"Error",
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
    // ������� ����� ����������� ������
	wchar_t *containerName = L"Responder"; // ��� ������������ ����������
	wchar_t *pkPath = L"E:\\Responder.pub"; // ���� ���������� ��������� �����

	TForm3 *generate = new TForm3(Owner);
	generate->Show();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::btnLoadKeyPairClick(TObject *Sender)
{
	// ��� ���������� - ��������� �����������.
	// ��� ��������� ����� - �������� ���� ���������
	crypt->EncryptSessionKey(L"MyContainerName", "E:\\Responder.pub", L"E:\\new.symkey", L"E:\\new.symkey.encr");
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::btnLoadResponderKeyClick(TObject *Sender)
{
    // ��� ����� - ���� �� ����� �������������� ������������� �����
	// ��� ��������� ����� - �������� ���� �����������
	// ��� ���������� - ��������� ����������
	crypt->DecryptSessionKey(L"E:\\new.symkey.encr", "E:\\MyContainerName.pub", L"Responder");
	// ���������� ���� ������ �������� � ����������� ������
    crypt->DecryptFileW(L"E:\\pic.enc", L"E:\\123.jpg");
}
//---------------------------------------------------------------------------

