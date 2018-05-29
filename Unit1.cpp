// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#include "SaveKeyWindow.h"
#include "GenerateKeys.h"
#include "include/WinCryptEx.h"
#include <set>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmainForm * mainForm;

// ---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent * Owner) : TForm(Owner)
{

	algorithmComboBox->ItemIndex = 0;
	checkCryptoProvider(0);
	crypt = new ProviderCryptography(PROV_GOST_2012_256);
	passwordEdit->PasswordChar = L'*';
	this->Height = 310;
	this->Position = poDesktopCenter;
	keyOpenDialog->Filter =
		"Файл симметричного ключа (*.symkey)|*.SYMKEY|Все файлы (*.*)|*.*";
	odOpenPubKey->Filter =
		"Файл открытого ключа (*.pubkey)|*.PUBKEY|Все файлы (*.*)|*.*";
	odResponderPubKey->Filter =
		"Файл открытого ключа (*.pubkey)|*.PUBKEY|Все файлы (*.*)|*.*";
	odOpenEncFile->Filter =
		"Зашифрованный файл (*.enc)|*.ENC|Все файлы (*.*)|*.*";
	pcMain->Pages[0]->Caption = L"Симметричное Шифрование";
	pcMain->Pages[1]->Caption = L"VPN";
	pcMain->ActivePageIndex = 0;

}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::chooseKeyCheckBoxClick(TObject * Sender)
{
	if (chooseKeyCheckBox->Checked)
	{
		passwordEdit->Enabled = false;
		encryptButton->Enabled = true;
		decryptButton->Enabled = true;
	}
	else
	{
		passwordEdit->Enabled = true;
		if (passwordEdit->Text.IsEmpty())
		{
			encryptButton->Enabled = false;
			decryptButton->Enabled = false;
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::saveKeyButtonClick(TObject * Sender)
{
	TForm2 * save = new TForm2(Owner);
	save->Show();
}

// ---------------------------------------------------------------------------"
void __fastcall TmainForm::passwordEditChange(TObject * Sender)
{
	if (!passwordEdit->Text.IsEmpty())
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
void __fastcall TmainForm::encryptButtonClick(TObject * Sender)
{

	if (!inputOpenDialog->Execute())
	{
		return;
	}
	if (!outputOpenDialog->Execute())
	{
		return;
	}
	if (chooseKeyCheckBox->Checked)
	{
		if (!keyOpenDialog->Execute())
		{
			return;
		}
		crypt->GenerateKey(keyOpenDialog->FileName.c_str());
		crypt->EncryptFile(inputOpenDialog->FileName.c_str(),
			outputOpenDialog->FileName.c_str());
	}
	else
	{
		UnicodeString unicodeLine = passwordEdit->Text;
		std::string password(AnsiString(unicodeLine).c_str());
		crypt->GenerateKey((char *)password.c_str());
		crypt->EncryptFile(inputOpenDialog->FileName.c_str(),
			outputOpenDialog->FileName.c_str());
	}

}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::decryptButtonClick(TObject * Sender)
{

	if (!inputOpenDialog->Execute())
	{
		return;
	}
	if (!outputOpenDialog->Execute())
	{
		return;
	}
	if (chooseKeyCheckBox->Checked)
	{
		if (!keyOpenDialog->Execute())
		{
			return;
		}
		crypt->GenerateKey(keyOpenDialog->FileName.c_str());
		crypt->DecryptFile(inputOpenDialog->FileName.c_str(),
			outputOpenDialog->FileName.c_str());
	}
	else
	{
		UnicodeString unicodeLine = passwordEdit->Text;
		std::string password(AnsiString(unicodeLine).c_str());
		crypt->GenerateKey((char *) password.c_str());
		crypt->DecryptFile(inputOpenDialog->FileName.c_str(),
			outputOpenDialog->FileName.c_str());
	}

}

// ---------------------------------------------------------------------------
void TmainForm::checkCryptoProvider(int index)
{
	if (algorithmComboBox->ItemIndex == index)
	{
		HCRYPTPROV hCryptProvider_;
		if (!CryptAcquireContext(&hCryptProvider_, NULL, NULL, 80,
			CRYPT_VERIFYCONTEXT))
		{
			MessageBoxW(NULL,
				L"Ошибка инициализации криптопровайдера!\n Проверьте, установлен ли пакет КриптоПроCSP 4",
				L"Error", MB_OK);
			saveKeyButton->Enabled = false;
			chooseKeyCheckBox->Enabled = false;
			passwordEdit->Enabled = false;
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::algorithmComboBoxChange(TObject * Sender)
{
	checkCryptoProvider(0);
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::sendButtonClick(TObject * Sender)
{
	if (ipEdit->Text.IsEmpty() || portEdit->Text.IsEmpty())
	{
		MessageBoxW(NULL,
			L"Ошибка поле IP-адреса или номера порта не может быть пустым",
			L"Error", MB_OK);
	}
	else
	{
		testClient = new Client(ipEdit->Text.c_str(), portEdit->Text.c_str());
		if (!testClient->Init())
		{
			MessageBoxW(NULL, L"Ошибка инициализации Winsock", L"Error", MB_OK);
			delete testClient;
		}
		if (!testClient->Connect())
		{
			MessageBoxW(NULL,
				L"TCP-сервер недоступен! Убедитеесь в правильности указанного IP-адреса и номера порта",
				L"Error", MB_OK);
			delete testClient;
		}
		else
		{
			testClient->Shutdown();
			testClient->CleanUp();
			delete testClient;
			// if ( !sendOpenDialog->Execute( ) )
			// {
			// return;
			// }
			if (this->prepareFile())
			{
				clientThread =
					new ClientThread((sendOpenDialog->FileName + ".enc").c_str
					(), ipEdit->Text.c_str(), portEdit->Text.c_str(), false);
				while (!clientThread->Finished)
				{
				}
				wchar_t tmpPath[50];
				wchar_t *encSessionkeyName = L"session.symkey.enc";
				GetTempPath(50, tmpPath);
				std::wstring encSymkeyPath = (std::wstring(tmpPath)+std::wstring(encSessionkeyName));
				clientThread =
					new ClientThread(encSymkeyPath.c_str(),
					ipEdit->Text.c_str(), portEdit->Text.c_str(), false);
				MessageBoxW(NULL, L"Шифрованная передача завершилась успешно",
					L"Info", MB_OK);

			}
		}

	}

}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::serverOnButtonClick(TObject * Sender)
{
	if (portEdit->Text.IsEmpty())
	{
		MessageBoxW(NULL, L"Ошибка номер порта пустой", L"Error", MB_OK);
	}
	else
	{
		testServer = new Server(portEdit->Text.c_str());
		if (!testServer->Init())
		{
			MessageBoxW(NULL, L"Ошибка инициализации Winsock", L"Error", MB_OK);
			delete testServer;
		}
		if (!testServer->Listen())
		{
			MessageBoxW(NULL,
				L"Ошибка при запуске TCP-сервера: невозможно выполнить привязку к указанному порту!",
				L"Error", MB_OK);
			delete testServer;
		}
		else
		{
			testServer->CleanUp();
			delete testServer;

			SelectDirectory("Укажите каталог для хранения принимаемых файлов",
				"Desktop", Dir,
				TSelectDirExtOpts() << sdNewFolder << sdShowEdit, NULL);

			if (serverOnButton->Enabled && !Dir.IsEmpty())
			{
				serverThread = new ServerThread(Dir.c_str(),
					portEdit->Text.c_str(), false);
				serverOnButton->Visible = false;
				serverOffButton->Visible = true;
				btnEncrypt->Visible = true;
				sendOpenKeyButton->Enabled = false;
			}
		}
	}

}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::serverOffButtonClick(TObject * Sender)
{
	if (serverOffButton->Visible == true)
	{
		serverThread->Terminate();
		serverOnButton->Visible = true;
		serverOffButton->Visible = false;
		btnEncrypt->Visible = false;
		sendOpenKeyButton->Enabled = true;
	}

}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::ipEditKeyPress(TObject * Sender,
	System::WideChar & Key)

{

	Set < char, '.', '9' > Dig;
	Dig << '0' << '1' << '2' << '3' << '4' << '5' << '6' << '7' << '8' <<
		'9' << '.';
	if (!Dig.Contains(Key) && Key != 8)
	{
		Key = '\0';
	}

}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::btnSettingsClick(TObject * Sender)
{
	TForm4 * generate = new TForm4(Owner);
	generate->Show();
}

// ---------------------------------------------------------------------------
bool TmainForm::prepareFile()
{
	// Метод, открывающий файлы перед их отправкой.
	// шифрует ключевой файл
	if (tedContainerName->Text == "")
	{
		MessageBoxW(NULL, L"Пожалуйста укажите название ключевого контейнера!",
			L"Error", MB_OK);
		return false;
	}
	else
	{
		HCRYPTPROV hTest;

		if (CryptAcquireContext(&hTest, tedContainerName->Text.c_str(), NULL,
			80, CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
		{
			if (!sendOpenDialog->Execute())
			{
				return false;
			}
			if (!odOpenPubKey->Execute())
			{
				return false;
			}
			// получение пути временной директории
			wchar_t tmpPath[50];
			wchar_t *sessionkeyName = L"session.symkey";
			wchar_t *encSessionkeyName = L"session.symkey.enc";
			GetTempPath(50, tmpPath);
			std::wstring symkeyPath = (std::wstring(tmpPath)+std::wstring(sessionkeyName));
			std::wstring encSymkeyPath = (std::wstring(tmpPath)+std::wstring(encSessionkeyName));

			wstring str;
			int i=0;
			for (i=0; i<10; i++)
			{
			int x= 65+ rand() %25;
			wchar_t a[1];
			a[0]=x;
			str+=std::wstring(a);
			}
			crypt->GenerateKey(str.c_str());
			crypt->SaveKey(symkeyPath);
			crypt->EncryptSessionKey(tedContainerName->Text.c_str(),
				odOpenPubKey->FileName.c_str(), symkeyPath,
				encSymkeyPath.c_str());
			return crypt->EncryptFile(sendOpenDialog->FileName.c_str(),
				(sendOpenDialog->FileName + ".enc").c_str());
		}
		else
		{
			MessageBoxW(NULL,
				L"Пожалуйста, проверьте наличие указанного контейнера!",
				L"Error", MB_OK);
			return false;
		}

	}
}
// ---------------------------------------------------------------------------
void __fastcall TmainForm::btnEncryptClick(TObject * Sender)
{
	if (tedContainerName->Text == "")
	{
		MessageBoxW(NULL, L"Пожалуйста укажите название ключевого контейнера!",
			L"Error", MB_OK);
	}
	else
	{
		HCRYPTPROV hTest;

		if (CryptAcquireContext(&hTest, tedContainerName->Text.c_str(), NULL,
			80, CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
		{
			odOpenEncFile->InitialDir = Dir;
			if (!odResponderPubKey->Execute())
			{
				return;
			}
			if (!odOpenEncFile->Execute())
			{
				return;
			}

			crypt->DecryptSessionKey((Dir + "\\session.symkey.enc").c_str(),
				odResponderPubKey->FileName.c_str(),
				tedContainerName->Text.c_str());
			crypt->DecryptFile((odOpenEncFile->FileName).c_str(),
				(odOpenEncFile->FileName).Delete(odOpenEncFile->FileName.Length
				() - 2, 3).c_str());
		}
		else
		{
			MessageBoxW(NULL,
				L"Пожалуйста, проверьте наличие указанного контейнера!",
				L"Error", MB_OK);
		}

	}
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::sendOpenKeyButtonClick(TObject *Sender)
{
	if (ipEdit->Text.IsEmpty() || portEdit->Text.IsEmpty())
	{
		MessageBoxW(NULL,
			L"Ошибка поле IP-адреса или номера порта не может быть пустым",
			L"Error", MB_OK);
	}
	else
	{
		testClient = new Client(ipEdit->Text.c_str(), portEdit->Text.c_str());
		if (!testClient->Init())
		{
			MessageBoxW(NULL, L"Ошибка инициализации Winsock", L"Error", MB_OK);
			delete testClient;
		}
		if (!testClient->Connect())
		{
			MessageBoxW(NULL,
				L"TCP-сервер недоступен! Убедитесь в правильности указанного IP-адреса и номера порта",
				L"Error", MB_OK);
			delete testClient;
		}
		else
		{
			testClient->Shutdown();
			testClient->CleanUp();
			delete testClient;
			if (!sendOpenDialog->Execute())
			{
				return;
			}
			clientThread = new ClientThread((sendOpenDialog->FileName).c_str(),
				ipEdit->Text.c_str(), portEdit->Text.c_str(), false);
			MessageBoxW(NULL,
				L"Передача файла успешна",
				L"Info", MB_OK);

		}

	}
}
// ---------------------------------------------------------------------------

//---------------------------------------------------------------------------

