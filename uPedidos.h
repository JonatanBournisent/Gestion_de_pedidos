//---------------------------------------------------------------------------

#ifndef uPedidosH
#define uPedidosH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Data.DB.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include "uFrame2.h"
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.CheckLst.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------
class TfPedidos : public TForm
{
__published:	// IDE-managed Components
	TDateTimePicker *DTP;
	TRadioGroup *RG1;
	TButton *Button1;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TRadioGroup *RG2;
	TRadioGroup *RG3;
	TRadioGroup *RG4;
	TSQLQuery *QueryAux;
	TDataSource *DataSource2;
	TSQLQuery *QueryPedidos;
	TDataSetProvider *DataSetProvider2;
	TClientDataSet *ClientDataSet2;
	TComboBox *cbRefProducto;
	TComboBox *cbRefMedioContacto;
	TEdit *edComentario;
	TCheckBox *CBOmitirEtiqueta;
	TDBGrid *DBGrid1;
	TEdit *edUnidades;
	TEdit *edBandGrand;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button2;
	TPopupMenu *PopupMenu1;
	TMenuItem *Modificarestepedido1;
	TMenuItem *Eliminarestepedido1;
	TSQLQuery *QueryGenCad;
	TButton *Button7;
	TButton *Button8;
	TMenuItem *Mandaraimprimirestaetiqueta1;
	TMenuItem *Agregaracoladeimpresin1;
	TUpDown *UpDown1;
	TUpDown *UpDown2;
	TRadioGroup *RGTexto;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Panel6;
	TPanel *Panel7;
	TPanel *Panel8;
	TPanel *Panel9;
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;
	TImage *Image4;
	TEdit *Edit1;
	TDataSource *DataSource3;
	TSQLQuery *QueryCliente;
	TDataSetProvider *DataSetProvider3;
	TClientDataSet *ClientDataSet3;
	TDBGrid *DBGrid2;
	TComboBox *cbRepartidor;
	TRadioGroup *rgUbicacion;
	TButton *Button9;
	TButton *Button10;
	TButton *Button3;
	TSQLQuery *QueryEtiquetas;
	TPanel *Panel10;
	TDBGrid *DBGrid3;
	TButton *Button5;
	TButton *Button6;
	TButton *Button4;
	TEdit *Edit2;
	TCheckBox *CheckBox1;
	TMenuItem *Marcarcomoimpresa1;
	TfrxReport *frxReport1;
	TButton *Button11;
	TPopupMenu *PopupMenu2;
	TMenuItem *Verdescripcion1;
	TPanel *Panel11;
	TMemo *Memo1;
	TSQLQuery *QueryComida;
	TButton *Button12;
	TLabel *Label3;
	TButton *Button13;
	TPanel *Panel12;
	TPanel *Panel13;
	TPanel *Panel14;
	TPanel *Panel15;
	TSQLQuery *QueryInfo;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TButton *Button15;
	TLabel *Label8;
	TLabel *Label9;
	TButton *Button14;
	TPanel *Panel16;
	TListBox *ListBox2;
	TButton *Button16;
	TLabel *Label11;
	TMainMenu *MainMenu1;
	TMenuItem *Acciones1;
	TMenuItem *Configurarunaalarma1;
	TMenuItem *Imprimirplanillasderepartos1;
	TMenuItem *Modificardatosdeuncliente1;
	TMenuItem *Modificardatosdeunacomida1;
	TMenuItem *Ver1;
	TMenuItem *Imprimircuentas1;
	TMenuItem *Gestionaralarmas1;
	TMenuItem *Verplanillasdereparto1;
	TMenuItem *Vermenusemanal1;
	TMenuItem *Marcarcomplementocomoimpreso1;
	TMenuItem *Marcarparavolveraimprimircomplemento1;
	TButton *Button17;
	TfrxReport *frxReport2;
	TDataSource *DataSource1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *CDSEtiquetas;
	TWideStringField *CDSEtiquetascomentario;
	TWideStringField *CDSEtiquetasc1;
	TWideStringField *CDSEtiquetasc2;
	TWideStringField *CDSEtiquetasc3;
	TWideStringField *CDSEtiquetasc4;
	TLargeintField *CDSEtiquetasnroApa;
	TWideStringField *CDSEtiquetasNumero;
	TWideStringField *CDSEtiquetasRepartidor;
	TIntegerField *CDSEtiquetasrefComida1;
	TIntegerField *CDSEtiquetasrefComida2;
	TIntegerField *CDSEtiquetasrefComida3;
	TPanel *Panel17;
	TDBGrid *DBGrid4;
	TButton *Button18;
	TButton *Button19;
	TDataSource *DataSource4;
	TClientDataSet *CDSEtiquetasComp;
	TWideStringField *WideStringField1;
	TWideStringField *WideStringField5;
	TWideStringField *WideStringField6;
	TWideStringField *WideStringField7;
	TDataSetProvider *DataSetProvider4;
	TSQLQuery *QueryEtiquetasComp;
	TBevel *Bevel1;
	TMenuItem *Verhistorialdepedidosdelcliente1;
	TLabel *Label12;
	TMenuItem *Copiarmenparawhatsapp1;
	TMemo *Memo2;
	TMenuItem *CopiarmenparaMailFBIG1;
	TMenuItem *Agregarunpedidoigual1;
	TTimer *Timer1;
	TMenuItem *Mandaraimprimirestecomplemento1;
	TCheckBox *CBParaCocina;
	TMenuItem *Verpedidosdehoy1;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TButton *Button20;
	TByteField *CDSEtiquetascomentarioParaCocina;
	TLabel *Label17;
	TLargeintField *CDSEtiquetasrefRep;
	TIntegerField *CDSEtiquetassalidaRep;
	TTimer *Timer2;
	TButton *Button21;
	TPanel *Panel18;
	TPanel *Panel19;
	TButton *Button22;
	TMemo *Memo3;
	TLabel *lbComplementos;
	TMenuItem *VercomprobantesX1;
	TLabel *Label18;
	TButton *Button23;
	TMenuItem *Emitiruncomprobanteelectronico1;
	TButton *Button24;
	TButton *Button25;
	TPanel *Panel20;
	TDBGrid *DBGrid5;
	TDataSetProvider *DSch;
	TClientDataSet *CDSch;
	TWideStringField *CDSchcliente;
	TDataSource *DScch;
	TSQLQuery *Querych;
	TButton *Button26;
	TLabel *Label19;
	TTimer *Timer3;
	TSQLQuery *QueryRep;
	TMenuItem *ransferiraotrocliente1;
	TMenuItem *Informacinnutricional1;
	TMenuItem *CopiarmenusemanalparaWhatsapp1;
	TButton *Button27;
	TMenuItem *CopiarcombinacionesJUEVES1;
	TMenuItem *Verinformacindelcliente1;
	TMenuItem *CopiarpedidoparaWhatsApp1;
	TMenuItem *Imprimir1;
	TMenuItem *Marcarparavolveraimprimir1;
	TMenuItem *ildarcomoimpreso1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *Configuraralarmadeentrega1;
	TMenuItem *N3;
	TButton *Button28;
	TButton *Button29;
	TButton *Button30;
	TButton *Button31;
	TButton *Button32;
	TButton *Button33;
	TButton *Button34;
	TButton *Button35;
	TLabel *Label20;
	TLabel *Label21;
	TPanel *Panel21;
	TMonthCalendar *MC;
	TEdit *Edit3;
	TMemo *Memo4;
	TButton *Button36;
	TButton *Button38;
	TButton *Button39;
	TLabel *Label22;
	TLabel *Label23;
	TMenuItem *Imprimirtodosestospedidos1;
	TMenuItem *Imprimirtodosestoscomplementos1;
	TButton *Button37;
	TPopupMenu *PopupMenu3;
	TMenuItem *Copiarsaludoyvalor1;
	TPopupMenu *PopupMenu4;
	TMenuItem *Copiarmensemanal1;
	TComboBox *CBmp;
	TLabel *Label24;
	TButton *Button40;
	TPopupMenu *PopupMenu5;
	TMenuItem *Establecercomopredeterminado1;
	TPopupMenu *PopupMenu6;
	TMenuItem *BDRecibimoselsig1;
	TMenuItem *BDVananecesitarvia1;
	TMenuItem *Errorpedidojueves1;
	TPopupMenu *PopupMenu7;
	TMenuItem *Verclientesquenormalmentesolicitan1;
	TPopupMenu *PopupMenu8;
	TMenuItem *DatosdeMonica1;
	TMenuItem *CopiardatosdeWilliams1;
	TPopupMenu *PopupMenu9;
	TMenuItem *Informacinparaoficinas1;
	TPopupMenu *PopupMenu10;
	TMenuItem *Viandasparaoficinas1;
	TMenuItem *Menudeldaparaoficinas1;
	TButton *Button41;
	TRadioGroup *rgOficinas;
	TLabel *Label25;
	TEdit *Edit4;
	TSpeedButton *Button43;
	TSpeedButton *Button44;
	TSpeedButton *Button45;
	TSpeedButton *Button46;
	TLabel *Label26;
	TSpeedButton *SpeedButton1;
	TPanel *panel_invisible;
	TMemo *qry_etiquetas_viandas_normales;
	TMemo *qry_etiquetas_viandas_oficinas;
	TMemo *qry_pedidos;
	TMemo *qry_etiquetas_complementos;
	TIntegerField *CDSEtiquetasCompsalidaRep;
	TWideStringField *ClientDataSet3calle;
	TWideStringField *ClientDataSet3numero;
	TFMTBCDField *ClientDataSet3acumuladoGlobal;
	TFMTBCDField *ClientDataSet3deuda;
	TIntegerField *ClientDataSet3pos;
	TIntegerField *ClientDataSet3division;
	TWideStringField *ClientDataSet3Repartidor;
	TIntegerField *ClientDataSet3idCliente;
	TWideStringField *ClientDataSet2Comentario;
	TWideStringField *ClientDataSet2com1;
	TWideStringField *ClientDataSet2com2;
	TWideStringField *ClientDataSet2com3;
	TWideStringField *ClientDataSet2com4;
	TIntegerField *ClientDataSet2refProducto;
	TIntegerField *ClientDataSet2idPedido;
	TIntegerField *ClientDataSet2refCantidad;
	TFMTBCDField *ClientDataSet2valor;
	TTimeField *ClientDataSet2hora;
	TMenuItem *Menusemanalparaoficinas1;
	TDBGrid *DBGrid6;
	TDataSetProvider *DataSetProvider5;
	TClientDataSet *CDS5;
	TDataSource *DataSource5;
	TIntegerField *CDS5refRepartidor;
	TLargeintField *CDS5cantDirecciones;
	TWideStringField *CDS5nombreRep;
	TIntegerField *CDS5reparto;
	TFMTBCDField *CDS5cantViandas;
	TWideStringField *CDS5repartidor;
	TTimer *Timer4;
	TSQLQuery *QueryComidasEsp;
	TDataSetProvider *DataSetProvider6;
	TClientDataSet *CDS6;
	TDataSource *DataSource6;
	TDBGrid *DBGrid7;
	TIntegerField *CDS6idComida;
	TWideStringField *CDS6nComida;
	TLargeintField *CDS6cantidad;
	TSQLQuery *qValorTotal;
	TPanel *Panel22;
	TfrxReport *frxReport3;
	TSQLQuery *QueryEtiquetasBolsas;
	TMemo *qry_etiquetas_bolsas;
	TPopupMenu *PopupMenu11;
	TMenuItem *Imprimiretiquetasdebolsas1;
	TButton *Button42;
	TMenuItem *Vercomplementos1;
	TMenuItem *Imprimiretiquetasdeviandasdeestereparto1;
	TMenuItem *Informaciondeviandasnormales1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DTPChange(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Modificarestepedido1Click(TObject *Sender);
	void __fastcall Eliminarestepedido1Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall edUnidadesKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall edBandGrandKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
	void __fastcall UpDown2Click(TObject *Sender, TUDBtnType Button);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall Image2Click(TObject *Sender);
	void __fastcall Image3Click(TObject *Sender);
	void __fastcall Image4Click(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall DBGrid2DblClick(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Edit1Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall Agregaracoladeimpresin1Click(TObject *Sender);
	void __fastcall Marcarcomoimpresa1Click(TObject *Sender);
	void __fastcall Mandaraimprimirestaetiqueta1Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Verdescripcion1Click(TObject *Sender);
	void __fastcall RGTextoClick(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall RG1Click(TObject *Sender);
	void __fastcall RG2Click(TObject *Sender);
	void __fastcall RG3Click(TObject *Sender);
	void __fastcall RG4Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall Configurarunaalarma1Click(TObject *Sender);
	void __fastcall FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize);
	void __fastcall Imprimirplanillasderepartos1Click(TObject *Sender);
	void __fastcall Modificardatosdeuncliente1Click(TObject *Sender);
	void __fastcall Modificardatosdeunacomida1Click(TObject *Sender);
	void __fastcall Imprimircuentas1Click(TObject *Sender);
	void __fastcall Gestionaralarmas1Click(TObject *Sender);
	void __fastcall Verplanillasdereparto1Click(TObject *Sender);
	void __fastcall Vermenusemanal1Click(TObject *Sender);
	void __fastcall Marcarcomplementocomoimpreso1Click(TObject *Sender);
	void __fastcall Marcarparavolveraimprimircomplemento1Click(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button19Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall Verhistorialdepedidosdelcliente1Click(TObject *Sender);
	void __fastcall Copiarmenparawhatsapp1Click(TObject *Sender);
	void __fastcall CopiarmenparaMailFBIG1Click(TObject *Sender);
	void __fastcall Agregarunpedidoigual1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Mandaraimprimirestecomplemento1Click(TObject *Sender);
	void __fastcall Verpedidosdehoy1Click(TObject *Sender);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall DBGrid2DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall Button21Click(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall RG1Enter(TObject *Sender);
	void __fastcall RG1Exit(TObject *Sender);
	void __fastcall RG2Enter(TObject *Sender);
	void __fastcall RG2Exit(TObject *Sender);
	void __fastcall RG3Exit(TObject *Sender);
	void __fastcall RG3Enter(TObject *Sender);
	void __fastcall RG4Enter(TObject *Sender);
	void __fastcall RG4Exit(TObject *Sender);
	void __fastcall Panel18Click(TObject *Sender);
	void __fastcall Panel19Click(TObject *Sender);
	void __fastcall Mem(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall VercomprobantesX1Click(TObject *Sender);
	void __fastcall Button23Click(TObject *Sender);
	void __fastcall Emitiruncomprobanteelectronico1Click(TObject *Sender);
	void __fastcall Button24Click(TObject *Sender);
	void __fastcall DBGrid2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Button25Click(TObject *Sender);
	void __fastcall Button26Click(TObject *Sender);
	void __fastcall Timer3Timer(TObject *Sender);
	void __fastcall ransferiraotrocliente1Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall Informacinnutricional1Click(TObject *Sender);
	void __fastcall CopiarmenusemanalparaWhatsapp1Click(TObject *Sender);
	void __fastcall Button27Click(TObject *Sender);
	void __fastcall CopiarcombinacionesJUEVES1Click(TObject *Sender);
	void __fastcall Verinformacindelcliente1Click(TObject *Sender);
	void __fastcall CopiarpedidoparaWhatsApp1Click(TObject *Sender);
	void __fastcall Configuraralarmadeentrega1Click(TObject *Sender);
	void __fastcall DTPExit(TObject *Sender);
	void __fastcall Button29Click(TObject *Sender);
	void __fastcall Button28Click(TObject *Sender);
	void __fastcall Button30Click(TObject *Sender);
	void __fastcall Button32Click(TObject *Sender);
	void __fastcall Button31Click(TObject *Sender);
	void __fastcall Button33Click(TObject *Sender);
	void __fastcall Button34Click(TObject *Sender);
	void __fastcall Button35Click(TObject *Sender);
	void __fastcall edUnidadesChange(TObject *Sender);
	void __fastcall Edit3KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit3Exit(TObject *Sender);
	void __fastcall edUnidadesExit(TObject *Sender);
	void __fastcall Button36Click(TObject *Sender);
	void __fastcall Button38Click(TObject *Sender);
	void __fastcall Button39Click(TObject *Sender);
	void __fastcall Edit3Change(TObject *Sender);
	void __fastcall MCClick(TObject *Sender);
	void __fastcall Imprimirtodosestospedidos1Click(TObject *Sender);
	void __fastcall Imprimirtodosestoscomplementos1Click(TObject *Sender);
	void __fastcall Button37Click(TObject *Sender);
	void __fastcall Copiarsaludoyvalor1Click(TObject *Sender);
	void __fastcall Copiarmensemanal1Click(TObject *Sender);
	void __fastcall Button40Click(TObject *Sender);
	void __fastcall Establecercomopredeterminado1Click(TObject *Sender);
	void __fastcall BDRecibimoselsig1Click(TObject *Sender);
	void __fastcall BDVananecesitarvia1Click(TObject *Sender);
	void __fastcall Errorpedidojueves1Click(TObject *Sender);
	void __fastcall Verclientesquenormalmentesolicitan1Click(TObject *Sender);
	void __fastcall DatosdeMonica1Click(TObject *Sender);
	void __fastcall CopiardatosdeWilliams1Click(TObject *Sender);
	void __fastcall Informacinparaoficinas1Click(TObject *Sender);
	void __fastcall Viandasparaoficinas1Click(TObject *Sender);
	void __fastcall Menudeldaparaoficinas1Click(TObject *Sender);
	void __fastcall Button41Click(TObject *Sender);
	void __fastcall cbRefProductoChange(TObject *Sender);
	void __fastcall rgOficinasClick(TObject *Sender);
	void __fastcall Edit4Exit(TObject *Sender);
	void __fastcall Edit4Enter(TObject *Sender);
	void __fastcall Button43Click(TObject *Sender);
	void __fastcall Button44Click(TObject *Sender);
	void __fastcall Button45Click(TObject *Sender);
	void __fastcall Button46Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall Menusemanalparaoficinas1Click(TObject *Sender);
	void __fastcall DBGrid6DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall DBGrid6DblClick(TObject *Sender);
	void __fastcall Timer4Timer(TObject *Sender);
	void __fastcall DBGrid6CellClick(TColumn *Column);
	void __fastcall DBGrid7DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall DBGrid7DblClick(TObject *Sender);
	void __fastcall ListBox2DblClick(TObject *Sender);
	void __fastcall Imprimiretiquetasdebolsas1Click(TObject *Sender);
	void __fastcall Button42Click(TObject *Sender);
	void __fastcall Vercomplementos1Click(TObject *Sender);
	void __fastcall Imprimiretiquetasdeviandasdeestereparto1Click(TObject *Sender);
	void __fastcall Informaciondeviandasnormales1Click(TObject *Sender);




private:	// User declarations
public:		// User declarations
	__fastcall TfPedidos(TComponent* Owner);

	bool mostroMsg1;
	bool mostroMsg2;

	float val1, val2, val3;

	int arrOpOficinaP1[10];
	int arrOpOficinaP2[10];

	int arrIdComida[9];
	String opciones[9];
	int idCliSel;
	float descuentoCliente;
	bool modificandoPedido;
	int idMod;

	int oriRgUbiID;
	int oriCbRepID;


	int idOpEsp1, idOpEsp2, idOpEsp3, idOpEsp4;
	int idOpEsp1Old, idOpEsp2Old, idOpEsp3Old, idOpEsp4Old;

	String generarCadComp(String tipo);
	int sectorRepartoGCC; // para generarCadComp
	int refRepartidorGCC;	// para generarCadComp


	String comaToDot(String str);

	float getValorTotal(void);

	void RestablecerFormulario(void);
	void CargarOpciones(void);
	String GetCodigo(int idComida);
	void verClienteSeleccionado(int idCliente);

	void imprimirEtiquetas(int llamador, int refRepartidor);
	void imprimirEtiquetasOficinas(void);
	void procesoImpresionEtiquetasPedidosOficinas(void);
	void imprimirComplementos(void);
	void imprimirEtiquetasBolsas(int refRep, int reparto);

	int contLineasImpresas; //cuenta las que se enviaron a la impresora
	int cantLineas; //contiene la cantidad de lineas a imprimir
	int cantidadPedidos;

	int llamadorAux;
	int refRepartidorAux;
	bool cargandoOpciones;
	bool blockRGTexto;	//bloquea el evento onclick del RGTexto para que no se dispare cuando cambio el itemindex manualmente
	bool cargandoPedido; //igual que el blockRGTexto pero mas general
	bool puedeSalir;
	bool advertirMismoCliente;  //intenta mitigar el error donde se carga un nuevo pedido pero en el cliente anterior
	bool advertirRevisarCantidades; //intenta mitigar el error donde se agrega o elimina un pedido y no se actualiza la cantidad


	void actualizarInfoVentas(void);
	int vTimer1;
	int vTimer2;
	float valorVianda;
	float valorViandaOficina;
	float valorEnvio;
	float valorViandaUnica;

	TDate fechaPrevia;

	int RGSeleccionado;

	String una, ens;

	bool esOpcionEspecial(int idComida);

	void completarEtiquetaPedido(String c1, String c2, String c3, String c4,
						   String cliente, String repartidor, String nroReparto,
						   String comentario, bool izq, bool c1Esp, bool c2Esp,
						   bool c3Esp, bool comentarioEsp, bool blanca);

	void completarEtiquetaComplemento(String c4, String cliente,
										String repartidor, String nroReparto,
										String comentario, bool izq,
										bool blanca);

	void completarEtiquetaBolsa(String numero, String calle,
										String repartidor,
										String detalle,
										String coment,
										String menuImp, bool izq,
										bool blanca);

	float roundToHight10(float val);

	void procesoImpresionEtiquetasPedidos(int reparto, int refRepartidor);
	void procesoImpresionEtiquetasComplementos();
	void deleteComidaEspecial(int refPedido, int refComida);
	void insertComidaEspecial(TDateTime dt, int refComida, int refPedido, int refReparto);
	String getCodigoComidaFromID(int id);
	String getImpresoraEtiquetas(void);
	void getPedidos(int refCliente, TDateTime dt);
	int getRefCantidad(int refCliente, TDateTime dt);
	bool menuImpreso;

	TDateTime mStartPrinting;
};
//---------------------------------------------------------------------------
extern PACKAGE TfPedidos *fPedidos;
//---------------------------------------------------------------------------
#endif
