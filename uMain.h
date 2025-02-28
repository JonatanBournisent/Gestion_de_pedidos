//---------------------------------------------------------------------------

#ifndef uMainH
#define uMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.SqlExpr.hpp>
#include <Data.FMTBcd.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Datasnap.Provider.hpp>
#include <Datasnap.DBClient.hpp>
#include "uFrame1.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Menus.hpp>
#include <Soap.WebServExp.hpp>
#include <Soap.WSDLBind.hpp>
#include <Soap.WSDLPub.hpp>
#include <System.TypInfo.hpp>
#include <Xml.XMLSchema.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TfMain : public TForm
{
__published:	// IDE-managed Components
	TButton *Button2;
	TButton *Button1;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button9;
	TButton *Button10;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TButton *Cuentas;
	TButton *Button14;
	TButton *Button8;
	TButton *Button15;
	TTimer *Alarmas;
	TButton *Button16;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *CDS1;
	TDataSource *DataSource1;
	TWideStringField *CDS1cliente;
	TFMTBCDField *CDS1deuda;
	TIntegerField *CDS1idCliente;
	TDBGrid *DBGrid1;
	TSQLQuery *Query2;
	TLabel *Label1;
	TPopupMenu *PopupMenu1;
	TMenuItem *Verestadodecuenta1;
	TMenuItem *Imprimirdetalledecuenta1;
	TButton *Button18;
	TButton *Button17;
	TButton *Button19;
	TButton *Button20;
	TButton *Button21;
	TButton *Button22;
	TMainMenu *MainMenu1;
	TMenuItem *Repartos1;
	TMenuItem *Imprimirplanillas1;
	TMenuItem *Cuentas1;
	TMenuItem *Cargarpagosdeclientes1;
	TMenuItem *Gestionarcuentasdeclientes1;
	TMenuItem *Imprimirdetalles1;
	TMenuItem *Clientes1;
	TMenuItem *Agregaruncliente1;
	TMenuItem *Modificardatosdeclientes1;
	TMenuItem *Gestionarrepartidores1;
	TMenuItem *Rastrearpagos1;
	TMenuItem *Comidasymen1;
	TMenuItem *Agregarunacomida1;
	TMenuItem *Modificarunacomida1;
	TMenuItem *Gestionarmensemanal1;
	TMenuItem *Alarmas1;
	TMenuItem *Configurarunaalarma1;
	TMenuItem *Gestionaralarmas1;
	TMenuItem *Pedidos1;
	TMenuItem *Cargarpedidos1;
	TMenuItem *Facturacin1;
	TMenuItem *Emitirfacturaselectrnicas1;
	TMenuItem *Verfacturasemitidas1;
	TMenuItem *Facturacinmensual1;
	TMenuItem *Gestionarclienteshabituales1;
	TMenuItem *Acercade1;
	TMenuItem *Configuracionesdeprograma1;
	TMenuItem *Gestindeprecioes1;
	TMenuItem *Verdetallesdedeuda1;
	TMenuItem *Gestionarrepartos1;
	TMenuItem *Gestinderecetas1;
	TMenuItem *GestiondeGastos1;
	TMenuItem *Ingredientes1;
	TMenuItem *Composiciondecomidas1;
	TMenuItem *InformacionNutricional1;
	TMenuItem *Frecuencias1;
	TMenuItem *Gestionarmenparaoficinas1;
	TMenuItem *Gestiondeproductos1;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall CuentasClick(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall AlarmasTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall Verestadodecuenta1Click(TObject *Sender);
	void __fastcall Imprimirdetalledecuenta1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button19Click(TObject *Sender);
	void __fastcall Button20Click(TObject *Sender);
	void __fastcall Button21Click(TObject *Sender);
	void __fastcall Button22Click(TObject *Sender);
	void __fastcall Cargarpedidos1Click(TObject *Sender);
	void __fastcall Imprimirplanillas1Click(TObject *Sender);
	void __fastcall Gestionarrepartidores1Click(TObject *Sender);
	void __fastcall Cargarpagosdeclientes1Click(TObject *Sender);
	void __fastcall Gestionarcuentasdeclientes1Click(TObject *Sender);
	void __fastcall Imprimirdetalles1Click(TObject *Sender);
	void __fastcall Emitirfacturaselectrnicas1Click(TObject *Sender);
	void __fastcall Rastrearpagos1Click(TObject *Sender);
	void __fastcall Agregaruncliente1Click(TObject *Sender);
	void __fastcall Modificardatosdeclientes1Click(TObject *Sender);
	void __fastcall Gestionarclienteshabituales1Click(TObject *Sender);
	void __fastcall Agregarunacomida1Click(TObject *Sender);
	void __fastcall Modificarunacomida1Click(TObject *Sender);
	void __fastcall Gestionarmensemanal1Click(TObject *Sender);
	void __fastcall Configurarunaalarma1Click(TObject *Sender);
	void __fastcall Gestionaralarmas1Click(TObject *Sender);
	void __fastcall Verfacturasemitidas1Click(TObject *Sender);
	void __fastcall Facturacinmensual1Click(TObject *Sender);
	void __fastcall Configuracionesdeprograma1Click(TObject *Sender);
	void __fastcall Gestindeprecioes1Click(TObject *Sender);
	void __fastcall Verdetallesdedeuda1Click(TObject *Sender);
	void __fastcall Gestionarrepartos1Click(TObject *Sender);
	void __fastcall Gestinderecetas1Click(TObject *Sender);
	void __fastcall GestiondeGastos1Click(TObject *Sender);
	void __fastcall Ingredientes1Click(TObject *Sender);
	void __fastcall Composiciondecomidas1Click(TObject *Sender);
	void __fastcall InformacionNutricional1Click(TObject *Sender);
	void __fastcall Frecuencias1Click(TObject *Sender);
	void __fastcall Gestionarmenparaoficinas1Click(TObject *Sender);
	void __fastcall Gestiondeproductos1Click(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TfMain(TComponent* Owner);
	int idProximaAlarma;
	TDateTime proximaAlarma;
};
//---------------------------------------------------------------------------
extern PACKAGE TfMain *fMain;
//---------------------------------------------------------------------------
#endif
