//---------------------------------------------------------------------------

#ifndef uDatosH
#define uDatosH
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
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeeData.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.DBChart.hpp>
#include <VCLTee.TeeDBCrossTab.hpp>
#include <Vcl.Tabs.hpp>
#include <Vcl.Samples.Spin.hpp>
//---------------------------------------------------------------------------
class TfDatos : public TForm
{
__published:	// IDE-managed Components
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *CDS1;
	TDataSource *DataSource1;
	TSQLQuery *QueryAux;
	TButton *Button1;
	TDBGrid *DBGrid1;
	TMonthCalendar *MC;
	TWideStringField *CDS1repartidor;
	TFMTBCDField *CDS1cobro;
	TFMTBCDField *CDS1montoVentas;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TShape *Shape1;
	TShape *Shape2;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TSpinEdit *SpinEdit1;
	TLabel *Label8;
	TPanel *Panel1;
	TSQLQuery *Query2;
	TDataSetProvider *DataSetProvider2;
	TClientDataSet *CDS2;
	TDataSource *DataSource2;
	TDBGrid *DBGrid2;
	TWideStringField *CDS2cliente;
	TFMTBCDField *CDS2cantViandas;
	TButton *Button6;
	TButton *Button7;
	TShape *Shape3;
	TLargeintField *CDS1cantDomicilios;
	TFMTBCDField *CDS1cantViandas;
	TLabel *Label9;
	TButton *Button8;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfDatos(TComponent* Owner);

	void generarGrafico(String query, String lTitulo, String bTitulo, String titulo, String xDispFormat);
};
//---------------------------------------------------------------------------
extern PACKAGE TfDatos *fDatos;
//---------------------------------------------------------------------------
#endif
