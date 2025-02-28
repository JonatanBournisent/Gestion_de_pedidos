object fMain: TfMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = 'Sistema de gest'#243'n de "El Sembrador"'
  ClientHeight = 510
  ClientWidth = 817
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnCanResize = FormCanResize
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 183
    Top = 23
    Width = 450
    Height = 25
    Alignment = taCenter
    AutoSize = False
    Caption = 'Recordatorio de deudas de clientes'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Button2: TButton
    Left = 665
    Top = 115
    Width = 137
    Height = 25
    Caption = 'Agregar cliente'
    TabOrder = 9
    OnClick = Button2Click
  end
  object Button1: TButton
    Left = 665
    Top = 158
    Width = 137
    Height = 25
    Caption = 'Modificar un cliente'
    TabOrder = 10
    OnClick = Button1Click
  end
  object Button3: TButton
    Left = 665
    Top = 287
    Width = 137
    Height = 25
    Caption = 'Repartidores'
    TabOrder = 13
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 16
    Top = 157
    Width = 137
    Height = 25
    Caption = 'Repartos'
    TabOrder = 2
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 16
    Top = 72
    Width = 137
    Height = 25
    Caption = 'Pedidos'
    TabOrder = 0
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 665
    Top = 201
    Width = 137
    Height = 25
    Caption = 'Agregar comidas'
    TabOrder = 11
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 665
    Top = 244
    Width = 137
    Height = 25
    Caption = 'Modificar comidas'
    TabOrder = 12
    OnClick = Button7Click
  end
  object Button9: TButton
    Left = 16
    Top = 328
    Width = 137
    Height = 25
    Caption = 'Menu semanal'
    TabOrder = 6
    OnClick = Button9Click
  end
  object Button10: TButton
    Left = 711
    Top = 24
    Width = 137
    Height = 25
    Caption = 'Productos'
    TabOrder = 14
    Visible = False
    OnClick = Button10Click
  end
  object Button11: TButton
    Left = 16
    Top = 114
    Width = 137
    Height = 25
    Caption = 'Cargar Pagos'
    TabOrder = 1
    OnClick = Button11Click
  end
  object Button12: TButton
    Left = 16
    Top = 200
    Width = 137
    Height = 25
    Caption = 'Imprimir Planillas'
    TabOrder = 3
    OnClick = Button12Click
  end
  object Button13: TButton
    Left = 665
    Top = 459
    Width = 137
    Height = 25
    Caption = 'Configuraciones'
    TabOrder = 15
    OnClick = Button13Click
  end
  object Cuentas: TButton
    Left = 16
    Top = 285
    Width = 137
    Height = 25
    Caption = 'Cuentas'
    TabOrder = 5
    OnClick = CuentasClick
  end
  object Button14: TButton
    Left = 16
    Top = 243
    Width = 137
    Height = 25
    Caption = 'Imprimir cuentas'
    TabOrder = 4
    OnClick = Button14Click
  end
  object Button8: TButton
    Left = 608
    Top = 24
    Width = 146
    Height = 25
    Caption = 'Datos Ctr+Shift+Alt+F12'
    TabOrder = 17
    Visible = False
    OnClick = Button8Click
  end
  object Button15: TButton
    Left = 16
    Top = 371
    Width = 137
    Height = 25
    Caption = 'Configurar alarma'
    TabOrder = 7
    OnClick = Button15Click
  end
  object Button16: TButton
    Left = 665
    Top = 72
    Width = 137
    Height = 25
    Caption = 'Gestionar alarmas'
    TabOrder = 8
    OnClick = Button16Click
  end
  object DBGrid1: TDBGrid
    Left = 183
    Top = 61
    Width = 450
    Height = 436
    Color = clBtnFace
    DataSource = DataSource1
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    ParentFont = False
    PopupMenu = PopupMenu1
    TabOrder = 16
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDrawColumnCell = DBGrid1DrawColumnCell
    OnDblClick = DBGrid1DblClick
    Columns = <
      item
        Expanded = False
        FieldName = 'cliente'
        Title.Alignment = taCenter
        Title.Caption = 'Cliente'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clBlack
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 282
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'deuda'
        Title.Alignment = taCenter
        Title.Caption = 'Deuda'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clBlack
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 134
        Visible = True
      end>
  end
  object Button18: TButton
    Left = 16
    Top = 414
    Width = 137
    Height = 25
    Caption = 'Factura electr'#243'nica'
    TabOrder = 18
    OnClick = Button18Click
  end
  object Button17: TButton
    Left = 665
    Top = 416
    Width = 137
    Height = 25
    Caption = 'Ver facturas emitidas'
    TabOrder = 19
    OnClick = Button17Click
  end
  object Button19: TButton
    Left = 665
    Top = 330
    Width = 137
    Height = 25
    Caption = 'Definir precios'
    TabOrder = 20
    OnClick = Button19Click
  end
  object Button20: TButton
    Left = 665
    Top = 373
    Width = 137
    Height = 25
    Caption = 'Facturacion mensual'
    TabOrder = 21
    OnClick = Button20Click
  end
  object Button21: TButton
    Left = 16
    Top = 457
    Width = 137
    Height = 25
    Caption = 'Cliente habituales'
    TabOrder = 22
    OnClick = Button21Click
  end
  object Button22: TButton
    Left = 32
    Top = 24
    Width = 137
    Height = 25
    Caption = 'Rastrear pagos'
    TabOrder = 23
    Visible = False
    OnClick = Button22Click
  end
  object Alarmas: TTimer
    OnTimer = AlarmasTimer
    Left = 432
    Top = 152
  end
  object SQLConnection1: TSQLConnection
    ConnectionName = 'MySQLConnection'
    DriverName = 'MySQL'
    KeepConnection = False
    LoginPrompt = False
    Params.Strings = (
      'DriverName=MySQL'
      'HostName=localhost'
      'Database=dbes'
      'User_Name=elsembrador'
      'Password=*-elsembrador63/*'
      'ServerCharSet=utf8'
      'BlobSize=-1'
      'ErrorResourceFile='
      'LocaleCode=0000'
      'Compressed=False'
      'Encrypted=False'
      'ConnectTimeout=60')
    Left = 239
    Top = 199
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 471
    Top = 151
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query2
    Left = 287
    Top = 197
  end
  object CDS1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    ReadOnly = True
    Left = 311
    Top = 197
    object CDS1cliente: TWideStringField
      FieldName = 'cliente'
    end
    object CDS1deuda: TFMTBCDField
      FieldName = 'deuda'
      DisplayFormat = '$ 0.00'
    end
    object CDS1idCliente: TIntegerField
      FieldName = 'idCliente'
    end
  end
  object DataSource1: TDataSource
    DataSet = CDS1
    Left = 335
    Top = 197
  end
  object Query2: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 263
    Top = 197
  end
  object PopupMenu1: TPopupMenu
    Left = 368
    Top = 328
    object Verestadodecuenta1: TMenuItem
      Caption = 'Ver estado de cuenta'
      OnClick = Verestadodecuenta1Click
    end
    object Imprimirdetalledecuenta1: TMenuItem
      Caption = 'Imprimir detalle de cuenta'
      OnClick = Imprimirdetalledecuenta1Click
    end
  end
  object MainMenu1: TMainMenu
    Left = 8
    Top = 8
    object Pedidos1: TMenuItem
      Caption = 'Pedidos'
      object Cargarpedidos1: TMenuItem
        Caption = 'Cargar pedidos'
        OnClick = Cargarpedidos1Click
      end
    end
    object Repartos1: TMenuItem
      Caption = 'Repartos'
      object Imprimirplanillas1: TMenuItem
        Caption = 'Imprimir planillas'
        OnClick = Imprimirplanillas1Click
      end
      object Gestionarrepartos1: TMenuItem
        Caption = 'Gestionar repartos'
        OnClick = Gestionarrepartos1Click
      end
      object Gestionarrepartidores1: TMenuItem
        Caption = 'Gestionar repartidores'
        OnClick = Gestionarrepartidores1Click
      end
    end
    object Cuentas1: TMenuItem
      Caption = 'Cuentas'
      object Cargarpagosdeclientes1: TMenuItem
        Caption = 'Cargar pagos de clientes'
        OnClick = Cargarpagosdeclientes1Click
      end
      object Gestionarcuentasdeclientes1: TMenuItem
        Caption = 'Gestionar cuentas de clientes'
        OnClick = Gestionarcuentasdeclientes1Click
      end
      object Imprimirdetalles1: TMenuItem
        Caption = 'Imprimir detalles de deudas'
        OnClick = Imprimirdetalles1Click
      end
      object Verdetallesdedeuda1: TMenuItem
        Caption = 'Ver detalles emitidos'
        OnClick = Verdetallesdedeuda1Click
      end
      object Rastrearpagos1: TMenuItem
        Caption = 'Rastrear pagos'
        OnClick = Rastrearpagos1Click
      end
    end
    object Clientes1: TMenuItem
      Caption = 'Clientes'
      object Agregaruncliente1: TMenuItem
        Caption = 'Agregar un cliente'
        OnClick = Agregaruncliente1Click
      end
      object Modificardatosdeclientes1: TMenuItem
        Caption = 'Modificar datos de clientes'
        OnClick = Modificardatosdeclientes1Click
      end
      object Gestionarclienteshabituales1: TMenuItem
        Caption = 'Gestionar clientes habituales'
        OnClick = Gestionarclienteshabituales1Click
      end
    end
    object Comidasymen1: TMenuItem
      Caption = 'Comidas y men'#250
      object Agregarunacomida1: TMenuItem
        Caption = 'Agregar una comida'
        OnClick = Agregarunacomida1Click
      end
      object Modificarunacomida1: TMenuItem
        Caption = 'Modificar una comida'
        OnClick = Modificarunacomida1Click
      end
      object Gestionarmensemanal1: TMenuItem
        Caption = 'Gestionar men'#250' semanal'
        OnClick = Gestionarmensemanal1Click
      end
      object Gestionarmenparaoficinas1: TMenuItem
        Caption = 'Gestionar men'#250' para oficinas'
        OnClick = Gestionarmenparaoficinas1Click
      end
      object Gestinderecetas1: TMenuItem
        Caption = 'Gesti'#243'n de recetas'
        OnClick = Gestinderecetas1Click
      end
      object Frecuencias1: TMenuItem
        Caption = 'Frecuencias'
        OnClick = Frecuencias1Click
      end
    end
    object Alarmas1: TMenuItem
      Caption = 'Alarmas'
      object Configurarunaalarma1: TMenuItem
        Caption = 'Configurar una alarma'
        OnClick = Configurarunaalarma1Click
      end
      object Gestionaralarmas1: TMenuItem
        Caption = 'Gestionar alarmas'
        OnClick = Gestionaralarmas1Click
      end
    end
    object Facturacin1: TMenuItem
      Caption = 'Facturaci'#243'n'
      object Emitirfacturaselectrnicas1: TMenuItem
        Caption = 'Emitir facturas electr'#243'nicas'
        OnClick = Emitirfacturaselectrnicas1Click
      end
      object Verfacturasemitidas1: TMenuItem
        Caption = 'Ver facturas emitidas'
        OnClick = Verfacturasemitidas1Click
      end
      object Facturacinmensual1: TMenuItem
        Caption = 'Facturaci'#243'n mensual...'
        OnClick = Facturacinmensual1Click
      end
    end
    object Acercade1: TMenuItem
      Caption = 'Acerca de...'
      object Configuracionesdeprograma1: TMenuItem
        Caption = 'Configuraciones de programa'
        OnClick = Configuracionesdeprograma1Click
      end
      object Gestindeprecioes1: TMenuItem
        Caption = 'Gesti'#243'n de precios'
        OnClick = Gestindeprecioes1Click
      end
      object Gestiondeproductos1: TMenuItem
        Caption = 'Gestion de productos'
        OnClick = Gestiondeproductos1Click
      end
      object GestiondeGastos1: TMenuItem
        Caption = 'Gestion de Gastos'
        OnClick = GestiondeGastos1Click
      end
      object Ingredientes1: TMenuItem
        Caption = 'Ingredientes'
        OnClick = Ingredientes1Click
      end
      object Composiciondecomidas1: TMenuItem
        Caption = 'Composicion de comidas'
        OnClick = Composiciondecomidas1Click
      end
      object InformacionNutricional1: TMenuItem
        Caption = 'Informacion Nutricional'
        OnClick = InformacionNutricional1Click
      end
    end
  end
end
