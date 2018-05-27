// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
// ---------------------------------------------------------------------------
USEFORM("Unit1.cpp", mainForm);
USEFORM("SaveKeyWindow.cpp", Form2);
USEFORM("SettingsWindow.cpp", Form3);
USEFORM("GenerateKeys.cpp", Form4);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(
	HINSTANCE,
	HINSTANCE,
	LPTSTR,
	int )
{
	try
	{
		Application->Initialize( );
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TmainForm), &mainForm);
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->CreateForm(__classid(TForm3), &Form3);
		Application->CreateForm(__classid(TForm4), &Form4);
		Application->Run( );
	}
	catch ( Exception & exception )
	{
		Application->ShowException( & exception );
	}
	catch ( ... )
	{
		try
		{
			throw Exception( "" );
		}
		catch ( Exception & exception )
		{
			Application->ShowException( & exception );
		}
	}
	return 0;
}
// ---------------------------------------------------------------------------
