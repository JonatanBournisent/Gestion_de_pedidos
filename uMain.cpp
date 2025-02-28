//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>

#pragma hdrstop

#include "uFrecuenciaComidas.h"
#include "VariablesGlobales.h"
#include "uFacturacionMensual.h"
#include "uInformacionNutricional.h"
#include "uMain.h"
#include "uIngredientes.h"
#include "uRecetas.h"
#include "uDatos.h"
#include "uPrecios.h"
#include "uRastrearPagos.h"
#include "uAlarma.h"
#include "uGestionarAlarmas.h"
#include "uConfigurarAlarma.h"
#include "uAgregarCliente.h"
#include "uModificarCliente.h"
#include "uRepartidores.h"
#include "uRepartos.h"
#include "uPedidos.h"
#include "uProductos.h"
#include "uMenuSemanal.h"
#include "uAgregarComida.h"
#include "uModificarComida.h"
#include "uCargarPagos.h"
#include "uImprimirPlanillas.h"
#include "uConfiguraciones.h"
#include "uCuentas.h"
#include "uImprimirCuentas.h"
#include "uEmitirComprobanteElectronico.h"
#include "uVerComprobantesElectronicos.h"
#include "uClientesHabituales.h"
#include "uComprobantesX.h"
#include "uGestionDeGastos.h"
#include "uFormulaComidas.h"
#include "uMenuOficina.h"
#include "uMensajes.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "uFrame1"
#pragma resource "*.dfm"
TfMain *fMain;

//variables externa declarada en VariablesGlobales.h
String servidor;
String dbName;
String userName;
String pass;

//---------------------------------------------------------------------------
__fastcall TfMain::TfMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button2Click(TObject *Sender)
{
   fAgregarCliente->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button1Click(TObject *Sender)
{
   fModificarCliente->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfMain::Button3Click(TObject *Sender)
{
   fRepartidores->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button4Click(TObject *Sender)
{
   fRepartos->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfMain::Button5Click(TObject *Sender)
{
   fPedidos->ShowModal();
   if(CDS1->Active)
   {
      Query2->Refresh();
	  CDS1->Refresh();
   }
   fMain->WindowState = wsNormal;
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button6Click(TObject *Sender)
{
   fAgregarComida->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button7Click(TObject *Sender)
{
   fModificarComida->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfMain::Button9Click(TObject *Sender)
{
   fMenuSemanal->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button10Click(TObject *Sender)
{
   fProductos->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button11Click(TObject *Sender)
{
   fCargarPagos->ShowModal();

   if(CDS1->Active)
   {
	  Query2->Refresh();
	  CDS1->Refresh();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button12Click(TObject *Sender)
{
   fImprimirPlanillas->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button13Click(TObject *Sender)
{
   fConfiguraciones->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::CuentasClick(TObject *Sender)
{
   fCuentas->ShowModal();
   if(CDS1->Active)
   {
	  Query2->Refresh();
	  CDS1->Refresh();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button14Click(TObject *Sender)
{
   fImprimirCuentas->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button8Click(TObject *Sender)
{
   fDatos->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Shift.Contains(ssCtrl) && Shift.Contains(ssShift) && Shift.Contains(ssAlt) && Key == VK_F12)
	  fDatos->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button15Click(TObject *Sender)
{
   fConfigurarAlarma->llamador = 0;
   fConfigurarAlarma->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::AlarmasTimer(TObject *Sender)
{
   if(CompareDateTime(Now(),proximaAlarma) == GreaterThanValue && idProximaAlarma != 0)
   {
	  Alarmas->Enabled = false;
	  fAlarma->idAlarma = idProximaAlarma;
	  fAlarma->ShowModal();

	  Query1->Close();
	  Query1->SQL->Clear();
	  Query1->SQL->Add("SELECT IFNULL(idAlarma,0) AS idAlarma, marcaTiempo FROM alarmas WHERE "
	  	  			   "vista = 0 AND paraCocina = 0 ORDER BY marcaTiempo LIMIT 1");
	  Query1->Open();
	  idProximaAlarma = Query1->FieldByName("idAlarma")->AsInteger;
	  proximaAlarma = Query1->FieldByName("marcaTiempo")->AsDateTime;
	  Query1->Close();

      Alarmas->Enabled = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfMain::FormShow(TObject *Sender)
{
   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("SELECT IFNULL(idAlarma,0) AS idAlarma, marcaTiempo FROM alarmas WHERE "
   					"vista = 0 AND paraCocina = 0 ORDER BY marcaTiempo LIMIT 1");
   Query1->Open();
   idProximaAlarma = Query1->FieldByName("idAlarma")->AsInteger;
   proximaAlarma = Query1->FieldByName("marcaTiempo")->AsDateTime;
   Query1->Close();

   CDS1->Active = false;

   Query2->Close();
   Query2->SQL->Clear();
   String q;
   q = "SELECT idCliente, CONCAT(calle, ' ', numero) AS cliente, (acumuladoGlobal - acumuladoParcial) AS deuda "
	   "FROM clientes WHERE ((acumuladoGlobal <> 0) AND ((acumuladoGlobal - acumuladoParcial) <> 0)) ORDER BY ABS(deuda)";

   Query2->SQL->Add(q);
   Query2->Open();
   CDS1->Active = true;

   Button5->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button16Click(TObject *Sender)
{
   fGestionarAlarmas->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::DBGrid1DblClick(TObject *Sender)
{
   if(!CDS1->Active)
	  return;

   fCuentas->idCliente = CDS1->FieldByName("idCliente")->AsInteger;
   fCuentas->ShowModal();

   Query2->Refresh();
   CDS1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfMain::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight,
          bool &Resize)
{
   Resize = false;
}
//---------------------------------------------------------------------------

void __fastcall TfMain::FormClose(TObject *Sender, TCloseAction &Action)
{
   Alarmas->Enabled = false;
   CDS1->Active = false;
   Query1->Close();
   Query2->Close();
   SQLConnection1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
   if(Column->Field->Index == 1 && Column->Field->AsFloat < 0)
	  dynamic_cast <TDBGrid *>(Sender)->Canvas->Font->Color = clGreen;
   else if(Column->Field->Index == 1)
	  dynamic_cast <TDBGrid *>(Sender)->Canvas->Font->Color = clRed;

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

void __fastcall TfMain::Verestadodecuenta1Click(TObject *Sender)
{
   DBGrid1DblClick(DBGrid1);
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Imprimirdetalledecuenta1Click(TObject *Sender)
{
   if(!CDS1->Active)
	  return;

   fImprimirCuentas->refClienteIndicado = CDS1->FieldByName("idCliente")->AsInteger;
   fImprimirCuentas->usarClienteIndicado = true;
   fImprimirCuentas->Show();
   fImprimirCuentas->Button8Click(fImprimirCuentas->RG1); // cualquier sender
}
//---------------------------------------------------------------------------

void __fastcall TfMain::FormCreate(TObject *Sender)
{
   TIniFile *Configuraciones;
   String Dir = GetCurrentDir()+"//Config.ini";
   Configuraciones = new TIniFile(Dir);

   servidor = Configuraciones->ReadString("MySQLServer","Servidor", "127.0.0.1");
   dbName = "dbes";
   userName = "elsembrador";
   pass = "*-elsembrador63/*";


   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
   delete Configuraciones;

   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("SELECT * FROM registros WHERE idRegistro = 1 LIMIT 1");
   Query1->Open();
   TDate ultimaApertura;
   TDate fechaUltimoCalculoSemanal;
   TDate fechaUltimoCalculoMensual;

   ultimaApertura = DateOf(Query1->FieldByName("ultimaApertura")->AsDateTime);
   fechaUltimoCalculoSemanal = DateOf(Query1->FieldByName("fechaUltimoCalculoSemanal")->AsDateTime);
   fechaUltimoCalculoMensual = DateOf(Query1->FieldByName("fechaUltimoCalculoMensual")->AsDateTime);

   Query1->Close();

   if(CompareDate(DateOf(Now()), ultimaApertura) == LessThanValue)
   {
	  Application->MessageBox(L"ERROR IMPORTANTE! (Codigo 0001) ES POSIBLE QUE LA FECHA DEL SISTEMA SEA INCORRECTA." ,L"ERROR GRAVE!",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  Application->MessageBox(L"Debe asegurarse de que la fecha y hora de Windows son correctas. De otro modo reinicie su PC y observe nuevamente. Si el problema persiste deberia configurarla manualmente. Puede continuar trabajando pero no modifique saldos y/o pagos ya que podria generar un error en el calculo de deudas." ,L"ERROR GRAVE!",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
   }
   else
   {
	  if(CompareDate(DateOf(Now()), ultimaApertura) == GreaterThanValue)
	  {
		 Query1->Close();
		 Query1->SQL->Clear();
		 Query1->SQL->Add("UPDATE registros SET ultimaApertura = DATE(NOW()) WHERE idRegistro = 1 LIMIT 1");
		 Query1->ExecSQL();
	  }


	  if(MonthOf(fechaUltimoCalculoMensual) != MonthOf(Now()))
	  {
		 Query1->Close();
		 Query1->SQL->Clear();
		 Query1->SQL->Add("UPDATE clientes SET acumuladoParcial = 0.0 WHERE clientes.refFrecuenciaPago = 3");
		 Query1->ExecSQL();

		 Query1->Close();
		 Query1->SQL->Clear();
		 Query1->SQL->Add("UPDATE registros SET fechaUltimoCalculoMensual = DATE(NOW()) WHERE idRegistro = 1 LIMIT 1");
		 Query1->ExecSQL();


		 TDateTime Momento;

		 Momento = IncHour(IncDay(EndOfTheMonth(Now()),-3), -15);

		 String q = DateTimeToStr(Momento);
		 q = "INSERT INTO alarmas (mensaje, marcaTiempo, frecuenciaRepeticion, vista, paraCocina) "
			 "VALUES ('Facturar el �ltimo d�a laboral del mes', :marcaTiempo, 0, 0, 0) ";
		 Query1->Close();
		 Query1->SQL->Clear();
		 Query1->SQL->Add(q);
		 Query1->ParamByName("marcaTiempo")->AsDateTime = Momento;
		 Query1->ExecSQL();
	  }


	  if(WeekOf(fechaUltimoCalculoSemanal) != WeekOf(Now()))
	  {
		 Query1->Close();
		 Query1->SQL->Clear();
		 Query1->SQL->Add("UPDATE clientes SET acumuladoParcial = 0.0 WHERE clientes.refFrecuenciaPago = 2");
		 Query1->ExecSQL();

		 Query1->Close();
		 Query1->SQL->Clear();
		 Query1->SQL->Add("UPDATE registros SET fechaUltimoCalculoSemanal = DATE(NOW()) WHERE idRegistro = 1 LIMIT 1");
		 Query1->ExecSQL();
	  }
   }
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button18Click(TObject *Sender)
{
   fEmitirComprobanteElectronico->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button17Click(TObject *Sender)
{
   fVerComprobantesElectronicos->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button19Click(TObject *Sender)
{
   fPrecios->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button20Click(TObject *Sender)
{
   fFacturacionMensual->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfMain::Button21Click(TObject *Sender)
{
   fClientesHabituales->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Button22Click(TObject *Sender)
{
   fRastrearPagos->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Cargarpedidos1Click(TObject *Sender)
{
   fPedidos->ShowModal();
   if(CDS1->Active)
   {
      Query2->Refresh();
	  CDS1->Refresh();
   }
   fMain->WindowState = wsNormal;
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Imprimirplanillas1Click(TObject *Sender)
{
   fImprimirPlanillas->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfMain::Gestionarrepartidores1Click(TObject *Sender)
{
   fRepartidores->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TfMain::Cargarpagosdeclientes1Click(TObject *Sender)
{
   fCargarPagos->ShowModal();

   if(CDS1->Active)
   {
	  Query2->Refresh();
	  CDS1->Refresh();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Gestionarcuentasdeclientes1Click(TObject *Sender)
{
   fCuentas->ShowModal();
   if(CDS1->Active)
   {
	  Query2->Refresh();
	  CDS1->Refresh();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Imprimirdetalles1Click(TObject *Sender)
{
   fImprimirCuentas->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Emitirfacturaselectrnicas1Click(TObject *Sender)
{
   fEmitirComprobanteElectronico->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Rastrearpagos1Click(TObject *Sender)
{
   fRastrearPagos->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Agregaruncliente1Click(TObject *Sender)
{
   fAgregarCliente->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Modificardatosdeclientes1Click(TObject *Sender)
{
   fModificarCliente->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Gestionarclienteshabituales1Click(TObject *Sender)
{
   fClientesHabituales->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Agregarunacomida1Click(TObject *Sender)
{
   fAgregarComida->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Modificarunacomida1Click(TObject *Sender)
{
   fModificarComida->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Gestionarmensemanal1Click(TObject *Sender)
{
   fMenuSemanal->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Configurarunaalarma1Click(TObject *Sender)
{
   fConfigurarAlarma->llamador = 0;
   fConfigurarAlarma->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Gestionaralarmas1Click(TObject *Sender)
{
   fGestionarAlarmas->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Verfacturasemitidas1Click(TObject *Sender)
{
   fVerComprobantesElectronicos->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Facturacinmensual1Click(TObject *Sender)
{
   fFacturacionMensual->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Configuracionesdeprograma1Click(TObject *Sender)
{
   fConfiguraciones->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Gestindeprecioes1Click(TObject *Sender)
{
   fPrecios->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Verdetallesdedeuda1Click(TObject *Sender)
{
   fComprobantesX->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Gestionarrepartos1Click(TObject *Sender)
{
   fRepartos->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Gestinderecetas1Click(TObject *Sender)
{
   fRecetas->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::GestiondeGastos1Click(TObject *Sender)
{
   fGestionDeGastos->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Ingredientes1Click(TObject *Sender)
{
   fIngredientes->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Composiciondecomidas1Click(TObject *Sender)
{
   fFormulaComidas->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::InformacionNutricional1Click(TObject *Sender)
{
   fInformacionNutricional->preseleccion = false;
   fInformacionNutricional->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Frecuencias1Click(TObject *Sender)
{
   fFrecuenciaComidas->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Gestionarmenparaoficinas1Click(TObject *Sender)
{
   fMenuOficina->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMain::Gestiondeproductos1Click(TObject *Sender)
{
	fProductos->ShowModal();
}
//---------------------------------------------------------------------------


