//---------------------------------------------------------------------------

#ifndef GenerateKeysH
#define GenerateKeysH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include "SaveKeyWindow.h"
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TEdit *tedContainerName;
	TLabel *Label1;
	TButton *btnGenerateKeys;
	TSaveDialog *keyGenerateDialog;
	TCheckBox *cbGenSessionKey;
	void __fastcall btnGenerateKeysClick(TObject *Sender);
private:	// User declarations
    TForm2 *save;
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
