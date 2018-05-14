// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
// ---------------------------------------------------------------------------
USEFORM("SaveKeyWindow.cpp", Form2);
USEFORM("Unit1.cpp", mainForm);
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
		Application->CreateForm(__classid(TmainForm), &mainForm);
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
