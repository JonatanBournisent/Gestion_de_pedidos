//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "uMenuDelDia.h"
#include "uSeleccionarComida.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfMenuDelDia *fMenuDelDia;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfMenuDelDia::TfMenuDelDia(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------

bool TfMenuDelDia::revisarAntecedentes(void)
{

	  String q = "SELECT nombre FROM comidas WHERE comidas.idComida IN (SELECT todas "
			  "FROM ((SELECT refComida1 AS todas FROM menudeldia WHERE Fecha >= :fi AND Fecha <= :ff AND refComida1 > 1 AND refComida1 NOT IN (SELECT refComida FROM comidasnocontroladas)) "
			  "UNION ALL (SELECT refComida2 AS todas FROM menudeldia WHERE Fecha >= :fi AND Fecha <= :ff AND refComida2 > 1 AND refComida2 NOT IN (SELECT refComida FROM comidasnocontroladas)) "
			  "UNION ALL (SELECT refComida3 AS todas FROM menudeldia WHERE Fecha >= :fi AND Fecha <= :ff AND refComida3 > 1 AND refComida3 NOT IN (SELECT refComida FROM comidasnocontroladas)) "
			  "UNION ALL (SELECT refComida4 AS todas FROM menudeldia WHERE Fecha >= :fi AND Fecha <= :ff AND refComida4 > 1 AND refComida4 NOT IN (SELECT refComida FROM comidasnocontroladas)) "
			  "UNION ALL (SELECT refComida5 AS todas FROM menudeldia WHERE Fecha >= :fi AND Fecha <= :ff AND refComida5 > 1 AND refComida5 NOT IN (SELECT refComida FROM comidasnocontroladas)) "
			  "UNION ALL (SELECT refComida6 AS todas FROM menudeldia WHERE Fecha >= :fi AND Fecha <= :ff AND refComida6 > 1 AND refComida6 NOT IN (SELECT refComida FROM comidasnocontroladas)) "
			  "UNION ALL (SELECT refComida7 AS todas FROM menudeldia WHERE Fecha >= :fi AND Fecha <= :ff AND refComida7 > 1 AND refComida7 NOT IN (SELECT refComida FROM comidasnocontroladas)) "
			  "UNION ALL (SELECT refComida8 AS todas FROM menudeldia WHERE Fecha >= :fi AND Fecha <= :ff AND refComida8 > 1 AND refComida8 NOT IN (SELECT refComida FROM comidasnocontroladas))) AS t "
			  "WHERE todas IN ( SELECT ref FROM ("
			  "(SELECT refComida1 AS ref FROM menudeldia WHERE fecha = :fecha AND refComida1 > 1) "
			  "UNION ALL (SELECT refComida2 AS ref FROM menudeldia WHERE fecha = :fecha AND refComida2 > 1) "
			  "UNION ALL (SELECT refComida3 AS ref FROM menudeldia WHERE fecha = :fecha AND refComida3 > 1) "
			  "UNION ALL (SELECT refComida4 AS ref FROM menudeldia WHERE fecha = :fecha AND refComida4 > 1) "
			  "UNION ALL (SELECT refComida5 AS ref FROM menudeldia WHERE fecha = :fecha AND refComida5 > 1) "
			  "UNION ALL (SELECT refComida6 AS ref FROM menudeldia WHERE fecha = :fecha AND refComida6 > 1) "
			  "UNION ALL (SELECT refComida7 AS ref FROM menudeldia WHERE fecha = :fecha AND refComida7 > 1) "
			  "UNION ALL (SELECT refComida8 AS ref FROM menudeldia WHERE fecha = :fecha AND refComida8 > 1)) m)) ";

	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add(q);
	  QueryAux->ParamByName("fi")->AsDate = IncDay(StartOfTheWeek(fecha), -14);
	  QueryAux->ParamByName("ff")->AsDate = IncDay(StartOfTheWeek(fecha), -1);
	  QueryAux->ParamByName("fecha")->AsDate = fecha;
	  QueryAux->Open();
	  QueryAux->First();
	  ListBox1->Clear();
	  while(!QueryAux->Eof)
	  {
	     ListBox1->Items->Add(QueryAux->FieldByName("nombre")->AsString);
	     QueryAux->Next();
	  }

	  if(!QueryAux->IsEmpty())
	  {
		 QueryAux->Close();
		 return true;
	  }
	  else
	  {
	     QueryAux->Close();
		 return false;
	  }

}

//---------------------------------------------------------------------------
void __fastcall TfMenuDelDia::FormShow(TObject *Sender)
{
   Panel1->Visible = false;

   ClientDataSet1->Active = false;
   SQLTable1->Active = false;
   ClientDataSet1->Filtered = false;

   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("SELECT idComida, nombre FROM comidas ORDER BY nombre");
   Query1->Open();
   ClientDataSet2->Active = true;

   QueryAux->Close();
   QueryAux->SQL->Clear();
   QueryAux->SQL->Add("SELECT * FROM menudeldia WHERE (fecha = :f)");
   QueryAux->ParamByName("f")->AsDate = fecha;
   QueryAux->Open();

   if(QueryAux->IsEmpty())
   {
	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("INSERT INTO menudeldia VALUES (NULL, :f, 1, 1, 1, 1, 1, 1, 1, 1)");
	  QueryAux->ParamByName("f")->AsDate = fecha;
	  QueryAux->ExecSQL();

	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("SELECT * FROM menudeldia WHERE (fecha = :f) LIMIT 1");
	  QueryAux->ParamByName("f")->AsDate = fecha;
	  QueryAux->Open();
   }

   arrid[0] = QueryAux->FieldByName("refComida1")->AsInteger;
   arrid[1] = QueryAux->FieldByName("refComida2")->AsInteger;
   arrid[2] = QueryAux->FieldByName("refComida3")->AsInteger;
   arrid[3] = QueryAux->FieldByName("refComida4")->AsInteger;
   arrid[4] = QueryAux->FieldByName("refComida5")->AsInteger;
   arrid[5] = QueryAux->FieldByName("refComida6")->AsInteger;
   arrid[6] = QueryAux->FieldByName("refComida7")->AsInteger;
   arrid[7] = QueryAux->FieldByName("refComida8")->AsInteger;



   id = QueryAux->FieldByName("idMenuDelDia")->AsInteger;
   QueryAux->Close();

   ClientDataSet1->Filter = "idMenuDelDia = " + IntToStr(id);
   ClientDataSet1->Filtered = true;
   SQLTable1->Active = true;
   ClientDataSet1->Active = true;

   ClientDataSet1->Edit();

   fMenuDelDia->Caption = "Seleccionar men� del d�a: " + FormatDateTime("dddd dd/mm/yyyy", fecha);
}
//---------------------------------------------------------------------------
void __fastcall TfMenuDelDia::Button1Click(TObject *Sender)
{
   int i,j;
   bool ok = true;

   for(i = 0; i < 5; i++)
	  if(arrid[i] == 1 && arrid[i+1] > 1)
	  {
		 ok = false;
		 i = 7;
	  }
   if(arrid[6] == 1 && arrid[7] > 1)
   {
	  ok = false;
   }


   if(!ok)
   {
	  Application->MessageBox(L"Todas las opciones del men� deben ser consecutivas.",L"No se realizaron cambios.",MB_OK | MB_ICONERROR);
	  return;
   }
   else
   {
	  for(i = 0; i < 8; i++)
		 for(j = i+1; j < 8; j++)
			if(arrid[i] != 1)
			   if(arrid[i] == arrid[j])
			   {
				  ok = false;
				  j = 8;
				  i = 8;
			   }
	  if(!ok)
	  {
		 Application->MessageBox(L"No se pueden repetir las opciones.",L"No se realizaron cambios.",MB_OK | MB_ICONERROR);
         return;
	  }
   }

   ClientDataSet1->ApplyUpdates(0);

   if(revisarAntecedentes())
   {
	  Panel1->Visible = true;
   }
   else
      Close();
}
//---------------------------------------------------------------------------
void __fastcall TfMenuDelDia::Button2Click(TObject *Sender)
{
   if(Application->MessageBox(L"Se van a descartar los cambios realizados. Desea continuar?",L"Descartar cambios?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
   {
	  ClientDataSet1->Cancel();
      Close();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfMenuDelDia::Button3Click(TObject *Sender)
{
   if(Application->MessageBox(L"Se va a borrar este men�. Desea continuar?",L"Borrar este men�?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
   {
	  ClientDataSet1->Cancel();
	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("UPDATE menudeldia SET refComida1 = 1, refComida2 = 1, refComida3 = 1, refComida4 = 1, refComida5 = 1, refComida6 = 1, refComida7 = 1, refComida8 = 1 WHERE (idMenuDelDia = :id)");
      QueryAux->ParamByName("id")->AsInteger = id;
	  QueryAux->ExecSQL();

	  ClientDataSet1->Refresh();
   }
}
//---------------------------------------------------------------------------
void __fastcall TfMenuDelDia::FormClose(TObject *Sender, TCloseAction &Action)
{
   ClientDataSet1->Active = false;
   SQLTable1->Active = false;
   ClientDataSet2->Active = false;
   Query1->Close();
   QueryAux->Close();
   SQLConnection1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfMenuDelDia::Comida1Click(TObject *Sender)
{
   arrid[0] = ClientDataSet2->FieldByName("idComida")->AsInteger;
}
//---------------------------------------------------------------------------
void __fastcall TfMenuDelDia::Comida2Click(TObject *Sender)
{
   arrid[1] = ClientDataSet2->FieldByName("idComida")->AsInteger;
}
//---------------------------------------------------------------------------
void __fastcall TfMenuDelDia::Comida3Click(TObject *Sender)
{
   arrid[2] = ClientDataSet2->FieldByName("idComida")->AsInteger;
}
//---------------------------------------------------------------------------
void __fastcall TfMenuDelDia::Comida4Click(TObject *Sender)
{
   arrid[3] = ClientDataSet2->FieldByName("idComida")->AsInteger;
}
//---------------------------------------------------------------------------
void __fastcall TfMenuDelDia::Comida5Click(TObject *Sender)
{
   arrid[4] = ClientDataSet2->FieldByName("idComida")->AsInteger;
}
//---------------------------------------------------------------------------
void __fastcall TfMenuDelDia::Comida6Click(TObject *Sender)
{
   arrid[5] = ClientDataSet2->FieldByName("idComida")->AsInteger;
}
//---------------------------------------------------------------------------
void __fastcall TfMenuDelDia::Comida7Click(TObject *Sender)
{
   arrid[6] = ClientDataSet2->FieldByName("idComida")->AsInteger;
}
//---------------------------------------------------------------------------
void __fastcall TfMenuDelDia::Comida8Click(TObject *Sender)
{
   arrid[7] = ClientDataSet2->FieldByName("idComida")->AsInteger;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuDelDia::Button5Click(TObject *Sender)
{
   Panel1->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuDelDia::Button6Click(TObject *Sender)
{
   Panel1->Visible = false;
   Close();
}
//---------------------------------------------------------------------------

void __fastcall TfMenuDelDia::Button7Click(TObject *Sender)
{
   fSeleccionarComida->ShowModal();
   if(fSeleccionarComida->idSeleccionado == 0)
	  return;
   ClientDataSet1->FieldByName("refComida1")->AsInteger = fSeleccionarComida->idSeleccionado;
   arrid[0] = fSeleccionarComida->idSeleccionado;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuDelDia::Button8Click(TObject *Sender)
{
   fSeleccionarComida->ShowModal();
   if(fSeleccionarComida->idSeleccionado == 0)
	  return;
   ClientDataSet1->FieldByName("refComida2")->AsInteger = fSeleccionarComida->idSeleccionado;
   arrid[1] = fSeleccionarComida->idSeleccionado;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuDelDia::Button9Click(TObject *Sender)
{
   fSeleccionarComida->ShowModal();
   if(fSeleccionarComida->idSeleccionado == 0)
	  return;
   ClientDataSet1->FieldByName("refComida3")->AsInteger = fSeleccionarComida->idSeleccionado;
   arrid[2] = fSeleccionarComida->idSeleccionado;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuDelDia::Button10Click(TObject *Sender)
{
   fSeleccionarComida->ShowModal();
   if(fSeleccionarComida->idSeleccionado == 0)
	  return;
   ClientDataSet1->FieldByName("refComida4")->AsInteger = fSeleccionarComida->idSeleccionado;
   arrid[3] = fSeleccionarComida->idSeleccionado;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuDelDia::Button11Click(TObject *Sender)
{
   fSeleccionarComida->ShowModal();
   if(fSeleccionarComida->idSeleccionado == 0)
	  return;
   ClientDataSet1->FieldByName("refComida5")->AsInteger = fSeleccionarComida->idSeleccionado;
   arrid[4] = fSeleccionarComida->idSeleccionado;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuDelDia::Button12Click(TObject *Sender)
{
   fSeleccionarComida->ShowModal();
   if(fSeleccionarComida->idSeleccionado == 0)
	  return;
   ClientDataSet1->FieldByName("refComida6")->AsInteger = fSeleccionarComida->idSeleccionado;
   arrid[5] = fSeleccionarComida->idSeleccionado;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuDelDia::Button13Click(TObject *Sender)
{
   fSeleccionarComida->ShowModal();
   if(fSeleccionarComida->idSeleccionado == 0)
	  return;
   ClientDataSet1->FieldByName("refComida7")->AsInteger = fSeleccionarComida->idSeleccionado;
   arrid[6] = fSeleccionarComida->idSeleccionado;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuDelDia::Button14Click(TObject *Sender)
{
   fSeleccionarComida->ShowModal();
   if(fSeleccionarComida->idSeleccionado == 0)
	  return;
   ClientDataSet1->FieldByName("refComida8")->AsInteger = fSeleccionarComida->idSeleccionado;
   arrid[7] = fSeleccionarComida->idSeleccionado;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuDelDia::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------

