//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "uMenuOficina.h"
#include "uSeleccionarComida.h"
#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "uFrameMenuOficina"
#pragma resource "*.dfm"
TfMenuOficina *fMenuOficina;

//---------------------------------------------------------------------------
__fastcall TfMenuOficina::TfMenuOficina(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfMenuOficina::FormShow(TObject *Sender)
{
   MC1->MultiSelect = false;
   MC1->Date = Now();
   MC1->MultiSelect = true;

   MC1->Date = StartOfTheWeek(Now());
   MC1->EndDate = IncDay(MC1->Date,5);


   frameMenuOficina1->inicializar(IncDay(StartOfTheWeek(MC1->Date), 0));
   frameMenuOficina2->inicializar(IncDay(StartOfTheWeek(MC1->Date), 1));
   frameMenuOficina3->inicializar(IncDay(StartOfTheWeek(MC1->Date), 2));
   frameMenuOficina4->inicializar(IncDay(StartOfTheWeek(MC1->Date), 3));
	frameMenuOficina5->inicializar(IncDay(StartOfTheWeek(MC1->Date), 4));
	ScrollBox1->VertScrollBar->Position = 0;
}
//---------------------------------------------------------------------------
void TfMenuOficina::mostrarMenu(void)
{
}
//---------------------------------------------------------------------------

void __fastcall TfMenuOficina::Button1Click(TObject *Sender)
{
   MC1->Date = IncDay(MC1->Date,-7);
   MC1->EndDate = IncDay(MC1->Date,5);

   frameMenuOficina1->inicializar(IncDay(StartOfTheWeek(MC1->Date), 0));
   frameMenuOficina2->inicializar(IncDay(StartOfTheWeek(MC1->Date), 1));
   frameMenuOficina3->inicializar(IncDay(StartOfTheWeek(MC1->Date), 2));
   frameMenuOficina4->inicializar(IncDay(StartOfTheWeek(MC1->Date), 3));
   frameMenuOficina5->inicializar(IncDay(StartOfTheWeek(MC1->Date), 4));
}
//---------------------------------------------------------------------------
void __fastcall TfMenuOficina::Button2Click(TObject *Sender)
{
   MC1->Date = IncDay(MC1->Date,7);
   MC1->EndDate = IncDay(MC1->Date,5);

   frameMenuOficina1->inicializar(IncDay(StartOfTheWeek(MC1->Date), 0));
   frameMenuOficina2->inicializar(IncDay(StartOfTheWeek(MC1->Date), 1));
   frameMenuOficina3->inicializar(IncDay(StartOfTheWeek(MC1->Date), 2));
   frameMenuOficina4->inicializar(IncDay(StartOfTheWeek(MC1->Date), 3));
   frameMenuOficina5->inicializar(IncDay(StartOfTheWeek(MC1->Date), 4));
}
//---------------------------------------------------------------------------

void __fastcall TfMenuOficina::FormMouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
   ScrollBox1->VertScrollBar->Position -= 4;
}
//---------------------------------------------------------------------------

void __fastcall TfMenuOficina::FormMouseWheelDown(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
   ScrollBox1->VertScrollBar->Position += 4;
}
//---------------------------------------------------------------------------


void __fastcall TfMenuOficina::FormClose(TObject *Sender, TCloseAction &Action)
{
   frameMenuOficina1->cerrar();
   frameMenuOficina2->cerrar();
   frameMenuOficina3->cerrar();
   frameMenuOficina4->cerrar();
   frameMenuOficina5->cerrar();
}
//---------------------------------------------------------------------------

