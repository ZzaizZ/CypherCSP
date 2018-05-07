// ---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>

#include "cryptography.h"

// ---------------------------------------------------------------------------
class TmainForm : public TForm
{
__published: // IDE-managed Components

	TButton * encryptButton;
	TButton * decryptButton;
	TEdit * inputEdit;
	TEdit * outputEdit;
	TLabel * inputLabel;
	TLabel * outputLabel;
	TOpenDialog * inputOpenDialog;
	TLabel * keyLabel;
	TEdit * keyEdit;
	TLabel * passwordLabel;
	TEdit * passwordEdit;
	TOpenDialog * outputOpenDialog;
	TOpenDialog * keyOpenDialog;
	TButton * loadKeyButton;
	TButton * saveKeyButton;
	TLabel * algorithmLabel;
	TComboBox * algorithmComboBox;
	TCheckBox * chooseKeyCheckBox;

	void __fastcall inputEditDblClick( TObject * Sender );
	void __fastcall keyEditDblClick( TObject * Sender );
	void __fastcall outputEditDblClick( TObject * Sender );
	void __fastcall chooseKeyCheckBoxClick( TObject * Sender );
	void __fastcall encryptButtonClick(TObject *Sender);
	void __fastcall decryptButtonClick(TObject *Sender);
	void __fastcall saveKeyButtonClick(TObject *Sender);

private: // User declarations
		public : // User declarations
	__fastcall TmainForm( TComponent * Owner );

	cryptography * crypt;
} ;

// ---------------------------------------------------------------------------
extern PACKAGE TmainForm * mainForm;
// ---------------------------------------------------------------------------
#endif
