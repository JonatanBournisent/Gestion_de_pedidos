//---------------------------------------------------------------------------

#ifndef uHistorialPedidosH
#define uHistorialPedidosH
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
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfHistorialPedidos : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TfHistorialPedidos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfHistorialPedidos *fHistorialPedidos;
//---------------------------------------------------------------------------
#endif
