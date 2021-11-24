//---------------------------------------------------------------------------

#ifndef uFrame3H
#define uFrame3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Mask.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
//---------------------------------------------------------------------------
class TFrame3 : public TFrame
{
__published:	// IDE-managed Components
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label7;
	TLabel *Label9;
	TDBEdit *DBEdNombre;
	TDBEdit *DBEdCodigo;
	TDBLookupComboBox *DBCategoria;
	TDBGrid *DBGrid1;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *ClientDataSet1;
	TDataSource *DataSource1;
	TSQLTable *SQLTable1;
	TDataSetProvider *DataSetProvider2;
	TClientDataSet *ClientDataSet2;
	TDataSource *DataSource2;
	TDataSetProvider *DataSetProvider4;
	TClientDataSet *ClientDataSet4;
	TDataSource *DataSource4;
	TSQLQuery *Query3;
	TDBMemo *DBMemo1;
	TSQLQuery *QueryAux;
	void __fastcall DBEdNombreChange(TObject *Sender);
	void __fastcall DBEdCodigoChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFrame3(TComponent* Owner);

	void restablecerFrame(void);
	void cerrarFrame(void);
	bool guardar(void);
	void cancelar(void);
	int llamador; //1: agregar una comida, 2: editar una comida
	int id;

	bool guardoOK;
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame3 *Frame3;
//---------------------------------------------------------------------------
#endif
