// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#include "SaveKeyWindow.h"
#include "include/WinCryptEx.h"
#include <set>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmainForm * mainForm;

// ---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm( TComponent * Owner ) : TForm( Owner )
{

	algorithmComboBox->ItemIndex = 0;
	checkCryptoProvider( 0 );
	crypt = new ProviderCryptography( PROV_GOST_2012_256 );
	passwordEdit->PasswordChar = L'*';
	this->Height = 310;
	this->Position = poDesktopCenter;
	keyOpenDialog->Filter =
		"����� ������������� ����� (*.symkey)|*.SYMKEY|��� ����� (*.*)|*.*";
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
	TForm2 * save = new TForm2( Owner );
	save->Show( );
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
void TmainForm::checkCryptoProvider( int index )
{
	if ( algorithmComboBox->ItemIndex == index )
	{ // �� ������ ������� - ��������� ���������������
		// ������ �������� �������� ��������� ����������������
		// ���� �������� ��, �� ������ ����� ������, ����� ��������� ���������
		HCRYPTPROV hCryptProvider_;
		if ( !CryptAcquireContext( &hCryptProvider_, NULL, NULL, 80,
			CRYPT_VERIFYCONTEXT ) )
		{
			MessageBoxW( NULL,
				L"������ ������������� ����������������. ���������, ���������� �� ����� ��������� CSP 4",
				L"Error", MB_OK );
			saveKeyButton->Enabled = false;
			chooseKeyCheckBox->Enabled = false;
			passwordEdit->Enabled = false;
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::algorithmComboBoxChange( TObject * Sender )
{
	checkCryptoProvider( 0 );
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::sendButtonClick( TObject * Sender )
{
	if ( ipEdit->Text.IsEmpty( ) || portEdit->Text.IsEmpty( ) )
	{
		MessageBoxW( NULL, L"������ ������� IP ����� � ���� �������", L"Error",
			MB_OK );
	}
	else
	{
		testClient = new Client( ipEdit->Text.c_str( ),
		portEdit->Text.c_str( ) );
		if ( !testClient->Init( ) )
		{
			MessageBoxW( NULL, L"������ ������������� Winsock", L"Error",
			MB_OK );
			delete testClient;
		}
		if ( !testClient->Connect( ) )
		{
			MessageBoxW( NULL,
				L"TCP-������ ����������! ��������� � ������������ ���������� IP ������ � ������ �����",
				L"Error", MB_OK );
			delete testClient;
		}
		else
		{
			testClient->Shutdown( );
			testClient->CleanUp( );
			delete testClient;
			if ( !sendOpenDialog->Execute( ) )
			{
				return;
			}
			clientThread = new ClientThread( sendOpenDialog->FileName.c_str( ),
				ipEdit->Text.c_str( ), portEdit->Text.c_str( ), false );
		}

	}

}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::serverOnButtonClick( TObject * Sender )
{
	if ( portEdit->Text.IsEmpty( ) )
	{
		MessageBoxW( NULL, L"������ ������� ����� �����", L"Error", MB_OK );
	}
	else
	{
		testServer = new Server( portEdit->Text.c_str( ) );
		if ( !testServer->Init( ) )
		{
			MessageBoxW( NULL, L"������ ������������� Winsock", L"Error",
			MB_OK );
			delete testServer;
		}
		if ( !testServer->Listen( ) )
		{
			MessageBoxW( NULL,
				L"������ ��� ������� TCP-�������: ���������� ��������� �������� � ���������� �����!",
				L"Error", MB_OK );
			delete testServer;
		}
		else
		{
			testServer->CleanUp( );
			delete testServer;
			UnicodeString Dir;
			SelectDirectory( "��������� ����� ��� �������� ���������� ������",
				"Desktop", Dir,
				TSelectDirExtOpts( ) << sdNewFolder << sdShowEdit, NULL );

			if ( serverOnButton->Enabled && !Dir.IsEmpty( ) )
			{
				serverThread = new ServerThread( Dir.c_str( ),
					portEdit->Text.c_str( ), false );
				serverOnButton->Visible = false;
				serverOffButton->Visible = true;
			}
		}
	}

}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::serverOffButtonClick( TObject * Sender )
{
	if ( serverOffButton->Visible == true )
	{
		serverThread->Terminate( );
		serverOnButton->Visible = true;
		serverOffButton->Visible = false;
	}

}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::ipEditKeyPress(
	TObject *          Sender,
	System::WideChar & Key )

{

	Set < char, '.', '9' > Dig;
	Dig << '0' << '1' << '2' << '3' << '4' << '5' << '6' << '7' << '8' <<
		'9' << '.';
	if ( !Dig.Contains( Key ) && Key != 8 )
	{
		Key = '\0';
	}

}
// ---------------------------------------------------------------------------
void __fastcall TmainForm::Button1Click(TObject *Sender)
{
    crypt->EncryptSessionKey(L"Sender", L"J:\\Responder.pubkey", L"J:\\session.symkey", L"J:\\session.symkey.encr");
	crypt->DecryptSessionKey(L"J:\\session.symkey.encr", L"J:\\Sender.pubkey", L"Responder");
    crypt->DecryptFileW(L"J:\\pic.enc", L"J:\\123.jpg");
}
//---------------------------------------------------------------------------

