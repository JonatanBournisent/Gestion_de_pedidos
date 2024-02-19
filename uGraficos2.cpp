//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGraficos2.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfGraficos2 *fGraficos2;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfGraficos2::TfGraficos2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfGraficos2::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------
void __fastcall TfGraficos2::FormResize(TObject *Sender)
{
   DBChart1->Width = fGraficos2->Width;
   DBChart1->Height = fGraficos2->Height - 35;
}
//---------------------------------------------------------------------------
