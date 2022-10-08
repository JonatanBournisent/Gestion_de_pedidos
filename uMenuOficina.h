//---------------------------------------------------------------------------

#ifndef uMenuOficinaH
#define uMenuOficinaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Data.DB.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "uFrameMenuOficina.h"
//---------------------------------------------------------------------------
class TfMenuOficina : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TMonthCalendar *MC1;
	TScrollBox *ScrollBox1;
	TframeMenuOficina *frameMenuOficina1;
	TframeMenuOficina *frameMenuOficina2;
	TframeMenuOficina *frameMenuOficina3;
	TframeMenuOficina *frameMenuOficina4;
	TframeMenuOficina *frameMenuOficina5;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);


private:	// User declarations
public:		// User declarations
	__fastcall TfMenuOficina(TComponent* Owner);


    void mostrarMenu(void);

};
//---------------------------------------------------------------------------
extern PACKAGE TfMenuOficina *fMenuOficina;
//---------------------------------------------------------------------------
#endif
