//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#include <FileCtrl.hpp>
#pragma hdrstop

#include "uFacturacionMensual.h"
#include "VariablesGlobales.h"
#include "uSeleccionarCliente.h"
#include "uCuentas.h"
#include "uEmitirComprobanteElectronico.h"
#include "uEmitirCompElectMonotributo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfFacturacionMensual *fFacturacionMensual;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfFacturacionMensual::TfFacturacionMensual(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfFacturacionMensual::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}

//---------------------------------------------------------------------------
void TfFacturacionMensual::buscarDatos(String orden)
{
	CDS1->Active = false;
	Query1->Close();
	Query1->SQL->Clear();
	String q;
	q = "SELECT idCliente, CONCAT(calle, ' ', numero) AS cliente, tipo "
		" FROM clientes "
		" WHERE clientes.generarFactura = 1 AND "
		" clientes.idCliente IN "
			" (SELECT refCliente FROM cantidades WHERE fecha >= :fi AND fecha <= :ff GROUP BY refCliente) "
		" ORDER BY " + orden;
	Query1->SQL->Add(q);
	Query1->ParamByName("fi")->AsDate = MC->Date;
	Query1->ParamByName("ff")->AsDate = MC->EndDate;
	Query1->Open();
	CDS1->Active = true;

	ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
}

//---------------------------------------------------------------------------
void __fastcall TfFacturacionMensual::FormShow(TObject *Sender)
{
	_directorioGuararFacturas = "";
	Label3->Caption = "";

	MC->MultiSelect = false;
	MC->Date = Now();
	MC->MultiSelect = true;

	if(DayOfTheMonth(Now()) <= 5)	//si es menos del 5 de este mes, asume que se trabaja sobre el mes anterior
	{
		MC->Date = StartOfTheMonth(IncDay(Now(), -10));      //mes pasado
		MC->EndDate = EndOfTheMonth(IncDay(Now(), -10));     //mes pasado
	}
	else
	{
		MC->Date = StartOfTheMonth(Now());
		MC->EndDate = EndOfTheMonth(Now());
	}

	buscarDatos("cliente");

	EmitirCompMonotributo1->Visible = false;
	DBGrid1->Columns->Items[1]->Visible = false;
	DBGrid1->Columns->Items[0]->Width = 255;

}
//---------------------------------------------------------------------------
void __fastcall TfFacturacionMensual::FormClose(TObject *Sender, TCloseAction &Action)

{
   CDS1->Active = false;
   Query1->Close();
   QueryAux->Close();
   SQLConnection1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfFacturacionMensual::Agregaruncliente1Click(TObject *Sender)
{
   if(!CDS1->Active)
	  return;

   fSeleccionarCliente->llamador = 1;
   fSeleccionarCliente->ShowModal();
   if(fSeleccionarCliente->idSeleccionado <= 2)
	  return;

   QueryAux->Close();
   QueryAux->SQL->Clear();
   String q;
   q = "UPDATE clientes SET generarFactura = 1 WHERE idCliente = :idCliente";
   QueryAux->SQL->Add(q);
   QueryAux->ParamByName("idCliente")->AsInteger = fSeleccionarCliente->idSeleccionado;
   QueryAux->ExecSQL();
   CDS1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfFacturacionMensual::Quitaresteclientedelalista1Click(TObject *Sender)
{
   if(!CDS1->Active || CDS1->IsEmpty())
	  return;

   QueryAux->Close();
   QueryAux->SQL->Clear();
   String q;
   q = "UPDATE clientes SET generarFactura = 0 WHERE idCliente = :idCliente";
   QueryAux->SQL->Add(q);
   QueryAux->ParamByName("idCliente")->AsInteger = CDS1idCliente->AsInteger;
   QueryAux->ExecSQL();
   CDS1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfFacturacionMensual::Verdetalledecuenta1Click(TObject *Sender)
{
   if(CDS1idCliente->AsInteger > 2)
   {
	  fCuentas->idCliente = CDS1idCliente->AsInteger;
	  fCuentas->ShowModal();
   }
}
//---------------------------------------------------------------------------
void __fastcall TfFacturacionMensual::Iraemitircomprobante1Click(TObject *Sender)

{
	fEmitirComprobanteElectronico->Show();
	fEmitirComprobanteElectronico->FDMemTable1->Cancel();
	fEmitirComprobanteElectronico->FDMemTable1->Active = false;
	fEmitirComprobanteElectronico->facturacionMensual = true;
	fEmitirComprobanteElectronico->nombreArchivoFactura = CDS1->FieldByName("cliente")->AsString;
	Memo1->Text = CDS1->FieldByName("cliente")->AsString;
	Memo1->SelectAll();
	Memo1->CopyToClipboard();


	fEmitirComprobanteElectronico->MC->Date = fFacturacionMensual->MC->EndDate;
   fEmitirComprobanteElectronico->mostrarCliente(CDS1idCliente->AsInteger);
   fEmitirComprobanteElectronico->CheckBox1->Checked = true;
   fEmitirComprobanteElectronico->chbFactA4->Checked = true;
   fEmitirComprobanteElectronico->FDMemTable1descripcion->Size = 40;

   fEmitirComprobanteElectronico->directorioGuararFacturas = fFacturacionMensual->_directorioGuararFacturas;


   QueryAux->Close();
   QueryAux->SQL->Clear();
   QueryAux->SQL->Add("SELECT 1.0 AS nroUnidades, CONCAT('Pedido ', DATE_FORMAT(fecha, '%d/%m/%Y')) AS descripcion, valorUnidad AS precioUnitario, valorUnidad AS subtotal FROM cuentas WHERE fecha >= :fi AND fecha <= :ff AND valorUnidad > 0.0 AND refCliente = :refCliente ORDER BY fecha DESC ");
   QueryAux->ParamByName("refCliente")->AsInteger = CDS1idCliente->AsInteger;
   QueryAux->ParamByName("fi")->AsDate = MC->Date;
   QueryAux->ParamByName("ff")->AsDate = MC->EndDate;
   QueryAux->Open();

   QueryAux->First();
   fEmitirComprobanteElectronico->blockCalcular2 = true;
   fEmitirComprobanteElectronico->FDMemTable1->Active = false;
   fEmitirComprobanteElectronico->FDMemTable1->Active = true;
   while (!QueryAux->Eof){

		fEmitirComprobanteElectronico->FDMemTable1->Insert();
		fEmitirComprobanteElectronico->FDMemTable1->FieldByName("nroUnidades")->AsFloat = QueryAux->FieldByName("nroUnidades")->AsFloat;
		fEmitirComprobanteElectronico->FDMemTable1->FieldByName("Descripcion")->AsString = QueryAux->FieldByName("descripcion")->AsString;
		fEmitirComprobanteElectronico->FDMemTable1->FieldByName("precioUnitario")->AsFloat = QueryAux->FieldByName("precioUnitario")->AsFloat;
		fEmitirComprobanteElectronico->FDMemTable1->Post();
		QueryAux->Next();
   }

   QueryAux->Close();
   fEmitirComprobanteElectronico->blockCalcular2 = false;
   fEmitirComprobanteElectronico->calcular2();
}
//---------------------------------------------------------------------------
void __fastcall TfFacturacionMensual::Button1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

void __fastcall TfFacturacionMensual::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Shift.Contains(ssCtrl) && Shift.Contains(ssShift) && Shift.Contains(ssAlt) && Key == VK_F12)
   {
	  EmitirCompMonotributo1->Visible = true;
	  DBGrid1->Columns->Items[1]->Visible = true;
	  DBGrid1->Columns->Items[0]->Width = 202;

	  if(DayOfTheMonth(Now()) <= 5)
	  {
		 MC->Date = StartOfTheMonth(IncDay(Now(), -10));      //mes pasado
		 MC->EndDate = EndOfTheMonth(IncDay(Now(), -10));     //mes pasado
	  }
	  else
	  {
		 MC->Date = StartOfTheMonth(Now());
		 MC->EndDate = EndOfTheMonth(Now());
	  }

	  buscarDatos("tipo");

//	  CDS1->Active = false;
//	  Query1->Close();
//	  Query1->SQL->Clear();
//	  String q;
////	  q = "SELECT idCliente, CONCAT(calle, ' ', numero) AS cliente, tipo FROM clientes WHERE clientes.generarFactura = 1 ORDER BY tipo DESC, cliente";
//	  q = "SELECT idCliente, CONCAT(calle, ' ', numero) AS cliente, tipo "
//	   " FROM clientes "
//	   " WHERE clientes.generarFactura = 1 AND "
//	   " clientes.idCliente IN "
//			" (SELECT refCliente FROM cantidades WHERE fecha >= :fi AND fecha <= :ff GROUP BY refCliente) "
//	   " ORDER BY tipo DESC, cliente";
//
//
//	  Query1->SQL->Add(q);
//	  Query1->ParamByName("fi")->AsDate = MC->Date;
//	  Query1->ParamByName("ff")->AsDate = MC->EndDate;
//	  Query1->Open();
//	  CDS1->Active = true;
   }
}
//---------------------------------------------------------------------------


void __fastcall TfFacturacionMensual::EmitirCompMonotributo1Click(TObject *Sender)

{
   QueryAux->Close();
   QueryAux->SQL->Clear();
   QueryAux->SQL->Add("SELECT SUM(valorUnidad) AS valorTotal FROM cuentas WHERE fecha >= :fi AND fecha <= :ff AND refCliente = :refCliente");
   QueryAux->ParamByName("refCliente")->AsInteger = CDS1idCliente->AsInteger;
   QueryAux->ParamByName("fi")->AsDate = MC->Date;
   QueryAux->ParamByName("ff")->AsDate = MC->EndDate;
   QueryAux->Open();

   QueryAux->First();
   fEmitirCompElectMonotributo->Show();
   fEmitirCompElectMonotributo->MC->Date = fFacturacionMensual->MC->EndDate;
   fEmitirCompElectMonotributo->MC2->MultiSelect = false;
   fEmitirCompElectMonotributo->MC2->Date = fFacturacionMensual->MC->EndDate;
   fEmitirCompElectMonotributo->MC2->MultiSelect = true;
   fEmitirCompElectMonotributo->mostrarCliente(CDS1idCliente->AsInteger);


//   float valor = QueryAux->FieldByName("valorTotal")->AsFloat;

//   int i = 0;
//   bool error = false;
//   while(!QueryAux->Eof)
//   {
//	  //Memo1->Lines->Add(QueryAux->FieldByName("cantidad")->AsString + ", " + QueryAux->FieldByName("valorUnidad")->AsString);
//	  if(i == 0)
//	  {
//		 fEmitirCompElectMonotributo->Edit3->Text = QueryAux->FieldByName("cantidad")->AsString;
//		 fEmitirCompElectMonotributo->Edit5->Text = QueryAux->FieldByName("valorUnidad")->AsString;
//	  }
//	  else if(i == 1)
//	  {
//		 fEmitirCompElectMonotributo->Edit6->Text = QueryAux->FieldByName("cantidad")->AsString;
//		 fEmitirCompElectMonotributo->Edit8->Text = QueryAux->FieldByName("valorUnidad")->AsString;
//	  }
//	  else if(i == 2)
//	  {
//		 fEmitirCompElectMonotributo->Edit9->Text = QueryAux->FieldByName("cantidad")->AsString;
//		 fEmitirCompElectMonotributo->Edit11->Text = QueryAux->FieldByName("valorUnidad")->AsString;
//	  }
//	  else if(i == 3)
//	  {
//		 fEmitirCompElectMonotributo->Edit12->Text = QueryAux->FieldByName("cantidad")->AsString;
//		 fEmitirCompElectMonotributo->Edit14->Text = QueryAux->FieldByName("valorUnidad")->AsString;
//	  }
//	  else if(i == 4)
//	  {
//		 fEmitirCompElectMonotributo->Edit15->Text = QueryAux->FieldByName("cantidad")->AsString;
//		 fEmitirCompElectMonotributo->Edit17->Text = QueryAux->FieldByName("valorUnidad")->AsString;
//	  }
//	  else
//	  {
//		 error = true;
//		 break;
//	  }
//	  QueryAux->Next();
//	  i++;
//   }
//   QueryAux->Close();
//
//   if(error)
//	  ShowMessage("ERROR: Hay mas datos para incluir en la factura pero no hay mas renglones disponibles. Deber� solucionar el inconveniente completando la misma de forma manual");

   //************ADAPTACION PARA NO CAMBIAR TODO***************
   //esto es un parche para que no aparezcan disctrimnados los datos en la factura. Por las dudas.

   float valorTotal = QueryAux->FieldByName("valorTotal")->AsFloat; //StrToFloat(fEmitirCompElectMonotributo->lbTotal->Caption.Delete(1,9));
   fEmitirCompElectMonotributo->Edit3->Text = "1";
   fEmitirCompElectMonotributo->Edit5->Text = FormatFloat("0.00", valorTotal);
   fEmitirCompElectMonotributo->Edit6->Text = "0";
   fEmitirCompElectMonotributo->Edit8->Text = "0";
   fEmitirCompElectMonotributo->Edit9->Text = "0";
   fEmitirCompElectMonotributo->Edit11->Text = "0";
   fEmitirCompElectMonotributo->Edit12->Text = "0";
   fEmitirCompElectMonotributo->Edit14->Text = "0";
   fEmitirCompElectMonotributo->Edit15->Text = "0";
   fEmitirCompElectMonotributo->Edit17->Text = "0";
   fEmitirCompElectMonotributo->Edit6->Enabled = false;
   fEmitirCompElectMonotributo->Edit7->Enabled = false;
   fEmitirCompElectMonotributo->Edit8->Enabled = false;
   fEmitirCompElectMonotributo->Edit9->Enabled = false;
   fEmitirCompElectMonotributo->Edit10->Enabled = false;
   fEmitirCompElectMonotributo->Edit11->Enabled = false;
   fEmitirCompElectMonotributo->Edit12->Enabled = false;
   fEmitirCompElectMonotributo->Edit13->Enabled = false;
   fEmitirCompElectMonotributo->Edit14->Enabled = false;
   fEmitirCompElectMonotributo->Edit15->Enabled = false;
   fEmitirCompElectMonotributo->Edit16->Enabled = false;
   fEmitirCompElectMonotributo->Edit17->Enabled = false;

}
//---------------------------------------------------------------------------

void __fastcall TfFacturacionMensual::CDS1tipoChange(TField *Sender)
{
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE clientes SET tipo = :tipo WHERE idCliente = :idCliente LIMIT 1");
   QueryUpdate->ParamByName("tipo")->AsString = CDS1->FieldByName("tipo")->AsString;
   QueryUpdate->ParamByName("idCliente")->AsInteger = CDS1->FieldByName("idCliente")->AsInteger;
   QueryUpdate->ExecSQL();
}
//---------------------------------------------------------------------------

void __fastcall TfFacturacionMensual::Button2Click(TObject *Sender)
{
   if(SelectDirectory("Directorio para guardar facturas", "", _directorioGuararFacturas) == true)
   {
	  Label3->Caption = _directorioGuararFacturas;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfFacturacionMensual::MCClick(TObject *Sender)
{
	if(DBGrid1->Columns->Items[1]->Visible)
		buscarDatos("tipo");
	else
		buscarDatos("cliente");
}
//---------------------------------------------------------------------------

void __fastcall TfFacturacionMensual::DBGrid1DblClick(TObject *Sender)
{
	if (CDS1->FieldByName("tipo")->AsString == "O") {
      Iraemitircomprobante1Click(Sender);
	}
}
//---------------------------------------------------------------------------

