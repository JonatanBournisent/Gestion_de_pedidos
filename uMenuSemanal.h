//---------------------------------------------------------------------------

#ifndef uMenuSemanalH
#define uMenuSemanalH
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
#include <Vcl.ExtCtrls.hpp>
#include "frxClass.hpp"
#include "frxExportBaseDialog.hpp"
#include "frxExportImage.hpp"
#include "frxRich.hpp"
//---------------------------------------------------------------------------
class TfMenuSemanal : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TMonthCalendar *MC1;
	TButton *Button7;
	TButton *Button8;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TListBox *ListBox1;
	TCheckBox *CheckBox1;
	TMonthCalendar *MC2;
	TButton *Button9;
	TButton *Button10;
	TListBox *ListBox2;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TSQLQuery *QueryMenu;
	TPanel *Panel1;
	TBevel *Bevel1;
	TButton *Button14;
	TButton *Button15;
	TButton *Button16;
	TButton *Button17;
	TMemo *Memo2;
	TSQLQuery *QueryAux;
	TButton *Button18;
	TTimer *Timer1;
	TButton *Button19;
	TfrxReport *frx_contenido_tapa;
	TButton *Button20;
	TfrxPNGExport *frxPNGExport1;
	TfrxReport *frx_contenido_lunes;
	TfrxRichObject *frxRichObject1;
	TButton *Button21;
	TSQLQuery *QueryComida;
	TSQLQuery *queryMenuWeb;
	TButton *Button22;
	TMemo *Memo1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall MC1Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall ListBox1DrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall MC2Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall ListBox2DrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button19Click(TObject *Sender);
	void __fastcall Button20Click(TObject *Sender);
	void __fastcall Button21Click(TObject *Sender);
	void __fastcall Button22Click(TObject *Sender);



private:	// User declarations
public:		// User declarations
	__fastcall TfMenuSemanal(TComponent* Owner);
	void actualizarMenu(void);
	void actualizarMenuOld(void);
	int iTitulo[6]; // define el indice de la fila del Memo donde estan los titulos.
	int iTitulo2[6];

	int iTituloOld[6]; // define el indice de la fila del Memo donde estan los titulos.
	int iTituloOld2[6];



	String DirMenuMail, DirMenuVenta, DirPlanillaVenta, DirPlanillaFijos, DirPlanillaInstrucciones;
	Variant vMSWord;
	Variant vWDocuments, vWDocument, Range;
	void GenerarMenuMail(String DirPlantilla, String DirDestino);
	void GenerarPlanillaFijos(String DirPlantilla, String DirDestino, int indiceDia);
	void GenerarMenuVenta(String DirPlantilla, String DirDestino);
	void GenerarPlanillaInstrucciones(String DirPlantilla, String DirDestino);
	void GenerarPlanillaVenta(String DirPlantilla, String DirDestino, int indiceDia);

	bool RevisarDuplicado(void);

	int indFile;
	TStringList * Lista;

};
//---------------------------------------------------------------------------
extern PACKAGE TfMenuSemanal *fMenuSemanal;
//---------------------------------------------------------------------------
#endif
