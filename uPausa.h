//---------------------------------------------------------------------------

#ifndef uPausaH
#define uPausaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TfPausa : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label21;
	TLabel *Label20;
	TLabel *Label22;
	TEdit *Edit3;
	TButton *Button28;
	void __fastcall Button28Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfPausa(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfPausa *fPausa;
//---------------------------------------------------------------------------
#endif
