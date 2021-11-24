//---------------------------------------------------------------------------

#ifndef uAgregarPagoH
#define uAgregarPagoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "uFrame2.h"
#include <Vcl.ComCtrls.hpp>
#include <Data.DB.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
//---------------------------------------------------------------------------
class TfAgregarPago : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TfAgregarPago(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TfAgregarPago *fAgregarPago;
//---------------------------------------------------------------------------
#endif
