//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uMensajes.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfMensajes *fMensajes;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfMensajes::TfMensajes(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfMensajes::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------
void TfMensajes::cargarTitulos(void)
{
	Query->Close();
	Query->SQL->Clear();
	Query->SQL->Add("SELECT titulo FROM mensajes ORDER BY idMensaje");
	Query->Open();

	CB->Items->Clear();
	while (!Query->Eof) {
		CB->Items->Add(Query->FieldByName("titulo")->AsString);
		Query->Next();
	}
	Query->Close();
}
//---------------------------------------------------------------------------
void TfMensajes::cargarMensaje(String titulo)
{
	Query->Close();
	Query->SQL->Clear();
	Query->SQL->Add("SELECT mensaje FROM mensajes WHERE titulo = :titulo");
	Query->ParamByName("titulo")->AsString = titulo;
	Query->Open();

	TStringStream *Stream;
	Stream = new TStringStream(Query->FieldByName("mensaje")->AsString);
	Memo1->Lines->LoadFromStream(Stream);
	Query->Close();
	delete Stream;
	Memo1->Enabled = true;
}
//---------------------------------------------------------------------------
void TfMensajes::actualizarMensaje(String titulo)
{
	TStringStream *Stream;
	Stream = new TStringStream();
	Memo1->Lines->SaveToStream(Stream);

	Query->Close();
	Query->SQL->Clear();
	Query->SQL->Add("UPDATE mensajes SET mensaje = :mensaje WHERE titulo = :titulo");
	Query->ParamByName("titulo")->AsString = titulo;
	Query->ParamByName("mensaje")->AsString = Stream->DataString;
	Query->ExecSQL();

	delete Stream;
}
//---------------------------------------------------------------------------
void TfMensajes::actualizarTitulo(String tituloViejo, String tituloNuevo)
{
	Query->Close();
	Query->SQL->Clear();
	Query->SQL->Add("UPDATE mensajes SET titulo = :tituloNuevo WHERE titulo = :tituloViejo");
	Query->ParamByName("tituloNuevo")->AsString = tituloNuevo;
	Query->ParamByName("tituloViejo")->AsString = tituloViejo;
	Query->ExecSQL();
}
//---------------------------------------------------------------------------
void __fastcall TfMensajes::FormShow(TObject *Sender)
{
	Panel1->Hide();
	Panel2->Hide();
	Button1->Enabled = true;
	Button2->Enabled = false;
	Button3->Enabled = false;
	Button4->Enabled = true;
	Modificartitulo1->Enabled = true;
	CB->Enabled = true;
	Memo1->Enabled = false;
	cargarTitulos();
}
//---------------------------------------------------------------------------
void __fastcall TfMensajes::Button1Click(TObject *Sender)
{
	if (CB->ItemIndex < 0) {
		return;
	}
	Button2->Enabled = true;
	Button3->Enabled = true;
	Button4->Enabled = false;
	Modificartitulo1->Enabled = false;
	CB->Enabled = false;

	cargarMensaje(CB->Items->Strings[CB->ItemIndex]);
}
//---------------------------------------------------------------------------
void __fastcall TfMensajes::Button2Click(TObject *Sender)
{
	if(Application->MessageBox(L"Se van a guardar los cambios. Desea continuar?", L"ATENCIÓN",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1) != IDYES)
	  return;

	Button1->Enabled = true;
	Button2->Enabled = false;
	Button3->Enabled = false;
	Button4->Enabled = true;
	Modificartitulo1->Enabled = true;
	CB->Enabled = true;
	actualizarMensaje(CB->Items->Strings[CB->ItemIndex]);
	Memo1->Enabled = false;
	Memo1->Clear();
	CB->ItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TfMensajes::Button3Click(TObject *Sender)
{
	if(Application->MessageBox(L"Se van a descartar los cambios realizados. Desea continuar?", L"ATENCIÓN",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON1) != IDYES)
	  return;

	Button1->Enabled = true;
	Button2->Enabled = false;
	Button3->Enabled = false;
	Button4->Enabled = true;
	Modificartitulo1->Enabled = true;
	CB->Enabled = true;
	Memo1->Clear();
	Memo1->Enabled = false;
	CB->ItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TfMensajes::Button5Click(TObject *Sender)
{
	if(Application->MessageBox(L"Se va a agregar un nuevo título. Desea continuar?", L"ATENCIÓN",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1) != IDYES)
	  return;

	Query->Close();
	Query->SQL->Clear();
	Query->SQL->Add("INSERT INTO mensajes (titulo) VALUES (:titulo)");
	Query->ParamByName("titulo")->AsString = Edit1->Text;
	Query->ExecSQL();

	cargarTitulos();
	CB->ItemIndex = CB->Items->IndexOf(Edit1->Text);
	Panel1->Hide();
	Button1Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfMensajes::Button4Click(TObject *Sender)
{
	Edit1->Text = "";
	Panel1->Show();
	Edit1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfMensajes::Button6Click(TObject *Sender)
{
	Panel1->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfMensajes::Modificartitulo1Click(TObject *Sender)
{
	if (CB->ItemIndex < 0) {
		return;
	}

	Edit2->Text = CB->Items->Strings[CB->ItemIndex];
	Panel2->Show();
	Edit2->SetFocus();
	Edit2->SelectAll();
}
//---------------------------------------------------------------------------
void __fastcall TfMensajes::Button7Click(TObject *Sender)
{
	if(Application->MessageBox(L"Se va a modificar el título actual. Desea continuar?", L"ATENCIÓN",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1) != IDYES)
	  return;

	actualizarTitulo(CB->Items->Strings[CB->ItemIndex], Edit2->Text);

	cargarTitulos();
	CB->ItemIndex = CB->Items->IndexOf(Edit2->Text);
	Panel2->Hide();
	Button1Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfMensajes::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (Button2->Enabled) {
		Application->MessageBox(L"Debe guardar o cancelar los cambios antes de salir", L"ERROR" ,MB_OK | MB_ICONERROR);
    	Action = caNone;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfMensajes::Button8Click(TObject *Sender)
{
	Panel2->Hide();
}
//---------------------------------------------------------------------------
