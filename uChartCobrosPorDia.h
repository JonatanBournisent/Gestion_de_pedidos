//---------------------------------------------------------------------------

#ifndef uChartCobrosPorDiaH
#define uChartCobrosPorDiaH
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
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.DBChart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
//---------------------------------------------------------------------------
class TfChartCobrosPorDia : public TForm
{
__published:	// IDE-managed Components
	TClientDataSet *CDS2;
	TLargeintField *CDS2diaDelMes;
	TDataSetProvider *DataSetProvider2;
	TSQLQuery *Query2;
	TDBChart *DBChart1;
	TBarSeries *Series2;
	TSQLConnection *SQLConnection1;
	TFMTBCDField *CDS2pagoRecibido;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TfChartCobrosPorDia(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfChartCobrosPorDia *fChartCobrosPorDia;
//---------------------------------------------------------------------------
#endif
