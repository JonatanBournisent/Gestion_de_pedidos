//---------------------------------------------------------------------------

#ifndef uFrameMenuOficinaH
#define uFrameMenuOficinaH
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
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TframeMenuOficina : public TFrame
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *CDS1;
	TIntegerField *CDS1idMenuOficinas;
	TWideStringField *CDS1plato1;
	TWideStringField *CDS1plato2;
	TLargeintField *CDS1esLight;
	TLargeintField *CDS1esVeggie;
	TIntegerField *CDS1nroOpcion;
	TDataSource *DataSource1;
	TSQLQuery *QueryAux;
	TSQLQuery *QueryUpdate;
	TPopupMenu *PopupMenu1;
	TMenuItem *Moverhaciaarriba1;
	TMenuItem *Moverhacaabajo1;
	TMenuItem *Agregaropcin1;
	TMenuItem *Eliminaropcin1;
	TPanel *Panel1;
	TButton *Button3;
	TButton *Button4;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TButton *Button5;
	TCheckBox *cerrado;
	TLabel *Label1;
	TMenuItem *Modificarestaopcin1;
	TMenuItem *Copiarestemen1;
	TMemo *Memo1;
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall CDS1esLightGetText(TField *Sender, UnicodeString &Text, bool DisplayText);
	void __fastcall CDS1esVeggieGetText(TField *Sender, UnicodeString &Text, bool DisplayText);
	void __fastcall Moverhaciaarriba1Click(TObject *Sender);
	void __fastcall Moverhacaabajo1Click(TObject *Sender);
	void __fastcall Agregaropcin1Click(TObject *Sender);
	void __fastcall Eliminaropcin1Click(TObject *Sender);
	void __fastcall cerradoClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
	void __fastcall Modificarestaopcin1Click(TObject *Sender);
	void __fastcall Copiarestemen1Click(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TframeMenuOficina(TComponent* Owner);

	void mostrarMenu(void);
	void inicializar(TDate fechaIni);
	TDate fecha;
	void cerrar(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TframeMenuOficina *frameMenuOficina;
//---------------------------------------------------------------------------
#endif
