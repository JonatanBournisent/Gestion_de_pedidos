//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uConfigurarAlarma.h"
#include "uMain.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfConfigurarAlarma *fConfigurarAlarma;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfConfigurarAlarma::TfConfigurarAlarma(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfConfigurarAlarma::Button1Click(TObject *Sender)
{
   if(Memo1->Text == "")
	  return;

   DTP->Date = MC->Date;

   if(llamador == 0)
   {
	  Query1->Close();
	  Query1->SQL->Clear();
	  String q;

	  q = "INSERT INTO alarmas (mensaje, marcaTiempo, frecuenciaRepeticion, vista, paraCocina) "
		  "VALUES (:mensaje, :marcaTiempo, :frecuenciaRepeticion, 0, :paraCocina) ";

	  Query1->SQL->Add(q);
	  Query1->ParamByName("mensaje")->AsString = Memo1->Text;
	  Query1->ParamByName("marcaTiempo")->AsDateTime = DTP->DateTime;
	  Query1->ParamByName("frecuenciaRepeticion")->AsInteger = RadioGroup1->ItemIndex;
	  if(!CheckBox1->Checked)
		 Query1->ParamByName("paraCocina")->AsInteger = 0;
	  else
		 Query1->ParamByName("paraCocina")->AsInteger = 1;

	  Query1->ExecSQL();

	  Close();
   }
   else if(llamador == 1)
   {
	  Query1->Close();
	  Query1->SQL->Clear();
	  String q;

	  q = "UPDATE alarmas SET mensaje = :mensaje, marcaTiempo = :marcaTiempo, "
		  "frecuenciaRepeticion = :frecuenciaRepeticion, vista = 0, paraCocina = :paraCocina "
		  "WHERE idAlarma = :idAlarma LIMIT 1";

	  Query1->SQL->Add(q);
	  Query1->ParamByName("idAlarma")->AsInteger = idAlarma;
	  Query1->ParamByName("mensaje")->AsString = Memo1->Text;
	  Query1->ParamByName("marcaTiempo")->AsDateTime = DTP->DateTime;
	  Query1->ParamByName("frecuenciaRepeticion")->AsInteger = RadioGroup1->ItemIndex;
	  if(!CheckBox1->Checked)
		 Query1->ParamByName("paraCocina")->AsInteger = 0;
	  else
		 Query1->ParamByName("paraCocina")->AsInteger = 1;

	  Query1->ExecSQL();

	  Close();
   }

   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("SELECT IFNULL(idAlarma,0) AS idAlarma, marcaTiempo FROM alarmas WHERE vista = 0 AND paraCocina = 0 ORDER BY marcaTiempo LIMIT 1");
   Query1->Open();
   fMain->idProximaAlarma = Query1->FieldByName("idAlarma")->AsInteger;
   fMain->proximaAlarma = Query1->FieldByName("marcaTiempo")->AsDateTime;
   Query1->Close();

   Application->MessageBox(L"La información fue guardada correctamente" ,L"Alarma guardada",MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
}
//---------------------------------------------------------------------------

void __fastcall TfConfigurarAlarma::FormShow(TObject *Sender)
{
   if(llamador == 0)
   {
	  MC->Date = Now();
	  DTP->DateTime = Now();
	  RadioGroup1->ItemIndex = 0;
	  CheckBox1->Checked = false;
	  Memo1->Clear();
   }
   else if(llamador == 1)
   {
      Query1->Close();
	  Query1->SQL->Clear();
	  String q;

	  q = "SELECT * FROM alarmas WHERE idAlarma = :idAlarma LIMIT 1";

	  Query1->SQL->Add(q);
	  Query1->ParamByName("idAlarma")->AsInteger = idAlarma;
	  Query1->Open();

	  Memo1->Text =  Query1->FieldByName("mensaje")->AsString;
	  MC->Date = Query1->FieldByName("marcaTiempo")->AsDateTime;
	  DTP->DateTime = Query1->FieldByName("marcaTiempo")->AsDateTime;
	  RadioGroup1->ItemIndex = Query1->FieldByName("frecuenciaRepeticion")->AsInteger;
	  if(Query1->FieldByName("paraCocina")->AsInteger == 0)
		 CheckBox1->Checked = false;
	  else
		 CheckBox1->Checked = true;

	  Close();
   }
}
//---------------------------------------------------------------------------
void __fastcall TfConfigurarAlarma::Button2Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TfConfigurarAlarma::FormClose(TObject *Sender, TCloseAction &Action)

{
   Query1->Close();
   SQLConnection1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfConfigurarAlarma::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------

