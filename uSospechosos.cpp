//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "uSospechosos.h"

#include "VariablesGlobales.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfSospechosos *fSospechosos;

extern String servidor;
extern String dbName;
extern String userName;
extern String pass;
//---------------------------------------------------------------------------
__fastcall TfSospechosos::TfSospechosos(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfSospechosos::FormCreate(TObject *Sender)
{
   SQLConnection1->Params->Values["HostName"] = servidor;
   SQLConnection1->Params->Values["Database"] = dbName;
   SQLConnection1->Params->Values["User_Name"] = userName;
   SQLConnection1->Params->Values["Password"] = pass;
}
//---------------------------------------------------------------------------
void __fastcall TfSospechosos::FormShow(TObject *Sender)
{
   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add("SELECT CONCAT(Calle, ' ', Numero) AS Direccion "
					"FROM clientes WHERE idCliente IN"
					"(SELECT refCliente FROM "
							"(SELECT refCliente, COUNT(*) AS ocurrencias FROM cantidades "
								"WHERE ("
								"fecha = DATE_ADD(DATE(NOW()), INTERVAL -7 DAY) OR "
								"fecha = DATE_ADD(DATE(NOW()), INTERVAL -14 DAY) OR "
								"fecha = DATE_ADD(DATE(NOW()), INTERVAL -21 DAY) OR "
								"fecha = DATE_ADD(DATE(NOW()), INTERVAL -28 DAY) OR "
								"fecha = DATE_ADD(DATE(NOW()), INTERVAL -35 DAY) OR "
								"fecha = DATE_ADD(DATE(NOW()), INTERVAL -42 DAY)) AND "
								"refCliente NOT IN("
								"	(SELECT refCliente FROM cantidades WHERE fecha =  DATE(NOW()))"
							")"
							"GROUP BY refCliente)t WHERE t.ocurrencias >= 5 "
					")"
					);

   CDS->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfSospechosos::FormClose(TObject *Sender, TCloseAction &Action)
{
   CDS->Active = false;
   Query1->Close();
}
//---------------------------------------------------------------------------
