//---------------------------------------------------------------------------

#ifndef uImportarPagosBancosH
#define uImportarPagosBancosH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
//---------------------------------------------------------------------------
class TfImportarPagosBancos : public TForm
{
__published:	// IDE-managed Components
	TFDMemTable *FDMemTable1;
	TDataSource *DataSource1;
	TDateField *FDMemTable1fecha;
	TWideStringField *FDMemTable1cliente;
	TFMTBCDField *FDMemTable1valor;
	TIntegerField *FDMemTable1idCliente;
	TDBGrid *DBGrid1;
	TRadioGroup *RadioGroup1;
	TButton *Button1;
	TSQLConnection *SQLConnection1;
	TSQLQuery *QueryAux;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall DBGrid1KeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TfImportarPagosBancos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfImportarPagosBancos *fImportarPagosBancos;
//---------------------------------------------------------------------------
#endif
