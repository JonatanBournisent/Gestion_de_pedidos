//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFormulaComidas.h"
#include "uSeleccionarComida.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfFormulaComidas *fFormulaComidas;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfFormulaComidas::TfFormulaComidas(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfFormulaComidas::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------
void __fastcall TfFormulaComidas::FormShow(TObject *Sender)
{
   idComida = -1;
   Panel1->Visible = false;
   QueryAux->Close();
   QueryAux->SQL->Clear();

   QueryAux->SQL->Add("SELECT nombre FROM ingredientes ORDER BY nombre");
   QueryAux->Open();
   QueryAux->First();
   ComboBox1->Clear();
   while(!QueryAux->Eof)
   {
	  ComboBox1->Items->Add(QueryAux->FieldByName("nombre")->AsString);
	  QueryAux->Next();
   }
   QueryAux->Close();
   ComboBox1->ItemIndex = -1;

   Edit1->Text = "0,00";

   fSeleccionarComida->ShowModal();
   if(fSeleccionarComida->idSeleccionado < 2)
   {
	  ShowMessage("Sebe seleccionar una comida. Cierre y vuelva a abrir esta ventana");
	  return;
   }

   idComida = fSeleccionarComida->idSeleccionado;

   CDS1->Active = false;
   Query1->Close();
   Query1->SQL->Clear();
   String q;
   q = "SELECT idFormulaComida, refIngrediente, cantidadCada100g, "
	   "(SELECT nombre FROM ingredientes WHERE idIngrediente = refIngrediente LIMIT 1) AS ingrediente "
	   "FROM formulacomidas WHERE refComida = :idComida ORDER BY ingrediente";
   Query1->SQL->Add(q);
   Query1->ParamByName("idComida")->AsInteger = idComida;
   Query1->Open();
   CDS1->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfFormulaComidas::Edit1Exit(TObject *Sender)
{
   String s = dynamic_cast<TEdit *>(Sender)->Text;

   try
   {
	  StrToFloat(s);
   }
   catch(...)
   {
	  s = "0,00";
   }

   dynamic_cast<TEdit *>(Sender)->Text = FormatFloat("0.00", StrToFloat(s));
}
//---------------------------------------------------------------------------
void __fastcall TfFormulaComidas::Edit1KeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == '.')
	  Key = ',';

   if((Key < '0' || Key > '9') && Key != '\b' && Key != ',')
	  Key = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfFormulaComidas::Button1Click(TObject *Sender)
{
   if(idComida < 2)
	  Close();


   if(ComboBox1->ItemIndex == -1)
	  return;


   QueryAux->Close();
   QueryAux->SQL->Clear();
   String q;

   q = "SELECT idFormulaComida FROM formulacomidas WHERE refComida = :refComida AND refIngrediente = (SELECT idIngrediente FROM ingredientes WHERE nombre = :nombre LIMIT 1) LIMIT 1";

   QueryAux->SQL->Add(q);
   QueryAux->ParamByName("refComida")->AsInteger = idComida;
   QueryAux->ParamByName("nombre")->AsString = ComboBox1->Items->Strings[ComboBox1->ItemIndex];
   QueryAux->Open();

   if(!QueryAux->IsEmpty())
   {
      QueryAux->Close();
	  Application->MessageBox(L"Este ingrediente ya se encuentra agregado.", L"ERROR",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
      return;
   }

   Panel1->Visible = false;
   QueryAux->Close();
   QueryAux->SQL->Clear();

   q = "INSERT INTO formulacomidas ( "
	   "refComida, refIngrediente, cantidadCada100g) "
	   "VALUES(:refComida, (SELECT idIngrediente FROM ingredientes WHERE nombre = :nombre LIMIT 1), :cantidadCada100g)";

   QueryAux->SQL->Add(q);
   QueryAux->ParamByName("refComida")->AsInteger = idComida;
   QueryAux->ParamByName("nombre")->AsString = ComboBox1->Items->Strings[ComboBox1->ItemIndex];
   QueryAux->ParamByName("cantidadCada100g")->AsFloat = StrToFloat(Edit1->Text);
   QueryAux->ExecSQL();

   CDS1->Active = false;
   CDS1->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfFormulaComidas::Agregaringrediente1Click(TObject *Sender)
{
   Edit1->Text = "0,00";
   ComboBox1->ItemIndex = -1;
   Panel1->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TfFormulaComidas::Button2Click(TObject *Sender)
{
   Panel1->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfFormulaComidas::Eliminaresteingrediente1Click(TObject *Sender)
{
   if(Application->MessageBox(L"Se va a quitar este ingrediente de esta comida. Desea continuar?", L"ATENCIÓN",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1) != IDYES)
	  return;

   QueryAux->Close();
   QueryAux->SQL->Clear();
   QueryAux->SQL->Add("DELETE FROM formulaComidas WHERE idFormulaComida = :idFormulaComida LIMIT 1");
   QueryAux->ParamByName("idFormulaComida")->AsInteger = CDS1->FieldByName("idFormulaComida")->AsInteger;
   QueryAux->ExecSQL();

   CDS1->Active = false;
   CDS1->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfFormulaComidas::FormClose(TObject *Sender, TCloseAction &Action)

{
   Query1->Close();
   QueryAux->Close();
   SQLConnection1->Close();
}
//---------------------------------------------------------------------------

