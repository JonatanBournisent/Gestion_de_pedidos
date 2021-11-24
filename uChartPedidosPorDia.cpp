//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uChartPedidosPorDia.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfChartPedidosPorDia *fChartPedidosPorDia;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfChartPedidosPorDia::TfChartPedidosPorDia(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfChartPedidosPorDia::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------
void __fastcall TfChartPedidosPorDia::FormResize(TObject *Sender)
{
   DBChart1->Width = fChartPedidosPorDia->Width;
   DBChart1->Height = fChartPedidosPorDia->Height - 35;
}
//---------------------------------------------------------------------------
void __fastcall TfChartPedidosPorDia::FormClose(TObject *Sender, TCloseAction &Action)

{
   CDS2->Active = false;
   Query2->Close();
   SQLConnection1->Close();
}
//---------------------------------------------------------------------------
