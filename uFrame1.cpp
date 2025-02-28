//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "uFrame1.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrame1 *Frame1;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TFrame1::TFrame1(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
bool TFrame1::guardar(void)
{
   if(!cuitOK)
	  return false;

   if(!modificando)
   {
	   QueryAux->Close();
	   QueryAux->SQL->Clear();
	   QueryAux->SQL->Add("SELECT idCliente FROM clientes WHERE calle = :calle AND numero = :numero LIMIT 1");
	   QueryAux->ParamByName("calle")->AsString = DBEdCalle->Text;
	   QueryAux->ParamByName("numero")->AsString = DBEdNumero->Text;
	   QueryAux->Open();
	   if(!QueryAux->IsEmpty())
	   {
		  QueryAux->Close();
		  Application->MessageBox(L"Ya existe un cliente con el mismo domicilio. Si necesita agregarlo de todos modos puede a�adir una distinci�n en el n�mero." ,L"No se realizaron cambios",MB_OK | MB_ICONERROR| MB_DEFBUTTON1);
		  return false;
	   }
	   QueryAux->Close();

	   QueryAux->Close();
	   QueryAux->SQL->Clear();
	   QueryAux->SQL->Add("SELECT idCliente FROM clientes WHERE numero = :numero LIMIT 1");
	   QueryAux->ParamByName("numero")->AsString = DBEdNumero->Text;
	   QueryAux->Open();
	   if(!QueryAux->IsEmpty())
	   {
		  QueryAux->Close();
		  Application->MessageBox(L"Ya existe un domicilio con el mismo n�mero. Para evitar ambig�edades por favor agregue una distinci�n al mismo" ,L"No se realizaron cambios",MB_OK | MB_ICONERROR| MB_DEFBUTTON1);
		  return false;
	   }
	   QueryAux->Close();
   }

   if(llamador == 1)
   {
	  ClientDataSet1->FieldByName("idCliente")->AsInteger = 0;
	  ClientDataSet1->FieldByName("saldo")->AsFloat = 0.0;
	  ClientDataSet1->FieldByName("tipo")->AsString = CBFacturar->Text;
	  ClientDataSet1->FieldByName("medioPagoDefecto")->AsString = CBmp->Text.SubString(1,1);
	  ClientDataSet1->FieldByName("esVisible")->AsInteger = 0;
	  ClientDataSet1->FieldByName("acumuladoGlobal")->AsFloat = 0.0;
	  ClientDataSet1->FieldByName("acumuladoParcial")->AsFloat = 0.0;
	}
	ClientDataSet1->FieldByName("refCondicionFrenteIVA")->AsInteger = CBCondicionFrenteIVA->ItemIndex + 1;
   ClientDataSet1->ApplyUpdates(0);


	if(modificando)
	{
	  QueryUpdate->SQL->Clear();
	  QueryUpdate->SQL->Add("CALL calcularSaldoCliente(:f1, :f2, :fref , :refCliente)");
	  QueryUpdate->ParamByName("f1")->AsDateTime = IncDay(StartOfTheWeek(Now()),-1);
	  QueryUpdate->ParamByName("f2")->AsDateTime = IncDay(StartOfTheMonth(Now()),-1);
	  QueryUpdate->ParamByName("fref")->AsDateTime = DateOf(IncYear(Now(), -10));
	  QueryUpdate->ParamByName("refCliente")->AsInteger = id;
	  QueryUpdate->ExecSQL();
   }
   modificando = false;
   CBCondicionFrenteIVA->ItemIndex = -1;
   return true;
}
//---------------------------------------------------------------------------
void TFrame1::cancelar(void)
{
   blockDBEdit = true;
   modificando = false;
   ClientDataSet1->Cancel();
   CBCondicionFrenteIVA->ItemIndex = -1;
   blockDBEdit = false;
}
//---------------------------------------------------------------------------
void __fastcall TFrame1::DBEdNombreChange(TObject *Sender)
{
   if(blockDBEdit)
	  return;

   if(!DBEdCalle->Focused())
   {
	  if(DBEdNombre->Text != "")
	  {
		 ClientDataSet4->Active = false;
		 Query3->Close();
		 Query3->SQL->Clear();
		 Query3->SQL->Add("SELECT nombre, apellido, calle, numero FROM clientes WHERE UPPER(nombre) LIKE :n ORDER BY nombre LIMIT 10");
		 Query3->ParamByName("n")->AsString = "%" + DBEdNombre->Text.UpperCase() + "%";
		 Query3->Open();
		 if(!Query3->IsEmpty())
			ClientDataSet4->Active = true;
	  }
	  else
	  {
		 ClientDataSet4->Close();
		 Query3->Close();
	  }

	  ShowScrollBar(DBGrid1->Handle, SB_VERT, true);

      modificoNombAp = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrame1::DBEdApellidoChange(TObject *Sender)
{
   if(blockDBEdit)
	  return;

   if(!DBEdNumero->Focused())
   {
	  if(DBEdApellido->Text != "")
	  {
		 ClientDataSet4->Active = false;
		 Query3->Close();
		 Query3->SQL->Clear();
		 Query3->SQL->Add("SELECT nombre, apellido, calle, numero FROM clientes WHERE UPPER(apellido) LIKE :n ORDER BY nombre LIMIT 10");
		 Query3->ParamByName("n")->AsString = "%" + DBEdApellido->Text.UpperCase() + "%";
		 Query3->Open();
		 if(!Query3->IsEmpty())
			ClientDataSet4->Active = true;
	  }
	  else
	  {
		 ClientDataSet4->Close();
		 Query3->Close();
	  }

	  ShowScrollBar(DBGrid1->Handle, SB_VERT, true);

	  modificoNombAp = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrame1::DBEdCalleChange(TObject *Sender)
{
   if(blockDBEdit)
	  return;

   if(DBEdCalle->Text != "")
   {
	  ClientDataSet4->Active = false;
	  Query3->Close();
	  Query3->SQL->Clear();
	  Query3->SQL->Add("SELECT nombre, apellido, calle, numero FROM clientes WHERE UPPER(calle) LIKE :n ORDER BY nombre LIMIT 10");
	  Query3->ParamByName("n")->AsString = "%" + DBEdCalle->Text.UpperCase() + "%";
	  Query3->Open();
	  if(!Query3->IsEmpty())
		 ClientDataSet4->Active = true;
   }
   else
   {
	  ClientDataSet4->Close();
	  Query3->Close();
   }

   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);

   if(!modificoNombAp)
      ClientDataSet1->FieldByName("nombre")->AsString = DBEdCalle->Text;
}
//---------------------------------------------------------------------------
void __fastcall TFrame1::DBEdNumeroChange(TObject *Sender)
{
   if(blockDBEdit)
	  return;

   if(DBEdNumero->Text != "")
   {
	  ClientDataSet4->Active = false;
	  Query3->Close();
	  Query3->SQL->Clear();
	  Query3->SQL->Add("SELECT nombre, apellido, calle, numero FROM clientes WHERE UPPER(numero) LIKE :n ORDER BY nombre LIMIT 10");
	  Query3->ParamByName("n")->AsString = "%" + DBEdNumero->Text.UpperCase() + "%";
	  Query3->Open();
	  if(!Query3->IsEmpty())
		 ClientDataSet4->Active = true;
   }
   else
   {
	  ClientDataSet4->Close();
	  Query3->Close();
   }

   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);

   if(!modificoNombAp)
      ClientDataSet1->FieldByName("apellido")->AsString = DBEdNumero->Text;
}
//---------------------------------------------------------------------------


void TFrame1::restablecerFrame(void)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;


   QueryUpdate->Close();
   QueryUpdate->SQL->Clear();
   QueryUpdate->SQL->Add("SELECT * FROM condicionesFrenteIVA ORDER BY idCondicionFrenteIVA");
   QueryUpdate->Open();
   CBCondicionFrenteIVA->Clear();
   QueryUpdate->First();
   while(!QueryUpdate->Eof)
   {
	  CBCondicionFrenteIVA->Items->Add(QueryUpdate->FieldByName("descripcion")->AsString);
	  QueryUpdate->Next();
   }
   QueryUpdate->Close();

   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("SELECT * FROM frecuenciapagos ORDER BY idFrecuenciaPago");
   Query1->Open();

   Query2->Close();
   Query2->SQL->Clear();
   Query2->SQL->Add("SELECT * FROM listasprecio ORDER BY idListaPrecio");
   Query2->Open();

   Query4->Close();
   Query4->SQL->Clear();
   Query4->SQL->Add("SELECT * FROM diapago ORDER BY idDiaPago");
   Query4->Open();

   Query3->Close();

   ClientDataSet2->Active = true;
   ClientDataSet3->Active = true;
   ClientDataSet5->Active = true;
   ClientDataSet4->Active = false;

   CBFacturar->ItemIndex = 0;
   CBmp->ItemIndex = 0;

   if(llamador == 1)
	  ClientDataSet1->Filtered = false;
   else if(llamador == 2)
   {
	  ClientDataSet1->Filter = "idCliente = " + IntToStr(id);
	  ClientDataSet1->Filtered = true;
   }
   SQLTable1->Active = true;

   blockDBEdit = true;
   ClientDataSet1->Active = true;

   if(llamador == 1)
   {
	  ClientDataSet1->Insert();
	  ClientDataSet1->FieldByName("bonificacion")->AsFloat = 0.0;
	  ClientDataSet1->FieldByName("imprimirDetalle")->AsInteger = 0;
	  ClientDataSet1->FieldByName("generarFactura")->AsInteger = 0;
	  ClientDataSet1->FieldByName("refFrecuenciaPago")->AsInteger = 1;
	  ClientDataSet1->FieldByName("refDiaPago")->AsInteger = 5;
	  ClientDataSet1->FieldByName("refListaPrecio")->AsInteger = 1;
	  ClientDataSet1->FieldByName("pagoAdelantado")->AsString = 'N';
	  ClientDataSet1->FieldByName("menuImpreso")->AsString = 'N';
	  CBCondicionFrenteIVA->ItemIndex = 2;
	  Label12->Caption = "DNI:";
	  ClientDataSet1->FieldByName("CUIT")->AsString = "00000000";
	  conDNI = true;
	  DBCUIT->MaxLength = 8;
//	  CBCondicionFrenteIVA->Enabled = false;
   }
   else if(llamador == 2)
   {
	  CBCondicionFrenteIVA->ItemIndex = ClientDataSet1->FieldByName("refCondicionFrenteIVA")->AsInteger - 1;
	  if(CBCondicionFrenteIVA->ItemIndex == 2)
	  {
		 Label12->Caption = "DNI:";
		 conDNI = true;
		 DBCUIT->MaxLength = 8;
	  }
	  else
	  {
		 Label12->Caption = "CUIT:";
		 conDNI = false;
		 DBCUIT->MaxLength = 13;
	  }
	  for(int i=0;i<CBFacturar->Items->Count;i++)
		 if(CBFacturar->Items->Strings[i] == ClientDataSet1->FieldByName("Tipo")->AsString)
		 {
			CBFacturar->ItemIndex = i;
			break;
		 }
	  for(int i=0;i<CBmp->Items->Count;i++)
		 if(CBmp->Items->Strings[i].SubString(1,1) == ClientDataSet1->FieldByName("medioPagoDefecto")->AsString)
		 {
			CBmp->ItemIndex = i;
			break;
		 }

	  ClientDataSet1->Edit();
	  modificando = true;
   }

   modificoNombAp = false;
   DBCUIT->Color = clWindow;
   DBCUIT->ShowHint = false;
   cuitOK = true;

   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);

   DBEdCalle->SetFocus();
   blockDBEdit = false;
}
//---------------------------------------------------------------------------

void TFrame1::cerrarFrame(void)
{
   blockDBEdit = true;
   modificando = false;
   ClientDataSet1->Cancel();
   ClientDataSet1->Active = false;
   ClientDataSet2->Active = false;
   ClientDataSet3->Active = false;
   ClientDataSet4->Active = false;
   SQLTable1->Active = false;
   Query1->Close();
   Query2->Close();
   Query3->Close();
   Query4->Close();

   blockDBEdit = false;
   SQLConnection1->Close();
   CBCondicionFrenteIVA->ItemIndex = -1;
   CBFacturar->ItemIndex = 0;
   CBmp->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFrame1::DBEdBonificacionKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
	  Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TFrame1::DBCUITKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(conDNI)
	  return;

   if(Key == VK_BACK)
   {
	  Key = NULL;
	  ClientDataSet1->FieldByName("CUIT")->AsString = "00-00000000-0";
	  DBCUIT->SelStart = 0;
   }
   else if(Key == VK_DELETE)
   {
	  Key = NULL;
	  ClientDataSet1->FieldByName("CUIT")->AsString = "00-00000000-0";
	  DBCUIT->SelStart = 0;
   }
}
//---------------------------------------------------------------------------

void __fastcall TFrame1::DBCUITKeyPress(TObject *Sender, System::WideChar &Key)
{
   if(conDNI)
	  return;

   DBCUIT->SelLength = 1;
}
//---------------------------------------------------------------------------

void __fastcall TFrame1::DBCUITKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(conDNI)
	  return;


   if(DBCUIT->SelStart == 2 || DBCUIT->SelStart == 11)
	  DBCUIT->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TFrame1::DBCUITExit(TObject *Sender)
{
   if(conDNI)
   {
	  if(DBCUIT->Text.Length() == 8)
	  {
		 DBCUIT->Color = clWindow;
		 DBCUIT->ShowHint = false;
		 cuitOK = true;
	  }
	  else
	  {
		 DBCUIT->Hint = "El DNI debe tener una longitud de 8 d�gitos. Complete con ceros a la izquierda";
		 DBCUIT->ShowHint = true;
		 DBCUIT->Color = clWebLightCoral;
		 cuitOK = false;
	  }

	  return;
   }
   if(DBCUIT->Text != "00-00000000-0")
   {
		int v1 = StrToInt(DBCUIT->Text[1]) * 5;
		v1 = v1 + StrToInt(DBCUIT->Text[2]) * 4;
		v1 = v1 + StrToInt(DBCUIT->Text[4]) * 3;
		v1 = v1 + StrToInt(DBCUIT->Text[5]) * 2;
		v1 = v1 + StrToInt(DBCUIT->Text[6]) * 7;
		v1 = v1 + StrToInt(DBCUIT->Text[7]) * 6;
		v1 = v1 + StrToInt(DBCUIT->Text[8]) * 5;
		v1 = v1 + StrToInt(DBCUIT->Text[9]) * 4;
		v1 = v1 + StrToInt(DBCUIT->Text[10]) * 3;
		v1 = v1 + StrToInt(DBCUIT->Text[11]) * 2;

		int v2 = v1 % 11;

		if(StrToInt(DBCUIT->Text[13]) == (11 - v2))
		{
		   DBCUIT->Color = clWindow;
		   DBCUIT->ShowHint = false;
		   cuitOK = true;
		}
		else if(StrToInt(DBCUIT->Text[13]) == 0 && (v2 == 0))
		{
		   DBCUIT->Color = clWindow;
		   DBCUIT->ShowHint = false;
		   cuitOK = true;
		}
		else
		{
		   DBCUIT->Hint = "El cuit ingresado no es v�lido";
		   DBCUIT->ShowHint = true;
		   DBCUIT->Color = clWebLightCoral;
		   cuitOK = false;
		}
//		CBCondicionFrenteIVA->Enabled = true;
//        CBCondicionFrenteIVA->SetFocus();
   }
   else
   {
//      CBCondicionFrenteIVA->ItemIndex = 2;
//	  CBCondicionFrenteIVA->Enabled = false;
	  cuitOK = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall TFrame1::CBCondicionFrenteIVAChange(TObject *Sender)
{
      if(CBCondicionFrenteIVA->ItemIndex == 2)
	  {
	     Label12->Caption = "DNI:";
		 conDNI = true;
		 if(DBCUIT->Text.Length() == 13)
			ClientDataSet1->FieldByName("CUIT")->AsString = "00000000";

		 DBCUIT->MaxLength = 8;
	  }
	  else
	  {
		 Label12->Caption = "CUIT:";
		 conDNI = false;
		 if(DBCUIT->Text.Length() == 8)
			ClientDataSet1->FieldByName("CUIT")->AsString = "00-00000000-0";

		 DBCUIT->MaxLength = 13;
	  }
}
//---------------------------------------------------------------------------


void __fastcall TFrame1::CBFacturarChange(TObject *Sender)
{
   if(ClientDataSet1->Active)
      ClientDataSet1->FieldByName("tipo")->AsString = CBFacturar->Text.SubString(1,1);
}
//---------------------------------------------------------------------------

void __fastcall TFrame1::CBmpChange(TObject *Sender)
{
   if(ClientDataSet1->Active)
	  ClientDataSet1->FieldByName("medioPagoDefecto")->AsString = CBmp->Text.SubString(1,1);
}
//---------------------------------------------------------------------------


