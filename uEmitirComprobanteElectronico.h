//---------------------------------------------------------------------------

#ifndef uEmitirComprobanteElectronicoH
#define uEmitirComprobanteElectronicoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "frxClass.hpp"
#include "frxExportPDF.hpp"
#include <Data.DB.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Vcl.ComCtrls.hpp>
#include "frxBarcode.hpp"
#include "frxBarcode2D.hpp"
#include "frxDBSet.hpp"
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include "frxExportBaseDialog.hpp"
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
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TfEmitirComprobanteElectronico : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label2;
	TLabel *Label1;
	TButton *Button10;
	TMonthCalendar *MC;
	TCheckBox *chbFactA4;
	TEdit *Edit2;
	TButton *Button1;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TfrxReport *frxReport2;
	TfrxPDFExport *frxPDFExport1;
	TfrxReport *frxReport3;
	TfrxDBDataset *frxDBDataset3;
	TSQLQuery *Query3;
	TDataSetProvider *DataSetProvider3;
	TClientDataSet *CDS3;
	TWideStringField *CDS3domicilio;
	TWideStringField *CDS3razonSocial;
	TWideStringField *CDS3condFrenteIVA;
	TWideStringField *CDS3cuit;
	TDataSource *DataSource3;
	TSQLQuery *QueryAux;
	TfrxReport *frxReport1;
	TLabel *lbSubtotal;
	TLabel *lbIVA21;
	TLabel *lbTotal;
	TShape *Shape1;
	TShape *Shape2;
	TCheckBox *CheckBox1;
	TSaveDialog *SD1;
	TShape *Shape3;
	TfrxBarCodeObject *frxBarCodeObject1;
	TFDMemTable *FDMemTable1;
	TFMTBCDField *FDMemTable1nroUnidades;
	TWideStringField *FDMemTable1descripcion;
	TFMTBCDField *FDMemTable1precioUnitario;
	TFMTBCDField *FDMemTable1subtotal;
	TDBGrid *DBGrid1;
	TDataSource *DataSource1;
	TfrxDBDataset *frxDBDataset1;
	TMainMenu *MainMenu1;
	TPopupMenu *PopupMenu1;
	TMenuItem *Agregarunitem1;
	TMenuItem *Eliminaresteitem1;
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall chbFactA4Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FDMemTable1BeforePost(TDataSet *DataSet);
	void __fastcall FDMemTable1precioUnitarioChange(TField *Sender);
	void __fastcall FDMemTable1nroUnidadesValidate(TField *Sender);
	void __fastcall FDMemTable1descripcionValidate(TField *Sender);
	void __fastcall FDMemTable1precioUnitarioValidate(TField *Sender);
	void __fastcall FDMemTable1AfterPost(TDataSet *DataSet);
	void __fastcall DBGrid1Exit(TObject *Sender);
	void __fastcall DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Eliminaresteitem1Click(TObject *Sender);
	void __fastcall Agregarunitem1Click(TObject *Sender);
	void __fastcall FDMemTable1AfterDelete(TDataSet *DataSet);



private:	// User declarations
public:		// User declarations
	__fastcall TfEmitirComprobanteElectronico(TComponent* Owner);

	int refCondicionFrenteIVA;
	bool CanPrint;
	int idCliente;
	float valorUnidad;
	float calcular2(void);
	void mostrarCliente(int refCliente);
//	float _subtotal, _totalIVA21, _total;
	bool blockCalcular2;

	bool facturacionBulk;

	String directorioGuararFacturas;
	String nombreArchivoFactura;

	String getPrinter(String tipo);
	bool validatePrinter(String impSel);
	String getDirFacturas(void);

	bool facturacionMensual;
};
//---------------------------------------------------------------------------
extern PACKAGE TfEmitirComprobanteElectronico *fEmitirComprobanteElectronico;
//---------------------------------------------------------------------------
#endif
