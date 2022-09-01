object fCuentas: TfCuentas
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Revisar estado de cuenta'
  ClientHeight = 658
  ClientWidth = 932
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 281
    Top = 33
    Width = 643
    Height = 134
  end
  object Label1: TLabel
    Left = 291
    Top = 81
    Width = 42
    Height = 16
    Caption = 'Label1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 291
    Top = 136
    Width = 42
    Height = 16
    Caption = 'Label1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 291
    Top = 109
    Width = 42
    Height = 16
    Caption = 'Label1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 291
    Top = 45
    Width = 54
    Height = 19
    Caption = 'Label4'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label6: TLabel
    Left = 387
    Top = 176
    Width = 111
    Height = 13
    Caption = 'CTRL + F1 para buscar'
  end
  object DBGrid1: TDBGrid
    Left = 4
    Top = 201
    Width = 920
    Height = 449
    DataSource = DataSource1
    PopupMenu = PopupMenu2
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDrawColumnCell = DBGrid1DrawColumnCell
    OnKeyDown = DBGrid1KeyDown
    OnKeyPress = DBGrid1KeyPress
    Columns = <
      item
        Expanded = False
        FieldName = 'fecha'
        Title.Alignment = taCenter
        Title.Caption = 'Fecha'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 120
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'unidades'
        Title.Alignment = taCenter
        Title.Caption = 'Unid.'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 80
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'pagoRealizado'
        Title.Alignment = taCenter
        Title.Caption = 'Pago'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 80
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'valorUnidad'
        Title.Alignment = taCenter
        Title.Caption = 'Valor Unid.'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 81
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'rep'
        Title.Alignment = taCenter
        Title.Caption = 'Entreg'#243
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 86
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'fechaIngresoPago'
        Title.Alignment = taCenter
        Title.Caption = 'Fecha Pago'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 77
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'medioDePago'
        PickList.Strings = (
          'A- Efectivo'
          'B - Banco Oscar'
          'C - Banco Monica'
          'D - Banco Williams'
          'M - MercadoPago Oscar'
          'N - MercadoPago Monica')
        Title.Alignment = taCenter
        Title.Caption = 'Medio Pago'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 84
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'obs'
        Title.Alignment = taCenter
        Title.Caption = 'Obs.'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 459
        Visible = True
      end>
  end
  object MC: TMonthCalendar
    Left = 8
    Top = 4
    Width = 260
    Height = 160
    MultiSelect = True
    Date = 43949.281096805560000000
    EndDate = 43949.000000000000000000
    MaxSelectRange = 500
    PopupMenu = PopupMenu1
    ShowToday = False
    ShowTodayCircle = False
    TabOrder = 1
    OnClick = MCClick
  end
  object Button2: TButton
    Left = 42
    Top = 170
    Width = 89
    Height = 25
    Caption = 'Anterior'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 146
    Top = 170
    Width = 87
    Height = 25
    Caption = 'Siguiente'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button1: TButton
    Left = 281
    Top = 4
    Width = 113
    Height = 25
    Caption = 'Seleccionar cliente'
    TabOrder = 4
    OnClick = Button1Click
  end
  object CheckBox1: TCheckBox
    Left = 250
    Top = 175
    Width = 130
    Height = 17
    Caption = 'Incluir d'#237'as sin actividad'
    TabOrder = 5
    OnClick = CheckBox1Click
  end
  object Button4: TButton
    Left = 784
    Top = 174
    Width = 140
    Height = 20
    Caption = 'Forzar recalculo de saldo'
    TabOrder = 6
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 585
    Top = 174
    Width = 193
    Height = 20
    Caption = 'Forzar calculo de todos los clientes'
    TabOrder = 7
    Visible = False
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 402
    Top = 4
    Width = 113
    Height = 25
    Caption = 'Modificar cliente'
    TabOrder = 8
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 524
    Top = 4
    Width = 113
    Height = 25
    Caption = 'Imprimir detalle'
    TabOrder = 9
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 781
    Top = 4
    Width = 143
    Height = 25
    Caption = 'Imprimir factura (FISCAL)'
    TabOrder = 10
    OnClick = Button8Click
  end
  object Button10: TButton
    Left = 646
    Top = 4
    Width = 113
    Height = 25
    Caption = 'Resumen WhatsApp'
    TabOrder = 11
    OnClick = Button10Click
  end
  object Panel1: TPanel
    Left = 304
    Top = 288
    Width = 353
    Height = 240
    Caption = 'Panel1'
    Color = 16567753
    ParentBackground = False
    ShowCaption = False
    TabOrder = 12
    object Label5: TLabel
      Left = 0
      Top = 15
      Width = 353
      Height = 18
      Alignment = taCenter
      AutoSize = False
      Caption = 'Rastrear un cliente (por comentario)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit1: TEdit
      Left = 83
      Top = 62
      Width = 185
      Height = 21
      TabOrder = 0
      Text = 'Edit1'
      OnChange = Edit1Change
    end
    object Button9: TButton
      Left = 83
      Top = 200
      Width = 185
      Height = 25
      Caption = 'Ocultar'
      TabOrder = 1
      OnClick = Button9Click
    end
    object DBGrid2: TDBGrid
      Left = 83
      Top = 89
      Width = 185
      Height = 105
      DataSource = DataSource2
      ParentShowHint = False
      ReadOnly = True
      ShowHint = False
      TabOrder = 2
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnDblClick = DBGrid2DblClick
      Columns = <
        item
          Expanded = False
          FieldName = 'cliente'
          Title.Alignment = taCenter
          Title.Caption = 'Cliente'
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -12
          Title.Font.Name = 'Tahoma'
          Title.Font.Style = [fsBold]
          Width = 153
          Visible = True
        end>
    end
  end
  object Button11: TButton
    Left = 504
    Top = 174
    Width = 75
    Height = 20
    Caption = 'Importar CSV'
    TabOrder = 13
    OnClick = Button11Click
  end
  object DataSource1: TDataSource
    DataSet = CDS
    Left = 834
    Top = 96
  end
  object CDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 782
    Top = 104
    object CDSidCuenta: TIntegerField
      FieldName = 'idCuenta'
      ReadOnly = True
    end
    object CDSfecha: TDateField
      FieldName = 'fecha'
      ReadOnly = True
      DisplayFormat = 'dddd dd/mm/yyyy'
    end
    object CDSunidades: TFMTBCDField
      FieldName = 'unidades'
      OnChange = CDSunidadesChange
      DisplayFormat = '0.00'
    end
    object CDSpagoRealizado: TFMTBCDField
      FieldName = 'pagoRealizado'
      OnChange = CDSpagoRealizadoChange
      DisplayFormat = '$ 0.00'
    end
    object CDSvalorUnidad: TFMTBCDField
      FieldName = 'valorUnidad'
      OnChange = CDSvalorUnidadChange
      DisplayFormat = '$ 0.00'
    end
    object CDSobs: TWideStringField
      FieldName = 'obs'
      OnChange = CDSobsChange
      Size = 100
    end
    object CDSrep: TWideStringField
      FieldName = 'rep'
      Size = 5
    end
    object CDSfechaIngresoPago: TDateField
      FieldName = 'fechaIngresoPago'
      OnChange = CDSfechaIngresoPagoChange
      OnGetText = CDSfechaIngresoPagoGetText
      DisplayFormat = 'dd/mm/yyyy'
      EditMask = '!99/99/0000;1;_'
    end
    object CDSmedioDePago: TWideStringField
      FieldName = 'medioDePago'
      OnChange = CDSmedioDePagoChange
      OnGetText = CDSmedioDePagoGetText
      Size = 1
    end
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 730
    Top = 104
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 682
    Top = 64
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
      'User_Name=root'
      'Password=CBR900rr'
      'ServerCharSet=utf8'
      'BlobSize=-1'
      'ErrorResourceFile='
      'LocaleCode=0000'
      'Compressed=False'
      'Encrypted=False'
      'ConnectTimeout=60')
    Left = 600
    Top = 72
  end
  object QueryAux: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 954
    Top = 96
  end
  object QueryUpdate: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 830
    Top = 40
  end
  object PopupMenu1: TPopupMenu
    Left = 80
    Top = 24
    object Mostrarestasemana1: TMenuItem
      Caption = 'Mostrar per'#237'odo actual'
      OnClick = Mostrarestasemana1Click
    end
  end
  object PopupMenu2: TPopupMenu
    Left = 56
    Top = 264
    object Verpedidosdeesteda1: TMenuItem
      Caption = 'Ver pedidos de este d'#237'a'
      OnClick = Verpedidosdeesteda1Click
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 456
    Top = 8
  end
  object Query2: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 450
    Top = 128
  end
  object DataSetProvider2: TDataSetProvider
    DataSet = Query2
    Left = 490
    Top = 128
  end
  object CDS2: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider2'
    Left = 534
    Top = 128
    object CDS2refCliente: TIntegerField
      FieldName = 'refCliente'
    end
    object CDS2cliente: TWideStringField
      FieldName = 'cliente'
      Size = 60
    end
  end
  object DataSource2: TDataSource
    DataSet = CDS2
    Left = 578
    Top = 128
  end
  object OD1: TOpenDialog
    DefaultExt = '.csv'
    Filter = '*.csv'
    Top = 152
  end
end
