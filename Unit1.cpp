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
	bool sucsess = true;
	if ( !crypt->open( inputEdit->Text.w_str( ), outputEdit->Text.w_str( ) ) )
	{
		MessageBoxW( NULL, L"Ошибка открытия файла", L"Error", MB_OK );
	}
	else
	{
		while ( crypt->readBlock( i, 4096, buffer ) )
		{
			if ( !crypt->encryptBlock( buffer,
				( char * )passwordEdit->Text.c_str( ) ) )
			{
				sucsess = false;
				break;
			}
			crypt->writeBlock( i, 4096, buffer );
			i++ ;
		}
		crypt->close( );
		if ( sucsess )
		{
			MessageBoxW( NULL, L"Файл зашифрован", L"Готово", MB_OK );
		}

	}

}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::decryptButtonClick( TObject * Sender )
{
	BYTE buffer[ 4096 ];
	int i = 0;
	int selectChoise = 0;
	bool sucsess = true;

	if ( !outputEdit->Text.Pos( ".enc" ) )
	{
		selectChoise =
			MessageBoxW( NULL,
			L"Вы уверены, что файл является шифрованным, в противном случае возможна потеря данных",
			L"Внимание", MB_YESNOCANCEL );
	}
	switch ( selectChoise )
	{
	case IDYES:
		if ( !crypt->open( outputEdit->Text.w_str( ),
			inputEdit->Text.w_str( ) ) )
		{
			MessageBoxW( NULL, L"Ошибка открытия файла", L"Error", MB_OK );
		}
		else
		{
			while ( crypt->readBlock( i, 4096, buffer ) )
			{
				if ( !crypt->decryptBlock( buffer,
					( char * )passwordEdit->Text.c_str( ) ) )
				{
					sucsess = false;
					break;
				}
				crypt->writeBlock( i, 4096, buffer );
				i++ ;
			}
			crypt->close( );
			if ( sucsess )
			{
				MessageBoxW( NULL, L"Файл расшифрован", L"Готово", MB_OK );
			}

		}
		break;
	case IDNO:
		MessageBoxW( NULL, L"Повторите выбор", L"Ошибка", MB_OK );
		break;
	case IDCANCEL:
		break;
	default:
		if ( !crypt->open( outputEdit->Text.w_str( ),
			inputEdit->Text.w_str( ) ) )
		{
			MessageBoxW( NULL, L"Ошибка открытия файла", L"Error", MB_OK );
		}
		else
		{
			while ( crypt->readBlock( i, 4096, buffer ) )
			{
				if ( !crypt->decryptBlock( buffer,
					( char * )passwordEdit->Text.c_str( ) ) )
				{
					sucsess = false;
					break;
				}
				crypt->writeBlock( i, 4096, buffer );
				i++ ;
			}
			crypt->close( );
			if ( sucsess )
			{
				MessageBoxW( NULL, L"Файл расшифрован", L"Готово", MB_OK );
			}

		}
		break;
	}

}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::saveKeyButtonClick( TObject * Sender )
{
	crypt->saveKey( keyEdit->Text.c_str( ) );
}

// ---------------------------------------------------------------------------"
void __fastcall TmainForm::inputEditChange( TObject * Sender )
{
	if ( !inputEdit->Text.IsEmpty( ) && !outputEdit->Text.IsEmpty( )
		&& !passwordEdit->Text.IsEmpty( ) )
	{
		encryptButton->Enabled = true;
		decryptButton->Enabled = true;
	}
	else
	{
		encryptButton->Enabled = false;
		decryptButton->Enabled = false;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::outputEditChange( TObject * Sender )
{
	if ( !inputEdit->Text.IsEmpty( ) && !outputEdit->Text.IsEmpty( )
		&& !passwordEdit->Text.IsEmpty( ) )
	{
		encryptButton->Enabled = true;
		decryptButton->Enabled = true;
	}
	else
	{
		encryptButton->Enabled = false;
		decryptButton->Enabled = false;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TmainForm::passwordEditChange( TObject * Sender )
{
	if ( !inputEdit->Text.IsEmpty( ) && !outputEdit->Text.IsEmpty( )
		&& !passwordEdit->Text.IsEmpty( ) )
	{
		encryptButton->Enabled = true;
		decryptButton->Enabled = true;
	}
	else
	{
		encryptButton->Enabled = false;
		decryptButton->Enabled = false;
	}
}
// ---------------------------------------------------------------------------
