//---------------------------------------------------------------------------

#ifndef uRepartosH
#define uRepartosH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TfRepartos : public TForm
{
__published:	// IDE-managed Components
	TSQLConnection *SQLConnection1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *ClientDataSet1;
	TDataSource *DataSource1;
	TSQLQuery *Query1;
	TDBGrid *DBGrid1;
	TButton *Button1;
	TRadioGroup *RG1;
	TSQLQuery *QueryAux;
	TComboBox *ComboBox1;
	TTimer *Timer1;
	TTimer *Timer2;
	TButton *Button6;
	TButton *Button7;
	TGroupBox *GroupBox1;
	TButton *Button2;
	TButton *Button3;
	TComboBox *ComboBox2;
	TButton *Button4;
	TButton *Button5;
	TButton *Button8;
	TPopupMenu *PopupMenu1;
	TMenuItem *Quitardeestaplanilla1;
	TMenuItem *ransferira1;
	TMenuItem *Item11;
	TMenuItem *Item21;
	TMenuItem *Item31;
	TMenuItem *Item41;
	TMenuItem *Item51;
	TMenuItem *Item61;
	TMenuItem *Item71;
	TMenuItem *Item81;
	TMenuItem *Item91;
	TMenuItem *Item101;
	TMenuItem *Item111;
	TMenuItem *Item121;
	TMenuItem *Item131;
	TMenuItem *Item141;
	TMenuItem *Item151;
	TMenuItem *Desplazarhaciaarriba1;
	TMenuItem *Desplazarhaciaabajo1;
	TMenuItem *Verestadodecuentacorriente1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall RG1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Button2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall Button3MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Button3MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Quitardeestaplanilla1Click(TObject *Sender);
	void __fastcall Item11Click(TObject *Sender);
	void __fastcall Item21Click(TObject *Sender);
	void __fastcall Item31Click(TObject *Sender);
	void __fastcall Item41Click(TObject *Sender);
	void __fastcall Item51Click(TObject *Sender);
	void __fastcall Item61Click(TObject *Sender);
	void __fastcall Item71Click(TObject *Sender);
	void __fastcall Item81Click(TObject *Sender);
	void __fastcall Item91Click(TObject *Sender);
	void __fastcall Item101Click(TObject *Sender);
	void __fastcall Item111Click(TObject *Sender);
	void __fastcall Item121Click(TObject *Sender);
	void __fastcall Item131Click(TObject *Sender);
	void __fastcall Item141Click(TObject *Sender);
	void __fastcall Item151Click(TObject *Sender);
	void __fastcall Desplazarhaciaarriba1Click(TObject *Sender);
	void __fastcall Desplazarhaciaabajo1Click(TObject *Sender);
	void __fastcall Verestadodecuentacorriente1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfRepartos(TComponent* Owner);

	void actualizarPlanillas(int idRepartidor);
	int maximaPosicion(int refRepartidor, int esSabado);
	int getIdRepartidor(String nombre);
	void transferir(String planilla);
	String ultimoNumeroAgregado;
	int idClienteABuscar;
	String planillaSeleccionada;
};
//---------------------------------------------------------------------------
extern PACKAGE TfRepartos *fRepartos;
//---------------------------------------------------------------------------
#endif
