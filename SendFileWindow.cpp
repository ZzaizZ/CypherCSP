// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SendFileWindow.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TsendForm * sendForm;

// ---------------------------------------------------------------------------
__fastcall TsendForm::TsendForm( TComponent * Owner ) : TForm( Owner )
{
	this->Position = poDesktopCenter;
}

// ---------------------------------------------------------------------------
void __fastcall TsendForm::connectButtonClick( TObject * Sender )
{
	client = new ClientThread(sendOpenDialog-> false );
}
// ---------------------------------------------------------------------------
