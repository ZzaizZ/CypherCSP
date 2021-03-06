//---------------------------------------------------------------------------

#ifndef SaveKeyWindowH
#define SaveKeyWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>

//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblPassPhrase;
	TLabel *lblApprovePassPhrase;
	TEdit *tedPassPhrase;
	TEdit *tedApprovePassPhrase;
	TButton *btnSaveKey;
	TSaveDialog *keySaveDialog;
	void __fastcall btnSaveKeyClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
