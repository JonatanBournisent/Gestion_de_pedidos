//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#include <IniFiles.hpp>
#include <Clipbrd.hpp>

#pragma hdrstop

#include "uComidasExcluidas.h"
#include "uMenuSemanal.h"
#include "uMenuDelDia.h"
#include "uAgregarComida.h"
#include "uModificarComida.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxClass"
#pragma link "frxExportBaseDialog"
#pragma link "frxExportImage"
#pragma link "frxRich"
#pragma resource "*.dfm"
TfMenuSemanal *fMenuSemanal;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfMenuSemanal::TfMenuSemanal(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void TfMenuSemanal::actualizarMenu()
{
   ListBox1->Clear();

   Query1->Close();
   Query1->SQL->Clear();
   String q = "SELECT *, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida1 LIMIT 1) AS c1, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida2 LIMIT 1) AS c2, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida3 LIMIT 1) AS c3, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida4 LIMIT 1) AS c4, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida5 LIMIT 1) AS c5, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida6 LIMIT 1) AS c6, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida7 LIMIT 1) AS c7, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida8 LIMIT 1) AS c8 "
			  "FROM menudeldia WHERE (fecha = :f) LIMIT 1";
   Query1->SQL->Add(q);
   
   for (int i = 0; i < 6; i++)
   {
		if(i > 0)
		 ListBox1->Items->Add("");

		iTitulo[i] = ListBox1->Items->Count;

		if(i == 0)
		 ListBox1->Items->Add("Lunes");
		else if(i == 1)
		 ListBox1->Items->Add("Martes");
		else if(i == 2)
		 ListBox1->Items->Add("Miércoles");
		else if(i == 3)
		 ListBox1->Items->Add("Jueves");
		else if(i == 4)
		 ListBox1->Items->Add("Viernes");
		else if(i == 5)
		 ListBox1->Items->Add("Sábado");
   
		Query1->ParamByName("f")->AsDate = IncDay(MC1->Date, i);
		Query1->Open();
		if(!Query1->IsEmpty())
		{
		  if(Query1->FieldByName("refComida1")->AsInteger == 1)
		  {
			 iTitulo2[i] = 10000;  //Un numero que nunca alcanza
			 ListBox1->Items->Add("CERRADO");
		  }
		  else
		  {
		 
		  ListBox1->Items->Add("Plato principal:");
		  ListBox1->Items->Add("  - " + Query1->FieldByName("c1")->AsString);

		  if(Query1->FieldByName("refComida2")->AsInteger != 1)
			 ListBox1->Items->Add("  - " + Query1->FieldByName("c2")->AsString);
		  if(Query1->FieldByName("refComida3")->AsInteger != 1)
			 ListBox1->Items->Add("  - " + Query1->FieldByName("c3")->AsString);
		  if(Query1->FieldByName("refComida4")->AsInteger != 1)
			 ListBox1->Items->Add("  - " + Query1->FieldByName("c4")->AsString);
		  if(Query1->FieldByName("refComida5")->AsInteger != 1)
			 ListBox1->Items->Add("  - " + Query1->FieldByName("c5")->AsString);
		  if(Query1->FieldByName("refComida6")->AsInteger != 1)
			 ListBox1->Items->Add("  - " + Query1->FieldByName("c6")->AsString);

		  iTitulo2[i] = ListBox1->Items->Count;
		  ListBox1->Items->Add("Complemento:");
	  
		  if(Query1->FieldByName("refComida7")->AsInteger != 1)
			 ListBox1->Items->Add("  - " + Query1->FieldByName("c7")->AsString);
		  if(Query1->FieldByName("refComida8")->AsInteger != 1)
			 ListBox1->Items->Add("  - " + Query1->FieldByName("c8")->AsString);
		  }
		}
		else
		{
		  iTitulo2[i] = 10000;
		  ListBox1->Items->Add("No configurado");
		}
		Query1->Close();
   }
}
//---------------------------------------------------------------------------
void TfMenuSemanal::actualizarMenuOld()
{
   ListBox2->Clear();

   Query1->Close();
   Query1->SQL->Clear();
   String q = "SELECT *, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida1 LIMIT 1) AS c1, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida2 LIMIT 1) AS c2, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida3 LIMIT 1) AS c3, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida4 LIMIT 1) AS c4, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida5 LIMIT 1) AS c5, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida6 LIMIT 1) AS c6, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida7 LIMIT 1) AS c7, "
			  "(SELECT nombre FROM comidas WHERE idComida = refComida8 LIMIT 1) AS c8 "
			  "FROM menudeldia WHERE (fecha = :f) LIMIT 1";
   Query1->SQL->Add(q);

   for (int i = 0; i < 6; i++)
   {
	  if(i > 0)
		 ListBox2->Items->Add("");

	  iTituloOld[i] = ListBox2->Items->Count;

	  if(i == 0)
		 ListBox2->Items->Add("Lunes");
	  else if(i == 1)
		 ListBox2->Items->Add("Martes");
	  else if(i == 2)
		 ListBox2->Items->Add("Miércoles");
	  else if(i == 3)
		 ListBox2->Items->Add("Jueves");
	  else if(i == 4)
		 ListBox2->Items->Add("Viernes");
	  else if(i == 5)
		 ListBox2->Items->Add("Sábado");

   Query1->ParamByName("f")->AsDate = IncDay(MC2->Date, i);
   Query1->Open();
   if(!Query1->IsEmpty())
   {
	  if(Query1->FieldByName("refComida1")->AsInteger == 1)
	  {
		 iTituloOld2[i] = 10000;  //Un numero que nunca alcanza
		 ListBox2->Items->Add("CERRADO");
	  }
	  else
	  {

	  ListBox2->Items->Add("Plato principal:");
	  ListBox2->Items->Add("  - " + Query1->FieldByName(String("C1"))->AsString);

	  if(Query1->FieldByName("refComida2")->AsInteger != 1)
		 ListBox2->Items->Add("  - " + Query1->FieldByName("c2")->AsString);
	  if(Query1->FieldByName("refComida3")->AsInteger != 1)
		 ListBox2->Items->Add("  - " + Query1->FieldByName("c3")->AsString);
	  if(Query1->FieldByName("refComida4")->AsInteger != 1)
		 ListBox2->Items->Add("  - " + Query1->FieldByName("c4")->AsString);
	  if(Query1->FieldByName("refComida5")->AsInteger != 1)
		 ListBox2->Items->Add("  - " + Query1->FieldByName("c5")->AsString);
	  if(Query1->FieldByName("refComida6")->AsInteger != 1)
		 ListBox2->Items->Add("  - " + Query1->FieldByName("c6")->AsString);

	  iTituloOld2[i] = ListBox2->Items->Count;
	  ListBox2->Items->Add("Complemento:");

	  if(Query1->FieldByName("refComida7")->AsInteger != 1)
		 ListBox2->Items->Add("  - " + Query1->FieldByName("c7")->AsString);
	  if(Query1->FieldByName("refComida8")->AsInteger != 1)
		 ListBox2->Items->Add("  - " + Query1->FieldByName("c8")->AsString);
	  }
   }
   else
   {
	  iTituloOld2[i] = 10000;
	  ListBox2->Items->Add("No configurado");
   }
   Query1->Close();
   }
}
//---------------------------------------------------------------------------
void __fastcall TfMenuSemanal::FormShow(TObject *Sender)
{
   TIniFile *Configuraciones;
   String Dir = GetCurrentDir()+"//Config.ini";
   Configuraciones = new TIniFile(Dir);

   DirMenuMail = Configuraciones->ReadString("Directorios","DirMenuMail","NO_CONFIGURADO");
   DirMenuVenta = Configuraciones->ReadString("Directorios","DirMenuVenta","NO_CONFIGURADO");
   DirPlanillaVenta = Configuraciones->ReadString("Directorios","DirPlanillaVenta","NO_CONFIGURADO");
   DirPlanillaFijos = Configuraciones->ReadString("Directorios","DirPlanillaFijos","NO_CONFIGURADO");
   DirPlanillaInstrucciones = Configuraciones->ReadString("Directorios","DirPlanillaInstrucciones","NO_CONFIGURADO");

   if(DirMenuMail == "NO_CONFIGURADO" || DirMenuVenta == "NO_CONFIGURADO" || DirPlanillaVenta == "NO_CONFIGURADO" || DirPlanillaFijos == "NO_CONFIGURADO" || DirPlanillaInstrucciones == "NO_CONFIGURADO")
   {
	  ShowMessage("Se deben configurar todos los directorios antes de generar las planillas de Word");
	  Button13->Enabled = false;
   }
   else
   {
      Button13->Enabled = true;
   }


   delete Configuraciones;



   MC1->Date = StartOfTheWeek(Now());
   MC1->EndDate = IncDay(MC1->Date,5);

   MC2->Date = StartOfTheWeek(IncWeek(MC1->Date, -52));
   MC2->EndDate = IncDay(MC2->Date,5);

   Button18->Enabled = true;

   actualizarMenu();
   actualizarMenuOld();
   CheckBox1->Checked = false;
   //ListBox1->Enabled = false;
   //ListBox2->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button1Click(TObject *Sender)
{
   fMenuDelDia->fecha = MC1->Date;
   fMenuDelDia->ShowModal();
   actualizarMenu();

   if(RevisarDuplicado())
	  Application->MessageBox(L"Hay al menos una comida repetida en el menú de esta semana",L"Hay una comida repetida",MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);

}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button2Click(TObject *Sender)
{
   fMenuDelDia->fecha = IncDay(MC1->Date, 1);
   fMenuDelDia->ShowModal();
   actualizarMenu();

   if(RevisarDuplicado())
	  Application->MessageBox(L"Hay al menos una comida repetida en el menú de esta semana",L"Hay una comida repetida",MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button3Click(TObject *Sender)
{
   fMenuDelDia->fecha = IncDay(MC1->Date, 2);
   fMenuDelDia->ShowModal();
   actualizarMenu();

   if(RevisarDuplicado())
	  Application->MessageBox(L"Hay al menos una comida repetida en el menú de esta semana",L"Hay una comida repetida",MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button4Click(TObject *Sender)
{
   fMenuDelDia->fecha = IncDay(MC1->Date, 3);
   fMenuDelDia->ShowModal();
   actualizarMenu();

   if(RevisarDuplicado())
	  Application->MessageBox(L"Hay al menos una comida repetida en el menú de esta semana",L"Hay una comida repetida",MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button5Click(TObject *Sender)
{
   fMenuDelDia->fecha = IncDay(MC1->Date, 4);
   fMenuDelDia->ShowModal();
   actualizarMenu();

   if(RevisarDuplicado())
	  Application->MessageBox(L"Hay al menos una comida repetida en el menú de esta semana",L"Hay una comida repetida",MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button6Click(TObject *Sender)
{
   fMenuDelDia->fecha = IncDay(MC1->Date, 5);
   fMenuDelDia->ShowModal();
   actualizarMenu();

   if(RevisarDuplicado())
	  Application->MessageBox(L"Hay al menos una comida repetida en el menú de esta semana",L"Hay una comida repetida",MB_OK | MB_ICONWARNING | MB_DEFBUTTON1);
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::MC1Click(TObject *Sender)
{
   MC1->Date = StartOfTheWeek(MC1->Date);
   MC1->EndDate = IncDay(MC1->Date,5);
   actualizarMenu();
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button7Click(TObject *Sender)
{
   MC1->Date = IncDay(MC1->Date,-7);
   MC1->EndDate = IncDay(MC1->Date,5);
   actualizarMenu();

   MC2->MultiSelect = false;
   MC2->Date = StartOfTheWeek(IncWeek(MC1->Date, -52));
   MC2->MultiSelect = true;
   MC2->EndDate = IncDay(MC2->Date,5);

//   MC2->Date = IncDay(MC2->Date,-7);
//   MC2->EndDate = IncDay(MC2->Date,5);
   actualizarMenuOld();
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button8Click(TObject *Sender)
{
   MC1->Date = IncDay(MC1->Date,7);
   MC1->EndDate = IncDay(MC1->Date,5);
   actualizarMenu();

   MC2->MultiSelect = false;
   MC2->Date = StartOfTheWeek(IncWeek(MC1->Date, -52));
   MC2->MultiSelect = true;
   MC2->EndDate = IncDay(MC2->Date,5);

//   MC2->Date = IncDay(MC2->Date,7);
//   MC2->EndDate = IncDay(MC2->Date,5);
   actualizarMenuOld();
}
//---------------------------------------------------------------------------


void __fastcall TfMenuSemanal::ListBox1DrawItem(TWinControl *Control, int Index, TRect &Rect,
          TOwnerDrawState State)
{
   if(Index == iTitulo[0] || Index == iTitulo[1] || Index == iTitulo[2] || Index == iTitulo[3] || Index == iTitulo[4] || Index == iTitulo[5])
   {
	  ListBox1->Canvas->Font->Style = TFontStyles() << fsUnderline;
	  ListBox1->Canvas->Font->Size = 12;
	  ListBox1->Canvas->Font->Color = clNavy;
	  ListBox1->Canvas->TextRect(Rect, Rect.Left+3, Rect.Top, ListBox1->Items->Strings[Index]);
   }
   else if(Index == iTitulo[0]+1 || Index == iTitulo[1]+1 || Index == iTitulo[2]+1 || Index == iTitulo[3]+1 || Index == iTitulo[4]+1 || Index == iTitulo[5]+1)
   {
	  ListBox1->Canvas->Font->Style = TFontStyles() << fsBold;
	  ListBox1->Canvas->Font->Size = 10;
	  ListBox1->Canvas->Font->Color = clHighlight;
	  ListBox1->Canvas->TextRect(Rect, Rect.Left+10, Rect.Top + 1, ListBox1->Items->Strings[Index]);
   }
   else if(Index == iTitulo2[0] || Index == iTitulo2[1] || Index == iTitulo2[2] || Index == iTitulo2[3] || Index == iTitulo2[4] || Index == iTitulo2[5])
   {
	  ListBox1->Canvas->Font->Style = TFontStyles() << fsBold;
	  ListBox1->Canvas->Font->Size = 10;
	  ListBox1->Canvas->Font->Color = clHighlight;
	  ListBox1->Canvas->TextRect(Rect, Rect.Left+10, Rect.Top + 1, ListBox1->Items->Strings[Index]);
   }
   else
   {
	  ListBox1->Canvas->Font->Size = 10;
	  ListBox1->Canvas->Font->Color = clBlack;
	  ListBox1->Canvas->TextRect(Rect, Rect.Left+10, Rect.Top+1, ListBox1->Items->Strings[Index]);
   }
	
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::ListBox1Click(TObject *Sender)
{
//   ListBox1->ItemIndex = -1;
//   Button1->SetFocus();	
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::CheckBox1Click(TObject *Sender)
{
   if(CheckBox1->Checked)
	  ListBox1->Enabled = true;
   else
      ListBox1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::FormClose(TObject *Sender, TCloseAction &Action)
{
   Query1->Close();
   QueryMenu->Close();
   SQLConnection1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::MC2Click(TObject *Sender)
{
   MC2->Date = StartOfTheWeek(MC2->Date);
   MC2->EndDate = IncDay(MC2->Date,5);
   actualizarMenuOld();
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button9Click(TObject *Sender)
{
   MC2->Date = IncDay(MC2->Date,-7);
   MC2->EndDate = IncDay(MC2->Date,5);
   actualizarMenuOld();
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button10Click(TObject *Sender)
{
   MC2->Date = IncDay(MC2->Date,7);
   MC2->EndDate = IncDay(MC2->Date,5);
   actualizarMenuOld();
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::ListBox2DrawItem(TWinControl *Control, int Index, TRect &Rect,
          TOwnerDrawState State)
{
   if(Index == iTituloOld[0] || Index == iTituloOld[1] || Index == iTituloOld[2] || Index == iTituloOld[3] || Index == iTituloOld[4] || Index == iTituloOld[5])
   {
	  ListBox2->Canvas->Font->Style = TFontStyles() << fsUnderline;
	  ListBox2->Canvas->Font->Size = 12;
	  ListBox2->Canvas->Font->Color = clNavy;
	  ListBox2->Canvas->TextRect(Rect, Rect.Left+3, Rect.Top, ListBox2->Items->Strings[Index]);
   }
   else if(Index == iTituloOld[0]+1 || Index == iTituloOld[1]+1 || Index == iTituloOld[2]+1 || Index == iTituloOld[3]+1 || Index == iTituloOld[4]+1 || Index == iTituloOld[5]+1)
   {
	  ListBox2->Canvas->Font->Style = TFontStyles() << fsBold;
	  ListBox2->Canvas->Font->Size = 10;
	  ListBox2->Canvas->Font->Color = clHighlight;
	  ListBox2->Canvas->TextRect(Rect, Rect.Left+10, Rect.Top + 1, ListBox2->Items->Strings[Index]);
   }
   else if(Index == iTituloOld2[0] || Index == iTituloOld2[1] || Index == iTituloOld2[2] || Index == iTituloOld2[3] || Index == iTituloOld2[4] || Index == iTituloOld2[5])
   {
	  ListBox2->Canvas->Font->Style = TFontStyles() << fsBold;
	  ListBox2->Canvas->Font->Size = 10;
	  ListBox2->Canvas->Font->Color = clHighlight;
	  ListBox2->Canvas->TextRect(Rect, Rect.Left+10, Rect.Top + 1, ListBox2->Items->Strings[Index]);
   }
   else
   {
	  ListBox2->Canvas->Font->Size = 10;
	  ListBox2->Canvas->Font->Color = clBlack;
	  ListBox2->Canvas->TextRect(Rect, Rect.Left+10, Rect.Top+1, ListBox2->Items->Strings[Index]);
   }
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button11Click(TObject *Sender)
{
   if(MC1->Date <= MC2->Date)
   {
	  Application->MessageBox(L"La fecha del menú actual debe ser superior a la del menú viejo.",L"No se realizaron cambios!",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return;
   }

   if(Application->MessageBox(L"Desea copiar el menú seleccionado a la semana actual?",L"Copiar menú?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
   {
	  Query1->Close();
	  Query1->SQL->Clear();
	  Query1->SQL->Add("SELECT COUNT(*) AS existe FROM menudeldia WHERE(Fecha >= :fi AND Fecha <= :ff) LIMIT 1");
	  Query1->ParamByName("fi")->AsDate = IncDay(MC1->Date,0);
	  Query1->ParamByName("ff")->AsDate = IncDay(MC1->Date,5);
	  Query1->Open();
	  int existe = Query1->FieldByName("existe")->AsInteger;
	  Query1->Close();

	  if(existe == 0)
	  {
		  int difDias = DaysBetween(MC1->Date, MC2->Date);

		  if (difDias > 6)
		  {

			 String q = "INSERT INTO menudeldia "
						"(fecha, refComida1,  refComida2, refComida3, refComida4, refComida5, refComida6, refComida7, refComida8) "
						"SELECT DATE_ADD(fecha, INTERVAL :dd DAY) , refComida1,  refComida2, refComida3, refComida4, refComida5, refComida6, refComida7, refComida8 "
						"FROM menudeldia WHERE (Fecha >= :fi AND Fecha <= :ff) LIMIT 6";


			 Query1->SQL->Clear();
			 Query1->SQL->Add(q);
			 Query1->ParamByName("fi")->AsDate = IncDay(MC2->Date,0);
			 Query1->ParamByName("ff")->AsDate = IncDay(MC2->Date,5);
			 Query1->ParamByName("dd")->AsInteger = difDias;
			 Query1->ExecSQL();
		  }
	  }
	  else
		 Application->MessageBox(L"Antes deberá eliminar el menú actual...",L"No se realizaron cambios!",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
   }

   actualizarMenu();
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button12Click(TObject *Sender)
{
   if(Application->MessageBox(L"Realmente desea eliminar el menú actual?",L"Eliminar menú?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
   {
      Query1->Close();
	  Query1->SQL->Clear();
	  Query1->SQL->Add("DELETE FROM menudeldia WHERE (Fecha >= :fi AND Fecha <= :ff) LIMIT 6");
	  Query1->ParamByName("fi")->AsDate = IncDay(MC1->Date,0);
	  Query1->ParamByName("ff")->AsDate = IncDay(MC1->Date,5);
	  Query1->ExecSQL();
	  actualizarMenu();
	  actualizarMenuOld();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button13Click(TObject *Sender)
{
   QueryMenu->Close();
   QueryMenu->SQL->Clear();
   QueryMenu->SQL->Add("SELECT COUNT(*) AS cantidad FROM menudeldia WHERE(fecha >= :fi AND fecha <= :ff) ORDER BY fecha LIMIT 6");
   QueryMenu->ParamByName("fi")->AsDate = IncDay(MC1->Date,0);
   QueryMenu->ParamByName("ff")->AsDate = IncDay(MC1->Date,5);
   QueryMenu->Open();

   if(QueryMenu->FieldByName("cantidad")->AsInteger < 6)      // este menu no esta completo
   {
	  QueryMenu->Close();
	  Application->MessageBox(L"El menú elegido no está completo",L"No se realizaron cambios!",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return;
   }
   QueryMenu->Close();


   if(Application->MessageBox(L"Desea generar las planillas de Word?",L"Generar planillas?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
   {

	  Panel1->Left = (fMenuSemanal->Width - Panel1->Width) / 2;
	  Panel1->Top = (fMenuSemanal->Height - Panel1->Height) / 2;

	  Panel1->Caption = "Generando planillas...";

	  Panel1->Visible = true;

	  fMenuSemanal->Repaint();

	  try
	  {
		 vMSWord = Variant::GetActiveObject("Word.Application");
	  }
	  catch(...)
	  {
		 vMSWord = Variant::CreateObject("Word.Application");
	  }

	  vMSWord.OlePropertySet("Visible", false);

	  String NombreArchivo = FormatDateTime("dd'-'mm'-'yyyy", StartOfTheWeek(MC1->Date)) + "." + FormatDateTime("dd'-'mm'-'yyyy", IncDay(StartOfTheWeek(MC1->Date),5)) + ".doc";

	  Panel1->Caption = "Generando planillas... (1/15)";
	  fMenuSemanal->Repaint();
	  GenerarMenuMail(GetCurrentDir() + "\\Plantillas\\PlantillaMenuMail.dot", DirMenuMail + "\\" + NombreArchivo);

	  Panel1->Caption = "Generando planillas... (2/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaInstrucciones(GetCurrentDir() + "\\Plantillas\\PlantillaPlanillaInstrucciones.dot", DirPlanillaInstrucciones + "\\" + NombreArchivo);
	  Panel1->Caption = "Generando planillas... (3/15)";
	  fMenuSemanal->Repaint();
	  GenerarMenuVenta(GetCurrentDir() + "\\Plantillas\\PlantillaMenuVenta.dot", DirMenuVenta + "\\" + NombreArchivo);
	  NombreArchivo = FormatDateTime("dddd dd'-'mm'-'yyyy", IncDay(StartOfTheWeek(MC1->Date),0)) + ".doc";
	  Panel1->Caption = "Generando planillas... (4/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaFijos(GetCurrentDir() + "\\Plantillas\\PlantillaFijosLunes.dot", DirPlanillaFijos + "\\" + NombreArchivo, 0);
	  Panel1->Caption = "Generando planillas... (5/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaVenta(GetCurrentDir() + "\\Plantillas\\PlantillaPlanillaVenta.dot", DirPlanillaVenta + "\\" + NombreArchivo, 0);
	  NombreArchivo = FormatDateTime("dddd dd'-'mm'-'yyyy", IncDay(StartOfTheWeek(MC1->Date),1)) + ".doc";
	  Panel1->Caption = "Generando planillas... (6/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaFijos(GetCurrentDir() + "\\Plantillas\\PlantillaFijosMartes.dot", DirPlanillaFijos + "\\" + NombreArchivo, 1);
	  Panel1->Caption = "Generando planillas... (7/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaVenta(GetCurrentDir() + "\\Plantillas\\PlantillaPlanillaVenta.dot", DirPlanillaVenta + "\\" + NombreArchivo, 1);
      NombreArchivo = FormatDateTime("dddd dd'-'mm'-'yyyy", IncDay(StartOfTheWeek(MC1->Date),2)) + ".doc";
	  Panel1->Caption = "Generando planillas... (8/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaFijos(GetCurrentDir() + "\\Plantillas\\PlantillaFijosMiercoles.dot", DirPlanillaFijos + "\\" + NombreArchivo, 2);
	  Panel1->Caption = "Generando planillas... (9/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaVenta(GetCurrentDir() + "\\Plantillas\\PlantillaPlanillaVenta.dot", DirPlanillaVenta + "\\" + NombreArchivo, 2);
	  NombreArchivo = FormatDateTime("dddd dd'-'mm'-'yyyy", IncDay(StartOfTheWeek(MC1->Date),3)) + ".doc";
	  Panel1->Caption = "Generando planillas... (10/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaFijos(GetCurrentDir() + "\\Plantillas\\PlantillaFijosJueves.dot", DirPlanillaFijos + "\\" + NombreArchivo, 3);
	  Panel1->Caption = "Generando planillas... (11/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaVenta(GetCurrentDir() + "\\Plantillas\\PlantillaPlanillaVenta.dot", DirPlanillaVenta + "\\" + NombreArchivo, 3);
	  NombreArchivo = FormatDateTime("dddd dd'-'mm'-'yyyy", IncDay(StartOfTheWeek(MC1->Date),4)) + ".doc";
	  Panel1->Caption = "Generando planillas... (12/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaFijos(GetCurrentDir() + "\\Plantillas\\PlantillaFijosViernes.dot", DirPlanillaFijos + "\\" + NombreArchivo, 4);
	  Panel1->Caption = "Generando planillas... (13/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaVenta(GetCurrentDir() + "\\Plantillas\\PlantillaPlanillaVenta.dot", DirPlanillaVenta + "\\" + NombreArchivo, 4);
	  NombreArchivo = FormatDateTime("dddd dd'-'mm'-'yyyy", IncDay(StartOfTheWeek(MC1->Date),5)) + ".doc";
	  Panel1->Caption = "Generando planillas... (14/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaFijos(GetCurrentDir() + "\\Plantillas\\PlantillaFijosSabado.dot", DirPlanillaFijos + "\\" + NombreArchivo, 5);
	  Panel1->Caption = "Generando planillas... (15/15)";
	  fMenuSemanal->Repaint();
	  GenerarPlanillaVenta(GetCurrentDir() + "\\Plantillas\\PlantillaPlanillaVenta.dot", DirPlanillaVenta + "\\" + NombreArchivo, 5);


	  vMSWord.OleFunction("Quit");

	  Panel1->Visible = false;

	  Application->MessageBox(L"Las planillas fueron generadas",L"Fin del proceso",MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
   }
}
//---------------------------------------------------------------------------


void TfMenuSemanal::GenerarMenuMail(String DirPlantilla, String DirDestino)
{
   String q;

   q = "SELECT *, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida1 LIMIT 1) AS nComida1, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida2 LIMIT 1) AS nComida2, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida3 LIMIT 1) AS nComida3, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida4 LIMIT 1) AS nComida4, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida5 LIMIT 1) AS nComida5, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida6 LIMIT 1) AS nComida6, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida7 LIMIT 1) AS nComida7, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida8 LIMIT 1) AS nComida8 "
	   "FROM menudeldia WHERE(fecha >= :fi AND fecha <= :ff) ORDER BY fecha LIMIT 6";

   QueryMenu->Close();
   QueryMenu->SQL->Clear();
   QueryMenu->SQL->Add(q);
   QueryMenu->ParamByName("fi")->AsDate = IncDay(MC1->Date,0);
   QueryMenu->ParamByName("ff")->AsDate = IncDay(MC1->Date,5);
   QueryMenu->Open();


   vWDocuments = vMSWord.OlePropertyGet("Documents");

   try
   {
	  //vWDocuments.Exec(Procedure("Open") << DirPlantilla);
	  vWDocuments.OleFunction("Open", StringToOleStr(DirPlantilla));
   }
   catch (...) { }

   try
   {
	  vWDocument = vMSWord.OlePropertyGet("ActiveDocument");
   }
   catch (...) { }


   Variant mySel, myBmark, myItem, mySelI, myRow, myTables, myTable, myRows;

   String lista[] = {"LUNESPP1", "LUNESPP2", "LUNESPP3", "LUNESPP4", "LUNESPP5", "LUNESPP6", "LUNESC1", "LUNESC2",
						 "MARTESPP1", "MARTESPP2", "MARTESPP3", "MARTESPP4", "MARTESPP5", "MARTESPP6", "MARTESC1", "MARTESC2",
						 "MIERCOLESPP1", "MIERCOLESPP2", "MIERCOLESPP3", "MIERCOLESPP4", "MIERCOLESPP5", "MIERCOLESPP6", "MIERCOLESC1", "MIERCOLESC2",
						 "JUEVESPP1", "JUEVESPP2", "JUEVESPP3", "JUEVESPP4", "JUEVESPP5", "JUEVESPP6", "JUEVESC1", "JUEVESC2",
						 "VIERNESPP1", "VIERNESPP2", "VIERNESPP3", "VIERNESPP4", "VIERNESPP5", "VIERNESPP6", "VIERNESC1", "VIERNESC2",
						 "SABADOPP1", "SABADOPP2", "SABADOPP3", "SABADOPP4", "SABADOPP5", "SABADOPP6", "SABADOC1", "SABADOC2"};

   String fechas[] = {"FECHALUNES", "FECHAMARTES", "FECHAMIERCOLES", "FECHAJUEVES", "FECHAVIERNES", "FECHASABADO"};



   QueryMenu->First();
   int i = 0;

   while(!QueryMenu->Eof)
   {
	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(fechas[i]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  Range.OleProcedure("Delete");
	  Range.OleProcedure("InsertAfter", StringToOleStr(FormatDateTime("dddd dd'/'mm'/'yyyy", QueryMenu->FieldByName("fecha")->AsDateTime).UpperCase()));
	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  Range.OleProcedure("Delete");
	  Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("nComida1")->AsString));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+1]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  Range.OleProcedure("Delete");
	  Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("nComida2")->AsString));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+2]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  Range.OleProcedure("Delete");
	  Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("nComida3")->AsString));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+3]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  Range.OleProcedure("Delete");
	  Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("nComida4")->AsString));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+4]));
	  Range = myItem.OlePropertyGet("Range");
      Range.OleProcedure("Select");
	  Range.OleProcedure("Delete");
	  Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("nComida5")->AsString));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+5]));
      Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  Range.OleProcedure("Delete");
	  Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("nComida6")->AsString));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+6]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  Range.OleProcedure("Delete");
	  Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("nComida7")->AsString));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+7]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  Range.OleProcedure("Delete");
	  Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("nComida8")->AsString));

	  i++;
	  QueryMenu->Next();
   }

   QueryMenu->First();
   i = 0;

   int j;
   bool borroSalsa = false;

   while(!QueryMenu->Eof)
   {
	  if(QueryMenu->FieldByName("refComida1")->AsInteger == 1 && QueryMenu->FieldByName("refComida7")->AsInteger == 1)
	  {
		 myBmark = vWDocument.OlePropertyGet("Bookmarks");
		 if(i == 0)
			myItem = myBmark.OleFunction("Item", StringToOleStr(String("LUNESPP1")));
		 else if(i == 1)
			myItem = myBmark.OleFunction("Item", StringToOleStr(String("MARTESPP1")));
		 else if(i == 2)
			myItem = myBmark.OleFunction("Item", StringToOleStr(String("MIERCOLESPP1")));
		 else if(i == 3)
			myItem = myBmark.OleFunction("Item", StringToOleStr(String("JUEVESPP1")));
		 else if(i == 4)
			myItem = myBmark.OleFunction("Item", StringToOleStr(String("VIERNESPP1")));
		 else if(i == 5)
			myItem = myBmark.OleFunction("Item", StringToOleStr(String("SABADOPP1")));

		 Range = myItem.OlePropertyGet("Range");
		 Range.OleProcedure("Select");
		 Range.OleProcedure("Delete");
		 Range.OleProcedure("InsertAfter", StringToOleStr(String("CERRADO")));

		 for(j=4;j<12;j++)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(4)));
			myRow.OleProcedure("Delete");
         }

         myTables = vWDocument.OlePropertyGet("Tables");
		 myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
         myRows = myTable.OlePropertyGet("Rows");
		 myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(2)));
		 myRow.OleProcedure("Delete");
	  }

	  else if(QueryMenu->FieldByName("refComida1")->AsInteger == 1)
	  {
		 for(j=3;j<9;j++)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(3)));
			myRow.OleProcedure("Delete");
		 }

		 if(QueryMenu->FieldByName("refComida7")->AsInteger == 1)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(4)));
			myRow.OleProcedure("Delete");

			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(4)));
			myRow.OleProcedure("Delete");
		 }
		 else if(QueryMenu->FieldByName("refComida8")->AsInteger == 1)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(5)));
			myRow.OleProcedure("Delete");
		 }
	  }
	  else if(QueryMenu->FieldByName("refComida2")->AsInteger == 1)
	  {
		 for(j=4;j<9;j++)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(4)));
			myRow.OleProcedure("Delete");
		 }

		 if(QueryMenu->FieldByName("refComida7")->AsInteger == 1)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(5)));
			myRow.OleProcedure("Delete");

			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(5)));
			myRow.OleProcedure("Delete");
		 }
		 else if(QueryMenu->FieldByName("refComida8")->AsInteger == 1)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(6)));
			myRow.OleProcedure("Delete");
		 }
	  }
	  else if(QueryMenu->FieldByName("refComida3")->AsInteger == 1)
	  {
		 for(j=5;j<9;j++)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(5)));
			myRow.OleProcedure("Delete");
		 }

		 if(QueryMenu->FieldByName("refComida7")->AsInteger == 1)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(6)));
			myRow.OleProcedure("Delete");

			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(6)));
			myRow.OleProcedure("Delete");
		 }
		 else if(QueryMenu->FieldByName("refComida8")->AsInteger == 1)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(7)));
			myRow.OleProcedure("Delete");
		 }
	  }
	  else if(QueryMenu->FieldByName("refComida4")->AsInteger == 1)
	  {
		 for(j=6;j<9;j++)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(6)));
			myRow.OleProcedure("Delete");
		 }

		 if(QueryMenu->FieldByName("refComida7")->AsInteger == 1)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(7)));
			myRow.OleProcedure("Delete");

			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(7)));
			myRow.OleProcedure("Delete");
		 }
		 else if(QueryMenu->FieldByName("refComida8")->AsInteger == 1)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(8)));
			myRow.OleProcedure("Delete");
		 }
	  }
	  else if(QueryMenu->FieldByName("refComida5")->AsInteger == 1)
	  {
		 for(j=7;j<9;j++)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(7)));
			myRow.OleProcedure("Delete");
		 }

		 if(QueryMenu->FieldByName("refComida7")->AsInteger == 1)
		 {
            myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(8)));
            myRow.OleProcedure("Delete");

            myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
            myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(8)));
			myRow.OleProcedure("Delete");
		 }
         else if(QueryMenu->FieldByName("refComida8")->AsInteger == 1)
		 {
            myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
            myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(9)));
			myRow.OleProcedure("Delete");
		 }
      }
	  else if(QueryMenu->FieldByName("refComida6")->AsInteger == 1)
	  {
		 myTables = vWDocument.OlePropertyGet("Tables");
		 myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
		 myRows = myTable.OlePropertyGet("Rows");
		 myRow = myRows.OleFunction(("Item"), StringToOleStr(IntToStr(8)));
		 myRow.OleFunction("Delete");

		 if(QueryMenu->FieldByName("refComida7")->AsInteger == 1)
         {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(9)));
			myRow.OleProcedure("Delete");

			myTables = vWDocument.OlePropertyGet("Tables");
            myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(9)));
			myRow.OleProcedure("Delete");
		 }
		 else if(QueryMenu->FieldByName("refComida8")->AsInteger == 1)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(10)));
			myRow.OleProcedure("Delete");
		 }
	  }
	  else if(QueryMenu->FieldByName("refComida7")->AsInteger == 1)
	  {
		 myTables = vWDocument.OlePropertyGet("Tables");
		 myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
		 myRows = myTable.OlePropertyGet("Rows");
		 myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(10)));
		 myRow.OleProcedure("Delete");

		 myTables = vWDocument.OlePropertyGet("Tables");
		 myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
		 myRows = myTable.OlePropertyGet("Rows");
		 myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(10)));
		 myRow.OleProcedure("Delete");
	  }
	  else if(QueryMenu->FieldByName("refComida8")->AsInteger == 1)
	  {
		 myTables = vWDocument.OlePropertyGet("Tables");
		 myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(i+1)));
		 myRows = myTable.OlePropertyGet("Rows");
		 myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(11)));
		 myRow.OleProcedure("Delete");
	  }

	  if((i == 3) && (QueryMenu->FieldByName("refComida2")->AsInteger == 2431 || QueryMenu->FieldByName("refComida2")->AsInteger == 2434 || QueryMenu->FieldByName("refComida2")->AsInteger == 2664))
	  {
         myTables = vWDocument.OlePropertyGet("Tables");
		 myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(4)));
		 myRows = myTable.OlePropertyGet("Rows");
		 myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(4)));
		 myRow.OleProcedure("Delete");
		 borroSalsa = true;
	  }
	  if((i == 3) && (QueryMenu->FieldByName("refComida4")->AsInteger == 2431 || QueryMenu->FieldByName("refComida4")->AsInteger == 2434 || QueryMenu->FieldByName("refComida4")->AsInteger == 2664))
	  {
         if(borroSalsa)
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(4)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(5)));
			myRow.OleProcedure("Delete");
		 }
		 else
		 {
			myTables = vWDocument.OlePropertyGet("Tables");
			myTable = myTables.OleFunction("Item", StringToOleStr(IntToStr(4)));
			myRows = myTable.OlePropertyGet("Rows");
			myRow = myRows.OleFunction("Item", StringToOleStr(IntToStr(6)));
			myRow.OleProcedure("Delete");
		 }
	  }

	  i++;
	  QueryMenu->Next();
   }

   QueryMenu->Close();

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("FECHAMENU")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(FormatDateTime("dd'/'mm'/'yyyy", MC1->Date) + " al " + FormatDateTime("dd'/'mm'/'yyyy", IncDay(MC1->Date,5))));

   vWDocument.OleProcedure("SaveAs", StringToOleStr(DirDestino));
   vWDocument.OleProcedure("Close");
}

//---------------------------------------------------------------------------

void TfMenuSemanal::GenerarPlanillaFijos(String DirPlantilla, String DirDestino, int indiceDia)
{
   vWDocuments = vMSWord.OlePropertyGet("Documents");

   try
   {
	  vWDocuments.OleFunction("Open", StringToOleStr(DirPlantilla));
   }
   catch (...) { }

   try
   {
	  vWDocument = vMSWord.OlePropertyGet("ActiveDocument");
   }
   catch (...) { }


   Variant mySel, myBmark, myItem, mySelI, myRow, myTables, myTable, myRows;



   String q;

   q = "SELECT *, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida1 LIMIT 1) AS cComida1, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida2 LIMIT 1) AS cComida2, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida3 LIMIT 1) AS cComida3, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida4 LIMIT 1) AS cComida4, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida5 LIMIT 1) AS cComida5, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida6 LIMIT 1) AS cComida6, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida7 LIMIT 1) AS cComida7, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida8 LIMIT 1) AS cComida8 "
       "FROM menudeldia WHERE(fecha = :f) LIMIT 1";


   QueryMenu->Close();
   QueryMenu->SQL->Clear();
   QueryMenu->SQL->Add(q);
   QueryMenu->ParamByName("f")->AsDate = IncDay(MC1->Date,indiceDia);
   QueryMenu->Open();


   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("PP1")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida1")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("PP2")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida2")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("PP3")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida3")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("PP4")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida4")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("PP5")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida5")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("PP6")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida6")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("C1")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida7")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("C2")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida8")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("FECHA")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(FormatDateTime("dddd dd'/'mm", QueryMenu->FieldByName("fecha")->AsDateTime).UpperCase()));

   vWDocument.OleProcedure("SaveAs", StringToOleStr(DirDestino));
   vWDocument.Exec(Procedure("Close"));

   QueryMenu->Close();
}

//---------------------------------------------------------------------------

void TfMenuSemanal::GenerarPlanillaVenta(String DirPlantilla, String DirDestino, int indiceDia)
{
   vWDocuments = vMSWord.OlePropertyGet("Documents");

   try
   {
      vWDocuments.OleFunction("Open", StringToOleStr(DirPlantilla));
   }
   catch (...) { }

   try
   {
      vWDocument = vMSWord.OlePropertyGet("ActiveDocument");
   }
   catch (...) { }


   Variant mySel, myBmark, myItem, mySelI, myRow, myTables, myTable, myRows;


   String q;

   q = "SELECT *, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida1 LIMIT 1) AS cComida1, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida2 LIMIT 1) AS cComida2, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida3 LIMIT 1) AS cComida3, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida4 LIMIT 1) AS cComida4, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida5 LIMIT 1) AS cComida5, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida6 LIMIT 1) AS cComida6, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida7 LIMIT 1) AS cComida7, "
	   "(SELECT UPPER(codigo) FROM comidas WHERE idComida = refComida8 LIMIT 1) AS cComida8 "
       "FROM menudeldia WHERE(fecha = :f) LIMIT 1";


   QueryMenu->Close();
   QueryMenu->SQL->Clear();
   QueryMenu->SQL->Add(q);
   QueryMenu->ParamByName("f")->AsDate = IncDay(MC1->Date,indiceDia);
   QueryMenu->Open();


   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("PP1")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida1")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("PP2")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida2")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("PP3")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida3")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("PP4")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida4")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("PP5")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida5")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("PP6")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida6")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("C1")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida7")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("C2")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(QueryMenu->FieldByName("cComida8")->AsString));

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("FECHA")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(FormatDateTime("dddd dd'/'mm", QueryMenu->FieldByName("fecha")->AsDateTime).UpperCase()));

   QueryMenu->Close();

   vWDocument.OleProcedure("SaveAs", StringToOleStr(DirDestino));
   vWDocument.Exec(Procedure("Close"));

}

//---------------------------------------------------------------------------

void TfMenuSemanal::GenerarPlanillaInstrucciones(String DirPlantilla, String DirDestino)
{
   vWDocuments = vMSWord.OlePropertyGet("Documents");

   try
   {
      vWDocuments.OleFunction("Open", StringToOleStr(DirPlantilla));
   }
   catch (...) { }

   try
   {
      vWDocument = vMSWord.OlePropertyGet("ActiveDocument");
   }
   catch (...) { }


   Variant mySel, myBmark, myItem, mySelI, myRow, myTables, myTable, myRows;

   String lista[] = {"PP1LUNES", "PP2LUNES", "PP3LUNES", "PP4LUNES", "PP5LUNES", "PP6LUNES", "C1LUNES", "C2LUNES",
                         "PP1MARTES", "PP2MARTES", "PP3MARTES", "PP4MARTES", "PP5MARTES", "PP6MARTES", "C1MARTES", "C2MARTES",
                         "PP1MIERCOLES", "PP2MIERCOLES", "PP3MIERCOLES", "PP4MIERCOLES", "PP5MIERCOLES", "PP6MIERCOLES", "C1MIERCOLES", "C2MIERCOLES",
                         "PP1JUEVES", "PP2JUEVES", "PP3JUEVES", "PP4JUEVES", "PP5JUEVES", "PP6JUEVES", "C1JUEVES", "C2JUEVES",
                         "PP1VIERNES", "PP2VIERNES", "PP3VIERNES", "PP4VIERNES", "PP5VIERNES", "PP6VIERNES", "C1VIERNES", "C2VIERNES",
                         "PP1SABADO", "PP2SABADO", "PP3SABADO", "PP4SABADO", "PP5SABADO", "PP6SABADO", "C1SABADO", "C2SABADO"};

   String fechas[] = {"FECHALUNES", "FECHAMARTES", "FECHAMIERCOLES", "FECHAJUEVES", "FECHAVIERNES", "FECHASABADO"};




   String q;

   q = "SELECT *, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida1 LIMIT 1) AS nComida1, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida2 LIMIT 1) AS nComida2, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida3 LIMIT 1) AS nComida3, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida4 LIMIT 1) AS nComida4, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida5 LIMIT 1) AS nComida5, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida6 LIMIT 1) AS nComida6, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida7 LIMIT 1) AS nComida7, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida8 LIMIT 1) AS nComida8 "
	   "FROM menudeldia WHERE(fecha >= :fi AND fecha <= :ff) ORDER BY fecha LIMIT 6";


   QueryMenu->Close();
   QueryMenu->SQL->Clear();
   QueryMenu->SQL->Add(q);
   QueryMenu->ParamByName("fi")->AsDate = IncDay(MC1->Date,0);
   QueryMenu->ParamByName("ff")->AsDate = IncDay(MC1->Date,5);
   QueryMenu->Open();


   QueryMenu->First();
   int i = 0;

   while(!QueryMenu->Eof)
   {
	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(fechas[i]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  Range.OleProcedure("Delete");
	  Range.OleProcedure("InsertAfter", StringToOleStr(FormatDateTime("dddd dd'/'mm'/'yyyy", QueryMenu->FieldByName("fecha")->AsDateTime).UpperCase()));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  //Range.OleProcedure("Delete");
	  if(QueryMenu->FieldByName("refComida1")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida1")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+1]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  //Range.OleProcedure("Delete");
	  if(QueryMenu->FieldByName("refComida2")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida2")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+2]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  //Range.OleProcedure("Delete");
	  if(QueryMenu->FieldByName("refComida3")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida3")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

      myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+3]));
      Range = myItem.OlePropertyGet("Range");
      Range.OleProcedure("Select");
      //Range.OleProcedure("Delete");
	  if(QueryMenu->FieldByName("refComida4")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida4")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+4]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
      //Range.OleProcedure("Delete");
      if(QueryMenu->FieldByName("refComida5")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida5")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

      myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+5]));
      Range = myItem.OlePropertyGet("Range");
      Range.OleProcedure("Select");
      //Range.OleProcedure("Delete");
	  if(QueryMenu->FieldByName("refComida6")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida6")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+6]));
      Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
      //Range.OleProcedure("Delete");
      if(QueryMenu->FieldByName("refComida7")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida7")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+7]));
      Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
      //Range.OleProcedure("Delete");
	  if(QueryMenu->FieldByName("refComida8")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida8")->AsString));
      else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

	  i++;
	  QueryMenu->Next();
   }

   QueryMenu->Close();

   vWDocument.OleProcedure("SaveAs", StringToOleStr(DirDestino));
   vWDocument.Exec(Procedure("Close"));
}

//---------------------------------------------------------------------------

void TfMenuSemanal::GenerarMenuVenta(String DirPlantilla, String DirDestino)
{
   vWDocuments = vMSWord.OlePropertyGet("Documents");

   try
   {
	  vWDocuments.OleFunction("Open", StringToOleStr(DirPlantilla));
   }
   catch (...) { }

   try
   {
	  vWDocument = vMSWord.OlePropertyGet("ActiveDocument");
   }
   catch (...) { }

   Variant mySel, myBmark, myItem, mySelI, myRow, myTables, myTable, myRows;

   String lista[] = {"PP1LUNES", "PP2LUNES", "PP3LUNES", "PP4LUNES", "PP5LUNES", "PP6LUNES", "C1LUNES", "C2LUNES",
                         "PP1MARTES", "PP2MARTES", "PP3MARTES", "PP4MARTES", "PP5MARTES", "PP6MARTES", "C1MARTES", "C2MARTES",
                         "PP1MIERCOLES", "PP2MIERCOLES", "PP3MIERCOLES", "PP4MIERCOLES", "PP5MIERCOLES", "PP6MIERCOLES", "C1MIERCOLES", "C2MIERCOLES",
                         "PP1JUEVES", "PP2JUEVES", "PP3JUEVES", "PP4JUEVES", "PP5JUEVES", "PP6JUEVES", "C1JUEVES", "C2JUEVES",
                         "PP1VIERNES", "PP2VIERNES", "PP3VIERNES", "PP4VIERNES", "PP5VIERNES", "PP6VIERNES", "C1VIERNES", "C2VIERNES",
						 "PP1SABADO", "PP2SABADO", "PP3SABADO", "PP4SABADO", "PP5SABADO", "PP6SABADO", "C1SABADO", "C2SABADO"};

   String fechas[] = {"FECHALUNES", "FECHAMARTES", "FECHAMIERCOLES", "FECHAJUEVES", "FECHAVIERNES", "FECHASABADO"};

   String q;

   q = "SELECT *, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida1 LIMIT 1) AS nComida1, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida2 LIMIT 1) AS nComida2, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida3 LIMIT 1) AS nComida3, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida4 LIMIT 1) AS nComida4, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida5 LIMIT 1) AS nComida5, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida6 LIMIT 1) AS nComida6, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida7 LIMIT 1) AS nComida7, "
	   "(SELECT UPPER(nombre) FROM comidas WHERE idComida = refComida8 LIMIT 1) AS nComida8 "
	   "FROM menudeldia WHERE(fecha >= :fi AND fecha <= :ff) ORDER BY fecha LIMIT 6";


   QueryMenu->Close();
   QueryMenu->SQL->Clear();
   QueryMenu->SQL->Add(q);
   QueryMenu->ParamByName("fi")->AsDate = IncDay(MC1->Date,0);
   QueryMenu->ParamByName("ff")->AsDate = IncDay(MC1->Date,5);
   QueryMenu->Open();


   QueryMenu->First();
   int i = 0;

   while(!QueryMenu->Eof)
   {
	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(fechas[i]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  Range.OleProcedure("Delete");
	  Range.OleProcedure("InsertAfter", StringToOleStr(FormatDateTime("dddd dd'/'mm'/'yyyy", QueryMenu->FieldByName("fecha")->AsDateTime).UpperCase()));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  //Range.OleProcedure("Delete");
	  if(QueryMenu->FieldByName("refComida1")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida1")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+1]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  //Range.OleProcedure("Delete");
	  if(QueryMenu->FieldByName("refComida2")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida2")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+2]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
	  //Range.OleProcedure("Delete");
	  if(QueryMenu->FieldByName("refComida3")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida3")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

      myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+3]));
      Range = myItem.OlePropertyGet("Range");
      Range.OleProcedure("Select");
      //Range.OleProcedure("Delete");
	  if(QueryMenu->FieldByName("refComida4")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida4")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+4]));
	  Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
      //Range.OleProcedure("Delete");
      if(QueryMenu->FieldByName("refComida5")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida5")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

      myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+5]));
      Range = myItem.OlePropertyGet("Range");
      Range.OleProcedure("Select");
      //Range.OleProcedure("Delete");
	  if(QueryMenu->FieldByName("refComida6")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida6")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+6]));
      Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
      //Range.OleProcedure("Delete");
      if(QueryMenu->FieldByName("refComida7")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida7")->AsString));
	  else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

	  myBmark = vWDocument.OlePropertyGet("Bookmarks");
	  myItem = myBmark.OleFunction("Item", StringToOleStr(lista[8*i+7]));
      Range = myItem.OlePropertyGet("Range");
	  Range.OleProcedure("Select");
      //Range.OleProcedure("Delete");
	  if(QueryMenu->FieldByName("refComida8")->AsInteger != 1)
		 Range.OleProcedure("InsertBefore", StringToOleStr(QueryMenu->FieldByName("nComida8")->AsString));
      else
		 Range.OleProcedure("InsertBefore", StringToOleStr(String(" ")));

	  i++;
	  QueryMenu->Next();
   }

   QueryMenu->Close();

   myBmark = vWDocument.OlePropertyGet("Bookmarks");
   myItem = myBmark.OleFunction("Item", StringToOleStr(String("FECHAMENU")));
   Range = myItem.OlePropertyGet("Range");
   Range.OleProcedure("Select");
   Range.OleProcedure("Delete");
   Range.OleProcedure("InsertAfter", StringToOleStr(FormatDateTime("dd'/'mm'/'yyyy", MC1->Date) + " al " + FormatDateTime("dd'/'mm'/'yyyy", IncDay(MC1->Date,5))));

   vWDocument.OleProcedure("SaveAs", StringToOleStr(DirDestino));
   vWDocument.Exec(Procedure("Close"));
}

//---------------------------------------------------------------------------
void __fastcall TfMenuSemanal::Button15Click(TObject *Sender)
{
   fModificarComida->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button14Click(TObject *Sender)
{
   fAgregarComida->ShowModal();
}
//---------------------------------------------------------------------------

bool TfMenuSemanal::RevisarDuplicado(void)
{
      QueryMenu->Close();
	  QueryMenu->SQL->Clear();
	  QueryMenu->SQL->Add("SELECT * FROM menudeldia WHERE (Fecha >= :fi AND Fecha <= :ff) LIMIT 6");
	  QueryMenu->ParamByName("fi")->AsDate = IncDay(MC1->Date,0);
	  QueryMenu->ParamByName("ff")->AsDate = IncDay(MC1->Date,5);
	  QueryMenu->Open();

	  QueryMenu->First();

	  TStrings *Lista = new TStringList();

	  while(!QueryMenu->Eof)
	  {
			if(QueryMenu->FieldByName("refComida1")->AsString != "1")
			   Lista->Add(QueryMenu->FieldByName("refComida1")->AsString);
			if(QueryMenu->FieldByName("refComida2")->AsString != "1")
			   Lista->Add(QueryMenu->FieldByName("refComida2")->AsString);
			if(QueryMenu->FieldByName("refComida3")->AsString != "1")
			   Lista->Add(QueryMenu->FieldByName("refComida3")->AsString);
			if(QueryMenu->FieldByName("refComida4")->AsString != "1")
			   Lista->Add(QueryMenu->FieldByName("refComida4")->AsString);
			if(QueryMenu->FieldByName("refComida5")->AsString != "1")
			   Lista->Add(QueryMenu->FieldByName("refComida5")->AsString);
			if(QueryMenu->FieldByName("refComida6")->AsString != "1")
			   Lista->Add(QueryMenu->FieldByName("refComida6")->AsString);
			if(QueryMenu->FieldByName("refComida7")->AsString != "1")
			   Lista->Add(QueryMenu->FieldByName("refComida7")->AsString);
			if(QueryMenu->FieldByName("refComida8")->AsString != "1")
			   Lista->Add(QueryMenu->FieldByName("refComida8")->AsString);

			QueryMenu->Next();
      }
	  bool duplicado = false;
	  int i, j;
	  for(i=0;i<Lista->Count-1;i++)
		 for(j=i+1;j<Lista->Count;j++)
			if(Lista->Strings[i] == Lista->Strings[j])
			{
			   duplicado = true;
			   i = Lista->Count;
			   j = i;
			}


	  delete Lista;

	  if(duplicado)
		 return true;
	  else
		 return false;

}
//--------------------------------------------------------------------------




void __fastcall TfMenuSemanal::Button16Click(TObject *Sender)
{
   fComidasExcluidas->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button17Click(TObject *Sender)
{
   Memo2->Clear();
   for(int w = 0; w < 6; w++)
   {
		QueryAux->Close();
		QueryAux->SQL->Clear();
		String q;
		q = "SELECT *, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida1 LIMIT 1) AS c1, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida1 LIMIT 1) AS cat1, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida2 LIMIT 1) AS c2, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida2 LIMIT 1) AS cat2, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida3 LIMIT 1) AS c3, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida3 LIMIT 1) AS cat3, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida4 LIMIT 1) AS c4, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida4 LIMIT 1) AS cat4, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida5 LIMIT 1) AS c5, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida5 LIMIT 1) AS cat5, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida6 LIMIT 1) AS c6, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida6 LIMIT 1) AS cat6, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida7 LIMIT 1) AS c7, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida7 LIMIT 1) AS cat7, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida8 LIMIT 1) AS c8, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida8 LIMIT 1) AS cat8 "
		   "FROM menudeldia WHERE fecha = :fecha LIMIT 1";

		QueryAux->SQL->Add(q);
		QueryAux->ParamByName("fecha")->AsDate = IncDay(StartOfTheWeek(MC1->Date), w);
		QueryAux->Open();


		if(QueryAux->IsEmpty() || QueryAux->FieldByName("refComida1")->AsInteger <= 1 || QueryAux->FieldByName("refComida7")->AsInteger <= 1)
		{
		  Memo2->Lines->Add("*Menú del día " + FormatDateTime("dddd dd/mm/yyyy", QueryAux->FieldByName("fecha")->AsDateTime) + "*");
		  Memo2->Lines->Add("");
		  Memo2->Lines->Add("	CERRADO");
		}
		else
		{
			int catV, catN;
			String rc, cc, c;
			catV = 1;
			catN = 1;

			Memo2->Lines->Add("*Menú del día " + FormatDateTime("dddd dd/mm/yyyy", QueryAux->FieldByName("fecha")->AsDateTime) + "*");
			Memo2->Lines->Add("");
			Memo2->Lines->Add("*Plato principal:*");
			Memo2->Lines->Add("  1 - " + QueryAux->FieldByName("c1")->AsString);

			int i = 2;
			int p = 2;
			while(i < 7)
			{
			  rc = "refComida" + IntToStr(i);
			  cc = "cat" + IntToStr(i);
			  c = "c" + IntToStr(i);
			  catN = QueryAux->FieldByName(cc)->AsInteger;

			  if(QueryAux->FieldByName(rc)->AsInteger != 2431  && QueryAux->FieldByName(rc)->AsInteger != 2434  && QueryAux->FieldByName(rc)->AsInteger != 2664)   //bolognesa o estofado
			  {
				 if(QueryAux->FieldByName(rc)->AsInteger > 1)
				 {
					if(catN > catV)
					{
					   if(w != 3)
					   {
						  Memo2->Lines->Add("");
						  Memo2->Lines->Add("*Guarnición:*");
					   }
					   catV = catN;
					}
					Memo2->Lines->Add("  " + IntToStr(p) + " - " + QueryAux->FieldByName(c)->AsString);
					p++;
				 }
				 else
				 {
					i = 10;    //sale del while
				 }
			  }
			  i++;
			}

			Memo2->Lines->Add("");
			Memo2->Lines->Add("*Complemento:*");

			i = 7;
			c = "c" + IntToStr(i);
			Memo2->Lines->Add("  " + IntToStr(p) + " - " + QueryAux->FieldByName(c)->AsString);
			p++;
			i = 8;
			c = "c" + IntToStr(i);
			Memo2->Lines->Add("  " + IntToStr(p) + " - " + QueryAux->FieldByName(c)->AsString);
		}
		Memo2->Lines->Add("");
		Memo2->Lines->Add("");
		Memo2->Lines->Add("");
   }

   Memo2->Lines->Add("_Si no desea recibir estos mensajes avísenos y será quitado inmediatamente de esta lista._");
   Memo2->Lines->Add("_El Sembrador - Viandas saludables_");

   QueryAux->Close();

   Memo2->SelectAll();
   Memo2->CopyToClipboard();
   Application->MessageBox(L"El menú fue copiado correctamente al portapapeles. Puede pegarlo donde prefiera",L"Menú copiado",MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button18Click(TObject *Sender)
{
   Button18->Enabled = false;

   Lista = new TStringList();
   Memo2->Clear();
   Lista->Clear();

   String linea;

   for(int w = 0; w < 6; w++)
   {
		QueryAux->Close();
		QueryAux->SQL->Clear();
		String q;
		q = "SELECT *, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida1 LIMIT 1) AS c1, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida1 LIMIT 1) AS cat1, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida2 LIMIT 1) AS c2, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida2 LIMIT 1) AS cat2, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida3 LIMIT 1) AS c3, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida3 LIMIT 1) AS cat3, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida4 LIMIT 1) AS c4, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida4 LIMIT 1) AS cat4, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida5 LIMIT 1) AS c5, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida5 LIMIT 1) AS cat5, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida6 LIMIT 1) AS c6, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida6 LIMIT 1) AS cat6, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida7 LIMIT 1) AS c7, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida7 LIMIT 1) AS cat7, "
		   "(SELECT nombre FROM comidas WHERE idComida = refComida8 LIMIT 1) AS c8, "
		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida8 LIMIT 1) AS cat8 "
		   "FROM menudeldia WHERE fecha = :fecha LIMIT 1";

		QueryAux->SQL->Add(q);
		QueryAux->ParamByName("fecha")->AsDate = IncDay(StartOfTheWeek(MC1->Date), w);
		QueryAux->Open();


		linea = "";

		if(QueryAux->IsEmpty() || QueryAux->FieldByName("refComida1")->AsInteger <= 1 || QueryAux->FieldByName("refComida7")->AsInteger <= 1)
		{
		  Lista->Add("*Menú del día " + FormatDateTime("dddd dd/mm/yyyy", QueryAux->FieldByName("fecha")->AsDateTime) + "*");
		  Lista->Add("");
		  Lista->Add("	CERRADO");
		}
		else
		{
			int catV, catN;
			String rc, cc, c;
			catV = 1;
			catN = 1;

			Lista->Add("*Menú del día " + FormatDateTime("dddd dd/mm/yyyy", QueryAux->FieldByName("fecha")->AsDateTime) + "*");
			Lista->Add("");
			Lista->Add("*Plato principal:*");
			//Lista->Add(QueryAux->FieldByName("c1")->AsString);
			linea = QueryAux->FieldByName("c1")->AsString;
			int i = 2;
			int p = 2;
			while(i < 7)
			{
			  rc = "refComida" + IntToStr(i);
			  cc = "cat" + IntToStr(i);
			  c = "c" + IntToStr(i);
			  catN = QueryAux->FieldByName(cc)->AsInteger;

			  if(QueryAux->FieldByName(rc)->AsInteger != 2431  && QueryAux->FieldByName(rc)->AsInteger != 2434  && QueryAux->FieldByName(rc)->AsInteger != 2664)   //bolognesa o estofado
			  {
				 if(QueryAux->FieldByName(rc)->AsInteger > 1)
				 {
					if(catN > catV)
					{
					   Lista->Add(linea);
					   linea = "";
					   Lista->Add("");
					   Lista->Add("*Guarnición:*");
					   catV = catN;
					}
					if(linea != "")
					{
					   linea = linea + "\n" + QueryAux->FieldByName(c)->AsString;
					}
					else
					   linea = QueryAux->FieldByName(c)->AsString;

					p++;
				 }
				 else
				 {
					i = 10;    //sale del while
				 }
			  }
			  i++;
			}

			Lista->Add(linea);
			linea = "";
			Lista->Add("");
			Lista->Add("*Complemento:*");

			i = 7;
			c = "c" + IntToStr(i);
			if(linea != "")
			{
			   linea = linea + "\n" + QueryAux->FieldByName(c)->AsString;
			}
			else
			   linea = QueryAux->FieldByName(c)->AsString;
			p++;
			i = 8;
			c = "c" + IntToStr(i);
			if(linea != "")
			{
			   linea = linea + "\n" + QueryAux->FieldByName(c)->AsString;
			}
			else
			   linea = QueryAux->FieldByName(c)->AsString;

			Lista->Add(linea);
		}

		Lista->Add("");
		Lista->Add("");
		Lista->Add("");
   }


	 Memo2->Clear();
	 Memo2->Text = Lista->Text;
	 indFile = 0;
	 Timer1->Enabled = true;


}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Timer1Timer(TObject *Sender)
{
   String a;

   if(indFile == Lista->Count - 2)
      a = "";

   if(indFile <= Lista->Count)
	  a = Lista->Strings[indFile];

   while(a != "*Plato principal:*" && a != "*Guarnición:*" && a != "*Complemento:*")
   {
	  indFile++;

	  if(indFile >= Lista->Count)
	  {
		 break;
	  }

	  a = Lista->Strings[indFile];
   }

   if(indFile < Lista->Count)
   {
	  TClipboard *cb;
	  cb = new TClipboard();
	  cb->AsText = Lista->Strings[indFile + 1];
	  delete cb;
	  Beep(2000, 150);
   }
   else
   {
	  Timer1->Enabled = false;
	  delete Lista;

	  for(int i = 0; i < 3; i++)
	  {
		 Beep(2500, 100);
		 Sleep(100);
      }
	  Button18->Enabled = true;
   }

   indFile++;

}
//---------------------------------------------------------------------------

void __fastcall TfMenuSemanal::Button19Click(TObject *Sender)
{
   if(Timer1->Enabled)
   {
	  Timer1->Enabled = false;
	  Button18->Enabled = true;
	  delete Lista;
   }
}
//---------------------------------------------------------------------------


void __fastcall TfMenuSemanal::Button20Click(TObject *Sender)
{
//
//	  Lista = new TStringList();
//   Memo2->Clear();
//   Lista->Clear();
//
//   String linea;
//
//   for(int w = 0; w < 1; w++)
//   {
//		QueryAux->Close();
//		QueryAux->SQL->Clear();
//		String q;
//		q = "SELECT *, "
//		   "(SELECT nombre FROM comidas WHERE idComida = refComida1 LIMIT 1) AS c1, "
//		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida1 LIMIT 1) AS cat1, "
//		   "(SELECT nombre FROM comidas WHERE idComida = refComida2 LIMIT 1) AS c2, "
//		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida2 LIMIT 1) AS cat2, "
//		   "(SELECT nombre FROM comidas WHERE idComida = refComida3 LIMIT 1) AS c3, "
//		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida3 LIMIT 1) AS cat3, "
//		   "(SELECT nombre FROM comidas WHERE idComida = refComida4 LIMIT 1) AS c4, "
//		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida4 LIMIT 1) AS cat4, "
//		   "(SELECT nombre FROM comidas WHERE idComida = refComida5 LIMIT 1) AS c5, "
//		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida5 LIMIT 1) AS cat5, "
//		   "(SELECT nombre FROM comidas WHERE idComida = refComida6 LIMIT 1) AS c6, "
//		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida6 LIMIT 1) AS cat6, "
//		   "(SELECT nombre FROM comidas WHERE idComida = refComida7 LIMIT 1) AS c7, "
//		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida7 LIMIT 1) AS cat7, "
//		   "(SELECT nombre FROM comidas WHERE idComida = refComida8 LIMIT 1) AS c8, "
//		   "(SELECT refCategoriaComida FROM comidas WHERE idComida = refComida8 LIMIT 1) AS cat8 "
//		   "FROM menudeldia WHERE fecha = :fecha LIMIT 1";
//
//		QueryAux->SQL->Add(q);
//		QueryAux->ParamByName("fecha")->AsDate = IncDay(StartOfTheWeek(MC1->Date), w);
//		QueryAux->Open();
//
//
//
//
//
//
//
//
//	   RichEdit1->Lines->LoadFromFile("rf.rtf");

//	   int n;
//	   TSearchTypes mySearchTypes = TSearchTypes();
//
//	   String p, c;
//	   for(int i = 1; i <= 3; i++)
//	   {
//		   p = "PP" + IntToStr(i);
//		   n = RichEdit1->FindTextW(p, 0, RichEdit1->Text.Length(), mySearchTypes);
//		   if(n > 0)
//		   {
//			   RichEdit1->SelStart = n;
//			   RichEdit1->SelLength = 3;
//			   c = "c" + IntToStr(i);
//			   if(QueryAux->FieldByName(c)->AsString != "")
//				  RichEdit1->SetSelTextBuf(QueryAux->FieldByName(c)->AsString.w_str());
//			   else
//				  RichEdit1->Lines->Delete(3);
//		   }
//	   }
//	   for(int i = 1; i <= 3; i++)
//	   {
//		   p = "G" + IntToStr(i);
//		   n = RichEdit1->FindTextW(p, 0, RichEdit1->Text.Length(), mySearchTypes);
//		   if(n > 0)
//		   {
//			   RichEdit1->SelStart = n;
//			   RichEdit1->SelLength = 3;
//			   c = "c" + IntToStr(i+3);
//			   if(QueryAux->FieldByName(c)->AsString != "")
//				  RichEdit1->SetSelTextBuf(QueryAux->FieldByName(c)->AsString.w_str());
//
//		   }
//	   }
//	   for(int i = 1; i <= 2; i++)
//	   {
//		   p = "C" + IntToStr(i);
//		   n = RichEdit1->FindTextW(p, 0, RichEdit1->Text.Length(), mySearchTypes);
//		   if(n > 0)
//		   {
//			   RichEdit1->SelStart = n;
//			   RichEdit1->SelLength = 3;
//			   c = "c" + IntToStr(i+6);
//			   if(QueryAux->FieldByName(c)->AsString != "")
//				  RichEdit1->SetSelTextBuf(QueryAux->FieldByName(c)->AsString.w_str());
//
//		   }
//	   }

//	   TfrxRichView * menu;
//	   menu = dynamic_cast <TfrxRichView *> (fMenuSemanal->frx_contenido_lunes->FindObject("Rich1"));
//
//	   TMemoryStream *stream = new TMemoryStream();
//	   RichEdit1->Lines->SaveToStream(stream);
//	   menu->LoadFromStream(stream);
//	   delete stream;
//
//
//   frx_contenido_lunes->PrepareReport(true);
//   frx_contenido_lunes->Export(frxPNGExport1);
//
//   delete menu;
//   QueryAux->Close();
//
//					  }
}
//---------------------------------------------------------------------------



