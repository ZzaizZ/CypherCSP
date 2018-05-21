// ---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>

#include "ProviderCryptography.h"

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
	TOpenDialog *keyOpenDialog;
	TButton *btnGenerateKeyPair;
	TButton *btnDecryptSessionKey;
	TButton *btnEncSessionKey;
	TOpenDialog *sdPublicKeySave;
	TEdit *tedSenderContainerName;
	TEdit *tedResponderPKPath;
	TEdit *tedInSessionKey;
	TEdit *tedOutSessionKey;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;

	void __fastcall chooseKeyCheckBoxClick( TObject * Sender );
	void __fastcall saveKeyButtonClick( TObject * Sender );
	void __fastcall passwordEditChange( TObject * Sender );
	void __fastcall encryptButtonClick( TObject * Sender );
	void __fastcall decryptButtonClick( TObject * Sender );
	void __fastcall algorithmComboBoxChange(TObject *Sender);
	void __fastcall btnGenerateKeyPairClick(TObject *Sender);
	void __fastcall btnEncSessionKeyClick(TObject *Sender);
	void __fastcall btnDecryptSessionKeyClick(TObject *Sender);

private: // User declarations
		public : // User declarations
	__fastcall TmainForm( TComponent * Owner );
    bool checkCryptoProvider(int index);

	ProviderCryptography * crypt;
} ;

// ---------------------------------------------------------------------------
extern PACKAGE TmainForm * mainForm;
// ---------------------------------------------------------------------------
#endif
