//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPrecios.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfPrecios *fPrecios;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfPrecios::TfPrecios(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
float TfPrecios::getValor(String txt)
{
   try
   {
	  if(txt.Pos("$ ") > 0)
		 return StrToFloat(txt.Delete(1,2));
	  else
		 return StrToFloat(txt);
   }
   catch(...)
   {
      return 0.00;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::FormShow(TObject *Sender)
{
   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("SELECT idListaPrecio, valor FROM listasprecio ORDER BY idListaPrecio");
   Query1->Open();
   Query1->First();

   while(!Query1->Eof)
   {
	  if(Query1->FieldByName("idListaPrecio")->AsInteger == 1)
		 Edit1->Text = FormatFloat("$ 0.00", Query1->FieldByName("valor")->AsFloat);
	  else if(Query1->FieldByName("idListaPrecio")->AsInteger == 2)
		 Edit2->Text = FormatFloat("$ 0.00", Query1->FieldByName("valor")->AsFloat);
	  else if(Query1->FieldByName("idListaPrecio")->AsInteger == 3)
		 Edit3->Text = FormatFloat("$ 0.00", Query1->FieldByName("valor")->AsFloat);
	  else if(Query1->FieldByName("idListaPrecio")->AsInteger == 4)
		 Edit4->Text = FormatFloat("$ 0.00", Query1->FieldByName("valor")->AsFloat);

	  Query1->Next();
   }
   Query1->Close();

   Edit1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::Edit1Enter(TObject *Sender)
{
   String txt = dynamic_cast<TEdit *>(Sender)->Text;
   if(txt.Pos("$ ") > 0)
	  dynamic_cast<TEdit *>(Sender)->Text = txt.Delete(1,2);
   dynamic_cast<TEdit *>(Sender)->SelectAll();
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::Edit2Enter(TObject *Sender)
{
   String txt = dynamic_cast<TEdit *>(Sender)->Text;
   if(txt.Pos("$ ") > 0)
	  dynamic_cast<TEdit *>(Sender)->Text = txt.Delete(1,2);
   dynamic_cast<TEdit *>(Sender)->SelectAll();
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::Edit3Enter(TObject *Sender)
{
   String txt = dynamic_cast<TEdit *>(Sender)->Text;
   if(txt.Pos("$ ") > 0)
	  dynamic_cast<TEdit *>(Sender)->Text = txt.Delete(1,2);
   dynamic_cast<TEdit *>(Sender)->SelectAll();
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::Edit4Enter(TObject *Sender)
{
   String txt = dynamic_cast<TEdit *>(Sender)->Text;
   if(txt.Pos("$ ") > 0)
	  dynamic_cast<TEdit *>(Sender)->Text = txt.Delete(1,2);
   dynamic_cast<TEdit *>(Sender)->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TfPrecios::Edit1Exit(TObject *Sender)
{
   String txt = dynamic_cast<TEdit *>(Sender)->Text;
   if(txt.Length() == 0)
      txt = "0,00";
   if(txt.Pos("$ ") == 0)
	  dynamic_cast<TEdit *>(Sender)->Text = FormatFloat("$ 0.00", StrToFloat(txt));
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::Edit2Exit(TObject *Sender)
{
   String txt = dynamic_cast<TEdit *>(Sender)->Text;
   if(txt.Length() == 0)
      txt = "0,00";
   if(txt.Pos("$ ") == 0)
	  dynamic_cast<TEdit *>(Sender)->Text = FormatFloat("$ 0.00", StrToFloat(txt));
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::Edit3Exit(TObject *Sender)
{
   String txt = dynamic_cast<TEdit *>(Sender)->Text;
   if(txt.Length() == 0)
      txt = "0,00";
   if(txt.Pos("$ ") == 0)
	  dynamic_cast<TEdit *>(Sender)->Text = FormatFloat("$ 0.00", StrToFloat(txt));
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::Edit4Exit(TObject *Sender)
{
   String txt = dynamic_cast<TEdit *>(Sender)->Text;
   if(txt.Length() == 0)
      txt = "0,00";
   if(txt.Pos("$ ") == 0)
	  dynamic_cast<TEdit *>(Sender)->Text = FormatFloat("$ 0.00", StrToFloat(txt));
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
   if(Key == '.')
	  Key = ',';
   if((Key < '0' || Key > '9') && Key != '\b' && Key != ',')
	  Key = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::Edit2KeyPress(TObject *Sender, System::WideChar &Key)
{
   if(Key == '.')
	  Key = ',';
   if((Key < '0' || Key > '9') && Key != '\b' && Key != ',')
	  Key = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::Edit3KeyPress(TObject *Sender, System::WideChar &Key)
{
   if(Key == '.')
	  Key = ',';
   if((Key < '0' || Key > '9') && Key != '\b' && Key != ',')
	  Key = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::Edit4KeyPress(TObject *Sender, System::WideChar &Key)
{
   if(Key == '.')
	  Key = ',';
   if((Key < '0' || Key > '9') && Key != '\b' && Key != ',')
	  Key = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::Button1Click(TObject *Sender)
{
   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("UPDATE listasprecio SET valor = :valor WHERE idListaPrecio = 1 LIMIT 1");
   Query1->ParamByName("valor")->AsFloat = getValor(Edit1->Text);
   Query1->ExecSQL();

   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("UPDATE listasprecio SET valor = :valor WHERE idListaPrecio = 2 LIMIT 1");
   Query1->ParamByName("valor")->AsFloat = getValor(Edit2->Text);
   Query1->ExecSQL();

   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("UPDATE listasprecio SET valor = :valor WHERE idListaPrecio = 3 LIMIT 1");
   Query1->ParamByName("valor")->AsFloat = getValor(Edit3->Text);
   Query1->ExecSQL();

   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("UPDATE listasprecio SET valor = :valor WHERE idListaPrecio = 4 LIMIT 1");
   Query1->ParamByName("valor")->AsFloat = getValor(Edit4->Text);
   Query1->ExecSQL();

   Application->MessageBox(L"Los precios fueron actualizados correctamente" ,L"Cambios realizados",MB_OK | MB_ICONINFORMATION| MB_DEFBUTTON1);
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TfPrecios::FormClose(TObject *Sender, TCloseAction &Action)
{
   Query1->Close();
   SQLConnection1->Close();
}
//---------------------------------------------------------------------------

