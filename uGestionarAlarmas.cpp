//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uGestionarAlarmas.h"
#include "uConfigurarAlarma.h"
#include "uMain.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfGestionarAlarmas *fGestionarAlarmas;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfGestionarAlarmas::TfGestionarAlarmas(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfGestionarAlarmas::FormShow(TObject *Sender)
{
   CDS1->Active = false;

   Query1->Close();
   Query1->SQL->Clear();
   String q;
   q = "SELECT *, ELT(frecuenciaRepeticion + 1, 'No repetir', 'Diariamente', 'Semanalmente') AS frec FROM alarmas ORDER by marcaTiempo DESC";

   Query1->SQL->Add(q);
   Query1->Open();

   if(Query1->IsEmpty())
   {
	  Query1->Close();
	  return;
   }
   CDS1->Active = true;

   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
}
//---------------------------------------------------------------------------
void __fastcall TfGestionarAlarmas::Modificarestaalarma1Click(TObject *Sender)
{
   if(!CDS1->Active)
	  return;

   fConfigurarAlarma->llamador = 1;
   fConfigurarAlarma->idAlarma = CDS1->FieldByName("idAlarma")->AsInteger;
   fConfigurarAlarma->ShowModal();
   CDS1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfGestionarAlarmas::FormClose(TObject *Sender, TCloseAction &Action)

{
   QueryAux->Close();
   QueryAux->SQL->Clear();
   QueryAux->SQL->Add("SELECT IFNULL(idAlarma,0) AS idAlarma, marcaTiempo FROM alarmas WHERE vista = 0 AND paraCocina = 0 ORDER BY marcaTiempo LIMIT 1");
   QueryAux->Open();
   fMain->idProximaAlarma = QueryAux->FieldByName("idAlarma")->AsInteger;
   fMain->proximaAlarma = QueryAux->FieldByName("marcaTiempo")->AsDateTime;
   QueryAux->Close();


   CDS1->Active = false;
   Query1->Close();
   QueryDelete->Close();
   QueryAux->Close();
   SQLConnection1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfGestionarAlarmas::SalirClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------


void __fastcall TfGestionarAlarmas::Eliminar1Click(TObject *Sender)
{
   if(!CDS1->Active)
	  return;

   QueryDelete->Close();
   QueryDelete->SQL->Clear();
   String q;
   q = "DELETE FROM alarmas WHERE idAlarma = :idAlarma LIMIT 1";
   QueryDelete->SQL->Add(q);
   QueryDelete->ParamByName("idAlarma")->AsInteger = CDS1->FieldByName("idAlarma")->AsInteger;
   QueryDelete->ExecSQL();

   CDS1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfGestionarAlarmas::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------

