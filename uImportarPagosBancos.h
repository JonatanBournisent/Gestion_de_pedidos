//---------------------------------------------------------------------------

#ifndef uImportarPagosBancosH
#define uImportarPagosBancosH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TfImportarPagosBancos : public TForm
{
__published:	// IDE-managed Components
	TListBox *ListBox1;
private:	// User declarations
public:		// User declarations
	__fastcall TfImportarPagosBancos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfImportarPagosBancos *fImportarPagosBancos;
//---------------------------------------------------------------------------
#endif
