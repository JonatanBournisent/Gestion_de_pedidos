//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "uFrameMenuOficina.h"
#include "uSeleccionarComida.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TframeMenuOficina *frameMenuOficina;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TframeMenuOficina::TframeMenuOficina(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void TframeMenuOficina::inicializar(TDate fechaIni)
{
   fecha = fechaIni;
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;

   cerrado->Checked = false;

   Panel1->Hide();

   Label1->Caption = FormatDateTime("dddd dd/mm", fecha );
   String s = Label1->Caption;
   String fst = s.SubString(1,1);
   s = s.Delete(1,1);
   s = s.Insert(fst.UpperCase(),1);
   Label1->Caption = s;

   mostrarMenu();
}
//---------------------------------------------------------------------------
void TframeMenuOficina::cerrar(void)
{
   QueryAux->Close();
   QueryUpdate->Close();
   CDS1->Active = false;
   Query1->Close();
}
//---------------------------------------------------------------------------
void TframeMenuOficina::mostrarMenu(void)
{
   if(!cerrado->Checked)
   {
//	  int recNo;
//
//	  if(CDS1->Active)
//		 recNo = CDS1->RecNo;
//	  else
//	     recNo = 1;

	  CDS1->Active = false;
	  Query1->Close();
	  Query1->SQL->Clear();
	  Query1->SQL->Add("SELECT idMenuOficinas, fecha, "
	  				   "orden AS nroOpcion, "
					   "(SELECT nombre FROM comidas WHERE idComida = refComida1) AS plato1, "
					   "(SELECT nombre FROM comidas WHERE idComida = refComida2) AS plato2, "
					   "IF(esLight = 'S',1,0) AS esLight, "
					   "IF(esVeggie = 'S',1,0) AS esVeggie "
					   "FROM menuOficinas WHERE fecha = :fecha "
					   "ORDER BY orden");

	  Query1->ParamByName("fecha")->AsDate = fecha;
	  Query1->Open();
	  CDS1->Active = true;

//	  if(!CDS1->IsEmpty())
//		 CDS1->RecNo = recNo;
   }
}
//---------------------------------------------------------------------------
void __fastcall TframeMenuOficina::DBGrid1DblClick(TObject *Sender)
{
   if(CDS1->IsEmpty())
      return;


   QueryAux->Close();
   QueryAux->SQL->Clear();
   QueryAux->SQL->Add("SELECT esLight, esVeggie FROM menuoficinas WHERE idMenuOficinas = :idMO LIMIT 1");
   QueryAux->ParamByName("idMO")->AsInteger = CDS1->FieldByName("idMenuOficinas")->AsInteger;
   QueryAux->Open();
   if(QueryAux->FieldByName("esLight")->AsString == "S")
	  CheckBox1->Checked = true;
   else
	  CheckBox1->Checked = false;

   if(QueryAux->FieldByName("esVeggie")->AsString == "S")
	  CheckBox2->Checked = true;
   else
	  CheckBox2->Checked = false;

   QueryAux->Close();

   Panel1->Show();
}
//---------------------------------------------------------------------------
void __fastcall TframeMenuOficina::CDS1esLightGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
   if(Sender->AsInteger == 0)
	  Text = "NO";
   else if(Sender->AsInteger == 1)
	  Text = "SI";
   else
      Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TframeMenuOficina::CDS1esVeggieGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
   if(Sender->AsInteger == 0)
	  Text = "NO";
   else if(Sender->AsInteger == 1)
	  Text = "SI";
   else
      Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TframeMenuOficina::Moverhaciaarriba1Click(TObject *Sender)
{
   if(!CDS1->Active)
	  return;

   if(CDS1->RecordCount <= 1)
	  return;

   if(CDS1->FieldByName("NroOpcion")->AsInteger > 1)
   {
	  int id = CDS1->FieldByName("idMenuOficinas")->AsInteger;
	  int pos = CDS1->FieldByName("NroOpcion")->AsInteger;

	  int recNo = CDS1->RecNo;

	  QueryUpdate->Close();
	  QueryUpdate->SQL->Clear();
	  QueryUpdate->SQL->Add("UPDATE menuoficinas SET orden = orden + 1 WHERE orden = (:pos - 1) AND fecha = :fecha");
	  QueryUpdate->ParamByName("pos")->AsInteger = pos;
	  QueryUpdate->ParamByName("fecha")->AsDate = fecha;
	  QueryUpdate->ExecSQL();

	  QueryUpdate->Close();
	  QueryUpdate->SQL->Clear();
	  QueryUpdate->SQL->Add("UPDATE menuoficinas SET orden = orden - 1 WHERE idMenuOficinas = :id");
	  QueryUpdate->ParamByName("id")->AsInteger = id;
	  QueryUpdate->ExecSQL();

	  CDS1->Refresh();

	  CDS1->RecNo = recNo - 1;

   }
}
//---------------------------------------------------------------------------
void __fastcall TframeMenuOficina::Moverhacaabajo1Click(TObject *Sender)
{
   if(!CDS1->Active)
	  return;

   if(CDS1->RecordCount <= 1)
	  return;

   if(CDS1->FieldByName("NroOpcion")->AsInteger < CDS1->RecordCount)
   {
	  int id = CDS1->FieldByName("idMenuOficinas")->AsInteger;
	  int pos = CDS1->FieldByName("NroOpcion")->AsInteger;

	  int recNo = CDS1->RecNo;

	  QueryUpdate->Close();
	  QueryUpdate->SQL->Clear();
	  QueryUpdate->SQL->Add("UPDATE menuoficinas SET orden = orden - 1 WHERE orden = (:pos + 1) AND fecha = :fecha");
	  QueryUpdate->ParamByName("pos")->AsInteger = pos;
	  QueryUpdate->ParamByName("fecha")->AsDate = fecha;
	  QueryUpdate->ExecSQL();

	  QueryUpdate->Close();
	  QueryUpdate->SQL->Clear();
	  QueryUpdate->SQL->Add("UPDATE menuoficinas SET orden = orden + 1 WHERE idMenuOficinas = :id");
	  QueryUpdate->ParamByName("id")->AsInteger = id;
	  QueryUpdate->ExecSQL();

	  CDS1->Refresh();

	  CDS1->RecNo = recNo + 1;
   }
}
//---------------------------------------------------------------------------
void __fastcall TframeMenuOficina::Agregaropcin1Click(TObject *Sender)
{
   if(!CDS1->Active)
	  return;


   QueryAux->Close();
   QueryAux->SQL->Clear();
   QueryAux->SQL->Add("SELECT MAX(orden) AS maximo FROM menuoficinas WHERE fecha = :fecha");
   QueryAux->ParamByName("fecha")->AsDate = fecha;
   QueryAux->Open();
   int maximo = QueryAux->FieldByName("maximo")->AsInteger;
   QueryAux->Close();


   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("INSERT INTO menuoficinas (fecha, orden, refComida1, refComida2, esLight, esVeggie) "
					  "VALUES (:fecha, :maximo + 1, 1, 1, 'N', 'N')");
   QueryUpdate->ParamByName("fecha")->AsDate = fecha;
   QueryUpdate->ParamByName("maximo")->AsInteger = maximo;
   QueryUpdate->ExecSQL();

   CDS1->Refresh();

   CDS1->Last();

   CheckBox1->Checked = false;
   CheckBox2->Checked = false;
   Panel1->Show();
}
//---------------------------------------------------------------------------
void __fastcall TframeMenuOficina::Eliminaropcin1Click(TObject *Sender)
{
   if(!CDS1->Active)
	  return;

   if(CDS1->RecordCount > 0)
   {
	  int id = CDS1->FieldByName("idMenuOficinas")->AsInteger;
	  int pos = CDS1->FieldByName("nroOpcion")->AsInteger;

	  QueryUpdate->Close();
	  QueryUpdate->SQL->Clear();
	  QueryUpdate->SQL->Add("UPDATE menuoficinas SET orden = orden - 1 WHERE orden > :pos AND fecha = :fecha");
	  QueryUpdate->ParamByName("pos")->AsInteger = pos;
	  QueryUpdate->ParamByName("fecha")->AsDate = fecha;
	  QueryUpdate->ExecSQL();

	  QueryUpdate->Close();
	  QueryUpdate->SQL->Clear();
	  QueryUpdate->SQL->Add("DELETE FROM menuoficinas WHERE idMenuOficinas = :id");
	  QueryUpdate->ParamByName("id")->AsInteger = id;
	  QueryUpdate->ExecSQL();

	  CDS1->Refresh();
   }
}
//---------------------------------------------------------------------------
void __fastcall TframeMenuOficina::cerradoClick(TObject *Sender)
{
   if(cerrado->Checked)
   {
      DBGrid1->Enabled = false;
   }
   else
   {
	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("SELECT idMenuOficinas FROM menuoficinas WHERE fecha = :fecha LIMIT 1");
	  QueryAux->ParamByName("fecha")->AsDate = fecha;
	  QueryAux->Open();
	  bool existe = !QueryAux->IsEmpty();
	  QueryAux->Close();

	  if(!existe)
	  {
		 QueryAux->Close();
		 QueryAux->SQL->Clear();
		 QueryAux->SQL->Add("INSERT INTO menuoficinas (fecha, orden, refComida1, refComida2, esLight, esVeggie) "
							"VALUES (:fecha, 1, 1, 1, 'N', 'N')");
		 QueryAux->ParamByName("fecha")->AsDate = fecha;
		 QueryAux->ExecSQL();
	  }
	  DBGrid1->Enabled = true;
   }
   mostrarMenu();
}
//---------------------------------------------------------------------------
void __fastcall TframeMenuOficina::Button3Click(TObject *Sender)
{
   fSeleccionarComida->ShowModal();
   if(fSeleccionarComida->idSeleccionado == 0)
	  return;

   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE menuoficinas SET refComida1 = :rc WHERE idMenuOficinas = :idMO LIMIT 1");
   QueryUpdate->ParamByName("idMO")->AsInteger = CDS1->FieldByName("idMenuOficinas")->AsInteger;
   QueryUpdate->ParamByName("rc")->AsInteger = fSeleccionarComida->idSeleccionado;
   QueryUpdate->ExecSQL();

   CDS1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TframeMenuOficina::Button4Click(TObject *Sender)
{
   fSeleccionarComida->ShowModal();
   if(fSeleccionarComida->idSeleccionado == 0)
	  return;

   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE menuoficinas SET refComida2 = :rc WHERE idMenuOficinas = :idMO LIMIT 1");
   QueryUpdate->ParamByName("idMO")->AsInteger = CDS1->FieldByName("idMenuOficinas")->AsInteger;
   QueryUpdate->ParamByName("rc")->AsInteger = fSeleccionarComida->idSeleccionado;
   QueryUpdate->ExecSQL();

   CDS1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TframeMenuOficina::Button5Click(TObject *Sender)
{
   Panel1->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TframeMenuOficina::CheckBox1Click(TObject *Sender)
{
   String esLight;

   if(CheckBox1->Checked)
	  esLight = "S";
   else
	  esLight = "N";

   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE menuoficinas SET esLight = :esLight WHERE idMenuOficinas = :idMO LIMIT 1");
   QueryUpdate->ParamByName("idMO")->AsInteger = CDS1->FieldByName("idMenuOficinas")->AsInteger;
   QueryUpdate->ParamByName("esLight")->AsString = esLight;
   QueryUpdate->ExecSQL();

   CDS1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TframeMenuOficina::CheckBox2Click(TObject *Sender)
{
  String esVeggie;

   if(CheckBox2->Checked)
	  esVeggie = "S";
   else
	  esVeggie = "N";

   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE menuoficinas SET esVeggie = :esVeggie WHERE idMenuOficinas = :idMO LIMIT 1");
   QueryUpdate->ParamByName("idMO")->AsInteger = CDS1->FieldByName("idMenuOficinas")->AsInteger;
   QueryUpdate->ParamByName("esVeggie")->AsString = esVeggie;
   QueryUpdate->ExecSQL();

   CDS1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TframeMenuOficina::Modificarestaopcin1Click(TObject *Sender)
{
   DBGrid1DblClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TframeMenuOficina::Copiarestemen1Click(TObject *Sender)
{
   CDS1->First();
   Memo1->Clear();

   String p1, p2, esLight, esVeggie;
   while(!CDS1->Eof)
   {
	  p1 = CDS1->FieldByName("plato1")->AsString;
	  p2 = CDS1->FieldByName("plato2")->AsString;
	  esLight = CDS1->FieldByName("esLight")->AsString;
	  esVeggie = CDS1->FieldByName("esVeggie")->AsString;

	  if(esLight == 1)
		 esLight = " (Light)";
	  else
		 esLight = "";

	  p2 = p2.LowerCase();

	  if(esVeggie == 1)
		 esVeggie = " (Veggie)";
	  else
		 esVeggie = "";

	  if(p1.LowerCase() != p2)      //CDS1->RecNo) + ". " +
		 Memo1->Lines->Add(IntToStr(p1 + " con " + p2 + esLight + esVeggie);
	  else
		 Memo1->Lines->Add(IntToStr(p1 + esLight + esVeggie);

	  CDS1->Next();
   }

   Memo1->SelectAll();
   Memo1->CopyToClipboard();
}
//---------------------------------------------------------------------------

