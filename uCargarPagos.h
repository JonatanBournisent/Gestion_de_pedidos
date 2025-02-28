//---------------------------------------------------------------------------

#ifndef uCargarPagosH
#define uCargarPagosH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TfCargarPagos : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TComboBox *ComboBox1;
	TSQLConnection *SQLConnection1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *CDS;
	TDataSource *DataSource1;
	TSQLQuery *Query1;
	TSQLQuery *QueryAux;
	TButton *Button1;
	TDateTimePicker *DTP;
	TFMTBCDField *CDSpagoRealizado;
	TIntegerField *CDSidCuenta;
	TFMTBCDField *CDSunidades;
	TFMTBCDField *CDSvalorUnidad;
	TWideStringField *CDScalle;
	TWideStringField *CDSnumero;
	TButton *Button2;
	TIntegerField *CDSrefCliente;
	TLargeintField *CDSrefFrecuenciaPago;
	TButton *Button3;
	TSQLQuery *QueryUpdate;
	TPanel *Panel1;
	TMemo *Memo1;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TPanel *Panel2;
	TButton *Button8;
	TMemo *Memo2;
	TLabel *Label1;
	TShape *Shape1;
	TShape *Shape2;
	TShape *Shape3;
	TLabel *Label2;
	TShape *Shape4;
	TButton *Button9;
	TPopupMenu *PopupMenu1;
	TMenuItem *Aadiruncomentario1;
	TFMTBCDField *CDSdeudaEfectivo;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall CDSpagoRealizadoChange(TField *Sender);
	void __fastcall DBGrid1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall DBGrid1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CDSunidadesChange(TField *Sender);
	void __fastcall CDSvalorUnidadChange(TField *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall CDSNewRecord(TDataSet *DataSet);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall DTPChange(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Aadiruncomentario1Click(TObject *Sender);
	void __fastcall Verestadodecuentadelcliente1Click(TObject *Sender);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
private:	// User declarations
public:		// User declarations

	  int idRepartidor;

	  String comaToDot(String str);

	  int existeObs;
	  int idObsCuenta;
	  int esSabado;
      bool mostrado;




	__fastcall TfCargarPagos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfCargarPagos *fCargarPagos;
//---------------------------------------------------------------------------
#endif
