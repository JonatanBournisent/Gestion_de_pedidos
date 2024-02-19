//---------------------------------------------------------------------------

#ifndef uGraficos2H
#define uGraficos2H
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
class TfGraficos2 : public TForm
{
__published:	// IDE-managed Components
	TDBChart *DBChart1;
	TBarSeries *Series2;
	TLineSeries *Series1;
	TClientDataSet *CDS2;
	TFMTBCDField *CDS2yData;
	TSQLTimeStampField *CDS2xData;
	TDataSetProvider *DataSetProvider2;
	TSQLQuery *Query2;
	TSQLConnection *SQLConnection1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfGraficos2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfGraficos2 *fGraficos2;
//---------------------------------------------------------------------------
#endif
