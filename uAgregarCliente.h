//---------------------------------------------------------------------------

#ifndef uAgregarClienteH
#define uAgregarClienteH
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
#include <Vcl.Mask.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include "uFrame1.h"

//---------------------------------------------------------------------------
class TfAgregarCliente : public TForm
{
__published:	// IDE-managed Components
	TFrame1 *Frame11;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TShape *Shape1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfAgregarCliente(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfAgregarCliente *fAgregarCliente;
//---------------------------------------------------------------------------
#endif
