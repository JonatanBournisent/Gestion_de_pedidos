//---------------------------------------------------------------------------

#ifndef uFacturacionMensualH
#define uFacturacionMensualH
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
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfFacturacionMensual : public TForm
{
__published:	// IDE-managed Components
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *CDS1;
	TDataSource *DataSource1;
	TSQLQuery *QueryAux;
	TIntegerField *CDS1idCliente;
	TWideStringField *CDS1cliente;
	TDBGrid *DBGrid1;
	TPopupMenu *PopupMenu1;
	TMenuItem *Agregaruncliente1;
	TMenuItem *Quitaresteclientedelalista1;
	TMenuItem *Iraemitircomprobante1;
	TMenuItem *Verdetalledecuenta1;
	TMonthCalendar *MC;
	TLabel *Label1;
	TButton *Button1;
	TMenuItem *EmitirCompMonotributo1;
	TWideStringField *CDS1tipo;
	TSQLQuery *QueryUpdate;
	TLabel *Label2;
	TLabel *Label3;
	TButton *Button2;
	TMemo *Memo1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Agregaruncliente1Click(TObject *Sender);
	void __fastcall Quitaresteclientedelalista1Click(TObject *Sender);
	void __fastcall Verdetalledecuenta1Click(TObject *Sender);
	void __fastcall Iraemitircomprobante1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EmitirCompMonotributo1Click(TObject *Sender);
	void __fastcall CDS1tipoChange(TField *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall MCClick(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfFacturacionMensual(TComponent* Owner);
	String _directorioGuararFacturas;


	void buscarDatos(String orden);
};
//---------------------------------------------------------------------------
extern PACKAGE TfFacturacionMensual *fFacturacionMensual;
//---------------------------------------------------------------------------
#endif
