//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uIngredientes.h"
#include "uValorNutricional.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfIngredientes *fIngredientes;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfIngredientes::TfIngredientes(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfIngredientes::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------
void __fastcall TfIngredientes::FormShow(TObject *Sender)
{
   Panel1->Visible = false;
   Edit1->Text = "";
//   CDS1->Active = false;
//   Query1->Close();
//   Query1->SQL->Clear();
//   String q;
//   q = "SELECT idIngrediente, nombre FROM ingredientes";
//   Query1->SQL->Add(q);
//   Query1->Open();
//   CDS1->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfIngredientes::Edit1Change(TObject *Sender)
{
   if(Edit1->Text == "")
   {
	   CDS1->Active = false;
	   Query1->Close();
	   Query1->SQL->Clear();
	   String q;
	   q = "SELECT idIngrediente, nombre FROM ingredientes";
	   Query1->SQL->Add(q);
	   Query1->Open();
	   CDS1->Active = true;
   }
   else
   {
       CDS1->Active = false;
	   Query1->Close();
	   Query1->SQL->Clear();
	   String q;
	   q = "SELECT idIngrediente, nombre FROM ingredientes WHERE UPPER(nombre) LIKE :nombre";
	   Query1->SQL->Add(q);
	   Query1->ParamByName("nombre")->AsString = "%" + Edit1->Text.UpperCase() + "%";
	   Query1->Open();
	   CDS1->Active = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfIngredientes::Button1Click(TObject *Sender)
{
   Edit2->Text = "";
   Panel1->Visible = true;
   Edit2->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfIngredientes::Button3Click(TObject *Sender)
{
   Panel1->Visible = false;
   QueryAux->Close();
   QueryAux->SQL->Clear();
   String q;

   q = "INSERT INTO ingredientes ( "
	   "nombre, valorEnergetico, carbohidratos, proteinas, "
	   "grasasTotales, grasasSaturadas, grasasTrans, "
	   "fibraAlimentaria, sodio) "
	   "VALUES(:nombre, 0.00, 0.0000, 0.0000, "
	   "0.0000, 0.0000, 0.0000, 0.0000, 0.00)";

   QueryAux->SQL->Add(q);
   QueryAux->ParamByName("nombre")->AsString = Edit2->Text;
   QueryAux->ExecSQL();

   QueryAux->Close();
   QueryAux->SQL->Clear();

   QueryAux->SQL->Add("SELECT MAX(idIngrediente) AS ultimo FROM ingredientes");
   QueryAux->Open();
   int ultimo = QueryAux->FieldByName("ultimo")->AsInteger;
   QueryAux->Close();

   fValorNutricional->idIngrediente = ultimo;
   fValorNutricional->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfIngredientes::Button4Click(TObject *Sender)
{
   Panel1->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfIngredientes::Button2Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

void __fastcall TfIngredientes::FormClick(TObject *Sender)
{
   Query1->Close();
   QueryAux->Close();
   SQLConnection1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfIngredientes::DBGrid1DblClick(TObject *Sender)
{
   fValorNutricional->idIngrediente = CDS1->FieldByName("idIngrediente")->AsInteger;
   fValorNutricional->ShowModal();
}
//---------------------------------------------------------------------------
