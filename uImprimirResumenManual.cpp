//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "uImprimirResumenManual.h"
#include "uSeleccionarCliente.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxClass"
#pragma link "frxExportPDF"
#pragma link "frxExportBaseDialog"
#pragma resource "*.dfm"
TfImprimirResumenManual *fImprimirResumenManual;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfImprimirResumenManual::TfImprimirResumenManual(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void TfImprimirResumenManual::mostrarCliente(int refCliente)
{
   idCliente = refCliente;


   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("SELECT CONCAT(calle, ' ', numero) AS cliente, acumuladoGlobal AS deuda, refListaPrecio, "
					"(SELECT valor FROM listasPrecio WHERE clientes.refListaPrecio = listasPrecio.idListaPrecio LIMIT 1) AS valorUnidad "
					" FROM clientes WHERE idCliente = :idCliente LIMIT 1");
   Query1->ParamByName("idCliente")->AsInteger = refCliente;
   Query1->Open();
   Edit2->Text = Query1->FieldByName("cliente")->AsString;

   Label1->Caption = "";

   if(Query1->FieldByName("deuda")->AsFloat > 0.0)
   {
	  Label1->Caption = "Atenci�n! Este cliente presenta una deuda a la fecha: " + FormatDateTime("dd/mm/yyy", Now()) + " de " + FormatFloat("$ 0.00", Query1->FieldByName("deuda")->AsFloat);
	  Label1->Font->Color = clRed;
   }
   else if(Query1->FieldByName("deuda")->AsFloat < 0.0)
   {
	  Label1->Caption = "Atenci�n! Este cliente presenta un saldo a favor a la fecha: " + FormatDateTime("dd/mm/yyy", Now()) + " de " + FormatFloat("$ 0.00", -1.0 * Query1->FieldByName("deuda")->AsFloat);
      Label1->Font->Color = clBlue;
   }

   valorUnidad = Query1->FieldByName("valorUnidad")->AsFloat;

   Query1->Close();

   Button10->Enabled = true;
}

//---------------------------------------------------------------------------

float TfImprimirResumenManual::calcular(void)
{
   float tot = StrToFloat(Edit1->Text.Delete(1,2)) +
				StrToFloat(Edit18->Text.Delete(1,2)) +
				StrToFloat(Edit19->Text.Delete(1,2)) +
				StrToFloat(Edit20->Text.Delete(1,2)) +
				StrToFloat(Edit21->Text.Delete(1,2));

   lbTotal->Caption = FormatFloat("TOTAL: $ 0.00", tot);
   return tot;
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit5Change(TObject *Sender)
{
   if(Edit3->Text != "0" && Edit4->Text != "" && Edit5->Text != "0")
   {
      Edit6->Enabled = true;
      Edit7->Enabled = true;
      Edit8->Enabled = true;
   }
   if(Edit5->Text.Length() > 0)
	  Edit1->Text = FormatFloat("$ 0.00", /*StrToFloat(Edit3->Text) * */ StrToFloat(Edit5->Text));

   calcular();
}
//---------------------------------------------------------------------------
void __fastcall TfImprimirResumenManual::Edit8Change(TObject *Sender)
{
   if(Edit6->Text != "0" && Edit7->Text != "" && Edit8->Text != "0")
   {
      Edit9->Enabled = true;
      Edit10->Enabled = true;
      Edit11->Enabled = true;
   }
   if(Edit8->Text.Length() > 0)
	  Edit18->Text = FormatFloat("$ 0.00", /*StrToFloat(Edit6->Text) * */StrToFloat(Edit8->Text));

   calcular();
}
//---------------------------------------------------------------------------
void __fastcall TfImprimirResumenManual::Edit11Change(TObject *Sender)
{
   if(Edit9->Text != "0" && Edit10->Text != "" && Edit11->Text != "0")
   {
      Edit12->Enabled = true;
      Edit13->Enabled = true;
      Edit14->Enabled = true;
   }
   if(Edit11->Text.Length() > 0)
	  Edit19->Text = FormatFloat("$ 0.00", /*StrToFloat(Edit9->Text) * */StrToFloat(Edit11->Text));

   calcular();
}
//---------------------------------------------------------------------------
void __fastcall TfImprimirResumenManual::Edit14Change(TObject *Sender)
{
   if(Edit12->Text != "0" && Edit13->Text != "" && Edit14->Text != "0")
   {
      Edit15->Enabled = true;
      Edit16->Enabled = true;
      Edit17->Enabled = true;
   }
   if(Edit14->Text.Length() > 0)
	  Edit20->Text = FormatFloat("$ 0.00", /*StrToFloat(Edit12->Text) * */StrToFloat(Edit14->Text));

   calcular();
}
//---------------------------------------------------------------------------
void __fastcall TfImprimirResumenManual::Button10Click(TObject *Sender)
{
   if(calcular() == 0.0)
   {
	  if(Application->MessageBox(L"Esta por generar un comprobante por un valor de $ 0,00. Realmente desea continuar?" ,L"ATENCI�N!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
	  {
		 return;
	  }
   }

   if(Application->MessageBox(L"Se va a generar un nuevo comprobante X. Desea continuar?" ,L"Imprimir planillas?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
	  return;

   CanPrint = false;
   String imp_actual;
   String DirComprobantesX;

   TIniFile *Configuraciones;
   String Dir = GetCurrentDir()+"//Config.ini";
   Configuraciones = new TIniFile(Dir);

   if(chbTicket->Checked)
	  imp_actual = Configuraciones->ReadString("Impresion","ImpresoraPlanillas","NO_CONFIGURADA");
   else
	  imp_actual = Configuraciones->ReadString("Impresion","ImpresoraPresupuestos","NO_CONFIGURADA");

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
			if(chbTicket->Checked)
			   Configuraciones->WriteString("Impresion","ImpresoraPlanillas","NO CONFIGURADA");
			else
			   Configuraciones->WriteString("Impresion","ImpresoraPresupuestos","NO CONFIGURADA");
		 }
	  }
	  delete Configuraciones;

	  if(CanPrint)
	  {

		 TfrxMemoView * mDia = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mDia"));
		 TfrxMemoView * mMes = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mMes"));
		 TfrxMemoView * mAno = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mAno"));

		 mDia->Text = IntToStr(DayOfTheMonth(MC->EndDate));
		 mMes->Text = IntToStr(MonthOfTheYear(MC->EndDate));
		 mAno->Text = IntToStr(YearOf(MC->EndDate));
         dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("Memo2"))->Text = FormatDateTime("dd/mm/yyy", MC->Date);



		 TfrxMemoView * mCliente = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mCliente"));
		 mCliente->Text = Edit2->Text;
		 dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mCliente"))->Text = Edit2->Text;


		 float total = 0.0;

		 if(Edit3->Enabled && Edit3->Text != "" && Edit3->Text != "0")
		 {
			TfrxMemoView * mUnidades = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mUnidades1"));
			TfrxMemoView * mDomicilio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mDomicilio1"));
			TfrxMemoView * mPrecio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mPrecio1"));
			TfrxMemoView * mSubtotal = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mSubtotal1"));


			mUnidades->Text = Edit3->Text;
			mDomicilio->Text = Edit4->Text;
			mPrecio->Text = "$"+ Edit5->Text;

			total = total + (StrToFloat(Edit3->Text) * StrToFloat(Edit5->Text));
			mSubtotal->Text = "$"+ FloatToStr(StrToFloat(Edit3->Text) * StrToFloat(Edit5->Text));

			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mUnidades1"))->Text = FormatFloat("0.00", StrToFloat(Edit3->Text));
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mDomicilio1"))->Text = Edit4->Text;
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mPrecio1"))->Text = FormatFloat("$ 0.00", StrToFloat(Edit5->Text));
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mSubtotal1"))->Text = FormatFloat("$ 0.00", StrToFloat(Edit3->Text) * StrToFloat(Edit5->Text));
		 }
		 else
		 {
            TfrxMemoView * mUnidades = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mUnidades1"));
			TfrxMemoView * mDomicilio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mDomicilio1"));
			TfrxMemoView * mPrecio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mPrecio1"));
			TfrxMemoView * mSubtotal = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mSubtotal1"));

			mUnidades->Text = "";
			mDomicilio->Text = "";
			mPrecio->Text = "";
			mSubtotal->Text = "";

			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mUnidades1"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mDomicilio1"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mPrecio1"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mSubtotal1"))->Text = "";
		 }
		 if(Edit6->Enabled && Edit6->Text != "" && Edit6->Text != "0")
		 {
			TfrxMemoView * mUnidades = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mUnidades2"));
			TfrxMemoView * mDomicilio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mDomicilio2"));
			TfrxMemoView * mPrecio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mPrecio2"));
			TfrxMemoView * mSubtotal = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mSubtotal2"));


			mUnidades->Text = Edit6->Text;
			mDomicilio->Text = Edit7->Text;
			mPrecio->Text = "$"+ Edit8->Text;

			total = total + (StrToFloat(Edit6->Text) * StrToFloat(Edit8->Text));
			mSubtotal->Text = "$"+ FloatToStr(StrToFloat(Edit6->Text) * StrToFloat(Edit8->Text));

			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mUnidades2"))->Text = FormatFloat("0.00", StrToFloat(Edit6->Text));
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mDomicilio2"))->Text = Edit7->Text;
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mPrecio2"))->Text = FormatFloat("$ 0.00", StrToFloat(Edit8->Text));
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mSubtotal2"))->Text = FormatFloat("$ 0.00", StrToFloat(Edit6->Text) * StrToFloat(Edit8->Text));
		 }
		 else
		 {
            TfrxMemoView * mUnidades = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mUnidades2"));
			TfrxMemoView * mDomicilio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mDomicilio2"));
			TfrxMemoView * mPrecio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mPrecio2"));
			TfrxMemoView * mSubtotal = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mSubtotal2"));

			mUnidades->Text = "";
			mDomicilio->Text = "";
			mPrecio->Text = "";
			mSubtotal->Text = "";

			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mUnidades2"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mDomicilio2"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mPrecio2"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mSubtotal2"))->Text = "";
		 }
		 if(Edit9->Enabled && Edit9->Text != "" && Edit9->Text != "0")
		 {
			TfrxMemoView * mUnidades = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mUnidades3"));
			TfrxMemoView * mDomicilio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mDomicilio3"));
			TfrxMemoView * mPrecio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mPrecio3"));
			TfrxMemoView * mSubtotal = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mSubtotal3"));


			mUnidades->Text = Edit9->Text;
			mDomicilio->Text = Edit10->Text;
			mPrecio->Text = "$"+ Edit11->Text;

			total = total + (StrToFloat(Edit9->Text) * StrToFloat(Edit11->Text));
			mSubtotal->Text = "$"+ FloatToStr(StrToFloat(Edit9->Text) * StrToFloat(Edit11->Text));

			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mUnidades3"))->Text = FormatFloat("0.00", StrToFloat(Edit9->Text));
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mDomicilio3"))->Text = Edit10->Text;
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mPrecio3"))->Text = FormatFloat("$ 0.00", StrToFloat(Edit11->Text));
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mSubtotal3"))->Text = FormatFloat("$ 0.00", StrToFloat(Edit9->Text) * StrToFloat(Edit11->Text));

		 }
		 else
		 {
            TfrxMemoView * mUnidades = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mUnidades3"));
			TfrxMemoView * mDomicilio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mDomicilio3"));
			TfrxMemoView * mPrecio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mPrecio3"));
			TfrxMemoView * mSubtotal = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mSubtotal3"));

			mUnidades->Text = "";
			mDomicilio->Text = "";
			mPrecio->Text = "";
			mSubtotal->Text = "";

			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mUnidades3"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mDomicilio3"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mPrecio3"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mSubtotal3"))->Text = "";
		 }
		 if(Edit12->Enabled && Edit12->Text != "" && Edit12->Text != "0")
		 {
			TfrxMemoView * mUnidades = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mUnidades4"));
			TfrxMemoView * mDomicilio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mDomicilio4"));
			TfrxMemoView * mPrecio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mPrecio4"));
			TfrxMemoView * mSubtotal = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mSubtotal4"));

			mUnidades->Text = Edit12->Text;
			mDomicilio->Text = Edit13->Text;
			mPrecio->Text = "$"+ Edit14->Text;

			total = total + (StrToFloat(Edit12->Text) * StrToFloat(Edit14->Text));
			mSubtotal->Text = "$"+ FloatToStr(StrToFloat(Edit12->Text) * StrToFloat(Edit14->Text));

			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mUnidades4"))->Text = FormatFloat("0.00", StrToFloat(Edit12->Text));
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mDomicilio4"))->Text = Edit13->Text;
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mPrecio4"))->Text = FormatFloat("$ 0.00", StrToFloat(Edit14->Text));
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mSubtotal4"))->Text = FormatFloat("$ 0.00", StrToFloat(Edit12->Text) * StrToFloat(Edit14->Text));
		 }
		 else
		 {
            TfrxMemoView * mUnidades = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mUnidades4"));
			TfrxMemoView * mDomicilio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mDomicilio4"));
			TfrxMemoView * mPrecio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mPrecio4"));
			TfrxMemoView * mSubtotal = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mSubtotal4"));

			mUnidades->Text = "";
			mDomicilio->Text = "";
			mPrecio->Text = "";
			mSubtotal->Text = "";

			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mUnidades4"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mDomicilio4"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mPrecio4"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mSubtotal4"))->Text = "";
		 }
		 if(Edit15->Enabled && Edit15->Text != "" && Edit15->Text != "0")
		 {
			TfrxMemoView * mUnidades = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mUnidades5"));
			TfrxMemoView * mDomicilio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mDomicilio5"));
			TfrxMemoView * mPrecio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mPrecio5"));
			TfrxMemoView * mSubtotal = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mSubtotal5"));

			mUnidades->Text = Edit15->Text;
			mDomicilio->Text = Edit16->Text;
			mPrecio->Text = "$"+ Edit17->Text;

			total = total + (StrToFloat(Edit15->Text) * StrToFloat(Edit17->Text));
			mSubtotal->Text = "$"+ FloatToStr(StrToFloat(Edit15->Text) * StrToFloat(Edit17->Text));

			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mUnidades5"))->Text = FormatFloat("0.00", StrToFloat(Edit15->Text));
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mDomicilio5"))->Text = Edit16->Text;
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mPrecio5"))->Text = FormatFloat("$ 0.00", StrToFloat(Edit17->Text));
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mSubtotal5"))->Text = FormatFloat("$ 0.00", StrToFloat(Edit15->Text) * StrToFloat(Edit17->Text));
		 }
		 else
		 {
            TfrxMemoView * mUnidades = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mUnidades5"));
			TfrxMemoView * mDomicilio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mDomicilio5"));
			TfrxMemoView * mPrecio = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mPrecio5"));
			TfrxMemoView * mSubtotal = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mSubtotal5"));

			mUnidades->Text = "";
			mDomicilio->Text = "";
			mPrecio->Text = "";
			mSubtotal->Text = "";

			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mUnidades5"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mDomicilio5"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mPrecio5"))->Text = "";
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mSubtotal5"))->Text = "";
		 }

		 TfrxMemoView * mTotal = dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("mTotal"));
		 mTotal->Text = FloatToStr(total);

		 dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("mTotal"))->Text = FormatFloat("Total: $ 0.00", total);


			Query1->Close();
			Query1->SQL->Clear();
			Query1->SQL->Add("INSERT INTO comprobantesX (fechaComprobante, fechaEmision, refCliente, total) "
							   "VALUES(:fc, NOW(), :rc, :total)");
			Query1->ParamByName("fc")->AsDate = MC->Date;
			Query1->ParamByName("rc")->AsInteger = idCliente;
			Query1->ParamByName("total")->AsFloat = total;
			Query1->ExecSQL();

			Query1->Close();
			Query1->SQL->Clear();
			Query1->SQL->Add("SELECT MAX(idComprobanteX) AS maxid FROM comprobantesX");
			Query1->Open();
			String s =  Query1->FieldByName("maxid")->AsString;
			Query1->Close();

			while(s.Length() < 7)
			   s = s.Insert("0", 1);

			s = "0010 - " + s;	//un punto de venta inventado

//			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport1->FindObject("Memo18"))->Text = s;
			dynamic_cast <TfrxMemoView *> (fImprimirResumenManual->frxReport2->FindObject("Memo18"))->Text = s;


		 if(chbTicket->Checked)
		 {
			frxReport1->PrintOptions->Printer = imp_actual;
			frxReport1->PrepareReport(true);
			frxReport1->Print();
		 }
		 else
		 {
			frxReport2->PrintOptions->Printer = imp_actual;
			frxReport2->PrepareReport(true);
			frxReport2->Print();

			frxPDFExport1->FileName = DirComprobantesX + "\\" + s + ".pdf";

			frxReport2->Export(frxPDFExport1);
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
void __fastcall TfImprimirResumenManual::FormShow(TObject *Sender)
{
      Edit2->Enabled = false;
      Edit3->Enabled = false;
      Edit4->Enabled = false;
      Edit5->Enabled = false;
      Edit6->Enabled = false;
      Edit7->Enabled = false;
      Edit8->Enabled = false;
      Edit9->Enabled = false;
      Edit10->Enabled = false;
      Edit11->Enabled = false;
      Edit12->Enabled = false;
      Edit13->Enabled = false;
      Edit14->Enabled = false;
      Edit15->Enabled = false;
      Edit16->Enabled = false;
      Edit17->Enabled = false;
      Edit2->Text = "";
      Edit3->Text = "0";
	  Edit4->Text = "Pedido";
      Edit5->Text = "0";
      Edit6->Text = "0";
	  Edit7->Text = "Pedido";
      Edit8->Text = "0";
      Edit9->Text = "0";
	  Edit10->Text = "Pedido";
      Edit11->Text = "0";
      Edit12->Text = "0";
	  Edit13->Text = "Pedido";
      Edit14->Text = "0";
      Edit15->Text = "0";
      Edit16->Text = "Pedido";
	  Edit17->Text = "0";

	  Label1->Caption = "";

	  Edit2->Enabled = true;
	  Edit3->Enabled = true;
	  Edit4->Enabled = true;
	  Edit5->Enabled = true;
	  Button10->Enabled = false;

	  MC->Date = Now();
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit2Change(TObject *Sender)
{
   if(Edit2->Text == "")
	  Button10->Enabled = false;
   else
      Button10->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Button1Click(TObject *Sender)
{
   fSeleccionarCliente->llamador = 1;
   fSeleccionarCliente->ShowModal();

   if(fSeleccionarCliente->idSeleccionado < 2)
	  return;

   mostrarCliente(fSeleccionarCliente->idSeleccionado);
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit3KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
	  Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit6KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
	  Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit9KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
	  Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit12KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
	  Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit15KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
	  Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit5KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
	  Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit8KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
	  Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit11KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
	  Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit14KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
	  Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit17KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
	  Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit3Change(TObject *Sender)
{
   if(Edit3->Text.Length() > 0)
	  Edit1->Text = FormatFloat("$ 0.00", StrToFloat(Edit3->Text) * StrToFloat(Edit5->Text));

   calcular();
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit6Change(TObject *Sender)
{
   if(Edit6->Text.Length() > 0)
	  Edit18->Text = FormatFloat("$ 0.00", StrToFloat(Edit6->Text) * StrToFloat(Edit8->Text));

   calcular();
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit9Change(TObject *Sender)
{
   if(Edit9->Text.Length() > 0)
	  Edit19->Text = FormatFloat("$ 0.00", StrToFloat(Edit9->Text) * StrToFloat(Edit11->Text));

   calcular();
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit12Change(TObject *Sender)
{
   if(Edit12->Text.Length() > 0)
	  Edit20->Text = FormatFloat("$ 0.00", StrToFloat(Edit12->Text) * StrToFloat(Edit14->Text));

   calcular();
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit15Change(TObject *Sender)
{
   if(Edit15->Text.Length() > 0)
	  Edit21->Text = FormatFloat("$ 0.00", StrToFloat(Edit15->Text) * StrToFloat(Edit17->Text));

   calcular();
}
//---------------------------------------------------------------------------

void __fastcall TfImprimirResumenManual::Edit17Change(TObject *Sender)
{
   if(Edit17->Text.Length() > 0)
	  Edit21->Text = FormatFloat("$ 0.00", /*StrToFloat(Edit15->Text) * */StrToFloat(Edit17->Text));

   calcular();
}
//---------------------------------------------------------------------------

