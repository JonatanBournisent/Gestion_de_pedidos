//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.NetEncoding.hpp>
#pragma hdrstop

#include "uEmitirComprobanteElectronico.h"
#include "uSeleccionarCliente.h"
#include "VariablesGlobales.h"
#include "FEAFIPLib_TLB.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxClass"
#pragma link "frxExportPDF"
#pragma link "frxBarcode"
#pragma link "frxBarcode2D"
#pragma link "frxDBSet"
#pragma link "frxExportBaseDialog"
#pragma resource "*.dfm"
TfEmitirComprobanteElectronico *fEmitirComprobanteElectronico;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfEmitirComprobanteElectronico::TfEmitirComprobanteElectronico(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool TfEmitirComprobanteElectronico::validatePrinter(String impSel)
{
	TPrinter *printers;
	printers = new TPrinter;

	for(int imp_index=0; imp_index<printers->Printers->Count; imp_index++)
	{
		if(printers->Printers->Strings[imp_index] == impSel)
		{
			delete printers;
			return true;
		}
	}
	delete printers;
	return false;
}
//---------------------------------------------------------------------------
String TfEmitirComprobanteElectronico::getDirFacturas(void)
{
	TIniFile *Configuraciones;
	String dir = GetCurrentDir()+"//Config.ini";
	Configuraciones = new TIniFile(dir);
	String dirFacturas = Configuraciones->ReadString("Directorios","Facturas","NO_CONFIGURADA");
	delete Configuraciones;
	return dirFacturas;
}
//---------------------------------------------------------------------------

String TfEmitirComprobanteElectronico::getPrinter(String tipo)
{
	TIniFile *Configuraciones;
	String dir = GetCurrentDir()+"//Config.ini";
	Configuraciones = new TIniFile(dir);
	String imp_actual;

	if(tipo == "PDF")
		imp_actual = Configuraciones->ReadString("Impresion","ImpresoraPDF","NO_CONFIGURADA");
	else if(tipo == "Planillas")
		imp_actual = Configuraciones->ReadString("Impresion","ImpresoraPlanillas","NO_CONFIGURADA");
	else if(tipo == "Presupuestos")
		imp_actual = Configuraciones->ReadString("Impresion","ImpresoraPresupuestos","NO_CONFIGURADA");
	else
		imp_actual = "NO_CONFIGURADA";

	delete Configuraciones;

	return imp_actual;
}
//---------------------------------------------------------------------------

void TfEmitirComprobanteElectronico::mostrarCliente(int refCliente)
{
   idCliente = refCliente;

   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("SELECT razonSocial AS cliente, acumuladoGlobal AS deuda, refListaPrecio, refCondicionFrenteIVA, "
					"(SELECT valor FROM listasPrecio WHERE clientes.refListaPrecio = listasPrecio.idListaPrecio LIMIT 1) AS valorUnidad "
					" FROM clientes WHERE idCliente = :idCliente LIMIT 1");
   Query1->ParamByName("idCliente")->AsInteger = refCliente;
   Query1->Open();
   Edit2->Text = Query1->FieldByName("cliente")->AsString;
   if(Edit2->Text.Length() < 2) //Uno o menos caracteres... quizas un espacio o un guion o nada.
	  Edit2->Text = "Consumidor Final";
   refCondicionFrenteIVA = Query1->FieldByName("refCondicionFrenteIVA")->AsInteger;

   Label1->Caption = "";

   if(Query1->FieldByName("deuda")->AsFloat > 0.0)
   {
	  Label1->Caption = "Atención! Este cliente presenta una deuda a la fecha: " + FormatDateTime("dd/mm/yyy", Now()) + " de " + FormatFloat("$ 0.00", Query1->FieldByName("deuda")->AsFloat);
	  Label1->Font->Color = clRed;
   }
   else if(Query1->FieldByName("deuda")->AsFloat < 0.0)
   {
	  Label1->Caption = "Atención! Este cliente presenta un saldo a favor a la fecha: " + FormatDateTime("dd/mm/yyy", Now()) + " de " + FormatFloat("$ 0.00", -1.0 * Query1->FieldByName("deuda")->AsFloat);
      Label1->Font->Color = clBlue;
   }

   valorUnidad = Query1->FieldByName("valorUnidad")->AsFloat;

   CDS3->Active = false;
   Query1->Close();

   String q;

	  q = "SELECT idCliente, razonSocial, domicilioFiscal AS domicilio, REPLACE(cuit,'-','') AS cuit, "
		  "(SELECT descripcion FROM condicionesFrenteIVA WHERE condicionesFrenteIVA.idCondicionFrenteIVA = clientes.refCondicionFrenteIVA LIMIT 1) AS condFrenteIVA "
		  "FROM clientes WHERE idCliente = :refCliente LIMIT 1";

   Query3->Close();
   Query3->SQL->Clear();
   Query3->SQL->Add(q);
   Query3->ParamByName("refCliente")->AsInteger = refCliente;

   Query3->Open();
   CDS3->Active = true;

   if(refCondicionFrenteIVA == 2)
   {
	  lbIVA21->Visible = true;
   }
   else
   {
	  lbIVA21->Visible = false;
   }
   Button10->Enabled = true;

}

//---------------------------------------------------------------------------

float TfEmitirComprobanteElectronico::calcular2(void)
{
	if (blockCalcular2) {
        return 0.0;
	}
	if (!FDMemTable1->Active) {
		return 0.0;
	}
   
	float tot = 0.0;
	int recNo = FDMemTable1->RecNo;


	DataSource1->Enabled = false;
	DataSource1->DataSet = NULL;

	FDMemTable1->First();
	while (!FDMemTable1->Eof){
		tot = tot + FDMemTable1->FieldByName("subtotal")->AsFloat;
		FDMemTable1->Next();
	}
	FDMemTable1->RecNo = recNo;
	DataSource1->DataSet = FDMemTable1;
    DataSource1->Enabled = true;

	float _subtotal = tot / 1.21;
	float _totalIVA21 = tot * 0.1735537190082645;
	float _total = tot;

	if(refCondicionFrenteIVA != 2)
		lbSubtotal->Caption = FormatFloat("Subtotal: $ 0.00", _total);
	else
		lbSubtotal->Caption = FormatFloat("Subtotal: $ 0.00", _subtotal);

	lbIVA21->Caption = FormatFloat("IVA 21%: $ 0.00", _totalIVA21);
	lbTotal->Caption = FormatFloat("TOTAL: $ 0.00", _total);
    ShowScrollBar(DBGrid1->Handle, SB_VERT, true);

	return _total;
}
//---------------------------------------------------------------------------
void __fastcall TfEmitirComprobanteElectronico::Button10Click(TObject *Sender)
{
	if(!CDS3->Active)
		return;

	if(calcular2() < 0.0)
		Application->MessageBox(L"No es posible generar un comprobante electrónico con valor negativo." ,L"Error.",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);

	else if(calcular2() == 0.0)
		if(Application->MessageBox(L"Esta por generar un comprobante por un valor de $ 0,00. Realmente desea continuar?" ,L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
			return;

	Button10->Enabled = false;

	String DirFacturas = getDirFacturas();

	if(DirFacturas == "NO_CONFIGURADA")
	{
		Application->MessageBox(L"Antes de continuar debe configurar un directorio para guardar las copias de respaldo" ,L"Configurar directorio.",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		CDS3->Active = false;
		Query3->Close();
		return;
	}

    String imp_actual = "NO_CONFIGURADA";

	if(CheckBox1->Checked)
		imp_actual = getPrinter("PDF");
	else if(chbFactA4->Checked)
	   imp_actual = getPrinter("Planillas");
	else
	   imp_actual = getPrinter("Presupuestos");

	if(imp_actual == "NO_CONFIGURADA")
	{
		Application->MessageBox(L"Debe configurar una impresora antes de imprimir." ,L"Error",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		return;
	}

	if(!validatePrinter(imp_actual))
	{
		Application->MessageBox(L"La impresora configurada no se encuentra en el sistema. Debera volver a configurarla" ,L"Error",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		return;
	}

	 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport1->FindObject("fechaComp"))->Text = FormatDateTime("dd/mm/yyy", MC->Date);
	 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("fechaComp"))->Text = FormatDateTime("dd/mm/yyy", MC->Date);
	 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("fechaComp"))->Text = FormatDateTime("dd/mm/yyy", MC->Date);


	 float total = calcular2();
	 float subtotalSIVA = total / 1.21;
	 float totalIVA21 = total * 0.1735537190082645;


	 QueryAux->Close();
	 QueryAux->SQL->Clear();
	 QueryAux->SQL->Add("SELECT montoMaximoFacturableSinDatos FROM registros WHERE idRegistro = 1 LIMIT 1");
	 QueryAux->Open();
	 float maximoFactSD = QueryAux->FieldByName("montoMaximoFacturableSinDatos")->AsFloat;
	 QueryAux->Close();

	 if(
			 (CDS3->FieldByName("cuit")->AsString == "00000000"
		  || CDS3->FieldByName("cuit")->AsString == "00000000000"
		  || CDS3->FieldByName("domicilio")->AsString == "-"
		  || CDS3->FieldByName("domicilio")->AsString == ""
		  || CDS3->FieldByName("razonSocial")->AsString == "-"
		  || CDS3->FieldByName("razonSocial")->AsString == "")
		  && (total > maximoFactSD)	 )
	 {
		  String msg = "Error: para emitir facturas con monto mayor a: " + FormatFloat("$ 0.00", maximoFactSD);
		  msg = msg + " debe completar todos los datos del cliente\nCuit/DNI, Domicilio Fiscal y Razón Social o Nombre y Apellido";
		  Application->MessageBox(msg.w_str() ,L"ERROR!",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		  CDS3->Active = false;
		  Query3->Close();
		  return;
	 }


	 if(
		  (refCondicionFrenteIVA == 2) &&
			 (CDS3->FieldByName("cuit")->AsString == "00000000"
		  || CDS3->FieldByName("cuit")->AsString == "00000000000"
		  || CDS3->FieldByName("domicilio")->AsString == "-"
		  || CDS3->FieldByName("domicilio")->AsString == ""
		  || CDS3->FieldByName("razonSocial")->AsString == "-"
		  || CDS3->FieldByName("razonSocial")->AsString == "") )
	 {
		  String msg = "Error: para emitir facturas A debe completar todos los datos del cliente\nCuit, Domicilio Fiscal y Razón Social o Nombre y Apellido";
		  Application->MessageBox(msg.w_str() ,L"ERROR!",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		  CDS3->Active = false;
		  Query3->Close();
		  return;
	 }

	 bool conDNI, sinID;

	 conDNI = false;
	 sinID = false;

	 if(CDS3->FieldByName("cuit")->AsString == "00000000" || CDS3->FieldByName("cuit")->AsString == "00000000000")
		 sinID = true;
	 else if(CDS3->FieldByName("cuit")->AsString.Length() == 8)
		conDNI = true;



	 int selModelo = 0;

	 if(refCondicionFrenteIVA == 2 && chbFactA4->Checked)
		selModelo = 1; //factura A A4
	 else if(refCondicionFrenteIVA == 2 && !chbFactA4->Checked)
		selModelo = 2; //TIQUE A
	 else if(refCondicionFrenteIVA != 2 && chbFactA4->Checked && sinID)
		selModelo = 3; //factura B A4 sin datos de cliente
	 else if(refCondicionFrenteIVA != 2 && chbFactA4->Checked)
		selModelo = 4; //factura B A4
	 else if(refCondicionFrenteIVA != 2 && !chbFactA4->Checked && sinID)
		selModelo = 5; //TIQUE B sin datos de cliente
	 else
		selModelo = 6; //TIQUE B con datos de cliente


	 String s;

	 if(selModelo == 1)
	 {
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo18"))->Visible = true;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo19"))->Visible = true;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo21"))->Visible = true;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("tipoComp"))->Text = "A";
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("codigoComp"))->Text = "COD. 01";
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("tipoDocumento"))->Text = "FACTURA";

		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("mSubtotal"))->Text = FormatFloat("Subtotal: $ 0.00", subtotalSIVA);   // subtotalSIVA
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("mTotalIVA21"))->Text = FormatFloat("IVA 21%: $ 0.00", totalIVA21); //  totalIVA21
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("mTotal"))->Text = FormatFloat("Total: $ 0.00", total); //total

		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("mTotalIVA21"))->Visible = true;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo27"))->Text = "CUIT:";

		s = "FACTURA A - ";
	 }
	 else if(selModelo == 2)
	 {
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("Memo19"))->Visible = true;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("tipoComp"))->Text = "FACTURA A. COD. 01";

		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("mSubtotal"))->Text = FormatFloat("Subtotal: $ 0.00", subtotalSIVA);
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("mTotalIVA21"))->Text = FormatFloat("IVA 21%: $ 0.00", totalIVA21);
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("mTotal"))->Text = FormatFloat("Total: $ 0.00", total);

		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("mTotalIVA21"))->Visible = true;

		if(conDNI)
		   dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo27"))->Text = "DNI:";
		else
		   dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo27"))->Text = "CUIT:";

		s = "FACTURA A - ";
	 }
	 else if(selModelo == 3)
	 {
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo18"))->Visible = false;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo19"))->Visible = false;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo21"))->Visible = false;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("tipoComp"))->Text = "B";
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("codigoComp"))->Text = "COD. 06";
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("tipoDocumento"))->Text = "FACTURA";

		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("mSubtotal"))->Text = FormatFloat("Subtotal: $ 0.00", total);
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("mTotalIVA21"))->Text = FormatFloat("IVA 21%: $ 0.00", totalIVA21);
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("mTotal"))->Text = FormatFloat("Total: $ 0.00", total);

		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("mTotalIVA21"))->Visible = false;

		if(conDNI)
		   dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo27"))->Text = "DNI:";
		else
		   dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo27"))->Text = "CUIT:";

		s = "FACTURA B - ";
	 }
	 else if(selModelo == 4)
	 {
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo18"))->Visible = true;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo19"))->Visible = true;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo21"))->Visible = true;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("tipoComp"))->Text = "B";
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("codigoComp"))->Text = "COD. 06";
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("tipoDocumento"))->Text = "FACTURA";

		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("mSubtotal"))->Text = FormatFloat("Subtotal: $ 0.00", total);
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("mTotalIVA21"))->Text = FormatFloat("IVA 21%: $ 0.00", totalIVA21);
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("mTotal"))->Text = FormatFloat("Total: $ 0.00", total);

		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("mTotalIVA21"))->Visible = false;

		if(conDNI)
		   dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo27"))->Text = "DNI:";
		else
		   dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo27"))->Text = "CUIT:";

		s = "FACTURA B - ";
	 }

	 else if(selModelo == 5)
	 {
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport1->FindObject("Memo19"))->Visible = false;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport1->FindObject("tipoComp"))->Text = "FACTURA B. COD. 06";

		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport1->FindObject("mSubtotal"))->Text = FormatFloat("Subtotal: $ 0.00", total);
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport1->FindObject("mTotalIVA21"))->Text = FormatFloat("IVA 21%: $ 0.00", totalIVA21);
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport1->FindObject("mTotal"))->Text = FormatFloat("Total: $ 0.00", total);

		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport1->FindObject("mTotalIVA21"))->Visible = false;

		s = "FACTURA B - ";
	 }
	 else if(selModelo == 6)
	 {
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("Memo19"))->Visible = true;
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("tipoComp"))->Text = "FACTURA B. COD. 06";

		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("mSubtotal"))->Text = FormatFloat("Subtotal: $ 0.00", total);
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("mTotalIVA21"))->Text = FormatFloat("IVA 21%: $ 0.00", totalIVA21);
		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("mTotal"))->Text = FormatFloat("Total: $ 0.00", total);

		dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("mTotalIVA21"))->Visible = false;

		if(conDNI)
		   dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo27"))->Text = "DNI:";
		else
		   dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo27"))->Text = "CUIT:";

		s = "FACTURA B - ";
	 }





//**************** CODIGOS SEGUN TABLA DE CODIGOS DE AFIP ************
//	001		FACTURA A                                                *
//	002		NOTA DE DEBITO A                                         *
//	003		NOTA DE CREDITO A                                        *
//                                                                   *
//	006		FACTURA B                                                *
//	007		NOTA DE DEBITO B                                         *
//	008		NOTA DE CREDIT B                                         *
//                                                                   *
//	011		FACTURA C                                                *
//	012		NOTA DE DEBITO C                                         *
//	013		NOTA DE CREDITO C                                        *
//                                                                   *
//**************** FIN CODIGOS SEGUN TABLA DE CODIGOS DE AFIP ********



//   URLs de autenticacion y negocio. Cambiarlas por las de producción al implementarlas en el cliente(abajo)
//   String URLWSAA = "https://wsaahomo.afip.gov.ar/ws/services/LoginCms"; //homologacion
//   String URLWSW = "https://wswhomo.afip.gov.ar/wsfev1/service.asmx";     //homologacion

   String URLWSAA = "https://wsaa.afip.gov.ar/ws/services/LoginCms";       //Produccion
   String URLWSW =  "https://servicios1.afip.gov.ar/wsfev1/service.asmx";   //Produccion

   WideString CAE = "";
   WideString Resultado = "";
   WideString Reproceso = "";
   WideString Vencimiento = "";
   WideString CUIT = "20149650939";     //CUIT EMISOR DE FACTURA
   double totalComp = StrToFloat(FormatFloat("0.00", total));
   double netoGravado = StrToFloat(FormatFloat("0.00", subtotalSIVA));
   double IVA21 = StrToFloat(FormatFloat("0.00", totalIVA21));


   bool error = false;

   double nro = 0;
   int PtoVta = 6;   //Punto de venta dado de alta en AFIP para Web Service

   int TipoComp;     //Codigo de Tipo de comprobante segun tabla de AFIP (resumen arriba)

   if(selModelo == 1)
	  TipoComp = 1;
   else if(selModelo == 2)
	  TipoComp = 1;
   else if(selModelo == 3)
	  TipoComp = 6;
   else if(selModelo == 4)
	  TipoComp = 6;
   else if(selModelo == 5)
	  TipoComp = 6;
   else if(selModelo == 6)
	  TipoComp = 6;
   else
   {
	  Application->MessageBox(L"Por algun motivo no se puede definir el tipo de comprobante.", L"ERROR",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
      CDS3->Active = false;
	  Query3->Close();
	  return;	//hay algun error
   }

   String FechaComp = FormatDateTime("yyyyMMdd", MC->Date);

   try
   {
	  StrToInt64(CDS3cuit->AsString);
   }
   catch(...)
   {
	  Application->MessageBox(L"Error al intentar converir el numero de CUIT del cliente a un valor entero", L"ERROR",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
      CDS3->Active = false;
	  Query3->Close();
	  return;
   }




   String tipoComp;

   if(TipoComp == 1)
	  tipoComp = "A";
   else if(TipoComp == 6)
	  tipoComp = "B";
   else
      return;

   String mensaje = "Se va a emitir una factura " + tipoComp + " a nombre de: \n\n";

   mensaje  = mensaje + "Fecha: " + FormatDateTime("dd/mm/yyyy", MC->Date);

   if(CDS3razonSocial->AsString == "")
	  mensaje  = mensaje + "\nRazón Social: NO ESPECIFICADA";
   else
	  mensaje  = mensaje + "\nRazón Social: " + CDS3razonSocial->AsString;

   if(conDNI)
	  mensaje  = mensaje + "\nDNI: " + CDS3cuit->AsString;
   else
	  mensaje  = mensaje + "\nCUIT: " + CDS3cuit->AsString;

   mensaje = mensaje + "\nCondición frente al IVA: " + CDS3condFrenteIVA->AsString;
   mensaje = mensaje + "\nNeto Gravado: " + FormatFloat("$ 0.00", netoGravado);
   mensaje = mensaje + "\nIVA 21%: " + FormatFloat("$ 0.00", IVA21);
   mensaje = mensaje + "\nImporte TOTAL: " + FormatFloat("$ 0.00", totalComp);
   mensaje = mensaje  + "\n\nRealmente desea continuar?";


   if(Application->MessageBox(L"Esta operación no puede cancelarse. Desea continuar?" ,L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
   {
	  Button10->Enabled = true;
	  return;
   }

   if(Application->MessageBox(mensaje.w_str() ,L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
   {
	  Button10->Enabled = true;
	  return;
   }


   bool comprobanteAutorizado = false;




   Twsfev1 *lwsfev1;
   lwsfev1 = new Twsfev1(Owner);
   lwsfev1->CUIT = StrToInt64(CUIT);
   lwsfev1->URL = URLWSW;

	if (lwsfev1->login("certificado.crt", "clave.key", URLWSAA))   //certificados y claves generados para el contribuyente emisor de la factura
	{
		if (lwsfev1->SFRecuperaLastCMP(PtoVta, TipoComp) == false)
		{
		   String msg = lwsfev1->ErrorDesc;
		   Application->MessageBox(msg.w_str(), L"ERROR",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		   Application->MessageBox(L"Error al intentar recuperar desde AFIP el número del último comprobante emitido", L"ERROR",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		   error = true;
		}
		else
		{
			nro = lwsfev1->SFLastCMP + 1;
			lwsfev1->Reset();

			if(sinID)
			   lwsfev1->AgregaFactura(1, 99, __int64(0)					   , nro, nro, FechaComp, totalComp, 0, netoGravado, 0, "", "", "", "PES", 1);
			else if(conDNI)
			   lwsfev1->AgregaFactura(1, 96, StrToInt64(CDS3cuit->AsString), nro, nro, FechaComp, totalComp, 0, netoGravado, 0, "", "", "", "PES", 1);
			else
			   lwsfev1->AgregaFactura(1, 80, StrToInt64(CDS3cuit->AsString), nro, nro, FechaComp, totalComp, 0, netoGravado, 0, "", "", "", "PES", 1);

			lwsfev1->AgregaIVA(5, netoGravado, IVA21); //ir a http://www.bitingenieria.com.ar/codigos.html

			if (lwsfev1->Autorizar(PtoVta, TipoComp))
			{
				lwsfev1->AutorizarRespuesta(0, CAE, Vencimiento, Resultado, Reproceso);
				if (Resultado == "A")
				{
					//ShowMessage("Felicitaciones! Si ve este mensaje instalo correctamente FEAFIP. CAE y Vencimiento :" + CAE + " " + Vencimiento);
					comprobanteAutorizado = true;
				}
				else
				{
					String msg = lwsfev1->AutorizarRespuestaObs(0);
					Application->MessageBox(msg.w_str(), L"ERROR",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
					Application->MessageBox(L"Hubo un error al intentar autorizar el comprobante", L"ERROR",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
					error = true;
				}
			}
			else
			{
				String msg = lwsfev1->ErrorDesc;
				Application->MessageBox(msg.w_str(), L"ERROR",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
				error = true;
			}
		}
	}
	else
	{
		String msg = lwsfev1->ErrorDesc;
		Application->MessageBox(msg.w_str(), L"ERROR",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		Application->MessageBox(L"Arror al intentar conectarse al Web Service de AFIP con las credenciales disponibles", L"ERROR",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		error = true;
	}


   if(error)
   {
	  delete lwsfev1;
	  CDS3->Active = false;
	  Query3->Close();
	  return;
   }







////ATENCION!!!!      SIMULACION***********************************************************
//
//   CAE = "71099320294706";
//   MC->Date = StrToDate("27/02/2021");
//   PtoVta = 3;
//   nro = 6;
//   CUIT = "23323762589";
//   TipoComp = 1;
//   total = 7872.03;
//   conDNI = false;
//   sinID = false;
//
//
////*********************************************************************




   String ptoDeVenta = IntToStr(PtoVta);
   while(ptoDeVenta.Length() < 5)
	  ptoDeVenta.Insert("0",1);

   String nroComp = IntToStr(__int64(nro));
   while(nroComp.Length() < 8)
	  nroComp.Insert("0",1);

   String tipoComprobante = IntToStr(TipoComp);

   while(tipoComprobante.Length() < 3)
	  tipoComprobante.Insert("0",1);

   String codigoBarra = CUIT + tipoComprobante + ptoDeVenta + CAE + Vencimiento; //cuit vendedor
   String fechaVencimiento = Vencimiento.SubString(7,2) + "/" + Vencimiento.SubString(5,2) + "/" + Vencimiento.SubString(1,4);







////ATENCION!!!! SIMULACION**************************************************
//   comprobanteAutorizado = true;      //para poder probar sin enviar a AFIP
//   fechaVencimiento = "01/01/2020";
////*************************************************************







   frxPDFExport1->FileName = DirFacturas + "\\" + s + ptoDeVenta + "-" + nroComp + ".pdf";

   if(comprobanteAutorizado)
   {
	 String importe = FormatFloat("0.00",total);
	 importe = importe.Delete(importe.Length() - 2, 1);
	 importe = importe.Insert(".", importe.Length() - 1);

	 if(importe.Pos(".0") > 0)
		importe = importe.SubString(1,importe.Pos(".0") - 1);

	 String json = "{\"ver\":1,\"fecha\":\"" + FormatDateTime("yyyy-mm-dd", MC->Date);
	 json = json + "\",\"cuit\":" + CUIT + ",\"ptoVta\":" + IntToStr(PtoVta);
	 json = json + ",\"tipoCmp\":" + IntToStr(TipoComp) + ",\"nroCmp\":" + IntToStr(__int64(nro));
	 json = json + ",\"importe\":";
	 json = json + importe;
	 json = json + ",\"moneda\":\"PES\",\"ctz\":1";

	 if(sinID)
		json = json + "";
	 else if(conDNI)
		json = json + ",\"tipoDocRec\":96";
	 else
		json = json + ",\"tipoDocRec\":80";

	 String nDoc = CDS3cuit->AsString;
//		 nDoc = "20295355442";

	 if(conDNI && nDoc.Length() > 0)
	 {
		while(nDoc.Pos("0") == 1)
		   nDoc = nDoc.Delete(1,1);
	 }

	 if(!sinID)
		json = json + ",\"nroDocRec\":" + nDoc;


	 json = json + ",\"tipoCodAut\":\"E\",\"codAut\":";
	 json = json + CAE + "}";

	 String encJSON = "https://www.afip.gob.ar/fe/qr/?p=" + TNetEncoding::Base64->Encode(json);

	 while(encJSON.Pos('\r'))
		encJSON = encJSON.Delete(encJSON.Pos('\r'), 1);
	 while(encJSON.Pos('\n'))
		encJSON = encJSON.Delete(encJSON.Pos('\n'), 1);



	  if(selModelo == 1 || selModelo == 3 || selModelo == 4)
	  {
		 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo33"))->Text = "ORIGINAL";
		 dynamic_cast <TfrxBarCodeView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("BarCode1"))->Text = codigoBarra;
		 dynamic_cast <TfrxBarcode2DView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Barcode2D1"))->Text = encJSON;
		 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("caeComp"))->Text = "N° de CAE: " + CAE;
		 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("nroComp"))->Text = ptoDeVenta + " - " + nroComp;
		 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("vencComp"))->Text = "Vto. de CAE: " + fechaVencimiento;
		 frxReport3->PrintOptions->Printer = imp_actual;
		 frxReport3->PrepareReport(true);
//		 frxReport3->ShowReport(true);
		 frxReport3->Print();
         dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport3->FindObject("Memo33"))->Text = "DUPLICADO";
		 frxReport3->PrepareReport(true);

		 if(!frxReport3->Export(frxPDFExport1))
		 {
			Application->MessageBox(L"Especifique manualmente una ubicación (y nombre de archivo) donde guardar una copia del comprobante.", L"ATENCIÓN",MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);
			if(SD1->Execute())
			   frxPDFExport1->FileName = SD1->FileName;
			frxReport3->Export(frxPDFExport1);
		 }

	  }
	  else if(selModelo == 2 || selModelo == 6)
	  {
		 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("caeComp"))->Text = "N° de CAE: " + CAE;
		 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("nroComp"))->Text = ptoDeVenta + " - " + nroComp;
		 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("vencComp"))->Text = "Vto. de CAE: " + fechaVencimiento;
		 dynamic_cast <TfrxBarcode2DView *> (fEmitirComprobanteElectronico->frxReport2->FindObject("Barcode2D1"))->Text = encJSON;
		 frxReport2->PrintOptions->Printer = imp_actual;
		 frxReport2->PrepareReport(true);
		 frxReport2->Print();
//		 frxReport2->ShowReport(true);

		 if(!frxReport2->Export(frxPDFExport1))
		 {
			Application->MessageBox(L"Especifique manualmente una ubicación donde guardar una copia del comprobante.", L"ATENCIÓN",MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);
			if(SD1->Execute())
			   frxPDFExport1->FileName = SD1->FileName;
			frxReport2->Export(frxPDFExport1);
		 }

	  }
	  else
	  {
		 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport1->FindObject("caeComp"))->Text = "N° de CAE: " + CAE;
		 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport1->FindObject("nroComp"))->Text = ptoDeVenta + " - " + nroComp;
		 dynamic_cast <TfrxMemoView *> (fEmitirComprobanteElectronico->frxReport1->FindObject("vencComp"))->Text = "Vto. de CAE: " + fechaVencimiento;
		 dynamic_cast <TfrxBarcode2DView *> (fEmitirComprobanteElectronico->frxReport1->FindObject("Barcode2D1"))->Text = encJSON;
		 frxReport1->PrintOptions->Printer = imp_actual;
		 frxReport1->PrepareReport(true);
		 frxReport1->Print();
//		 frxReport1->ShowReport(true);

		 if(!frxReport1->Export(frxPDFExport1))
		 {
			Application->MessageBox(L"Especifique manualmente una ubicación donde guardar una copia del comprobante.", L"ATENCIÓN",MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);
			if(SD1->Execute())
			   frxPDFExport1->FileName = SD1->FileName;
			frxReport1->Export(frxPDFExport1);
		 }
	  }



		QueryAux->Close();
		QueryAux->SQL->Clear();
		String qy;

		qy = "INSERT INTO comprobanteselectronicos ("
			 "refCliente, cuitCliente, refCondicionFrenteIVA, fecha, refTipoComp, "
			 "ptoVenta, nroComprobante, netoGravado, iva21, total, CAE, vencimientoCAE) "
			 "VALUES ("
			 ":refCliente, :cuitCliente, :refCondicionFrenteIVA, :fecha, :refTipoComp, "
			 ":ptoVenta, :nroComprobante, :netoGravado, :iva21, :total, :CAE, :vencimientoCAE) ";


		QueryAux->SQL->Add(qy);
		QueryAux->ParamByName("refCliente")->AsInteger = idCliente;
		QueryAux->ParamByName("cuitCliente")->AsString = CDS3->FieldByName("cuit")->AsString;
		QueryAux->ParamByName("refCondicionFrenteIVA")->AsInteger = refCondicionFrenteIVA;
		QueryAux->ParamByName("fecha")->AsDate = MC->Date;
		QueryAux->ParamByName("refTipoComp")->AsInteger = TipoComp; //Segun tablas de AFIP
		QueryAux->ParamByName("ptoVenta")->AsInteger = PtoVta;
		QueryAux->ParamByName("nroComprobante")->AsInteger = StrToInt(nroComp);
		QueryAux->ParamByName("netoGravado")->AsFloat = netoGravado;
		QueryAux->ParamByName("iva21")->AsFloat = IVA21;
		QueryAux->ParamByName("total")->AsFloat = totalComp;
		QueryAux->ParamByName("CAE")->AsString = CAE;
		QueryAux->ParamByName("vencimientoCAE")->AsDate = StrToDate(fechaVencimiento);
		QueryAux->ExecSQL();

   }
   else
   {
	  Application->MessageBox(L"El comprobante no fue autorizado", L"ERROR",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  CDS3->Active = false;
	  Query3->Close();
   }

   delete lwsfev1;


	Button10->Enabled = true;

	if (facturacionMensual) {
      Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfEmitirComprobanteElectronico::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
	SQLConnection1->Params->Values["Password"] = pass;
	facturacionBulk = false;
	facturacionMensual = false;
}
//---------------------------------------------------------------------------
void __fastcall TfEmitirComprobanteElectronico::FormShow(TObject *Sender)
{
	  blockCalcular2 = false;
	  facturacionBulk = false;
	  Edit2->Text = "";

	  Label1->Caption = "";

	  Edit2->Enabled = true;
	  Button10->Enabled = false;
	  Button1->SetFocus();

	  CheckBox1->Checked = false;
	  chbFactA4->Checked = false;

	  lbIVA21->Visible = false;
	  refCondicionFrenteIVA = 0;


	  MC->Date = Now();
	  directorioGuararFacturas = "";
      FDMemTable1->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::Button1Click(TObject *Sender)
{
   Query1->Close();
   CDS3->Active = false;
   Query3->Close();
   QueryAux->Close();
   Button10->Enabled = false;

   fSeleccionarCliente->llamador = 1;
   fSeleccionarCliente->ShowModal();

   if(fSeleccionarCliente->idSeleccionado < 2)
	  return;

   mostrarCliente(fSeleccionarCliente->idSeleccionado);
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::chbFactA4Click(TObject *Sender)
{
	if(!FDMemTable1->Active)
		return;

	FDMemTable1->Cancel();

	if(!chbFactA4->Checked)
	{
		bool largo = false;

		if (FDMemTable1->Active) {
			 int recNro = FDMemTable1->RecNo;
			 DataSource1->Enabled = false;

			 while (!FDMemTable1->Eof) {
				if (FDMemTable1descripcion->AsString.Length() > 17) {
				   largo = true;
				   break;
				}
				FDMemTable1->Next();
			 }

			 FDMemTable1->RecNo = recNro;
			 DataSource1->Enabled = true;
		}


		int recNro = FDMemTable1->RecNo;
		DataSource1->Enabled = false;

		while (!FDMemTable1->Eof) {
			 FDMemTable1->Edit();
			 FDMemTable1descripcion->AsString = FDMemTable1descripcion->AsString.SubString(1,17);
			 FDMemTable1->Post();
			 FDMemTable1->Next();
		}

		FDMemTable1->RecNo = recNro;
		DataSource1->Enabled = true;

		if(largo)
		 Application->MessageBox(L"En formato tique, las descripciones pueden tener un máximo de 17 caracteres de longitud" ,L"Antención",MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::CheckBox1Click(TObject *Sender)
{
   if(CheckBox1->Checked)
	  chbFactA4->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::FormClose(TObject *Sender, TCloseAction &Action)

{
	Query1->Close();
	CDS3->Active = false;
	Query3->Close();
	QueryAux->Close();
	SQLConnection1->Close();
	FDMemTable1->Cancel();
	FDMemTable1->Active = false;
	facturacionMensual = false;
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::FDMemTable1BeforePost(TDataSet *DataSet)

{
	if (DataSet->FieldByName("nroUnidades")->IsNull ||
		DataSet->FieldByName("nroUnidades")->AsFloat == 0.0 ||
		DataSet->FieldByName("descripcion")->AsString == "" ||
		DataSet->FieldByName("precioUnitario")->IsNull ||
		DataSet->FieldByName("precioUnitario")->AsFloat == 0.0 ||
		DataSet->FieldByName("subtotal")->IsNull ||
		DataSet->FieldByName("subtotal")->AsFloat == 0.0)
	{
		DataSet->Cancel();
	}

}
//---------------------------------------------------------------------------



void __fastcall TfEmitirComprobanteElectronico::FDMemTable1precioUnitarioChange(TField *Sender)
          
{
	Sender->DataSet->FieldByName("subtotal")->AsFloat = Sender->AsFloat;
//	calcular2();
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::FDMemTable1nroUnidadesValidate(TField *Sender)
          
{
	if (Sender->IsNull || Sender->AsFloat == 0.0) {
		throw(Exception("Se debe indicar un valor mayor que cero"));
	}
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::FDMemTable1descripcionValidate(TField *Sender)
          
{
	if (Sender->AsString == "") {
	   throw(Exception("Debe ingresar una descripción"));
	}	
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::FDMemTable1precioUnitarioValidate(TField *Sender)
          
{
	if (Sender->IsNull || Sender->AsFloat == 0.0) {
		throw(Exception("Se debe indicar un valor mayor que cero"));
	}	
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::FDMemTable1AfterPost(TDataSet *DataSet)

{
   calcular2();
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::DBGrid1Exit(TObject *Sender)
{
	if(FDMemTable1->Active && FDMemTable1->State == dsEdit)
		FDMemTable1->Post();
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::DBGrid1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if (Key == VK_RETURN) {
		if(FDMemTable1->Active && FDMemTable1->State == dsEdit)
			FDMemTable1->Post();
	}
}
//---------------------------------------------------------------------------



void __fastcall TfEmitirComprobanteElectronico::Eliminaresteitem1Click(TObject *Sender)

{
	if(FDMemTable1->Active)
		FDMemTable1->Delete();

	ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::Agregarunitem1Click(TObject *Sender)

{
	if(FDMemTable1->Active)
		FDMemTable1->Insert();

	ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
}
//---------------------------------------------------------------------------

void __fastcall TfEmitirComprobanteElectronico::FDMemTable1AfterDelete(TDataSet *DataSet)

{
	calcular2();
}
//---------------------------------------------------------------------------


