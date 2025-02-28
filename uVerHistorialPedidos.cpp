//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "uVerHistorialPedidos.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfVerHistorialPedidos *fVerHistorialPedidos;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfVerHistorialPedidos::TfVerHistorialPedidos(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfVerHistorialPedidos::mostrar(int refCliente, TDate fini, TDate ffin)
{
   CDS1->Active = false;
   Query1->Close();
   Query1->SQL->Clear();
   String q;
   q = "SELECT idPedido, momento AS fecha, comentario, "
	   "(SELECT nombre FROM comidas WHERE idComida = refComida1 LIMIT 1) AS opcion1, "
	   "(SELECT nombre FROM comidas WHERE idComida = refComida2 LIMIT 1) AS opcion2, "
	   "(SELECT nombre FROM comidas WHERE idComida = refComida3 LIMIT 1) AS opcion3, "
	   "(SELECT nombre FROM comidas WHERE idComida = refComida4 LIMIT 1) AS complemento "
	   "FROM pedidos WHERE refCliente = :refCliente AND momento >= :mi AND momento <= :mf";

   Query1->SQL->Add(q);
   Query1->ParamByName("refCliente")->AsInteger = refCliente;
//   Query1->ParamByName("fi")->AsDate = fini;
//   Query1->ParamByName("ff")->AsDate = ffin;
   Query1->ParamByName("mi")->AsDateTime = StartOfTheDay(fini);
   Query1->ParamByName("mf")->AsDateTime = EndOfTheDay(ffin);
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
void __fastcall TfVerHistorialPedidos::FormShow(TObject *Sender)
{
   QueryAux->Close();
   QueryAux->SQL->Clear();
   String q;
   q = "SELECT CONCAT(calle,' ',numero) AS cliente "
	   "FROM clientes WHERE idCliente = :idCliente LIMIT 1";

   QueryAux->SQL->Add(q);
   QueryAux->ParamByName("idCliente")->AsInteger = idCliente;
   QueryAux->Open();
   Label1->Caption = "Cliente: " + QueryAux->FieldByName("cliente")->AsString;
   QueryAux->Close();

   periodo = 0;

   mostrar(idCliente, IncWeek(StartOfTheWeek(Now()), periodo), IncWeek(EndOfTheWeek(Now()), periodo));
}
//---------------------------------------------------------------------------
void __fastcall TfVerHistorialPedidos::Button1Click(TObject *Sender)
{
   periodo--;

   mostrar(idCliente, IncWeek(StartOfTheWeek(Now()), periodo), IncWeek(EndOfTheWeek(Now()), periodo));
}
//---------------------------------------------------------------------------
void __fastcall TfVerHistorialPedidos::Button2Click(TObject *Sender)
{
   periodo++;

   mostrar(idCliente, IncWeek(StartOfTheWeek(Now()), periodo), IncWeek(EndOfTheWeek(Now()), periodo));
}
//---------------------------------------------------------------------------
void __fastcall TfVerHistorialPedidos::FormClose(TObject *Sender, TCloseAction &Action)

{
   CDS1->Active = false;
   Query1->Close();

   SQLConnection1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfVerHistorialPedidos::CDS1fechaGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
   if(DateOf(Sender->AsDateTime) == DateOf(Now()))
	  Text = "Hoy";
   else if(DateOf(Sender->AsDateTime) == IncDay(DateOf(Now()), -1))
	  Text = "Ayer";
   else
      Text = FormatDateTime("dddd dd/mm/yyyy", Sender->AsString);
}
//---------------------------------------------------------------------------

void __fastcall TfVerHistorialPedidos::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
   if(State.Contains(gdSelected))
   {
	  dynamic_cast <TDBGrid *>(Sender)->Canvas->Font->Color = clWhite;
	  dynamic_cast <TDBGrid *>(Sender)->Canvas->Brush->Color = TColor(0x00C07000);
   }
   else
   {
	  if(dynamic_cast <TDBGrid *>(Sender)->DataSource->DataSet->RecNo % 2)
		 dynamic_cast <TDBGrid *>(Sender)->Canvas->Brush->Color = TColor(0x00D9D9D9);
       else
		 dynamic_cast <TDBGrid *>(Sender)->Canvas->Brush->Color = TColor(0x00F2F2F2);
   }
   dynamic_cast <TDBGrid *>(Sender)->DefaultDrawColumnCell(Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------

void __fastcall TfVerHistorialPedidos::FormCreate(TObject *Sender)
{
//   TIniFile *Configuraciones;
//   String Dir = GetCurrentDir()+"//Config.ini";
//   Configuraciones = new TIniFile(Dir);
//
//   SQLConnection1->Params->Values["HostName"] = Configuraciones->ReadString("MySQLServer","Servidor", "127.0.0.1");
//   SQLConnection1->Params->Values["User_Name"] = "elsembrador";
//   SQLConnection1->Params->Values["Password"] = "*-elsembrador63/*";
//
//   delete Configuraciones;

   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------

