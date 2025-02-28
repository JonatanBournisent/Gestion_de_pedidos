//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "uImprimirCuentas.h"
#include "uSeleccionarCliente.h"
#include "uImprimirResumenManual.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma link "frxExportPDF"
#pragma link "frxExportBaseDialog"
#pragma resource "*.dfm"
TfImprimirCuentas *fImprimirCuentas;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfImprimirCuentas::TfImprimirCuentas(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfImprimirCuentas::Button1Click(TObject *Sender)
{
   String q;

   usarSaldos = false;

   if((RG1->ItemIndex <= 1) && (!CheckBox1->Checked))
   {
	  QueryAux->Close();
	  QueryAux->SQL->Clear();
	  QueryAux->SQL->Add("SELECT fecha FROM cuentas WHERE fecha >= :fi LIMIT 1");
	  if(RG1->ItemIndex == 0)
		 QueryAux->ParamByName("fi")->AsDate = StartOfTheWeek(DateOf(Now()));
	  else if(RG1->ItemIndex == 1)
		 QueryAux->ParamByName("fi")->AsDate = StartOfTheMonth(DateOf(Now()));
	  QueryAux->Open();

	  if(!QueryAux->IsEmpty())
		 usarSaldos = true;

	  QueryAux->Close();
   }



   if(CompareDate(MC->Date,DateOf(Now())) == EqualsValue && usarSaldos)
   {
	  q = "SELECT idCliente, nombre, apellido, calle, numero, acumuladoGlobal AS deudaTotal, acumuladoParcial AS subtotal, "
		  "(SELECT posicion FROM repartos WHERE repartos.esSabado = :es AND clientes.idCliente = repartos.refCliente LIMIT 1) AS pos, "
		  "(SELECT refRepartidor FROM repartos WHERE repartos.esSabado = :es AND clientes.idCliente = repartos.refCliente LIMIT 1) AS rep, "
		  "(SELECT 1.0 * COUNT(*) AS cant FROM cuentas WHERE cuentas.fecha >= :fi AND cuentas.fecha <= :ff AND cuentas.refCliente = clientes.idCliente AND valorUnidad > 0) AS unidadesPeriodo, "
		  "(acumuladoGlobal - acumuladoParcial) AS saldoAnterior, "
		  "((SELECT valor FROM listasPrecio WHERE clientes.refListaPrecio = listasPrecio.idListaPrecio LIMIT 1) * ((100.0 - clientes.bonificacion) / 100.0)) AS precio, "
		  "(SELECT 1) AS imprimir, "
		  "(SELECT valorTotal * ((100.0 - (SELECT bonificacion FROM clientes WHERE idCliente = clientes.idCliente AND fecha = :ff LIMIT 1)) / 100.0) FROM cantidades WHERE fecha = :ff AND clientes.idCliente = cantidades.refCliente LIMIT 1) AS agregado ";
   }

   else
   {
	  q = "SELECT idCliente, nombre, apellido, calle, numero, "
		  "(SELECT posicion FROM repartos WHERE esSabado = :es AND idCliente = refCliente LIMIT 1) AS pos, "
		  "(SELECT refRepartidor FROM repartos WHERE esSabado = :es AND idCliente = refCliente LIMIT 1) AS rep, "
		  "(SELECT IFNULL(SUM(saldoParcial),0) FROM cuentas WHERE cuentas.fecha <= :ff AND  cuentas.refCliente = clientes.idCliente) AS deudaTotal, "   //calcula la deuda h/fecha seleccionada
		  "(SELECT 1.0 * COUNT(*) AS cant FROM cuentas WHERE cuentas.fecha >= :fi AND cuentas.fecha <= :ff AND cuentas.refCliente = clientes.idCliente AND valorUnidad > 0) AS unidadesPeriodo, "
		  "(SELECT IFNULL(SUM(valorUnidad),0) FROM cuentas WHERE cuentas.fecha >= :fi AND cuentas.fecha <= :ff AND cuentas.refCliente = clientes.idCliente) AS subtotal, "
		  "(SELECT deudaTotal - subtotal) AS saldoAnterior, "
		  "((SELECT valor FROM listasPrecio WHERE refListaPrecio = idListaPrecio LIMIT 1) * ((100.0 - bonificacion) / 100.0)) AS precio, "
		  "(SELECT 1) AS imprimir, "
		  "(SELECT valorTotal * ((100.0 - (SELECT bonificacion FROM clientes WHERE idCliente = clientes.idCliente AND fecha = :ff LIMIT 1)) / 100.0) FROM cantidades WHERE fecha = :ff AND idCliente = refCliente LIMIT 1) AS agregado ";

   }

   if(RG1->ItemIndex == 0)
   {
	  if(RG2->ItemIndex == 0)
		 q = q + "FROM clientes WHERE(refFrecuenciaPago = 2 AND esVisible = 1 AND refDiaPago <= 5 AND imprimirDetalle = 1) ORDER BY rep, pos";
	  if(RG2->ItemIndex == 1)
		 q = q + "FROM clientes WHERE(refFrecuenciaPago = 2 AND esVisible = 1 AND refDiaPago = 6 AND imprimirDetalle = 1) ORDER BY rep, pos";
   }
   else if(RG1->ItemIndex == 1)
	  q = q + "FROM clientes WHERE(refFrecuenciaPago = 3 AND esVisible = 1 AND imprimirDetalle = 1) ORDER BY rep, pos";

   CDS->Active = false;
   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add(q);

   Query1->ParamByName("es")->AsInteger = RG2->ItemIndex;

   if(RG1->ItemIndex == 0)
	  Query1->ParamByName("fi")->AsDate = StartOfTheWeek(MC->Date);
   else if(RG1->ItemIndex == 1)
	  Query1->ParamByName("fi")->AsDate = StartOfTheMonth(MC->Date);

   Query1->ParamByName("ff")->AsDate = MC->Date;
   Query1->Open();
   CDS->Active = true;


   CDS->First();
   while(!CDS->Eof)
   {
	  CDS->Edit();
	  if(CDS->FieldByName("agregado")->AsInteger == NULL)
	  {
		 CDS->FieldByName("agregado")->AsFloat = 0;
		 CDS->FieldByName("imprimir")->AsFloat = 0;
	  }
	  if(CDS->FieldByName("unidadesPeriodo")->AsFloat == NULL)
		 CDS->FieldByName("unidadesPeriodo")->AsFloat = 0;
	  if(CDS->FieldByName("saldoAnterior")->AsFloat == NULL)
		 CDS->FieldByName("saldoAnterior")->AsFloat = 0;
	  if(CDS->FieldByName("subtotal")->AsFloat == NULL)
		 CDS->FieldByName("subtotal")->AsFloat = 0;
	  if(CDS->FieldByName("deudaTotal")->AsFloat == NULL)
		 CDS->FieldByName("deudaTotal")->AsFloat = 0;
	  CDS->Next();
   }
   CDS->First();

   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);

   Button2->Enabled = false;

}
//---------------------------------------------------------------------------
void __fastcall TfImprimirCuentas::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, TGridDrawState State)
{
   int DrawState;
   if(State.Contains(gdFocused))
   {
	  if(Column->Field == CB->Field)
	  {
		 CB->Left = Rect.Left + DBGrid1->Left + 2;
		 CB->Top = Rect.Top + DBGrid1->Top + 2;
		 CB->Width = Rect.Right - Rect.Left;
		 CB->Height = Rect.Bottom - Rect.Top;

		 CB->Visible = true;
	  }
   }
   else if(Column->Index == 7)
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

void __fastcall TfImprimirCuentas::DBGrid1ColExit(TObject *Sender)
{
   if(DBGrid1->SelectedField == CB->Field)
	  CB->Visible = false;

   if(CDS->Active && CDS->State == dsEdit)
	  CDS->Post();
}
//---------------------------------------------------------------------------


void __fastcall TfImprimirCuentas::Button4Click(TObject *Sender)
{
   Button2->Enabled = false;

   if(CDS->RecordCount == 0)
   {
	  Application->MessageBox(L"No hay comprobantes para imprimir..." ,L"No hay comprobantes para imprimir!",MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
	  return;
   }
   else if(CDS->RecordCount == 1)
   {
	  if(Application->MessageBox(L"Se va a generar e imprimir un nuevo comprobante X. Desea continuar?" ,L"Imprimir comprobante?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
		 return;
   }
   else
   {
	  if(Application->MessageBox(L"Se van a generar e imprimir nuevos comprobantes X. Desea continuar?" ,L"Imprimir comprobantes?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
		 return;
   }

   CanPrint = false;
   String imp_actual;
   String DirComprobantesX;

   TIniFile *Configuraciones;
   String Dir = GetCurrentDir()+"//Config.ini";
   Configuraciones = new TIniFile(Dir);

   if(Sender == Button2) //para imprimir en PDF
	  imp_actual = Configuraciones->ReadString("Impresion","ImpresoraPDF","NO_CONFIGURADA");
   else if(!chbTicket->Checked)
	  imp_actual = Configuraciones->ReadString("Impresion","ImpresoraPresupuestos","NO_CONFIGURADA");
   else
	  imp_actual = Configuraciones->ReadString("Impresion","ImpresoraPlanillas","NO_CONFIGURADA");

   DirComprobantesX = Configuraciones->ReadString("Directorios","ComprobantesX","NO_CONFIGURADA");

   if(DirComprobantesX == "NO_CONFIGURADA")
   {
	   delete Configuraciones;
	   Application->MessageBox(L"Antes de continuar debe configurar un directorio para guardar las copias de respaldo" ,L"Configurar directorio.",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	   return;
   }


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
			if(!chbTicket->Checked)
			   Configuraciones->WriteString("Impresion","ImpresoraPresupuestos","NO CONFIGURADA");
			else
			   Configuraciones->WriteString("Impresion","ImpresoraPlanillas","NO CONFIGURADA");
		 }
	  }
	  delete Configuraciones;

	  int repartidorAnterior;

	  if(CanPrint)
	  {
		 repartidorAnterior = CDS->FieldByName("rep")->AsInteger;
		 while(!CDS->Eof)
		 {
			if(CDS->FieldByName("rep")->AsInteger != repartidorAnterior)
			{
			   Application->MessageBox(L"Se imprimieron todos los comprobantes asignados a un repartidor, presione OK para continuar con el siguiente" ,L"Presione OK para continuar.",MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
			   repartidorAnterior = CDS->FieldByName("rep")->AsInteger;
			}

			if(CDS->FieldByName("imprimir")->AsInteger == 1)
			{

				String q1,q2;



				if(CompareDate(MC->Date,DateOf(Now())) == EqualsValue && usarSaldos)
				{
				   q1 = "SELECT "
					 "t.unidades AS unidades, t.valorUnidad AS valorUnidad, t.subtotal AS subtotal, t.detalle AS detalle "
					 "FROM "

					 "("
						"( "
						   "SELECT "
						   "(SELECT 1.0) AS unidades, "
						   "valorUnidad, "
						   "(valorUnidad) AS subtotal, "
						   "CONCAT('Pedido ', DATE_FORMAT(fecha, '%d/%m/%Y')) AS detalle "
						   "FROM cuentas WHERE fecha >= :fi AND fecha <= :ff AND refCliente = :refCliente AND unidades > 0 ORDER BY fecha"
						") "

						"UNION ALL "
						"( "
						   "SELECT "
						   "(SELECT 1.0) AS unidades, "
						   "CAST((SELECT :u) AS DECIMAL(19,2)) AS valorUnidad, "
						   "CAST((SELECT :u) AS DECIMAL(19,2)) AS subtotal, "

						   "CONCAT('Pedido ', DATE_FORMAT(:fechaDetalle, '%d/%m/%Y')) AS detalle "
						") "

						"UNION ALL "
						"( "
						   "SELECT (SELECT 1.0) AS unidades, "
						   "((SELECT (acumuladoGlobal - acumuladoParcial) FROM clientes WHERE idCliente = :refCliente)) AS valorUnidad, "
						   "((SELECT (acumuladoGlobal - acumuladoParcial) FROM clientes WHERE idCliente = :refCliente)) AS subtotal, "
						   "CONCAT('Saldo al ', DATE_FORMAT(:fechaSaldo, '%d/%m/%Y')) AS detalle"
						")"
					 ") t "
					 "WHERE t.subtotal <> 0";
				}
				else
				{
				   q1 = "SELECT "
					 "t.unidades AS unidades, t.valorUnidad AS valorUnidad, t.subtotal AS subtotal, t.detalle AS detalle "
					 "FROM "

					 "("
						"( "
						   "SELECT "
						   "(SELECT 1.0) AS unidades, "
						   "valorUnidad, "
						   "(valorUnidad) AS subtotal, "
						   "CONCAT('Pedido ', DATE_FORMAT(fecha, '%d/%m/%Y')) AS detalle "
						   "FROM cuentas WHERE fecha >= :fi AND fecha <= :ff AND refCliente = :refCliente AND unidades > 0 ORDER BY fecha"
						") "

						"UNION ALL "
						"( "
						   "SELECT "
						   "(SELECT 1.0) AS unidades, "
						   "CAST((SELECT :u) AS DECIMAL(19,2)) AS valorUnidad, "
						   "CAST((SELECT :u) AS DECIMAL(19,2)) AS subtotal, "

						   "CONCAT('Pedido ', DATE_FORMAT(:fechaDetalle, '%d/%m/%Y')) AS detalle "
						") "

						"UNION ALL "
						"( "
						   "SELECT (SELECT 1.0) AS unidades, "
						   "((SELECT IFNULL(SUM(saldoParcial),0) FROM cuentas WHERE refCliente = :refCliente AND fecha <= :fechaSaldo) - (SELECT IFNULL(SUM(pagoRealizado),0) FROM cuentas WHERE refCliente = :refCliente AND fecha >= :fi AND fecha <= :ff)) AS valorUnidad, "
						   "((SELECT IFNULL(SUM(saldoParcial),0) FROM cuentas WHERE refCliente = :refCliente AND fecha <= :fechaSaldo) - (SELECT IFNULL(SUM(pagoRealizado),0) FROM cuentas WHERE refCliente = :refCliente AND fecha >= :fi AND fecha <= :ff)) AS subtotal, "
						   "CONCAT('Saldo al ', DATE_FORMAT(:fechaSaldo, '%d/%m/%Y')) AS detalle"
						")"
					 ") t "
					 "WHERE t.subtotal <> 0";
				}


				CDS2->Active = false;
				Query2->Close();
				Query2->SQL->Clear();
				Query2->SQL->Add(q1);
				if(RG1->ItemIndex == 0)
				{
				   Query2->ParamByName("fi")->AsDate = StartOfTheWeek(MC->Date);
				   Query2->ParamByName("ff")->AsDate = MC->Date;
				   Query2->ParamByName("fechaSaldo")->AsDate = IncDay(StartOfTheWeek(MC->Date),-2);
				}
				else if(RG1->ItemIndex == 1)
				{
				   Query2->ParamByName("fi")->AsDate = StartOfTheMonth(MC->Date);
				   Query2->ParamByName("ff")->AsDate = MC->Date;
				   Query2->ParamByName("fechaSaldo")->AsDate = IncDay(StartOfTheMonth(MC->Date),-1);
				}
				else if(RG1->ItemIndex == 2)
				{
				   Query2->ParamByName("fi")->AsDate = DateOf(Now());
				   Query2->ParamByName("ff")->AsDate = DateOf(Now());
				   Query2->ParamByName("fechaSaldo")->AsDate = IncDay(DateOf(Now()),-1);
				}
				Query2->ParamByName("refCliente")->AsInteger = CDS->FieldByName("idCliente")->AsInteger;
				Query2->ParamByName("u")->AsFloat = CDS->FieldByName("agregado")->AsFloat;//FormatFloat("0.00", CDS->FieldByName("agregado")->AsFloat);
				Query2->ParamByName("fechaDetalle")->AsDate = MC->Date;

				Query2->Open();
				CDS2->Active = true;


				if(CompareDate(MC->Date,DateOf(Now())) == EqualsValue && usarSaldos)
				{
				   q2 = "SELECT "
						"CONCAT(nombre, ' ', apellido) AS cliente, "
						"CONCAT(calle, ' ', numero) AS domicilio, "
						"(SELECT CAST(:fechaDetalle AS DATE)) AS dfechaDetalle, "
						"(SELECT CAST(:fechaDetalle AS DATE)) AS mfechaDetalle, "
						"(SELECT CAST(:fechaDetalle AS DATE)) AS yfechaDetalle, "
						"(SELECT CAST(:fechaDetalle AS DATE)) AS fechaDetalleMensual, "
						"("

						   "acumuladoGlobal "
						   "+ :u "
						") AS total "
						"FROM clientes WHERE idCliente = :refCLiente";
				}
				else
				{
				   q2 = "SELECT "
						"CONCAT(nombre, ' ', apellido) AS cliente, "
						"CONCAT(calle, ' ', numero) AS domicilio, "
						"(SELECT CAST(:fechaDetalle AS DATE)) AS dfechaDetalle, "
						"(SELECT CAST(:fechaDetalle AS DATE)) AS mfechaDetalle, "
						"(SELECT CAST(:fechaDetalle AS DATE)) AS yfechaDetalle, "
						"(SELECT CAST(:fechaDetalle AS DATE)) AS fechaDetalleMensual, "
						"("

						   ":u "

						   "+ (SELECT IFNULL(SUM(saldoParcial),0) FROM cuentas WHERE refCliente = :refCliente AND fecha <= :ff) "

						") AS total "
						"FROM clientes WHERE idCliente = :refCLiente";
				}


				CDS3->Active = false;
				Query3->Close();
				Query3->SQL->Clear();
				Query3->SQL->Add(q2);
				if(RG1->ItemIndex == 0)
				{
				   if(!(CompareDate(MC->Date,DateOf(Now())) == EqualsValue && usarSaldos))
				      Query3->ParamByName("ff")->AsDate = MC->Date;
				}
				else if(RG1->ItemIndex == 1)
				{
				   if(!(CompareDate(MC->Date,DateOf(Now())) == EqualsValue && usarSaldos))
					  Query3->ParamByName("ff")->AsDate = MC->Date;
				}
				else if(RG1->ItemIndex == 2)
				{
				   if(!(CompareDate(MC->Date,DateOf(Now())) == EqualsValue && usarSaldos))
					  Query3->ParamByName("ff")->AsDate = DateOf(Now());
				}
				Query3->ParamByName("refCliente")->AsInteger = CDS->FieldByName("idCliente")->AsInteger;
				Query3->ParamByName("u")->AsFloat = CDS->FieldByName("agregado")->AsFloat;
				Query3->ParamByName("fechaDetalle")->AsDate = MC->Date;

				Query3->Open();
				CDS3->Active = true;

				QueryAux->Close();
				QueryAux->SQL->Clear();
				QueryAux->SQL->Add("INSERT INTO comprobantesX (fechaComprobante, fechaEmision, refCliente, total) "
								   "VALUES(:fc, NOW(), :rc, :total)");
				QueryAux->ParamByName("fc")->AsDate = MC->Date;
				QueryAux->ParamByName("rc")->AsInteger = CDS->FieldByName("idCliente")->AsInteger;
				QueryAux->ParamByName("total")->AsFloat = CDS3->FieldByName("total")->AsFloat;
				QueryAux->ExecSQL();

				QueryAux->Close();
				QueryAux->SQL->Clear();
				QueryAux->SQL->Add("SELECT MAX(idComprobanteX) AS maxid FROM comprobantesX");
				QueryAux->Open();
				String s =  QueryAux->FieldByName("maxid")->AsString;
				QueryAux->Close();

				while(s.Length() < 7)
				   s = s.Insert("0", 1);

				s = "0010 - " + s;	//un punto de venta inventado

				dynamic_cast <TfrxMemoView *> (fImprimirCuentas->frxReport4->FindObject("Memo18"))->Text = s;
				dynamic_cast <TfrxMemoView *> (fImprimirCuentas->frxReport5->FindObject("Memo18"))->Text = s;
				dynamic_cast <TfrxMemoView *> (fImprimirCuentas->frxReport3->FindObject("Memo16"))->Text = s;

				if(RG1->ItemIndex == 0)
				{
				   if(!chbTicket->Checked)
				   {
					   frxReport4->PrepareReport(true);
	//				   frxReport4->ShowReport(true);
					   frxReport4->PrintOptions->Printer = imp_actual;
					   frxReport4->Print();

					   frxPDFExport1->FileName = DirComprobantesX + "\\" + s + ".pdf";
//					   dynamic_cast <TfrxPictureView *> (fImprimirCuentas->frxReport4->FindObject("Picture1"))->Visible = false;
//					   frxReport4->PrepareReport(true);
					   frxReport4->Export(frxPDFExport1);
//					   dynamic_cast <TfrxPictureView *> (fImprimirCuentas->frxReport4->FindObject("Picture1"))->Visible = true;
				   }
				   else
				   {
					   dynamic_cast <TfrxMemoView *> (fImprimirCuentas->frxReport3->FindObject("Memo17"))->Visible = false;

					   frxReport3->PrepareReport(true);
	//				   frxReport3->ShowReport(true);
					   frxReport3->PrintOptions->Printer = imp_actual;
					   frxReport3->Print();

					   frxPDFExport1->FileName = DirComprobantesX + "\\" + s + ".pdf";
//					   dynamic_cast <TfrxPictureView *> (fImprimirCuentas->frxReport3->FindObject("Picture1"))->Visible = false;
//					   frxReport3->PrepareReport(true);
					   frxReport3->Export(frxPDFExport1);
//					   dynamic_cast <TfrxPictureView *> (fImprimirCuentas->frxReport3->FindObject("Picture1"))->Visible = true;
				   }
				}
				else if(RG1->ItemIndex == 1)
				{
				   if(!chbTicket->Checked)
				   {
					   dynamic_cast <TfrxMemoView *> (fImprimirCuentas->frxReport3->FindObject("Memo17"))->Visible = true;

					   frxReport5->PrepareReport(true);
	//				   frxReport5->ShowReport(true);
					   frxReport5->PrintOptions->Printer = imp_actual;
					   frxReport5->Print();

					   frxPDFExport1->FileName = DirComprobantesX + "\\" + s + ".pdf";
//					   dynamic_cast <TfrxPictureView *> (fImprimirCuentas->frxReport5->FindObject("Picture1"))->Visible = false;
//					   frxReport5->PrepareReport(true);
					   frxReport5->Export(frxPDFExport1);
//					   dynamic_cast <TfrxPictureView *> (fImprimirCuentas->frxReport5->FindObject("Picture1"))->Visible = true;
				   }
				   else
				   {
					   frxReport3->PrepareReport(true);
	//				   frxReport3->ShowReport(true);
					   frxReport3->PrintOptions->Printer = imp_actual;
					   frxReport3->Print();

					   frxPDFExport1->FileName = DirComprobantesX + "\\" + s + ".pdf";
//					   dynamic_cast <TfrxPictureView *> (fImprimirCuentas->frxReport3->FindObject("Picture1"))->Visible = false;
//					   frxReport3->PrepareReport(true);
					   frxReport3->Export(frxPDFExport1);
//					   dynamic_cast <TfrxPictureView *> (fImprimirCuentas->frxReport3->FindObject("Picture1"))->Visible = true;
				   }
				}
				else
				{
				   if(!chbTicket->Checked)
				   {
					   frxReport4->PrepareReport(true);
	//				   frxReport4->ShowReport(true);
					   frxReport4->PrintOptions->Printer = imp_actual;
					   frxReport4->Print();

					   frxPDFExport1->FileName = DirComprobantesX + "\\" + s + ".pdf";
//					   dynamic_cast <TfrxPictureView *> (fImprimirCuentas->frxReport4->FindObject("Picture1"))->Visible = false;
//					   frxReport4->PrepareReport(true);
					   frxReport4->Export(frxPDFExport1);
//					   dynamic_cast <TfrxPictureView *> (fImprimirCuentas->frxReport4->FindObject("Picture1"))->Visible = true;
				   }
				   else
				   {
					   frxReport2->PrepareReport(true);
	//				   frxReport2->ShowReport(true);
					   frxReport2->PrintOptions->Printer = imp_actual;
					   frxReport2->Print();

					   frxPDFExport1->FileName = DirComprobantesX + "\\" + s + ".pdf";
//					   dynamic_cast <TfrxPictureView *> (fImprimirCuentas->frxReport2->FindObject("Picture1"))->Visible = false;
//					   frxReport2->PrepareReport(true);
					   frxReport2->Export(frxPDFExport1);
//					   dynamic_cast <TfrxPictureView *> (fImprimirCuentas->frxReport2->FindObject("Picture1"))->Visible = true;
				   }
				}
			}

			CDS->Next();
			if(CDS->Eof)
			   Application->MessageBox(L"Todos los comprobantes fueron enviados a cola de impresión." ,L"Fin de tarea, presione OK para finalizar.",MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
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
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirCuentas::Button5Click(TObject *Sender)
{
   if(!CDS->Active)
	  return;

   CDS->First();
   while(!CDS->Eof)
   {
	  CDS->Edit();
	  CDS->FieldByName("imprimir")->AsInteger = 1;
	  CDS->Next();
   }
   CDS->First();
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirCuentas::Button6Click(TObject *Sender)
{
   if(!CDS->Active)
	  return;

   CDS->First();
   while(!CDS->Eof)
   {
	  CDS->Edit();
	  CDS->FieldByName("imprimir")->AsInteger = 0;
	  CDS->Next();
   }
   CDS->First();
}
//---------------------------------------------------------------------------


void __fastcall TfImprimirCuentas::Button7Click(TObject *Sender)
{
   CDS->First();
   Button2->Enabled = false;

   Button4Click(Button7);
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirCuentas::RG1Click(TObject *Sender)
{
   if(RG1->ItemIndex != 0)
	  RG2->Enabled = false;
   else
	  RG2->Enabled = true;

   if(RG1->ItemIndex > 1)
      Button1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirCuentas::Button8Click(TObject *Sender)
{
   if(!usarClienteIndicado)
   {
	  fSeleccionarCliente->llamador = 1;
	  fSeleccionarCliente->ShowModal();

	  if(fSeleccionarCliente->idSeleccionado < 2)
		 return;

	  refClienteIndicado = fSeleccionarCliente->idSeleccionado;  //Lo aprovecho para recalcular al cambiar la fecha
   }

   String q;

   q = "SELECT idCliente, nombre, apellido, calle, numero, "
	   "(SELECT 1) AS rep, "   //repartidor para completar el campo, inventado
	   "(SELECT IFNULL(SUM(saldoParcial),0) FROM cuentas WHERE cuentas.fecha <= :ff AND  cuentas.refCliente = clientes.idCliente) AS deudaTotal, "   //calcula la deuda h/fecha seleccionada
	   "(SELECT 1.0 * COUNT(*) AS cant FROM cuentas WHERE cuentas.fecha >= :fi AND cuentas.fecha <= :ff AND cuentas.refCliente = clientes.idCliente) AS unidadesPeriodo, "
	   "(SELECT IFNULL(SUM(valorUnidad),0) FROM cuentas WHERE cuentas.fecha >= :fi AND cuentas.fecha <= :ff AND cuentas.refCliente = clientes.idCliente) AS subtotal, "
	   "(SELECT deudaTotal - subtotal) AS saldoAnterior, "
	   "((SELECT valor FROM listasPrecio WHERE refListaPrecio = idListaPrecio LIMIT 1) * ((100.0 - bonificacion) / 100.0)) AS precio, "
	   "(SELECT 1) AS imprimir, "
	   "(SELECT valorTotal FROM cantidades WHERE fecha = :ff AND idCliente = refCliente LIMIT 1) AS agregado "
	   "FROM clientes WHERE(idCliente = :idC)";

   CDS->Active = false;
   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add(q);

   if(refClienteIndicado > 2)
	  Query1->ParamByName("idC")->AsInteger = refClienteIndicado;
   else
	  return;


   if(RG1->ItemIndex == 0)
	  Query1->ParamByName("fi")->AsDate = StartOfTheWeek(MC->Date);
   else if(RG1->ItemIndex == 1)
	  Query1->ParamByName("fi")->AsDate = StartOfTheMonth(MC->Date);
   else if(RG1->ItemIndex == 2)
	  Query1->ParamByName("fi")->AsDate = DateOf(Now());

   Query1->ParamByName("ff")->AsDate = MC->Date;


   Query1->Open();
   CDS->Active = true;


   CDS->First();
   while(!CDS->Eof)
   {
	  CDS->Edit();
	  if(CDS->FieldByName("agregado")->AsInteger == NULL)
	  {
		 CDS->FieldByName("agregado")->AsFloat = 0;
		 CDS->FieldByName("imprimir")->AsFloat = 0;
	  }
	  if(CDS->FieldByName("unidadesPeriodo")->AsInteger == NULL)
		 CDS->FieldByName("unidadesPeriodo")->AsFloat = 0;
	  if(CDS->FieldByName("saldoAnterior")->AsInteger == NULL)
		 CDS->FieldByName("saldoAnterior")->AsFloat = 0;
	  if(CDS->FieldByName("subtotal")->AsInteger == NULL)
		 CDS->FieldByName("subtotal")->AsFloat = 0;
	  if(CDS->FieldByName("deudaTotal")->AsInteger == NULL)
		 CDS->FieldByName("deudaTotal")->AsFloat = 0;
	  CDS->Next();
   }
   CDS->First();

   if(CompareDate(MC->Date,DateOf(Now())) != EqualsValue)
   {
	  CDS->Edit();
	  CDS->FieldByName("agregado")->AsFloat = 0.0;
	  CDS->FieldByName("imprimir")->AsInteger = 1;
	  CDS->Post();
   }

   if(CDS->RecordCount == 1)
	  Button2->Enabled = true;
   else
	  Button2->Enabled = false;

   usarClienteIndicado = false;
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirCuentas::Button9Click(TObject *Sender)
{
   fImprimirResumenManual->ShowModal();
   Button2->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TfImprimirCuentas::FormShow(TObject *Sender)
{
   CheckBox1->Checked = false;
   RG1->ItemIndex = 0;
   MC->Date = Now();
   if(DayOfTheWeek(MC->Date) == 6)
	  RG2->ItemIndex = 1;
   else
	  RG2->ItemIndex = 0;

   Button2->Enabled = false;

   chbTicket->Checked = false;
   CDS3total->DisplayFormat = "Total: $ 0.00";
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirCuentas::MCClick(TObject *Sender)
{
   if(DayOfTheWeek(MC->Date) == 6)
	  RG2->ItemIndex = 1;
   else
	  RG2->ItemIndex = 0;

   usarClienteIndicado = true;
   Button8Click(MC);
   usarClienteIndicado = false;
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirCuentas::FormClose(TObject *Sender, TCloseAction &Action)

{
   usarClienteIndicado = false;
   refClienteIndicado = false;

   CDS->Active = false;
   CDS2->Active = false;
   CDS3->Active = false;

   Query1->Close();
   Query2->Close();
   Query3->Close();
   QueryAux->Close();

   SQLConnection1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirCuentas::Button2Click(TObject *Sender)
{
   Button4Click(Button2);
   Button2->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirCuentas::FormCreate(TObject *Sender)
{
   refClienteIndicado = false;

   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;

}
//---------------------------------------------------------------------------


void __fastcall TfImprimirCuentas::DBGrid1KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
      Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirCuentas::chbTicketClick(TObject *Sender)
{
//   if(chbTicket->Checked && RG1->ItemIndex == 0)
//	  CDS3total->DisplayFormat = "0.00";
//   else
//	  CDS3total->DisplayFormat = "Total: $ 0.00";
}
//---------------------------------------------------------------------------




