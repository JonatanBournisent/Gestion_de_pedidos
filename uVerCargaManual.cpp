//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "uVerCargaManual.h"
#include "uVerHistorialPedidos.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfVerCargaManual *fVerCargaManual;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfVerCargaManual::TfVerCargaManual(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfVerCargaManual::FormShow(TObject *Sender)
{
   ClientDataSet3->Active = false;
   QueryCantidad->Close();
   QueryCantidad->SQL->Clear();
   String q;

   q = "SELECT idCantidad, refCliente, medioPago, nroBandejas AS bandGrand, nroUnidades AS cantViandas, txtComplemento AS complemento, (sectorReparto + 1) AS reparto, "
	   "(SELECT descripcion FROM repartidores WHERE repartidores.idRepartidor = cantidades.refRepartidor LIMIT 1) AS repartidor, "
	   "(SELECT CONCAT(calle, ' ' ,numero) FROM clientes WHERE clientes.idCliente = cantidades.refCliente LIMIT 1) AS cliente, "
	   "(SELECT GROUP_CONCAT(DISTINCT comentario SEPARATOR ' & ') FROM pedidos WHERE refCantidad = cantidades.idCantidad) AS comentarios, "

	   "(SELECT pagoAdelantado FROM clientes WHERE refCliente = idCliente LIMIT 1) AS pagoAdelantado, "
	   "(SELECT refFrecuenciaPago FROM clientes WHERE cantidades.refCliente = idCliente LIMIT 1) AS frecuenciaPago, "
	   "(SELECT refDiaPago FROM clientes WHERE cantidades.refCliente = idCliente LIMIT 1) AS diaPago, "

	   "(SELECT valor "
				"FROM listasPrecio WHERE "
					"(SELECT refListaPrecio FROM clientes WHERE clientes.idCliente = refCliente LIMIT 1) = idListaPrecio LIMIT 1) * (SELECT ((100.0 - bonificacion) / 100.0) FROM clientes WHERE clientes.idCliente = refCliente LIMIT 1) * nroUnidades + (SELECT (acumuladoGlobal) AS acumGlobal FROM clientes WHERE refCliente = idCliente LIMIT 1) "
	   "AS var_dummy, "

	   "(SELECT (acumuladoGlobal - acumuladoParcial) AS deuda FROM clientes WHERE refCliente = idCliente LIMIT 1) AS deuda "

	   "FROM cantidades WHERE cargaManual = 1 AND fecha = :fecha "
	   "ORDER BY repartidor, reparto";


   QueryCantidad->SQL->Add(q);
   QueryCantidad->ParamByName("fecha")->AsDate = MC->Date;
   QueryCantidad->Open();
   ClientDataSet3->Active = true;

   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
}
//---------------------------------------------------------------------------
void __fastcall TfVerCargaManual::FormClose(TObject *Sender, TCloseAction &Action)

{
   ClientDataSet3->Active = false;
   QueryCantidad->Close();
   SQLConnection1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfVerCargaManual::Button1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TfVerCargaManual::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
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

void __fastcall TfVerCargaManual::DBGrid1DblClick(TObject *Sender)
{
   fVerHistorialPedidos->idCliente = ClientDataSet3->FieldByName("refCliente")->AsInteger;
   fVerHistorialPedidos->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfVerCargaManual::FormCreate(TObject *Sender)
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

void __fastcall TfVerCargaManual::ClientDataSet3comentariosGetText(TField *Sender,
          UnicodeString &Text, bool DisplayText)
{
   if(Sender->AsString.Pos(" / ") == 1)
   {
	  Text = Sender->AsString.SubString(3,Sender->AsString.Length() - 3);
   }
   else
	  Text = Sender->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TfVerCargaManual::ClientDataSet3var_dummyGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
   if(Sender->AsFloat < 0.0)
   {
	  Text = "NO";
	  return;
   }
   if(Sender->DataSet->FieldByName("medioPago")->AsString != "A")
   {
	  Text = "NO";
	  return;
   }
   if(Sender->DataSet->FieldByName("frecuenciaPago")->AsInteger == 1)
   {
	  Text = "$" + Sender->AsString;
	  return;
   }
   if(Sender->DataSet->FieldByName("frecuenciaPago")->AsInteger == 2)
   {
	   if(DayOfTheWeek(MC->Date) == Sender->DataSet->FieldByName("diaPago")->AsInteger)
	   {
		  if(Sender->DataSet->FieldByName("pagoAdelantado")->AsString == "S")
		  {
			 Text = "???";
			 return;
		  }

		  Text = "$" + Sender->AsString;
		  return;
	   }
	   if(Sender->DataSet->FieldByName("diaPago")->AsInteger == 5)
	   {
		  Text = "$" + Sender->AsString;
		  return;
	   }
	   if(Sender->DataSet->FieldByName("diaPago")->AsInteger == 6)
	   {
		  Text = "$" + Sender->AsString;
		  return;
	   }
	   if(Sender->DataSet->FieldByName("deuda")->AsFloat > 0.0)
	   {
		  Text = "$" + Sender->DataSet->FieldByName("deuda")->AsString;
		  return;
	   }
	   Text = "NO";
	   return;
   }
   if(Sender->DataSet->FieldByName("frecuenciaPago")->AsInteger == 3)
   {
	   if(Sender->DataSet->FieldByName("deuda")->AsFloat > 0.0)
	   {
		  Text = "$" + Sender->AsString;
		  return;
	   }
	   if(Sender->DataSet->FieldByName("deuda")->AsFloat > 0.0)
	   {
		  Text = "$" + Sender->DataSet->FieldByName("deuda")->AsString;
		  return;
	   }
	   Text = "NO";
	   return;
   }
}
//---------------------------------------------------------------------------

