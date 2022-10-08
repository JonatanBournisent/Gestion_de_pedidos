//---------------------------------------------------------------------------

#ifndef uSospechososH
#define uSospechososH
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
//---------------------------------------------------------------------------
class TfSospechosos : public TForm
{
__published:	// IDE-managed Components
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *CDS;
	TDataSource *DataSource1;
	TDBGrid *DBGrid1;
	TWideStringField *CDSDireccion;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TfSospechosos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfSospechosos *fSospechosos;
//---------------------------------------------------------------------------
#endif
