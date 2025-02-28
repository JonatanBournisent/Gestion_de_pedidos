//---------------------------------------------------------------------------

#ifndef uFrame1H
#define uFrame1H
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
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Mask.hpp>
//---------------------------------------------------------------------------
class TFrame1 : public TFrame
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TDBEdit *DBEdNombre;
	TDBEdit *DBEdApellido;
	TDBEdit *DBEdCalle;
	TDBEdit *DBEdNumero;
	TDBLookupComboBox *DBFrecPago;
	TDBLookupComboBox *DBListaPrecio;
	TDBEdit *DBEdBonificacion;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *ClientDataSet1;
	TDataSource *DataSource1;
	TSQLTable *SQLTable1;
	TDataSetProvider *DataSetProvider2;
	TClientDataSet *ClientDataSet2;
	TDataSource *DataSource2;
	TDataSetProvider *DataSetProvider3;
	TClientDataSet *ClientDataSet3;
	TDataSource *DataSource3;
	TSQLQuery *Query2;
	TDBGrid *DBGrid1;
	TDataSetProvider *DataSetProvider4;
	TClientDataSet *ClientDataSet4;
	TDataSource *DataSource4;
	TSQLQuery *Query3;
	TLabel *Label9;
	TDBLookupComboBox *DBDiaPago;
	TDataSetProvider *DataSetProvider5;
	TClientDataSet *ClientDataSet5;
	TDataSource *DataSource5;
	TSQLQuery *Query4;
	TLabel *Label10;
	TSQLQuery *QueryUpdate;
	TDBCheckBox *DBCheckBox1;
	TWideStringField *ClientDataSet1calle;
	TWideStringField *ClientDataSet1numero;
	TWideStringField *ClientDataSet1nombre;
	TWideStringField *ClientDataSet1apellido;
	TIntegerField *ClientDataSet1refFrecuenciaPago;
	TIntegerField *ClientDataSet1refDiaPago;
	TIntegerField *ClientDataSet1refListaPrecio;
	TIntegerField *ClientDataSet1idCliente;
	TIntegerField *ClientDataSet1esVisible;
	TFMTBCDField *ClientDataSet1saldo;
	TByteField *ClientDataSet1imprimirDetalle;
	TFMTBCDField *ClientDataSet1bonificacion;
	TDBEdit *DBRazonSocial;
	TLabel *Label8;
	TWideStringField *ClientDataSet1CUIT;
	TWideStringField *ClientDataSet1razonSocial;
	TWideStringField *ClientDataSet1domicilioFiscal;
	TDBEdit *DBDomicilioFiscal;
	TLabel *Label11;
	TDBEdit *DBCUIT;
	TLabel *Label12;
	TComboBox *CBCondicionFrenteIVA;
	TLabel *Label13;
	TIntegerField *ClientDataSet1refCondicionFrenteIVA;
	TFMTBCDField *ClientDataSet1acumuladoGlobal;
	TFMTBCDField *ClientDataSet1acumuladoParcial;
	TDBCheckBox *DBCheckBox2;
	TByteField *ClientDataSet1generarFactura;
	TSQLQuery *QueryAux;
	TWideStringField *ClientDataSet1tipo;
	TDBEdit *DBEdBanco1;
	TDBEdit *DBEdBanco2;
	TDBEdit *DBEdBanco3;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TWideStringField *ClientDataSet1nombreBanco1;
	TWideStringField *ClientDataSet1nombreBanco2;
	TWideStringField *ClientDataSet1nombreBanco3;
	TComboBox *CBFacturar;
	TLabel *Label17;
	TComboBox *CBmp;
	TLabel *Label18;
	TWideStringField *ClientDataSet1medioPagoDefecto;
	TDBCheckBox *DBCheckBox3;
	TWideStringField *ClientDataSet1pagoAdelantado;
	TDBCheckBox *DBCheckBox5;
	TWideStringField *ClientDataSet1menuImpreso;
	TLabel *Label19;
	void __fastcall DBEdNombreChange(TObject *Sender);
	void __fastcall DBEdApellidoChange(TObject *Sender);
	void __fastcall DBEdCalleChange(TObject *Sender);
	void __fastcall DBEdNumeroChange(TObject *Sender);
	void __fastcall DBEdBonificacionKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall DBCUITKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBCUITKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall DBCUITKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBCUITExit(TObject *Sender);
	void __fastcall CBCondicionFrenteIVAChange(TObject *Sender);
	void __fastcall CBFacturarChange(TObject *Sender);
	void __fastcall CBmpChange(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TFrame1(TComponent* Owner);

	void restablecerFrame(void);
	void cerrarFrame(void);
	bool guardar(void);
	void cancelar(void);
	bool modificoNombAp;
	bool modificando;
	int llamador;
	int id;
	bool cuitOK;
	bool blockDBEdit;
	bool conDNI;
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame1 *Frame1;
//---------------------------------------------------------------------------
#endif
