//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#include <IniFiles.hpp>
#pragma hdrstop

#include "uImprimirPlanillas.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
TfImprimirPlanillas *fImprimirPlanillas;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfImprimirPlanillas::TfImprimirPlanillas(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfImprimirPlanillas::Button1Click(TObject *Sender)
{
   if(Application->MessageBox(L"Se van a imprimir las planillas seleccionadas. Desea continuar?" ,L"Imprimir planillas?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
	  return;

   CanPrint = false;
   String imp_actual;

   TIniFile *Configuraciones;
   String Dir = GetCurrentDir()+"//Config.ini";
   Configuraciones = new TIniFile(Dir);
   imp_actual = Configuraciones->ReadString("Impresion","ImpresoraPlanillas","NO_CONFIGURADA");


   if(imp_actual != "NO_CONFIGURADA")
   {
	  CanPrint = true;

	  int imp_index;

	  if(CanPrint)
	  {
		 TPrinter *printer;
		 printer = new TPrinter;
		 for(imp_index=0; imp_index<printer->Printers->Count; imp_index++)
		 {
			if(printer->Printers->Strings[imp_index] == imp_actual)
			   break;
		 }
		 if(imp_index < printer->Printers->Count)
			CanPrint = true;
		 else
		 {
			CanPrint = false;
			Configuraciones->WriteString("Impresion","ImpresoraPlanillas","NO CONFIGURADA");
		 }
	  }
      delete Configuraciones;

      if(CanPrint)
	  {

		 CDS->Active = false;

		 String q;

		 if(ComboBox1->ItemIndex != 0)
		 {
			TfrxMemoView * Repartidor = dynamic_cast <TfrxMemoView *> (fImprimirPlanillas->frxReport1->FindObject("Memo1"));
		    Repartidor->Text = "Repartidor: " + ComboBox1->Text + "          Fecha: " + FormatDateTime("dddd dd 'de' mmmm 'de' yyyy", MC->Date);

			Query1->Close();
			Query1->SQL->Clear();
			Query1->SQL->Add(consulta);
			Query1->ParamByName("rep")->AsInteger = idRepartidor;
			Query1->ParamByName("sab")->AsInteger = esSabado;
			Query1->ParamByName("d")->AsDate = MC->Date;
			Query1->Open();

			CDS->Active = true;
			frxReport1->PrepareReport(true);
			frxReport1->PrintOptions->Printer = imp_actual;
			frxReport1->Print();
			CDS->Active = false;
			Query1->Close();
		 }
		 else
		 {
			QueryAux->Close();
			QueryAux->SQL->Clear();
			QueryAux->SQL->Add("SELECT DISTINCT refRepartidor, "
			                   "(SELECT descripcion FROM repartidores WHERE repartos.refRepartidor = repartidores.idRepartidor) AS nombre "
							   "FROM repartos WHERE esSabado = :es AND refCliente > 2 ORDER BY nombre");
			QueryAux->ParamByName("es")->AsInteger = esSabado;
			QueryAux->Open();

			QueryAux->First();

			while(!QueryAux->Eof)
			{
				TfrxMemoView * Repartidor = dynamic_cast <TfrxMemoView *> (fImprimirPlanillas->frxReport1->FindObject("Memo1"));
		     	Repartidor->Text = "Repartidor: " + QueryAux->FieldByName("nombre")->AsString + "          Fecha: " + FormatDateTime("dddd dd 'de' mmmm 'de' yyyy", MC->Date);


			   Query1->Close();
			   Query1->SQL->Clear();
			   Query1->SQL->Add(consulta);
			   Query1->ParamByName("rep")->AsInteger = QueryAux->FieldByName("refRepartidor")->AsInteger;
			   Query1->ParamByName("sab")->AsInteger = esSabado;
			   Query1->ParamByName("d")->AsDate = MC->Date;
			   Query1->Open();

			   CDS->Active = true;
			   frxReport1->PrepareReport(true);
			   frxReport1->PrintOptions->Printer = imp_actual;
			   frxReport1->Print();
			   CDS->Active = false;
			   Query1->Close();

			   QueryAux->Next();
			}
			QueryAux->Close();

		 }
      }
      else
      {
		 String str;
		 str = "Se produjo un error al intentar localizar la impresora seleccionada.";
		 str = str + '\n';
		 str = str + "La reconfiguraracion de la impresora podria solucionar el problema.";

		 Application->MessageBox(str.w_str() ,L"Error", MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  }
   }
   else
   {
	  delete Configuraciones;
	  Application->MessageBox(L"Debe configurar una impresora antes de imprimir." ,L"Error",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
   }

   Button1->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfImprimirPlanillas::FormShow(TObject *Sender)
{
   MC->Date = Now();

   MCClick(fImprimirPlanillas);

   Button1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirPlanillas::ComboBox1Change(TObject *Sender)
{
   if(ComboBox1->ItemIndex == 0)
	  idRepartidor = 0;
   else
   {
	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("SELECT idRepartidor FROM repartidores WHERE descripcion = :des LIMIT 1");
	  QueryAux->ParamByName("des")->AsString = ComboBox1->Text;
	  QueryAux->Open();
	  idRepartidor = QueryAux->FieldByName("idRepartidor")->AsInteger;
	  QueryAux->Close();
   }
}
//---------------------------------------------------------------------------


void __fastcall TfImprimirPlanillas::MCClick(TObject *Sender)
{
   if(DayOfTheWeek(MC->Date) == DaySaturday)
	  esSabado = 1;
   else
	  esSabado = 0;


   QueryAux->Close();
   QueryAux->SQL->Clear();

   if(esSabado)
	  QueryAux->SQL->Add("SELECT descripcion FROM repartidores WHERE reparteSabados = 1 ORDER BY descripcion");
   else
	  QueryAux->SQL->Add("SELECT descripcion FROM repartidores ORDER BY descripcion");

   QueryAux->Open();

   ComboBox1->Clear();
   QueryAux->First();
   ComboBox1->Items->Add("Todas las planillas");

   while(!QueryAux->Eof)
   {
	  ComboBox1->Items->Add(QueryAux->FieldByName("descripcion")->AsString);

	  QueryAux->Next();
   }
   QueryAux->Close();
   ComboBox1->ItemIndex = 0;
   idRepartidor = 0;

   Button1->Enabled = true;

   CBxViernes->Checked = false;
   CBxSabado->Checked = false;
   CBxDeshabilitar->Checked = false;
}
//---------------------------------------------------------------------------




void __fastcall TfImprimirPlanillas::FormClose(TObject *Sender, TCloseAction &Action)

{
   CDS->Active = false;
   Query1->Close();
   QueryAux->Close();
   SQLConnection1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirPlanillas::Button2Click(TObject *Sender)
{

		if(ComboBox1->ItemIndex == 0)
		{
		   Application->MessageBox(L"Antes debe seleccioar una planilla específica para mostrar" ,L"Imprimir planillas?",MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON2);
		   return;
		}

		 TfrxMemoView * titulo = dynamic_cast <TfrxMemoView *> (fImprimirPlanillas->frxReport1->FindObject("Memo1"));
		 titulo->Text = "Repartidor: " + ComboBox1->Text + "          Fecha: " + FormatDateTime("dddd dd 'de' mmmm 'de' yyyy", MC->Date);

		 CDS->Active = false;

		 if(ComboBox1->ItemIndex != 0)
		 {
			Query1->Close();
			Query1->SQL->Clear();
			Query1->SQL->Add(consulta);
			Query1->ParamByName("rep")->AsInteger = idRepartidor;
			Query1->ParamByName("sab")->AsInteger = esSabado;
			Query1->ParamByName("d")->AsDate = MC->Date;
			Query1->Open();

			CDS->Active = true;
			frxReport1->PrepareReport(true);
			frxReport1->ShowReport(true);
			CDS->Active = false;
			Query1->Close();
		 }
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirPlanillas::Button3Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirPlanillas::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;

   /*

   consulta = "SELECT idReparto, refCliente, refRepartidor, posicion, esSabado, "
			 "(SELECT txtComplemento FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d AND cargaManual = 0) LIMIT 1) AS comp, "
			 "(SELECT nroBandejas FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d AND cargaManual = 0) LIMIT 1) AS bandGrand, "
			 "(SELECT nroUnidades FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND nroUnidades <> nroBandejas AND cantidades.fecha = :d AND cargaManual = 0) LIMIT 1) AS unid, "
			 "(SELECT calle FROM clientes WHERE refCliente = idCliente LIMIT 1) AS calle, "
			 "(SELECT numero FROM clientes WHERE refCliente = idCliente LIMIT 1) AS numero, "

			 "(SELECT valor "
				"FROM listasPrecio WHERE "
					"(SELECT refListaPrecio FROM clientes WHERE clientes.idCliente = repartos.refCliente LIMIT 1) = idListaPrecio LIMIT 1) * (SELECT nroUnidades FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d) LIMIT 1) * (SELECT ((100.0 - bonificacion) / 100.0) FROM clientes WHERE clientes.idCliente = repartos.refCliente LIMIT 1) "
				"AS valorPedido, "

			 "(SELECT valor "
				"FROM listasPrecio WHERE "
					"(SELECT refListaPrecio FROM clientes WHERE clientes.idCliente = repartos.refCliente LIMIT 1) = idListaPrecio LIMIT 1) * (SELECT ((100.0 - bonificacion) / 100.0) FROM clientes WHERE clientes.idCliente = repartos.refCliente LIMIT 1) * (SELECT nroUnidades FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d) LIMIT 1) + (SELECT (acumuladoGlobal) AS acumGlobal FROM clientes WHERE refCliente = idCliente LIMIT 1) "
				"AS saldoTotal, "

			 "(SELECT (acumuladoGlobal - acumuladoParcial) AS deuda FROM clientes WHERE refCliente = idCliente LIMIT 1) AS deuda "

			 "FROM repartos WHERE (refRepartidor = :rep AND esSabado = :sab) "

			 "UNION ALL ("

			 "SELECT 0 AS idReparto, refCliente, refRepartidor, 100 AS posicion, :sab AS esSabado, txtComplemento AS comp, "
			 "nroBandejas AS bandGrand, nroUnidades AS unid, "
			 "(SELECT calle FROM clientes WHERE refCliente = idCliente LIMIT 1) AS calle, "
			 "(SELECT numero FROM clientes WHERE refCliente = idCliente LIMIT 1) AS numero, "

			 "(SELECT valor "
				"FROM listasPrecio WHERE "
					"(SELECT refListaPrecio FROM clientes WHERE clientes.idCliente = cantidades.refCliente LIMIT 1) = idListaPrecio LIMIT 1) * nroUnidades * (SELECT ((100.0 - bonificacion) / 100.0) FROM clientes WHERE clientes.idCliente = cantidades.refCliente LIMIT 1) "
				"AS valorPedido, "

			 "(SELECT valor "
				"FROM listasPrecio WHERE "
					"(SELECT refListaPrecio FROM clientes WHERE clientes.idCliente = cantidades.refCliente LIMIT 1) = idListaPrecio LIMIT 1) * (SELECT ((100.0 - bonificacion) / 100.0) FROM clientes WHERE clientes.idCliente = cantidades.refCliente LIMIT 1) * nroUnidades + (SELECT (acumuladoGlobal) AS acumGlobal FROM clientes WHERE refCliente = idCliente LIMIT 1) "
				"AS saldoTotal, "

			 "(SELECT (acumuladoGlobal - acumuladoParcial) AS deuda FROM clientes WHERE refCliente = idCliente LIMIT 1) AS deuda "

			 "FROM cantidades WHERE (fecha = :d AND refRepartidor = :rep AND cargaManual = 1) )"



			  "ORDER BY posicion"; */

   consulta = "SELECT idReparto, refCliente, refRepartidor, posicion, esSabado, "
			 "(SELECT txtComplemento FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d AND cargaManual = 0) LIMIT 1) AS comp, "
			 "(SELECT medioPago FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d AND cargaManual = 0) LIMIT 1) AS medioPago, "
			 "(SELECT nroBandejas FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d AND cargaManual = 0) LIMIT 1) AS bandGrand, "
			 "(SELECT nroUnidades FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND nroUnidades <> nroBandejas AND cantidades.fecha = :d AND cargaManual = 0) LIMIT 1) AS unid, "
			 "IFNULL((SELECT nroUnidades FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = DATE_ADD(:d, INTERVAL -1 DAY)) LIMIT 1), 0) AS unidAyer, "
			 "(SELECT calle FROM clientes WHERE refCliente = idCliente LIMIT 1) AS calle, "
			 "(SELECT numero FROM clientes WHERE refCliente = idCliente LIMIT 1) AS numero, "
			 "(SELECT pagoAdelantado FROM clientes WHERE refCliente = idCliente LIMIT 1) AS pagoAdelantado, "
			 "(SELECT CASE WHEN menuImpreso = 'S' THEN 1 ELSE 0 END FROM clientes WHERE refCliente = idCliente LIMIT 1) AS menuImpreso, "
			 "(SELECT refFrecuenciaPago FROM clientes WHERE refCliente = idCliente LIMIT 1) AS frecuenciaPago, "
			 "(SELECT refDiaPago FROM clientes WHERE refCliente = idCliente LIMIT 1) AS diaPago, "

			 "(SELECT valor "
				"FROM listasPrecio WHERE "
					"(SELECT refListaPrecio FROM clientes WHERE clientes.idCliente = repartos.refCliente LIMIT 1) = idListaPrecio LIMIT 1) * (SELECT nroUnidades FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d) LIMIT 1) * (SELECT ((100.0 - bonificacion) / 100.0) FROM clientes WHERE clientes.idCliente = repartos.refCliente LIMIT 1) "
				"AS valorPedido, "

			 "(SELECT valor "
				"FROM listasPrecio WHERE "
					"(SELECT refListaPrecio FROM clientes WHERE clientes.idCliente = repartos.refCliente LIMIT 1) = idListaPrecio LIMIT 1) * (SELECT ((100.0 - bonificacion) / 100.0) FROM clientes WHERE clientes.idCliente = repartos.refCliente LIMIT 1) * (SELECT nroUnidades FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d) LIMIT 1) + (SELECT (acumuladoGlobal) AS acumGlobal FROM clientes WHERE refCliente = idCliente LIMIT 1) "
				"AS saldoTotal, "

			 "(SELECT valor "
				"FROM listasPrecio WHERE "
					"(SELECT refListaPrecio FROM clientes WHERE clientes.idCliente = repartos.refCliente LIMIT 1) = idListaPrecio LIMIT 1) * (SELECT ((100.0 - bonificacion) / 100.0) FROM clientes WHERE clientes.idCliente = repartos.refCliente LIMIT 1) * (SELECT nroUnidades FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d) LIMIT 1) + (SELECT (acumuladoGlobal) AS acumGlobal FROM clientes WHERE refCliente = idCliente LIMIT 1) "
				"AS var_dummy, "

			 "(SELECT (acumuladoGlobal - acumuladoParcial) AS deuda FROM clientes WHERE refCliente = idCliente LIMIT 1) AS deuda "

			 "FROM repartos WHERE (refRepartidor = :rep AND esSabado = :sab) "

			  "ORDER BY posicion";



//consulta = "SELECT repartos.idReparto, repartos.refCliente, repartos.refRepartidor, repartos.posicion, repartos.esSabado, "
//			 "cantidades2.txtComplemento AS comp, "
//			 "cantidades2.medioPago AS medioPago, "
//			 "cantidades2.nroBandejas AS bandGrand, "
//			 "cantidades2.nroUnidades AS unid, "
//			 "IFNULL((SELECT nroUnidades FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = DATE_ADD(:d, INTERVAL -1 DAY)) LIMIT 1), 0) AS unidAyer, "
//			 "clientes2.calle AS calle, "
//			 "clientes2.numero AS numero, "
//			 "clientes2.pagoAdelantado AS pagoAdelantado, "
//			 "CASE WHEN clientes2.menuImpreso = 'S' THEN 1 ELSE 0 END AS menuImpreso, "
//			 "clientes2.refFrecuenciaPago AS frecuenciaPago, "
//			 "clientes2.refDiaPago AS diaPago, "
//
//			 "(SELECT valor "
//				"FROM listasPrecio WHERE "
//					"clientes2.refListaPrecio = idListaPrecio LIMIT 1) * (SELECT nroUnidades FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d) LIMIT 1) * ((100.0 - clientes2.bonificacion) / 100.0) "
//				"AS valorPedido, "
//
//			 "((SELECT valor "
//				"FROM listasPrecio WHERE "
//					"clientes2.refListaPrecio = idListaPrecio LIMIT 1) * ((100.0 - clientes2.bonificacion) / 100.0) * (SELECT nroUnidades FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d) LIMIT 1) + (clientes2.acumuladoGlobal)) "
//				"AS saldoTotal, "
//
//			 "((SELECT valor "
//				"FROM listasPrecio WHERE "
//					"clientes2.refListaPrecio = idListaPrecio LIMIT 1) * ((100.0 - clientes2.bonificacion) / 100.0) * (SELECT nroUnidades FROM cantidades WHERE (cantidades.refCliente = repartos.refCliente AND cantidades.fecha = :d) LIMIT 1) + (clientes2.acumuladoGlobal)) "
//				"AS var_dummy, "
//
//			 "(clientes2.acumuladoGlobal - clientes2.acumuladoParcial) AS deuda "
//
//			 "FROM repartos "
//			 " LEFT JOIN cantidades AS cantidades2 ON cantidades2.refCliente = repartos.refCliente AND cantidades2.fecha = :d AND cantidades2.cargaManual = 0"
//			 " LEFT JOIN clientes AS clientes2 ON clientes2.idCliente = repartos.refCliente "
//
//			 " WHERE (repartos.refRepartidor = :rep AND repartos.esSabado = :sab) "
//
//			  "ORDER BY posicion";




}
//---------------------------------------------------------------------------

void __fastcall TfImprimirPlanillas::CDSsaldoTotalValidate(TField *Sender)
{
   CDS->FieldByName("saldoTotal")->AsFloat = CDS->FieldByName("valorPedido")->AsFloat + CDS->FieldByName("deuda")->AsFloat;
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirPlanillas::CDSdeudaGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
   if(Sender->AsFloat == 0 || Sender->AsFloat > 30000)
   {
	  Text = "";
	  return;
   }
   if(Sender->AsFloat > 0)
   {
	  Text = "Debe: " + FormatFloat("$0", Sender->AsFloat);
	  return;
   }
   if(Sender->AsFloat < 0)
   {
	  Text = "A fav.: " + FormatFloat("$0", Sender->AsFloat * -1.0);
	  return;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirPlanillas::CDSvalorPedidoGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
   if(Sender->AsFloat == 0)
   {
	  Text = "";
	  return;
   }
   if(Sender->AsFloat > 0)
   {
	  Text = "Valor: " + FormatFloat("$0", Sender->AsFloat);
	  return;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirPlanillas::CDSsaldoTotalGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
   if(Sender->AsFloat == 0 || Sender->AsFloat > 30000)
   {
	  Text = "";
	  return;
   }
   if(Sender->AsFloat > 0)
   {
	  Text = "Saldo hoy: " + FormatFloat("$0", Sender->AsFloat);
	  return;
   }
   if(Sender->AsFloat < 0)
   {
	  Text = "A fav. hoy: " + FormatFloat("$0", Sender->AsFloat * -1.0);
	  return;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirPlanillas::CDSvar_dummyGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
   if(CBxDeshabilitar->Checked)
   {
      Text = "";
	  return;
   }
   if(Sender->DataSet->FieldByName("bandGrand")->AsInteger == 0)
   {
	  Text = "";
	  return;
   }
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
	   if(CBxViernes->Checked && Sender->DataSet->FieldByName("diaPago")->AsInteger == 5)
	   {
		  Text = "$" + Sender->AsString;
		  return;
	   }
	   if(CBxSabado->Checked && Sender->DataSet->FieldByName("diaPago")->AsInteger == 6)
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


void __fastcall TfImprimirPlanillas::CDSmenuImpresoGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText)
{
   if(CBxViernes->Checked || DayOfTheWeek(MC->Date) == 5)
   {
	   if(Sender->AsInteger == 1)
	   {
		  Text = "M";
	   }
	   else
		  Text = "";

	   return;
   }

   if((CBxSabado->Checked || DayOfTheWeek(MC->Date) == 6) && !(CBxViernes->Checked || DayOfTheWeek(MC->Date) == 5))
   {
	   if(CDS->FieldByName("unidAyer")->AsFloat > 0)
	   {
	      Text = "";
		  return;
	   }
	   if(Sender->AsInteger == 1)
	   {
		  Text = "M";
	   }
	   else
		  Text = "";

	   return;
   }

   Text = "";
   return;
}
//---------------------------------------------------------------------------

