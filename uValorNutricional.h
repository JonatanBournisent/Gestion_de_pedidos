//---------------------------------------------------------------------------

#ifndef uValorNutricionalH
#define uValorNutricionalH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Data.DB.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
//---------------------------------------------------------------------------
class TfValorNutricional : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *Edit1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit2;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *Edit3;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *Edit4;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *Edit5;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *Edit6;
	TLabel *Label12;
	TLabel *Label13;
	TEdit *Edit7;
	TLabel *Label14;
	TLabel *Label15;
	TEdit *Edit8;
	TLabel *Label16;
	TShape *Shape1;
	TLabel *Label17;
	TShape *Shape2;
	TButton *Button1;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TLabel *Label18;
	TLabel *Label19;
	TButton *Button2;
	TPanel *Panel1;
	TButton *Button3;
	TButton *Button4;
	TEdit *Edit9;
	TButton *Button5;
	void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall Edit2KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit3KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit4KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit5KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit6KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit7KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit8KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit2Exit(TObject *Sender);
	void __fastcall Edit3Exit(TObject *Sender);
	void __fastcall Edit4Exit(TObject *Sender);
	void __fastcall Edit5Exit(TObject *Sender);
	void __fastcall Edit6Exit(TObject *Sender);
	void __fastcall Edit7Exit(TObject *Sender);
	void __fastcall Edit8Exit(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfValorNutricional(TComponent* Owner);

	int idIngrediente;
};
//---------------------------------------------------------------------------
extern PACKAGE TfValorNutricional *fValorNutricional;
//---------------------------------------------------------------------------
#endif
