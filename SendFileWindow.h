// ---------------------------------------------------------------------------

#ifndef SendFileWindowH
#define SendFileWindowH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "ClientThread.h"

// ---------------------------------------------------------------------------
class TsendForm : public TForm
{
__published: // IDE-managed Components

	TLabel * ipLabel;
	TEdit * ipEdit;
	TButton * connectButton;
	void __fastcall connectButtonClick(TObject *Sender);

private: // User declarations
		public : // User declarations

	__fastcall TsendForm( TComponent * Owner );

	ClientThread * client;
} ;

// ---------------------------------------------------------------------------
extern PACKAGE TsendForm * sendForm;
// ---------------------------------------------------------------------------
#endif
