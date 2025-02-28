//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uVerComprobantesElectronicos.h"
#include "VariablesGlobales.h"
#include "uSeleccionarCliente.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfVerComprobantesElectronicos *fVerComprobantesElectronicos;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfVerComprobantesElectronicos::TfVerComprobantesElectronicos(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfVerComprobantesElectronicos::DBGrid1DrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State)

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

void __fastcall TfVerComprobantesElectronicos::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------
void __fastcall TfVerComprobantesElectronicos::FormShow(TObject *Sender)
{
   omitir = true;
   Edit1->Clear();
   CDS1->Active = false;
   Query1->Close();
   Query1->SQL->Clear();
   String q;
   q = "SELECT idComprobanteElectronico, IF(cuitCliente = '00000000000', '-', cuitCliente) AS cuitCliente, fecha, netoGravado, iva21, total, "
	   "(SELECT CONCAT(calle, ' ', numero) FROM clientes WHERE comprobantesElectronicos.refCliente = clientes.idCliente LIMIT 1) AS cliente, "
	   "(SELECT descripcion FROM condicionesFrenteIVA WHERE comprobantesElectronicos.refCondicionFrenteIVA = condicionesFrenteIVA.idCondicionFrenteIVA LIMIT 1) AS cfIVA, "
	   "(SELECT ELT(refTipoComp, 'Factura A', 'Nota de D�bito A', 'Nota de Cr�dito A', '','','Factura B', 'Nota de D�bito B', 'Nota de Cr�dito B')) AS tipoComp, "
	   "(SELECT CONCAT(LPAD(ptoVenta,5,'0'),'-',LPAD(nroComprobante,8,'0'))) AS nroComp "
	   "FROM comprobantesElectronicos ORDER BY idComprobanteElectronico DESC LIMIT 50";

   Query1->SQL->Add(q);
//   Query1->ParamByName("refCliente")->AsInteger = idCliente;

   Query1->Open();

   if(Query1->IsEmpty())
   {
	  Query1->Close();
	  return;
   }

   CDS1->Active = true;
   MC1->Enabled = true;
   Button1->Enabled = true;

   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
}
//---------------------------------------------------------------------------
void __fastcall TfVerComprobantesElectronicos::Edit1Change(TObject *Sender)
{
   if(omitir)
   {
	  omitir = false;
	  return;
   }
   if(Edit1->Text.Length() == 0)
   {
       CDS1->Active = false;
	   Query1->Close();
	   Query1->SQL->Clear();
	   String q;
	   q = "SELECT idComprobanteElectronico, IF(cuitCliente = '00000000000', '-', cuitCliente) AS cuitCliente, fecha, netoGravado, iva21, total, "
	   "(SELECT CONCAT(calle, ' ', numero) FROM clientes WHERE comprobantesElectronicos.refCliente = clientes.idCliente LIMIT 1) AS cliente, "
	   "(SELECT descripcion FROM condicionesFrenteIVA WHERE comprobantesElectronicos.refCondicionFrenteIVA = condicionesFrenteIVA.idCondicionFrenteIVA LIMIT 1) AS cfIVA, "
	   "(SELECT ELT(refTipoComp, 'Factura A', 'Nota de D�bito A', 'Nota de Cr�dito A', '','','Factura B', 'Nota de D�bito B', 'Nota de Cr�dito B')) AS tipoComp, "
	   "(SELECT CONCAT(LPAD(ptoVenta,5,'0'),'-',LPAD(nroComprobante,8,'0'))) AS nroComp "
	   "FROM comprobantesElectronicos ORDER BY idComprobanteElectronico DESC LIMIT 50";

	   Query1->SQL->Add(q);
	   Query1->Open();

	   if(Query1->IsEmpty())
	   {
		  Query1->Close();
		  return;
	   }

	   CDS1->Active = true;

	   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);

	   MC1->Enabled = true;
	   Button1->Enabled = true;

   }
   else
   {
	   CDS1->Active = false;
	   Query1->Close();
	   Query1->SQL->Clear();
	   String q;
	   q = "SELECT idComprobanteElectronico, nroComprobante, IF(cuitCliente = '00000000000', '-', cuitCliente) AS cuitCliente, fecha, netoGravado, iva21, total, "
	   "(SELECT CONCAT(calle, ' ', numero) FROM clientes WHERE comprobantesElectronicos.refCliente = clientes.idCliente LIMIT 1) AS cliente, "
	   "(SELECT descripcion FROM condicionesFrenteIVA WHERE comprobantesElectronicos.refCondicionFrenteIVA = condicionesFrenteIVA.idCondicionFrenteIVA LIMIT 1) AS cfIVA, "
	   "(SELECT ELT(refTipoComp, 'Factura A', 'Nota de D�bito A', 'Nota de Cr�dito A', '','','Factura B', 'Nota de D�bito B', 'Nota de Cr�dito B')) AS tipoComp, "
	   "(SELECT CONCAT(LPAD(ptoVenta,5,'0'),'-',LPAD(nroComprobante,8,'0'))) AS nroComp "
	   "FROM comprobantesElectronicos WHERE nroComprobante = :nroComprobante ORDER BY idComprobanteElectronico DESC LIMIT 50";

	   Query1->SQL->Add(q);
	   Query1->ParamByName("nroComprobante")->AsInteger = StrToInt(Edit1->Text);

	   Query1->Open();

	   if(Query1->IsEmpty())
	   {
		  Query1->Close();
		  return;
	   }

	   CDS1->Active = true;

	   MC1->Enabled = false;
	   Button1->Enabled = false;

	   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
   }
}
//---------------------------------------------------------------------------
void __fastcall TfVerComprobantesElectronicos::MC1Click(TObject *Sender)
{
   CDS1->Active = false;
   Query1->Close();
   Query1->SQL->Clear();
   String q;
   q = "SELECT idComprobanteElectronico, IF(cuitCliente = '00000000000', '-', cuitCliente) AS cuitCliente, fecha, netoGravado, iva21, total, "
	   "(SELECT CONCAT(calle, ' ', numero) FROM clientes WHERE comprobantesElectronicos.refCliente = clientes.idCliente LIMIT 1) AS cliente, "
	   "(SELECT descripcion FROM condicionesFrenteIVA WHERE comprobantesElectronicos.refCondicionFrenteIVA = condicionesFrenteIVA.idCondicionFrenteIVA LIMIT 1) AS cfIVA, "
	   "(SELECT ELT(refTipoComp, 'Factura A', 'Nota de D�bito A', 'Nota de Cr�dito A', '','','Factura B', 'Nota de D�bito B', 'Nota de Cr�dito B')) AS tipoComp, "
	   "(SELECT CONCAT(LPAD(ptoVenta,5,'0'),'-',LPAD(nroComprobante,8,'0'))) AS nroComp "
	   "FROM comprobantesElectronicos WHERE fecha = :fecha ORDER BY idComprobanteElectronico DESC LIMIT 50";

   Query1->SQL->Add(q);
   Query1->ParamByName("fecha")->AsDate = MC1->Date;

   Query1->Open();

   if(Query1->IsEmpty())
   {
	  Query1->Close();
	  return;
   }
   omitir = true;
   Edit1->Clear();
   MC1->Date = Now();

   CDS1->Active = true;

   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
}
//---------------------------------------------------------------------------

void __fastcall TfVerComprobantesElectronicos::Button1Click(TObject *Sender)
{
   fSeleccionarCliente->llamador = 1;
   fSeleccionarCliente->ShowModal();
   if(fSeleccionarCliente->idSeleccionado <= 2)
	  return;

   CDS1->Active = false;
   Query1->Close();
   Query1->SQL->Clear();
   String q;
	  q = "SELECT idComprobanteElectronico, refCliente, IF(cuitCliente = '00000000000', '-', cuitCliente) AS cuitCliente, fecha, netoGravado, iva21, total, "
	   "(SELECT CONCAT(calle, ' ', numero) FROM clientes WHERE comprobantesElectronicos.refCliente = clientes.idCliente LIMIT 1) AS cliente, "
	   "(SELECT descripcion FROM condicionesFrenteIVA WHERE comprobantesElectronicos.refCondicionFrenteIVA = condicionesFrenteIVA.idCondicionFrenteIVA LIMIT 1) AS cfIVA, "
	   "(SELECT ELT(refTipoComp, 'Factura A', 'Nota de D�bito A', 'Nota de Cr�dito A', '','','Factura B', 'Nota de D�bito B', 'Nota de Cr�dito B')) AS tipoComp, "
	   "(SELECT CONCAT(LPAD(ptoVenta,5,'0'),'-',LPAD(nroComprobante,8,'0'))) AS nroComp "
	   "FROM comprobantesElectronicos WHERE refCliente = :refCliente ORDER BY idComprobanteElectronico DESC LIMIT 50";

   Query1->SQL->Add(q);
   Query1->ParamByName("refCliente")->AsInteger = fSeleccionarCliente->idSeleccionado;

   Query1->Open();

   if(Query1->IsEmpty())
   {
	  Query1->Close();
	  return;
   }

   omitir = true;
   Edit1->Clear();
   MC1->Date = Now();

   CDS1->Active = true;

   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
}
//---------------------------------------------------------------------------
void __fastcall TfVerComprobantesElectronicos::Button2Click(TObject *Sender)
{
   FormShow(Button1);
}
//---------------------------------------------------------------------------
void __fastcall TfVerComprobantesElectronicos::Edit1KeyPress(TObject *Sender, System::WideChar &Key)

{
   if((Key < '0' || Key > '9') && Key != '\b')
      Key = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfVerComprobantesElectronicos::Button3Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TfVerComprobantesElectronicos::DBGrid1DblClick(TObject *Sender)
{
   TIniFile *Configuraciones;
   String Dir = GetCurrentDir() + "//Config.ini";
   Configuraciones = new TIniFile(Dir);
   String path = Configuraciones->ReadString("Directorios","Facturas", "NO_CONFIGURADA");
   delete Configuraciones;

   String nroComp = CDS1->FieldByName("nroComp")->AsString;


   path = path + "\\" + CDS1->FieldByName("tipoComp")->AsString + nroComp + ".pdf";


   if (FileExists(path))
   {
	  ShellExecuteA(Handle, "open", AnsiString(path).c_str(), NULL, NULL, SW_SHOWNORMAL);
   }
   else
   {
	  Application->MessageBox(L"Lamentablemente el archivo que buscamos ya no existe... :(" ,L"El archivo no existe",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
   }
}
//---------------------------------------------------------------------------

