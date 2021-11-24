//---------------------------------------------------------------------------

#ifndef uVerComprobantesElectronicosH
#define uVerComprobantesElectronicosH
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
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TfVerComprobantesElectronicos : public TForm
{
__published:	// IDE-managed Components
	TShape *Shape1;
	TLabel *Label1;
	TLabel *Label3;
	TDBGrid *DBGrid1;
	TEdit *Edit1;
	TMonthCalendar *MC1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *CDS1;
	TDataSource *DataSource1;
	TIntegerField *CDS1idComprobanteElectronico;
	TWideStringField *CDS1cliente;
	TWideStringField *CDS1cuitCliente;
	TWideStringField *CDS1cfIVA;
	TDateField *CDS1fecha;
	TWideStringField *CDS1tipoComp;
	TWideStringField *CDS1nroComp;
	TFMTBCDField *CDS1netoGravado;
	TFMTBCDField *CDS1iva21;
	TFMTBCDField *CDS1total;
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall MC1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfVerComprobantesElectronicos(TComponent* Owner);

	bool omitir;
};
//---------------------------------------------------------------------------
extern PACKAGE TfVerComprobantesElectronicos *fVerComprobantesElectronicos;
//---------------------------------------------------------------------------
#endif
