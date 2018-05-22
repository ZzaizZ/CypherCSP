//---------------------------------------------------------------------------

#ifndef GenerateKeyPairWindowH
#define GenerateKeyPairWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "ProviderCryptography.h"
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblContainerName;
	TEdit *tedContainerName;
	TButton *btnGenerate;
	TSaveDialog *keyGenerateDialog;
	void __fastcall btnGenerateClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
