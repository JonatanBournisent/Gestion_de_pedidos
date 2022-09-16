//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uImportarPagosBancos.h"
#include "uCuentas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfImportarPagosBancos *fImportarPagosBancos;
//---------------------------------------------------------------------------
__fastcall TfImportarPagosBancos::TfImportarPagosBancos(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfImportarPagosBancos::FormClose(TObject *Sender, TCloseAction &Action)

{
   FDMemTable1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfImportarPagosBancos::DBGrid1DblClick(TObject *Sender)
{
   int idCli = FDMemTable1->FieldByName("idCliente")->AsInteger;
   if(idCli < 3)
	  return;

   fCuentas->idCliente = idCli;
   fCuentas->FormShow(fCuentas->Label1);
}
//---------------------------------------------------------------------------

