//---------------------------------------------------------------------------

#include <vcl.h>
#include <Clipbrd.hpp>
#pragma hdrstop

#include "uImportarPagosBancos.h"
#include "VariablesGlobales.h"
#include "uCuentas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfImportarPagosBancos *fImportarPagosBancos;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfImportarPagosBancos::TfImportarPagosBancos(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfImportarPagosBancos::FormClose(TObject *Sender, TCloseAction &Action)

{
   FDMemTable1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfImportarPagosBancos::DBGrid1DblClick(TObject *Sender)
{
   int idCli = FDMemTable1->FieldByName("idCliente")->AsInteger;
   if(idCli < 3)
	  return;

   fCuentas->idCliente = idCli;
   fCuentas->FormShow(fCuentas->Label1);
}
//---------------------------------------------------------------------------

void __fastcall TfImportarPagosBancos::Button1Click(TObject *Sender)
{
   try {
	   TStringList *infoBanco = new TStringList();
	   TStringList *cliente = new TStringList();
	   TStringList *direccionCliente = new TStringList();
	   TStringList *pago = new TStringList();
	   TStringList *fecha = new TStringList();

	   TClipboard *cb;
	   cb = new TClipboard();
	   infoBanco->Text = cb->AsText;
	   delete cb;

	   int p;
	   for (int i = 0; i < infoBanco->Count; i++) {
		   while (infoBanco->Strings[i].Pos('\t')){
				p = infoBanco->Strings[i].Pos('\t');
				infoBanco->Strings[i] = infoBanco->Strings[i].Delete(p,1);
				infoBanco->Strings[i] = infoBanco->Strings[i].Insert(";",p);
		   }
	   }

	   QueryAux->Close();
	   QueryAux->SQL->Clear();
	   QueryAux->SQL->Add("SELECT idCliente, RPAD(CONCAT(calle, ' ',numero), 30, ' ') AS nombre, nombreBanco1, nombreBanco2, nombreBanco3 FROM clientes");
	   QueryAux->Open();

	   TStringList *nombresBancos1 = new TStringList();
	   TStringList *nombresBancos2 = new TStringList();
	   TStringList *nombresBancos3 = new TStringList();
	   TStringList *idClientes = new TStringList();
	   TStringList *nombreCliente = new TStringList();

	   String nb1;
	   String dato;
	   while(!QueryAux->Eof)
	   {
		  idClientes->Add(QueryAux->FieldByName("idCliente")->AsString);
		  nombreCliente->Add(QueryAux->FieldByName("nombre")->AsString);
	//	  nombresBancos1->Add(QueryAux->FieldByName("nombreBanco1")->AsString);
		  nb1 = QueryAux->FieldByName("nombreBanco1")->AsString;
		  p = nb1.Pos("|");
		  if (p > 0) {
			 while (p > 0) {
				dato = nb1.SubString(1,p-1);
				idClientes->Add(QueryAux->FieldByName("idCliente")->AsString);
				nombreCliente->Add(QueryAux->FieldByName("nombre")->AsString);
				nombresBancos1->Add(dato);
				nombresBancos2->Add(QueryAux->FieldByName("nombreBanco2")->AsString);
				nombresBancos3->Add(QueryAux->FieldByName("nombreBanco3")->AsString);
				nb1 = nb1.Delete(1,p);

				p = nb1.Pos("|");
			 }
			 nombresBancos1->Add(nb1);
			 nombresBancos2->Add(QueryAux->FieldByName("nombreBanco2")->AsString);
			 nombresBancos3->Add(QueryAux->FieldByName("nombreBanco3")->AsString);

		  }
		  else {
			 nombresBancos1->Add(QueryAux->FieldByName("nombreBanco1")->AsString);
			 nombresBancos2->Add(QueryAux->FieldByName("nombreBanco2")->AsString);
			 nombresBancos3->Add(QueryAux->FieldByName("nombreBanco3")->AsString);
		  }
		  QueryAux->Next();
	   }
	   QueryAux->Close();

	   //fechaPago = TDate();
	   //int idCliente = 0;
	   //valorPago = 0.0

	   String strFecha, strPago, strCliente, strNombreCliente, s, infoCliente;


	   FDMemTable1->Close();
	   FDMemTable1->Open();

	   bool flag;
	   for (int i = 0; i < infoBanco->Count; i++)
	   {
			flag = false;
			s = infoBanco->Strings[i];
			strFecha = s.SubString(1, s.Pos(";")-1);
			s = s.Delete(1,s.Pos(";"));
			s = s.Delete(1,s.Pos(";"));
			infoCliente = s.SubString(1, s.Pos(";")-1);
			s = s.Delete(1,s.Pos(";"));
			strPago = s.SubString(1, s.Pos(";")-1);

			while(strPago.Pos("$") > 0)
			strPago = strPago.Delete(strPago.Pos("$"), 1);

			while(strPago.Pos(" ") > 0)
			strPago = strPago.Delete(strPago.Pos(" "), 1);

			while(strPago.Pos(".") > 0)
			strPago = strPago.Delete(strPago.Pos("."), 1);

		  if((StrToFloat(strPago) < 0.1))
			 continue;


		  for (int j = 0; j < nombresBancos1->Count; j++)
		  {
			 bool isOK1 = nombresBancos1->Strings[j] != "";
			 bool isOK2 = nombresBancos2->Strings[j] != "";
			 bool isOK3 = nombresBancos3->Strings[j] != "";




			 s = infoBanco->Strings[i];
			 if ((infoCliente.Pos(nombresBancos1->Strings[j]) > 0 && isOK1) ||
				 (infoCliente.Pos(nombresBancos2->Strings[j]) > 0 && isOK2) ||
				 (infoCliente.Pos(nombresBancos3->Strings[j]) > 0 && isOK3))
			 {
				 strCliente = idClientes->Strings[j];
				 strNombreCliente = nombreCliente->Strings[j];
				 strFecha = s.SubString(1, s.Pos(";")-1);
				 s = s.Delete(1,s.Pos(";"));
				 s = s.Delete(1,s.Pos(";"));
				 s = s.Delete(1,s.Pos(";"));
				 strPago = s.SubString(1, s.Pos(";")-1);

				 while(strPago.Pos("$") > 0)
					strPago = strPago.Delete(strPago.Pos("$"), 1);

				 while(strPago.Pos(" ") > 0)
					strPago = strPago.Delete(strPago.Pos(" "), 1);

				 while(strPago.Pos(".") > 0)
					strPago = strPago.Delete(strPago.Pos("."), 1);

				 cliente->Add(strCliente);
				 direccionCliente->Add(strNombreCliente);
				 pago->Add(strPago);
				 fecha->Add(strFecha);

				 flag = true;
				 break;
			 }
		  }

		  if (!flag && (StrToFloat(strPago) > 0.1))
		  {
			 cliente->Add("0");
			 direccionCliente->Add(infoCliente);
			 pago->Add(strPago);
			 fecha->Add(strFecha);
		  }
	   }



	   for(int i = 0; i<cliente->Count; i++)
	   {
		  FDMemTable1->Append();
		  FDMemTable1->FieldByName("fecha")->AsDateTime = StrToDate(fecha->Strings[i]);
		  FDMemTable1->FieldByName("cliente")->AsString = direccionCliente->Strings[i];
		  FDMemTable1->FieldByName("valor")->AsString = pago->Strings[i];
		  FDMemTable1->FieldByName("idCliente")->AsString = cliente->Strings[i];
		  FDMemTable1->Post();
	   }


	   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);

	   delete infoBanco;
	   delete nombresBancos1;
	   delete nombresBancos2;
	   delete nombresBancos3;
	   delete idClientes;
	   delete cliente;
	   delete direccionCliente;
	   delete nombreCliente;
	   delete pago;
	   delete fecha;    
   } catch (...) {
   	   Beep();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfImportarPagosBancos::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------

void __fastcall TfImportarPagosBancos::DBGrid1KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '\x16')
	  Button1Click(Sender);
}
//---------------------------------------------------------------------------

