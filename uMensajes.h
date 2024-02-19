//---------------------------------------------------------------------------

#ifndef uMensajesH
#define uMensajesH
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
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TfMensajes : public TForm
{
__published:	// IDE-managed Components
	TComboBox *CB;
	TMemo *Memo1;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TPanel *Panel1;
	TEdit *Edit1;
	TButton *Button5;
	TButton *Button6;
	TPanel *Panel2;
	TEdit *Edit2;
	TButton *Button7;
	TButton *Button8;
	TMainMenu *MainMenu1;
	TMenuItem *Acciones1;
	TMenuItem *Modificartitulo1;
	TLabel *Label1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Modificartitulo1Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button8Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfMensajes(TComponent* Owner);

	void cargarTitulos(void);
	void cargarMensaje(String titulo);
	void actualizarMensaje(String titulo);
	void actualizarTitulo(String tituloViejo, String tituloNuevo);
};
//---------------------------------------------------------------------------
extern PACKAGE TfMensajes *fMensajes;
//---------------------------------------------------------------------------
#endif
