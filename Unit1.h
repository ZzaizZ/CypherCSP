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
<<<<<<< HEAD
	TOpenDialog * keyOpenDialog;
	TButton * sendButton;
	TOpenDialog * sendOpenDialog;
	TLabel * ipLabel;
	TButton *serverOnButton;
	TEdit * ipEdit;
	TLabel * portLabel;
	TEdit * portEdit;
	TButton *serverOffButton;
=======
	TOpenDialog *keyOpenDialog;
>>>>>>> netVersion

	void __fastcall chooseKeyCheckBoxClick( TObject * Sender );
	void __fastcall saveKeyButtonClick( TObject * Sender );
	void __fastcall passwordEditChange( TObject * Sender );
	void __fastcall encryptButtonClick( TObject * Sender );
	void __fastcall decryptButtonClick( TObject * Sender );
<<<<<<< HEAD
	void __fastcall algorithmComboBoxChange( TObject * Sender );
	void __fastcall sendButtonClick( TObject * Sender );
	void __fastcall serverOnButtonClick( TObject * Sender );
	void __fastcall serverOffButtonClick(TObject *Sender);
	void __fastcall ipEditKeyPress(TObject *Sender, System::WideChar &Key);
=======
	void __fastcall algorithmComboBoxChange(TObject *Sender);
>>>>>>> netVersion

private: // User declarations
		public : // User declarations
	__fastcall TmainForm( TComponent * Owner );

	void checkCryptoProvider( int index );

	ProviderCryptography * crypt;
	ServerThread * serverThread;
	ClientThread * clientThread;
	Client * testClient;
	Server * testServer;

} ;

// ---------------------------------------------------------------------------
extern PACKAGE TmainForm * mainForm;
// ---------------------------------------------------------------------------
#endif
