//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFrame4.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrame4 *Frame4;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TFrame4::TFrame4(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------

void TFrame4::restablecerFrame(void)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;

   idSeleccionado = 0;
   ClientDataSet1->Active = false;
   Edit1->Clear();
   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);

   Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void TFrame4::cerrarFrame(void)
{
   ClientDataSet1->Active = false;
   Query1->Close();

   SQLConnection1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFrame4::Edit1Change(TObject *Sender)
{
   if((Edit1->Text != "" && Edit1->Text.Length() >= 2) || Sender == Label1)
   {
	  ClientDataSet1->Active = false;

	  String q;
//	  q = "SELECT idComida, nombre, codigo, descripcion, dirImagen, "
//		  "(SELECT descripcion FROM categoriacomidas WHERE refCategoriaComida = idCategoriaComida LIMIT 1) AS categoria "
//		  "FROM comidas WHERE (idComida > 1 AND (UPPER(nombre) LIKE :v OR UPPER(codigo) LIKE :v)) ORDER BY nombre LIMIT 10";

	  q = "SELECT idComida, nombre, codigo, IF(UPPER(nombre) LIKE :v1, 0, 1) AS esIgual, "           // (CHAR_LENGTH(nombre) - CHAR_LENGTH(:v1)) AS difLon,
		  "(SELECT descripcion FROM categoriacomidas WHERE refCategoriaComida = idCategoriaComida LIMIT 1) AS categoria "
		  "FROM comidas WHERE (idComida > 1 AND (UPPER(nombre) LIKE UPPER(:v) OR UPPER(codigo) LIKE UPPER(:v))) ORDER BY esIgual, nombre LIMIT 50";    //ABS(difLon),


	  String buscar = Edit1->Text;
	  String buscarAux = buscar + "%";
	  buscarAux = buscarAux.UpperCase();
	  int pos;
	  while(buscar.Pos(" "))
	  {
		  pos = buscar.Pos(" ");
		  buscar = buscar.Delete(pos, 1);
		  buscar = buscar.Insert("%", pos);
	  }
	  buscar = "%" + buscar + "%";

	  Query1->Close();
	  Query1->SQL->Clear();
	  Query1->SQL->Add(q);
	  Query1->ParamByName("v")->AsString = buscar;
	  Query1->ParamByName("v1")->AsString = buscarAux;
	  Query1->Open();

	  ClientDataSet1->Active = true;
   }
   else
   {
	  ClientDataSet1->Active = false;
	  Query1->Close();
   }
   ShowScrollBar(DBGrid1->Handle, SB_VERT, true);
}
//---------------------------------------------------------------------------
void __fastcall TFrame4::DBGrid1DblClick(TObject *Sender)
{
   if(!ClientDataSet1->IsEmpty())
	  idSeleccionado = ClientDataSet1->FieldByName("idComida")->AsInteger;
   else
	  idSeleccionado = 0;
}
//---------------------------------------------------------------------------


void __fastcall TFrame4::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
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

void __fastcall TFrame4::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_RETURN)
	  Edit1Change(Label1);
   else if(Key == VK_DOWN)
      DBGrid1->SetFocus();
}
//---------------------------------------------------------------------------


