//---------------------------------------------------------------------------

#ifndef uSeleccionarComidaH
#define uSeleccionarComidaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "uFrame4.h"
//---------------------------------------------------------------------------
class TfSeleccionarComida : public TForm
{
__published:	// IDE-managed Components
	TFrame4 *Frame41;
	TButton *Button1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Frame41DBGrid1DblClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Frame41DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
public:		// User declarations
	__fastcall TfSeleccionarComida(TComponent* Owner);

	int idSeleccionado;
};
//---------------------------------------------------------------------------
extern PACKAGE TfSeleccionarComida *fSeleccionarComida;
//---------------------------------------------------------------------------
#endif
