// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmainForm * mainForm;

// ---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm( TComponent * Owner ) : TForm( Owner )
{
	crypt = new cryptography( );
    algorithmComboBox->ItemIndex = 0;
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::inputEditDblClick( TObject * Sender )
{
	if ( !inputOpenDialog->Execute( ) )
	{
		return;
	}
	inputEdit->Text = inputOpenDialog->FileName;
	outputEdit->Text = inputEdit->Text + ".enc";
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::keyEditDblClick( TObject * Sender )
{
	if ( !keyOpenDialog->Execute( ) )
	{
		return;
	}
	keyEdit->Text = keyOpenDialog->FileName;
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::outputEditDblClick( TObject * Sender )
{
	if ( !outputOpenDialog->Execute( ) )
	{
		return;
	}
	outputEdit->Text = outputOpenDialog->FileName;
}
// ---------------------------------------------------------------------------

void __fastcall TmainForm::chooseKeyCheckBoxClick( TObject * Sender )
{
	if ( chooseKeyCheckBox->Checked )
	{
		keyEdit->Visible = true;
		keyLabel->Visible = true;
		saveKeyButton->Visible = true;
		loadKeyButton->Visible = true;
		passwordEdit->Enabled = false;
		passwordLabel->Enabled = false;
	}
	else
	{
		keyEdit->Visible = false;
		keyLabel->Visible = false;
		saveKeyButton->Visible = false;
		loadKeyButton->Visible = false;
		passwordEdit->Enabled = true;
		passwordLabel->Enabled = true;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::encryptButtonClick( TObject * Sender )
{
	BYTE buffer[ 4096 ];
	int i = 0;
	if ( !crypt->open( inputEdit->Text.w_str( ), outputEdit->Text.w_str( ) ) )
	{
		MessageBoxW( NULL, L"Ошибка открытия", L"Error", MB_OK );
	}
	while ( crypt->readBlock( i, 4096, buffer ) )
	{
		crypt->encryptBlock( buffer, ( char * )passwordEdit->Text.c_str( ) );
		crypt->writeBlock( i, 4096, buffer );
		i++ ;
	}
	crypt->close( );
	delete[ ]buffer;
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::decryptButtonClick( TObject * Sender )
{
	BYTE buffer[ 4096 ];
	int i = 0;
	if ( !crypt->open( inputEdit->Text.w_str( ), outputEdit->Text.w_str( ) ) )
	{
		MessageBoxW( NULL, L"Ошибка открытия", L"Error", MB_OK );
	}
	while ( crypt->readBlock( i, 4096, buffer ) )
	{
		crypt->decryptBlock( buffer, ( char * )passwordEdit->Text.c_str( ) );
		crypt->writeBlock( i, 4096, buffer );
		i++ ;
	}
	crypt->close( );
	delete[ ]buffer;
}
// ---------------------------------------------------------------------------
