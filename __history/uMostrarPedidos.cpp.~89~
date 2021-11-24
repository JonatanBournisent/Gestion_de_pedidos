//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uMostrarPedidos.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfMostrarPedidos *fMostrarPedidos;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfMostrarPedidos::TfMostrarPedidos(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfMostrarPedidos::DTPChange(TObject *Sender)
{
         CBE->Visible = false;
		 CBC->Visible = false;
		 String q1;
		 q1 = "SELECT idPedido, TIME(momento) AS hora, comentario, etiquetaImpresa, complementoImpreso, "
		      "(SELECT CONCAT(calle, ' ', numero) FROM clientes WHERE pedidos.refCliente = clientes.idCliente LIMIT 1) AS cliente, "
			  "(SELECT IF(codigo = :una, '1', IF(codigo = :ens, 'ENS', codigo)) FROM comidas WHERE refComida1 = idComida LIMIT 1) AS com1, "
			  "(SELECT IF(codigo = :una, '1', IF(codigo = :ens, 'ENS', codigo)) FROM comidas WHERE refComida2 = idComida LIMIT 1) AS com2, "
			  "(SELECT IF(codigo = :una, '1', IF(codigo = :ens, 'ENS', codigo)) FROM comidas WHERE refComida3 = idComida LIMIT 1) AS com3, "
			  "(SELECT IF(codigo = :una, '1', IF(codigo = :ens, 'ENS', codigo)) FROM comidas WHERE refComida4 = idComida LIMIT 1) AS com4 "
			  "FROM pedidos WHERE DATE(momento) = :d ORDER BY momento DESC";

		 CDS2->Active = false;
		 QueryPedidos->Close();
		 QueryPedidos->SQL->Clear();
		 QueryPedidos->SQL->Add(q1);
		 QueryPedidos->ParamByName("d")->AsDate = DTP->Date;
		 QueryPedidos->ParamByName("una")->AsString = una;
		 QueryPedidos->ParamByName("ens")->AsString = ens;
		 QueryPedidos->Open();

		 if(QueryPedidos->IsEmpty())
		 {
            CDS2->Active = false;
			QueryPedidos->Close();
			CBE->Visible = false;
			CBC->Visible = false;
			return;
		 }
		 CDS2->Active = true;

         ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
}
//---------------------------------------------------------------------------
void __fastcall TfMostrarPedidos::FormShow(TObject *Sender)
{
   DTPChange(fMostrarPedidos);
}
//---------------------------------------------------------------------------
void __fastcall TfMostrarPedidos::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
   int DrawState;
   if(State.Contains(gdFocused))
   {
	  if(Column->Field == CBE->Field)
      {
		 CBE->Left = Rect.Left + DBGrid1->Left + 2;
		 CBE->Top = Rect.Top + DBGrid1->Top + 2;
		 CBE->Width = Rect.Right - Rect.Left;
		 CBE->Height = Rect.Bottom - Rect.Top;

		 CBE->Visible = true;
	  }
	  else if(Column->Field == CBC->Field)
	  {
		 CBC->Left = Rect.Left + DBGrid1->Left + 2;
		 CBC->Top = Rect.Top + DBGrid1->Top + 2;
		 CBC->Width = Rect.Right - Rect.Left;
		 CBC->Height = Rect.Bottom - Rect.Top;

		 CBC->Visible = true;
	  }
   }
   else if(Column->Field == CBE->Field || Column->Field == CBC->Field)
   {
      DrawRect = new TRect(Rect);
	  InflateRect(DrawRect,-1,-1);

	  if(Column->Field->AsInteger == 0)
         DrawState = DFCS_BUTTONCHECK;
	  else
         DrawState = DFCS_BUTTONCHECK | DFCS_CHECKED;

	  DBGrid1->Canvas->FillRect(Rect);
	  DrawFrameControl(DBGrid1->Canvas->Handle , DrawRect, DFC_BUTTON, DrawState);
      delete DrawRect;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarPedidos::DBGrid1ColExit(TObject *Sender)
{
   if(DBGrid1->SelectedField == CBC->Field)
	  CBC->Visible = false;
   else if(DBGrid1->SelectedField == CBE->Field)
	  CBE->Visible = false;

   if(CDS2->Active && CDS2->State == dsEdit)
	  CDS2->Post();
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarPedidos::CDS2etiquetaImpresaChange(TField *Sender)
{
   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE pedidos SET etiquetaImpresa = :etiquetaImpresa WHERE idPedido = :idPedido LIMIT 1");
   QueryUpdate->ParamByName("etiquetaImpresa")->AsInteger = Sender->AsInteger;
   QueryUpdate->ParamByName("idPedido")->AsInteger = CDS2->FieldByName("idPedido")->AsInteger;
   QueryUpdate->ExecSQL();
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarPedidos::CDS2complementoImpresoChange(TField *Sender)
{
   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE pedidos SET complementoImpreso = :complementoImpreso WHERE idPedido = :idPedido LIMIT 1");
   QueryUpdate->ParamByName("complementoImpreso")->AsInteger = Sender->AsInteger;
   QueryUpdate->ParamByName("idPedido")->AsInteger = CDS2->FieldByName("idPedido")->AsInteger;
   QueryUpdate->ExecSQL();
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarPedidos::FormClose(TObject *Sender, TCloseAction &Action)

{
   CDS2->Active = false;
   QueryPedidos->Close();

   SQLConnection1->Close();
}
//---------------------------------------------------------------------------





void __fastcall TfMostrarPedidos::FormCreate(TObject *Sender)
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

void __fastcall TfMostrarPedidos::Marcarcomoimpreso3Click(TObject *Sender)
{
   if(Application->MessageBox(L"Se van a marcar todas las etiquetas de complementos como impresas. Desea continuar?",L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
	  return;

   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE pedidos SET complementoImpreso = 1 WHERE DATE(momento) = DATE(:fecha)");
   QueryUpdate->ParamByName("fecha")->AsDateTime = DTP->DateTime;
   QueryUpdate->ExecSQL();

   CDS2->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarPedidos::Marcarcomonoimpreso3Click(TObject *Sender)
{
   if(Application->MessageBox(L"Se van a marcar todas las etiquetas de complementos como no impresas. Desea continuar?",L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
	  return;

   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE pedidos SET complementoImpreso = 0 WHERE DATE(momento) = DATE(:fecha)");
   QueryUpdate->ParamByName("fecha")->AsDateTime = DTP->DateTime;
   QueryUpdate->ExecSQL();

   CDS2->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarPedidos::Marcarcomoimpreso1Click(TObject *Sender)
{
   if(Application->MessageBox(L"Se van a marcar todas las etiquetas de pedidos del primer reparto como impresas. Desea continuar?",L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
	  return;

   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE pedidos SET etiquetaImpresa = 1 WHERE (DATE(momento) = DATE(:fecha) "
						 "AND (SELECT sectorReparto FROM cantidades WHERE (pedidos.refCantidad = cantidades.idCantidad) LIMIT 1) = 0)");
   QueryUpdate->ParamByName("fecha")->AsDateTime = DTP->DateTime;
   QueryUpdate->ExecSQL();

   CDS2->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarPedidos::Marcarcomoimpreso2Click(TObject *Sender)
{
   if(Application->MessageBox(L"Se van a marcar todas las etiquetas de pedidos del segundo reparto como impresas. Desea continuar?",L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
	  return;

   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE pedidos SET etiquetaImpresa = 1 WHERE (DATE(momento) = DATE(:fecha) "
						 "AND (SELECT sectorReparto FROM cantidades WHERE (pedidos.refCantidad = cantidades.idCantidad) LIMIT 1) = 1)");
   QueryUpdate->ParamByName("fecha")->AsDateTime = DTP->DateTime;
   QueryUpdate->ExecSQL();

   CDS2->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarPedidos::Marcarcomonoimpreso1Click(TObject *Sender)
{
   if(Application->MessageBox(L"Se van a marcar todas las etiquetas de pedidos del primer reparto como no impresas. Desea continuar?",L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
	  return;

   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE pedidos SET etiquetaImpresa = 0 WHERE (DATE(momento) = DATE(:fecha) "
						 "AND (SELECT sectorReparto FROM cantidades WHERE (pedidos.refCantidad = cantidades.idCantidad) LIMIT 1) = 0)");
   QueryUpdate->ParamByName("fecha")->AsDateTime = DTP->DateTime;
   QueryUpdate->ExecSQL();

   CDS2->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarPedidos::Marcarcomonoimpreso2Click(TObject *Sender)
{
   if(Application->MessageBox(L"Se van a marcar todas las etiquetas de pedidos del segundo reparto como no impresas. Desea continuar?",L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
	  return;

   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("UPDATE pedidos SET etiquetaImpresa = 0 WHERE (DATE(momento) = DATE(:fecha) "
						 "AND (SELECT sectorReparto FROM cantidades WHERE (pedidos.refCantidad = cantidades.idCantidad) LIMIT 1) = 1)");
   QueryUpdate->ParamByName("fecha")->AsDateTime = DTP->DateTime;
   QueryUpdate->ExecSQL();

   CDS2->Refresh();
}
//---------------------------------------------------------------------------


