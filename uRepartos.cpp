//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "uRepartos.h"
#include "uCuentas.h"
#include "uSeleccionarCliente.h"
#include "uImprimirPlanillas.h"
#include "VariablesGlobales.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfRepartos *fRepartos;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfRepartos::TfRepartos(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TfRepartos::actualizarPlanillas(int idRepartidor)
{
   ClientDataSet1->Active = false;

   String q;
   q = "SELECT idReparto, refCliente, refRepartidor, posicion, esSabado, "
	   "(SELECT calle FROM clientes WHERE refCliente = idCliente LIMIT 1) AS calle, "
	   "(SELECT numero FROM clientes WHERE refCliente = idCliente LIMIT 1) AS numero "
	   "FROM repartos WHERE (refRepartidor = :rep AND esSabado = :sab) ORDER BY posicion";

   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add(q);
   Query1->ParamByName("rep")->AsInteger = idRepartidor;
   Query1->ParamByName("sab")->AsInteger = RG1->ItemIndex;
   Query1->Open();

   if(Query1->IsEmpty())  // esto agrega la division de reparto si no existia.
   {
	  Query1->Close();
	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("INSERT INTO repartos VALUES (NULL, 1, :idRep, 1, :esSab)");
	  QueryAux->ParamByName("idRep")->AsInteger = idRepartidor;
	  QueryAux->ParamByName("esSab")->AsInteger = RG1->ItemIndex;
	  QueryAux->ExecSQL();
	  Query1->Open();
   }

   ClientDataSet1->Active = true;

   if(ClientDataSet1->RecordCount < 2)
	  Button7->Enabled = false;
   else
	  Button7->Enabled = true;

   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
}
//---------------------------------------------------------------------------

int TfRepartos::maximaPosicion(int refRepartidor, int esSabado)
{
   QueryAux->Close();
   QueryAux->SQL->Clear();
   QueryAux->SQL->Add("SELECT MAX(posicion) as maximo FROM repartos WHERE (refRepartidor = :rr AND esSabado = :es)");
   QueryAux->ParamByName("rr")->AsInteger = refRepartidor;
   QueryAux->ParamByName("es")->AsInteger = esSabado;
   QueryAux->Open();
   int maximo = QueryAux->FieldByName("maximo")->AsInteger;
   QueryAux->Close();

   return maximo;
}
//---------------------------------------------------------------------------

int TfRepartos::getIdRepartidor(String nombre)
{
   QueryAux->Close();
   QueryAux->SQL->Clear();
   QueryAux->SQL->Add("SELECT idRepartidor FROM repartidores WHERE descripcion = :des LIMIT 1");
   QueryAux->ParamByName("des")->AsString = nombre;
   QueryAux->Open();
   int idRepartidor = QueryAux->FieldByName("idRepartidor")->AsInteger;
   QueryAux->Close();
   return idRepartidor;
}
//---------------------------------------------------------------------------

void TfRepartos::transferir(String planilla)
{
   if(ClientDataSet1->FieldByName("refCliente")->AsInteger == 1 || ClientDataSet1->FieldByName("refCliente")->AsInteger == 2)
   {
	  Application->MessageBox(L"No se pueden transferir los espacios ni las divisiones de repartos",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return;
   }

   String str = L"Se va a transferir el cliente a la planilla: " + ComboBox2->Text.UpperCase() + L". Desea continuar?";


   if(Application->MessageBox(str.w_str() ,L"Transferir?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
   {
      int idRepDestino = getIdRepartidor(planilla);

	  int refRep = getIdRepartidor(ComboBox1->Text);
	  int esSab = RG1->ItemIndex;
	  int pos = ClientDataSet1->FieldByName("posicion")->AsInteger;
	  int idRegistro = ClientDataSet1->FieldByName("idReparto")->AsInteger;

	  int maximo = maximaPosicion(idRepDestino, esSab);

	  if(maximo < 60)
	  {
         QueryAux->Close();
		 QueryAux->SQL->Clear();
		 QueryAux->SQL->Add("UPDATE repartos SET posicion = :posDest, refRepartidor = :refRepDest WHERE (idReparto = :id) LIMIT 1");
		 QueryAux->ParamByName("refRepDest")->AsInteger = idRepDestino;
		 QueryAux->ParamByName("posDest")->AsInteger = maximo + 1;
		 QueryAux->ParamByName("id")->AsInteger = idRegistro;
		 QueryAux->ExecSQL();


		 QueryAux->Close();
		 QueryAux->SQL->Clear();
		 QueryAux->SQL->Add("UPDATE repartos SET posicion = (posicion - 1) "
							"WHERE (refRepartidor = :rr AND esSabado = :es AND posicion > :pos)");
		 QueryAux->ParamByName("rr")->AsInteger = refRep;
		 QueryAux->ParamByName("es")->AsInteger = esSab;
		 QueryAux->ParamByName("pos")->AsInteger = pos;
		 QueryAux->ExecSQL();

		 ClientDataSet1->Refresh();
	  }
	  else
		 Application->MessageBox(L"Ya no hay espacio en la planilla destino.",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
   }
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::FormClose(TObject *Sender, TCloseAction &Action)
{
   ClientDataSet1->Active = false;
   Query1->Close();
   QueryAux->Close();

   SQLConnection1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfRepartos::ComboBox1Change(TObject *Sender)
{
   actualizarPlanillas(getIdRepartidor(ComboBox1->Text));
}
//---------------------------------------------------------------------------
void __fastcall TfRepartos::FormShow(TObject *Sender)
{

   if(DayOfTheWeek(Now()) == DaySaturday)
   {
	  RG1->ItemIndex = 1;
   }
   else
	  RG1->ItemIndex = 0;

   RG1Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfRepartos::RG1Click(TObject *Sender)
{
   QueryAux->Close();
   QueryAux->SQL->Clear();

   if(RG1->ItemIndex == 0)
	  QueryAux->SQL->Add("SELECT idRepartidor, descripcion FROM repartidores ORDER BY descripcion");
   else
	  QueryAux->SQL->Add("SELECT idRepartidor, descripcion FROM repartidores WHERE reparteSabados = 1 ORDER BY descripcion");
   QueryAux->Open();

   ComboBox1->Clear();
   ComboBox2->Clear();
   QueryAux->First();
   int idx = 0;
   while(!QueryAux->Eof)
   {
	  ComboBox1->Items->Add(QueryAux->FieldByName("descripcion")->AsString);
	  ComboBox2->Items->Add(QueryAux->FieldByName("descripcion")->AsString);
	  if(idx < 15)
	  {
		 ransferira1->Items[idx]->Visible = true;
		 ransferira1->Items[idx]->Caption = QueryAux->FieldByName("descripcion")->AsString;
      }
	  QueryAux->Next();
	  idx++;
   }
   while(idx < 15)
   {
	  ransferira1->Items[idx]->Visible = false;
	  idx++;
   }
   QueryAux->Close();
   ComboBox1->ItemIndex = 0;
   ComboBox2->ItemIndex = -1;

   actualizarPlanillas(getIdRepartidor(ComboBox1->Text));
}
//---------------------------------------------------------------------------
void __fastcall TfRepartos::Button1Click(TObject *Sender)
{
   fSeleccionarCliente->llamador = 1;
   fSeleccionarCliente->ShowModal();
   if(fSeleccionarCliente->idSeleccionado == 0)
	  Application->MessageBox(L"Debe seleccionar el cliente a agregar.",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
   else
   {

      int refRep = getIdRepartidor(ComboBox1->Text);
	  int esSab = RG1->ItemIndex;

	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("SELECT COUNT(*) AS existe FROM repartos WHERE (refCliente = :rc AND esSabado = :sab) LIMIT 1");
	  QueryAux->ParamByName("rc")->AsInteger = fSeleccionarCliente->idSeleccionado;
	  QueryAux->ParamByName("sab")->AsInteger = esSab;
	  QueryAux->Open();

	  if(QueryAux->FieldByName("existe")->AsInteger > 0)
	  {
		 Application->MessageBox(L"Este cliente ya existe en los repartos",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		 QueryAux->Close();
		 return;
	  }

	  int maximo = maximaPosicion(refRep, esSab);

	  if(maximo < 60)
	  {
		 QueryAux->SQL->Clear();
		 QueryAux->SQL->Add("INSERT INTO repartos VALUES (NULL, :idCli, :idRep, :pos, :esSab)");
		 QueryAux->ParamByName("idCli")->AsInteger = fSeleccionarCliente->idSeleccionado;
		 QueryAux->ParamByName("idRep")->AsInteger = refRep;
		 QueryAux->ParamByName("pos")->AsInteger = maximo + 1;
		 QueryAux->ParamByName("esSab")->AsInteger = esSab;
		 QueryAux->ExecSQL();

         QueryAux->Close();
		 QueryAux->SQL->Clear();
		 QueryAux->SQL->Add("UPDATE clientes SET esVisible = 1 WHERE (idCliente = :idc) LIMIT 1");
		 QueryAux->ParamByName("idc")->AsInteger = fSeleccionarCliente->idSeleccionado;
		 QueryAux->ExecSQL();


		 ClientDataSet1->Refresh();
		 ClientDataSet1->RecNo = ClientDataSet1->RecordCount;
		 DBGrid1->SetFocus();
	  }
	  else
		 Application->MessageBox(L"Ya no hay espacio en esta planilla.",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);

      ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
   }
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Button4Click(TObject *Sender)
{
   if(ClientDataSet1->FieldByName("refCliente")->AsInteger == 1 || ClientDataSet1->FieldByName("refCliente")->AsInteger == 2)
   {
	  Application->MessageBox(L"No se pueden transferir los espacios ni las divisiones de repartos",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return;
   }

   if(ComboBox2->ItemIndex == -1)
   {
	  Application->MessageBox(L"Antes debe especificar la planilla destino.",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return;
   }

   String str = L"Se va a transferir el cliente a la planilla: " + ComboBox2->Text.UpperCase() + L". Desea continuar?";


   if(Application->MessageBox(str.w_str() ,L"Transferir?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
   {
      int idRepDestino = getIdRepartidor(ComboBox2->Text);

	  int refRep = getIdRepartidor(ComboBox1->Text);
	  int esSab = RG1->ItemIndex;
	  int pos = ClientDataSet1->FieldByName("posicion")->AsInteger;
	  int idRegistro = ClientDataSet1->FieldByName("idReparto")->AsInteger;

	  int maximo = maximaPosicion(idRepDestino, esSab);

	  if(maximo < 60)
	  {
         QueryAux->Close();
		 QueryAux->SQL->Clear();
		 QueryAux->SQL->Add("UPDATE repartos SET posicion = :posDest, refRepartidor = :refRepDest WHERE (idReparto = :id) LIMIT 1");
		 QueryAux->ParamByName("refRepDest")->AsInteger = idRepDestino;
		 QueryAux->ParamByName("posDest")->AsInteger = maximo + 1;
		 QueryAux->ParamByName("id")->AsInteger = idRegistro;
		 QueryAux->ExecSQL();


		 QueryAux->Close();
		 QueryAux->SQL->Clear();
		 QueryAux->SQL->Add("UPDATE repartos SET posicion = (posicion - 1) "
							"WHERE (refRepartidor = :rr AND esSabado = :es AND posicion > :pos)");
		 QueryAux->ParamByName("rr")->AsInteger = refRep;
		 QueryAux->ParamByName("es")->AsInteger = esSab;
		 QueryAux->ParamByName("pos")->AsInteger = pos;
		 QueryAux->ExecSQL();

		 ClientDataSet1->Refresh();
	  }
	  else
		 Application->MessageBox(L"Ya no hay espacio en la planilla destino.",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
   }

   ComboBox2->ItemIndex = -1;
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Button2MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   Timer1Timer(Button2);
   Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Button2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
   Timer1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Timer2Timer(TObject *Sender)
{
   int refRep = getIdRepartidor(ComboBox1->Text);
   int esSab = RG1->ItemIndex;
   int pos = ClientDataSet1->FieldByName("posicion")->AsInteger;
   int idRegistro = ClientDataSet1->FieldByName("idReparto")->AsInteger;

   int maximo = maximaPosicion(refRep, esSab);

   if(ClientDataSet1->FieldByName("posicion")->AsInteger < maximo)
   {
	  int indx = ClientDataSet1->RecNo;

	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("UPDATE repartos SET posicion = (posicion - 1) "
	                     "WHERE (refRepartidor = :rr AND esSabado = :es AND posicion = :pos) LIMIT 1");
	  QueryAux->ParamByName("rr")->AsInteger = refRep;
	  QueryAux->ParamByName("es")->AsInteger = esSab;
	  QueryAux->ParamByName("pos")->AsInteger = pos + 1;
	  QueryAux->ExecSQL();

	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("UPDATE repartos SET posicion = (posicion + 1) WHERE (idReparto = :id) LIMIT 1");
	  QueryAux->ParamByName("id")->AsInteger = idRegistro;
	  QueryAux->ExecSQL();


	  ClientDataSet1->Refresh();

	  ClientDataSet1->RecNo = indx + 1;
	  DBGrid1->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Button3MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
   Timer2Timer(Button3);
   Timer2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Button3MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
   Timer2->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Timer1Timer(TObject *Sender)
{
   if(ClientDataSet1->FieldByName("posicion")->AsInteger > 1)
   {
	  int refRep = getIdRepartidor(ComboBox1->Text);
	  int esSab = RG1->ItemIndex;
	  int pos = ClientDataSet1->FieldByName("posicion")->AsInteger;
	  int idRegistro = ClientDataSet1->FieldByName("idReparto")->AsInteger;

	  int indx = ClientDataSet1->RecNo;

	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("UPDATE repartos SET posicion = (posicion + 1) "
						 "WHERE (refRepartidor = :rr AND esSabado = :es AND posicion = :pos) LIMIT 1");
	  QueryAux->ParamByName("rr")->AsInteger = refRep;
	  QueryAux->ParamByName("es")->AsInteger = esSab;
	  QueryAux->ParamByName("pos")->AsInteger = pos - 1;
	  QueryAux->ExecSQL();

	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("UPDATE repartos SET posicion = (posicion - 1) WHERE (idReparto = :id) LIMIT 1");
	  QueryAux->ParamByName("id")->AsInteger = idRegistro;
	  QueryAux->ExecSQL();


	  ClientDataSet1->Refresh();

	  ClientDataSet1->RecNo = indx - 1;
	  DBGrid1->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Button5Click(TObject *Sender)
{
   if(ClientDataSet1->FieldByName("refCliente")->AsInteger == 1)
   {
	  Application->MessageBox(L"No se puede eliminar una división de reparto",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return;
   }

   int refRep = getIdRepartidor(ComboBox1->Text);
   int esSab = RG1->ItemIndex;
   int pos = ClientDataSet1->FieldByName("posicion")->AsInteger;
   int idRegistro = ClientDataSet1->FieldByName("idReparto")->AsInteger;
   int idEliminado = ClientDataSet1->FieldByName("refCliente")->AsInteger;

   String str = L"Se va a quitar el cliente: " + ClientDataSet1->FieldByName("calle")->AsString;
   str = str + L" " + ClientDataSet1->FieldByName("numero")->AsString + L" de esta planilla. Desea continuar?";

   if(idEliminado == 2 || Application->MessageBox(str.w_str() ,L"Eliminar de esta planilla?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
   {
	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("DELETE FROM repartos WHERE (idReparto = :id) LIMIT 1");
	  QueryAux->ParamByName("id")->AsInteger = idRegistro;
	  QueryAux->ExecSQL();

	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("UPDATE repartos SET posicion = (posicion - 1) "
	                     "WHERE (refRepartidor = :rr AND esSabado = :es AND posicion > :pos)");
	  QueryAux->ParamByName("rr")->AsInteger = refRep;
	  QueryAux->ParamByName("es")->AsInteger = esSab;
	  QueryAux->ParamByName("pos")->AsInteger = pos;
	  QueryAux->ExecSQL();

      QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("SELECT COUNT(*) AS existe FROM repartos WHERE (refCliente = :rc) LIMIT 1");
	  QueryAux->ParamByName("rc")->AsInteger = idEliminado;
	  QueryAux->Open();
	  int existe = QueryAux->FieldByName("existe")->AsInteger;
	  QueryAux->Close();

	  if(existe == 0)
	  {
		 QueryAux->Close();
		 QueryAux->SQL->Clear();
		 QueryAux->SQL->Add("UPDATE clientes SET esVisible = 0 WHERE (idCliente = :idc) LIMIT 1");
		 QueryAux->ParamByName("idc")->AsInteger = idEliminado;
		 QueryAux->ExecSQL();
	  }

	  ClientDataSet1->Refresh();
   }
}
//---------------------------------------------------------------------------


void __fastcall TfRepartos::Button6Click(TObject *Sender)
{
	  int refRep = getIdRepartidor(ComboBox1->Text);
	  int esSab = RG1->ItemIndex;

	  int maximo = maximaPosicion(refRep, esSab);

	  if(maximo < 60)
	  {
		 QueryAux->SQL->Clear();
		 QueryAux->SQL->Add("INSERT INTO repartos VALUES (NULL, 2, :idRep, :pos, :esSab)");
		 QueryAux->ParamByName("idRep")->AsInteger = refRep;
		 QueryAux->ParamByName("pos")->AsInteger = maximo + 1;
		 QueryAux->ParamByName("esSab")->AsInteger = esSab;
		 QueryAux->ExecSQL();

		 ClientDataSet1->Refresh();
		 ClientDataSet1->RecNo = ClientDataSet1->RecordCount;
		 DBGrid1->SetFocus();
	  }
	  else
		 Application->MessageBox(L"Ya no hay espacio en esta planilla.",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Button7Click(TObject *Sender)
{
   fImprimirPlanillas->Show();
   fImprimirPlanillas->esSabado = RG1->ItemIndex;

   for(int i = 0; i < fImprimirPlanillas->ComboBox1->Items->Count; i++)
	  if(fImprimirPlanillas->ComboBox1->Items->Strings[i] == ComboBox1->Text)
	  {
		 fImprimirPlanillas->ComboBox1->ItemIndex = i;
		 i = 1000;
	  }
   fImprimirPlanillas->ComboBox1Change(fImprimirPlanillas->ComboBox1);
   fImprimirPlanillas->ComboBox1->Text = ComboBox1->Text;
   fImprimirPlanillas->Button2Click(fRepartos);
   fImprimirPlanillas->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Button8Click(TObject *Sender)
{
   if(ComboBox2->ItemIndex == -1)
   {
	  Application->MessageBox(L"Antes debe especificar la planilla destino.",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return;
   }

   int esSab = RG1->ItemIndex;
   int idRepNuevo = getIdRepartidor(ComboBox2->Text);
   int idRepViejo = getIdRepartidor(ComboBox1->Text);
   if(maximaPosicion(idRepNuevo, esSab) > 1)
   {
	  Application->MessageBox(L"La planilla destino no puede contener direcciones. Solo una división de reparto.",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return;
   }

   String str = L"Se van a transferir TODAS LAS DIRECCIONES a la planilla: " + ComboBox2->Text.UpperCase() + L". Desea continuar?";


   if(Application->MessageBox(str.w_str() ,L"¡ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
	  return;



   QueryAux->Close();                 //Borro division de reparto de la planilla nueva
   QueryAux->SQL->Clear();
   if(esSab == 0)
	  QueryAux->SQL->Add("DELETE FROM repartos WHERE (refCliente = 1 AND refRepartidor = :refRepartidor AND esSabado = 0) LIMIT 1");
   else if(esSab == 1)
	  QueryAux->SQL->Add("DELETE FROM repartos WHERE (refCliente = 1 AND refRepartidor = :refRepartidor AND esSabado = 1) LIMIT 1");

   QueryAux->ParamByName("refRepartidor")->AsInteger = idRepNuevo;
   QueryAux->ExecSQL();


   QueryAux->Close();                  //Cambio de repartidor todas las direcciones de la planilla vieja
   QueryAux->SQL->Clear();
   if(esSab == 0)
	  QueryAux->SQL->Add("UPDATE repartos SET refRepartidor = :nuevaRefRepartidor WHERE (refRepartidor = :viejaRefRepartidor AND esSabado = 0)");
   else if(esSab == 1)
	  QueryAux->SQL->Add("UPDATE repartos SET refRepartidor = :nuevaRefRepartidor WHERE (refRepartidor = :viejaRefRepartidor AND esSabado = 1)");

   QueryAux->ParamByName("nuevaRefRepartidor")->AsInteger = idRepNuevo;
   QueryAux->ParamByName("viejaRefRepartidor")->AsInteger = idRepViejo;
   QueryAux->ExecSQL();



   QueryAux->Close();                 //Agrego una division de reparto en la posicion 1 de la planilla vieja
   QueryAux->SQL->Clear();
   if(esSab == 0)
	  QueryAux->SQL->Add("INSERT INTO repartos VALUES (NULL, 1, :refRep, 1, 0)");
   else if(esSab == 1)
	  QueryAux->SQL->Add("INSERT INTO repartos VALUES (NULL, 1, :refRep, 1, 1)");

   QueryAux->ParamByName("refRep")->AsInteger = idRepViejo;
   QueryAux->ExecSQL();

   ClientDataSet1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Quitardeestaplanilla1Click(TObject *Sender)
{
   Button5Click(Button5);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item11Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------


void __fastcall TfRepartos::Item21Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item31Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item41Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item51Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item61Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item71Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item81Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item91Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item101Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item111Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item121Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item131Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item141Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Item151Click(TObject *Sender)
{
   if(!ClientDataSet1->Active)
	  return;

   transferir(ComboBox2->Items->Strings[dynamic_cast<TMenuItem *>(Sender)->MenuIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Desplazarhaciaarriba1Click(TObject *Sender)
{
   Timer1Timer(Timer1);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Desplazarhaciaabajo1Click(TObject *Sender)
{
   Timer2Timer(Timer2);
}
//---------------------------------------------------------------------------

void __fastcall TfRepartos::Verestadodecuentacorriente1Click(TObject *Sender)
{
   if(ClientDataSet1->FieldByName("refCliente")->AsInteger > 2)
   {
	  fCuentas->idCliente = ClientDataSet1->FieldByName("refCliente")->AsInteger;
	  fCuentas->ShowModal();
   }
}
//---------------------------------------------------------------------------

