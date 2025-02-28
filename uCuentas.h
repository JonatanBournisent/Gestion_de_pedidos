//---------------------------------------------------------------------------

#ifndef uCuentasH
#define uCuentasH
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
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TfCuentas : public TForm
{
__published:	// IDE-managed Components
	TDataSource *DataSource1;
	TClientDataSet *CDS;
	TDataSetProvider *DataSetProvider1;
	TSQLQuery *Query1;
	TSQLConnection *SQLConnection1;
	TDBGrid *DBGrid1;
	TSQLQuery *QueryAux;
	TMonthCalendar *MC;
	TButton *Button2;
	TButton *Button3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TDateField *CDSfecha;
	TFMTBCDField *CDSunidades;
	TFMTBCDField *CDSpagoRealizado;
	TFMTBCDField *CDSvalorUnidad;
	TBevel *Bevel1;
	TButton *Button1;
	TIntegerField *CDSidCuenta;
	TSQLQuery *QueryUpdate;
	TCheckBox *CheckBox1;
	TPopupMenu *PopupMenu1;
	TMenuItem *Mostrarestasemana1;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TWideStringField *CDSobs;
	TWideStringField *CDSrep;
	TButton *Button7;
	TButton *Button8;
	TPopupMenu *PopupMenu2;
	TMenuItem *Verpedidosdeesteda1;
	TTimer *Timer1;
	TButton *Button10;
	TPanel *Panel1;
	TLabel *Label5;
	TEdit *Edit1;
	TButton *Button9;
	TSQLQuery *Query2;
	TDataSetProvider *DataSetProvider2;
	TClientDataSet *CDS2;
	TDataSource *DataSource2;
	TDBGrid *DBGrid2;
	TIntegerField *CDS2refCliente;
	TWideStringField *CDS2cliente;
	TLabel *Label6;
	TButton *Button11;
	TOpenDialog *OD1;
	TDateField *CDSfechaIngresoPago;
	TWideStringField *CDSmedioDePago;
	TMenuItem *Asignarpagoseleccionado1;
	TMenuItem *Quitarinformaciondepago1;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall MCClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CDSunidadesChange(TField *Sender);
	void __fastcall CDSpagoRealizadoChange(TField *Sender);
	void __fastcall CDSvalorUnidadChange(TField *Sender);
	void __fastcall CDSobsChange(TField *Sender);
	void __fastcall DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGrid1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Mostrarestasemana1Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Verpedidosdeesteda1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall DBGrid2DblClick(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall CDSfechaIngresoPagoGetText(TField *Sender, UnicodeString &Text,
          bool DisplayText);
	void __fastcall CDSmedioDePagoGetText(TField *Sender, UnicodeString &Text, bool DisplayText);
	void __fastcall CDSmedioDePagoChange(TField *Sender);
	void __fastcall CDSfechaIngresoPagoChange(TField *Sender);
	void __fastcall Asignarpagoseleccionado1Click(TObject *Sender);
	void __fastcall Quitarinformaciondepago1Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TfCuentas(TComponent* Owner);


	int idCliente;
	int frecPago;

	void calcular(bool parcial);
};
//---------------------------------------------------------------------------
extern PACKAGE TfCuentas *fCuentas;
//---------------------------------------------------------------------------
#endif
