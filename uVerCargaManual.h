//---------------------------------------------------------------------------

#ifndef uVerCargaManualH
#define uVerCargaManualH
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
//---------------------------------------------------------------------------
class TfVerCargaManual : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TDataSource *DataSource3;
	TSQLQuery *QueryCantidad;
	TDataSetProvider *DataSetProvider3;
	TClientDataSet *ClientDataSet3;
	TSQLConnection *SQLConnection1;
	TWideStringField *ClientDataSet3repartidor;
	TWideStringField *ClientDataSet3cliente;
	TIntegerField *ClientDataSet3idCantidad;
	TIntegerField *ClientDataSet3bandGrand;
	TFMTBCDField *ClientDataSet3cantViandas;
	TWideStringField *ClientDataSet3complemento;
	TButton *Button1;
	TMonthCalendar *MC;
	TIntegerField *ClientDataSet3refCliente;
	TIntegerField *ClientDataSet3reparto;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfVerCargaManual(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfVerCargaManual *fVerCargaManual;
//---------------------------------------------------------------------------
#endif
