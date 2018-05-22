// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#include "SaveKeyWindow.h"
#include "GenerateKeyPairWindow.h"
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
	// this->Height = 210;
	this->Position = poDesktopCenter;
	keyOpenDialog->Filter =
		"Файлы симметричного ключа (*.symkey)|*.SYMKEY|Все файлы (*.*)|*.*";
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
	{ // На первой позиции - КриптоПРО крипропровайдер
		// делаем тестовое создание контекста криптопровайдера
		// если создаётся ок, то работа будет дальше, иначе интерфейс неактивен
		HCRYPTPROV hCryptProvider_;
		if ( !CryptAcquireContext( &hCryptProvider_, NULL, NULL, 80,
			CRYPT_VERIFYCONTEXT ) )
		{
			MessageBoxW( NULL,
				L"Ошибка инициализации криптопровайдера. Проверьте, установлен ли пакет КриптоПРО CSP 4",
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
		MessageBoxW( NULL, L"Ошибка укажите IP адрес и порт сервера", L"Error",
			MB_OK );
	}
	else
	{
		testClient = new Client( ipEdit->Text.c_str( ),
		portEdit->Text.c_str( ) );
		if ( !testClient->Init( ) )
		{
			MessageBoxW( NULL, L"Ошибка инициализации Winsock", L"Error",
			MB_OK );
			delete testClient;
		}
		if ( !testClient->Connect( ) )
		{
			MessageBoxW( NULL,
				L"TCP-сервер недоступен! Убедитесь в правильности указанного IP адреса и номера порта",
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
		MessageBoxW( NULL, L"Ошибка укажите номер порта", L"Error", MB_OK );
	}
	else
	{
		testServer = new Server( portEdit->Text.c_str( ) );
		if ( !testServer->Init( ) )
		{
			MessageBoxW( NULL, L"Ошибка инициализации Winsock", L"Error",
			MB_OK );
			delete testServer;
		}
		if ( !testServer->Listen( ) )
		{
			MessageBoxW( NULL,
				L"Ошибка при запуске TCP-сервера: невозможно выполнить привязку к указанному порту!",
				L"Error", MB_OK );
			delete testServer;
		}
		else
		{
			testServer->CleanUp( );
			delete testServer;
			UnicodeString Dir;
			SelectDirectory( "Выберетие папку для хранения полученных файлов",
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
void __fastcall TmainForm::btnGenerateKeyPairClick( TObject * Sender )
{
	// сделать через всплывающее окошко
	//wchar_t * containerName = L"Responder"; // имя создаваемого контейнера
	//wchar_t * pkPath = L"E:\\Responder.pub"; // путь сохранения открытого ключа

	TForm3 * generate = new TForm3( Owner );
	generate->Show( );
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::btnEncSessionKeyClick( TObject * Sender )
{
	// Имя контейнера - контейнер отправителя.
	// Имя открытого ключа - открытый ключ получаеля
	// crypt->EncryptSessionKey(L"MyContainerName", L"E:\\Responder.pub", L"E:\\new.symkey", L"E:\\new.symkey.encr");
	crypt->EncryptSessionKey( tedSenderContainerName->Text.c_str( ),
		tedResponderPKPath->Text.c_str( ), tedInSessionKey->Text.c_str( ),
		tedOutSessionKey->Text.c_str( ) );
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::btnDecryptSessionKeyClick( TObject * Sender )
{
	// Имя файла - путь до файла зашифрованного симметричного ключа
	// Имя открытого ключа - открытый ключ отправителя
	// Имя контейнера - контейнер получателя
	wchar_t * send = pathSendPubEdit->Text.c_str( );
	wchar_t * pkp = encrSymkeyEdit->Text.c_str( );
	wchar_t * cn = contRespondEdit->Text.c_str( );
	// crypt->DecryptSessionKey(L"E:\\new.symkey.encr", L"E:\\MyContainerName.pub", L"Responder");
	if ( crypt->DecryptSessionKey( send, pkp, cn ) )
	{
		MessageBoxW( NULL, L"Симметричный ключ успешно расшифрован", L"Info",
			MB_OK );
		encryptButton->Enabled = true;
		decryptButton->Enabled = true;
	}
	// сессионный ключ теперь хранится в оперативной памяти
	// в аргументах ниже - зашифрованный файл, потом расшифрованный

}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::Button1Click( TObject * Sender )
{
	if ( !keyOpenDialog->Execute( ) )
	{
		return;
	}
	crypt->SaveKey( keyOpenDialog->FileName.c_str( ) );
}
// ---------------------------------------------------------------------------
