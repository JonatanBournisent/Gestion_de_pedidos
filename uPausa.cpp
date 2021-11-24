//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPausa.h"
#include "uPedidos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfPausa *fPausa;
//---------------------------------------------------------------------------
__fastcall TfPausa::TfPausa(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfPausa::Button28Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TfPausa::FormClose(TObject *Sender, TCloseAction &Action)
{
   fPedidos->contLineasImpresas = 0;
   fPedidos->Edit2->Text = Edit3->Text;
   fPedidos->cantLineas = StrToInt(fPedidos->Edit2->Text);
}
//---------------------------------------------------------------------------
void __fastcall TfPausa::FormShow(TObject *Sender)
{
   Edit3->Text = "10000";
}
//---------------------------------------------------------------------------
