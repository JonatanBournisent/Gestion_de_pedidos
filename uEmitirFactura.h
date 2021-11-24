//---------------------------------------------------------------------------

#ifndef uEmitirFacturaH
#define uEmitirFacturaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include <Data.DB.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Vcl.ComCtrls.hpp>
#include "frxBarcode.hpp"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfEmitirFactura : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TfEmitirFactura(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfEmitirFactura *fEmitirFactura;
//---------------------------------------------------------------------------
#endif
