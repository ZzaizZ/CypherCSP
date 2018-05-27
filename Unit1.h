// ---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <FileCtrl.hpp>

#include "ProviderCryptography.h"
#include "ServerThread.h"
#include "ClientThread.h"
#include <Vcl.Mask.hpp>
#include <Vcl.ComCtrls.hpp>

// ---------------------------------------------------------------------------
class TmainForm : public TForm
{
__published: // IDE-managed Components

	TButton * encryptButton;
	TButton * decryptButton;
	TOpenDialog * inputOpenDialog;
	TLabel * passwordLabel;
	TEdit * passwordEdit;
	TOpenDialog * outputOpenDialog;
	TButton * saveKeyButton;
	TLabel * algorithmLabel;
	TComboBox * algorithmComboBox;
	TCheckBox * chooseKeyCheckBox;
	TOpenDialog * keyOpenDialog;
	TButton * sendButton;
	TOpenDialog * sendOpenDialog;
	TLabel * ipLabel;
	TButton *serverOnButton;
	TEdit * ipEdit;
	TLabel * portLabel;
	TEdit * portEdit;
	TButton *serverOffButton;
	TButton *btnSettings;
	TPageControl *pcMain;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TOpenDialog *odOpenPubKey;
	TEdit *tedContainerName;
	TLabel *lblContainerName;
	TButton *btnEncrypt;
	TOpenDialog *odOpenSessionKey;
	TOpenDialog *odResponderPubKey;
	TOpenDialog *odOpenEncFile;

	void __fastcall chooseKeyCheckBoxClick( TObject * Sender );
	void __fastcall saveKeyButtonClick( TObject * Sender );
	void __fastcall passwordEditChange( TObject * Sender );
	void __fastcall encryptButtonClick( TObject * Sender );
	void __fastcall decryptButtonClick( TObject * Sender );
	void __fastcall algorithmComboBoxChange( TObject * Sender );
	void __fastcall sendButtonClick( TObject * Sender );
	void __fastcall serverOnButtonClick( TObject * Sender );
	void __fastcall serverOffButtonClick(TObject *Sender);
	void __fastcall ipEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall btnSettingsClick(TObject *Sender);
	void __fastcall btnEncryptClick(TObject *Sender);

private: // User declarations
		public : // User declarations
	__fastcall TmainForm( TComponent * Owner );

	void checkCryptoProvider( int index );

	ProviderCryptography * crypt;
	ServerThread * serverThread;
	ClientThread * clientThread;
	Client * testClient;
	Server * testServer;
	UnicodeString Dir;

	bool prepareFile();

	wchar_t *senderContainerName;
	wchar_t *responderContainerName;
	wchar_t *sessionKey;
	wchar_t *senderPubKey;
	wchar_t *responderPubKey;


} ;

// ---------------------------------------------------------------------------
extern PACKAGE TmainForm * mainForm;
// ---------------------------------------------------------------------------
#endif
