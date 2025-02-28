object fDatos: TfDatos
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Consultar datos de ventas'
  ClientHeight = 639
  ClientWidth = 700
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Shape2: TShape
    Left = 8
    Top = 528
    Width = 562
    Height = 104
    Brush.Style = bsClear
  end
  object Shape1: TShape
    Left = 8
    Top = 377
    Width = 562
    Height = 145
    Brush.Style = bsClear
  end
  object Label1: TLabel
    Left = 24
    Top = 586
    Width = 31
    Height = 13
    Caption = 'Label1'
  end
  object Label2: TLabel
    Left = 24
    Top = 392
    Width = 31
    Height = 13
    Caption = 'Label2'
  end
  object Label3: TLabel
    Left = 24
    Top = 424
    Width = 31
    Height = 13
    Caption = 'Label3'
  end
  object Label4: TLabel
    Left = 24
    Top = 539
    Width = 31
    Height = 13
    Caption = 'Label4'
  end
  object Label5: TLabel
    Left = 24
    Top = 562
    Width = 31
    Height = 13
    Caption = 'Label5'
  end
  object Label6: TLabel
    Left = 24
    Top = 457
    Width = 31
    Height = 13
    Caption = 'Label6'
  end
  object Label7: TLabel
    Left = 24
    Top = 490
    Width = 31
    Height = 13
    Caption = 'Label7'
  end
  object Label8: TLabel
    Left = 400
    Top = 152
    Width = 44
    Height = 13
    Caption = 'Limitar a:'
  end
  object Shape3: TShape
    Left = 395
    Top = 102
    Width = 175
    Height = 74
    Brush.Style = bsClear
  end
  object Label9: TLabel
    Left = 24
    Top = 610
    Width = 31
    Height = 13
    Caption = 'Label9'
  end
  object Button1: TButton
    Left = 271
    Top = 8
    Width = 113
    Height = 168
    Caption = 'Consultar'
    TabOrder = 0
    OnClick = Button1Click
  end
  object DBGrid1: TDBGrid
    Left = 9
    Top = 187
    Width = 562
    Height = 184
    DataSource = DataSource1
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'repartidor'
        Title.Alignment = taCenter
        Title.Caption = 'Repartidor'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 126
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'cantViandas'
        Title.Alignment = taCenter
        Title.Caption = 'Cant Viand'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 83
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'cantDomicilios'
        Title.Alignment = taCenter
        Title.Caption = 'Cant Dom'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 95
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'montoVentas'
        Title.Alignment = taCenter
        Title.Caption = '$ Entregado'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 104
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'cobro'
        Title.Alignment = taCenter
        Title.Caption = '$ Cobrado'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 113
        Visible = True
      end>
  end
  object MC: TMonthCalendar
    Left = 8
    Top = 1
    Width = 257
    Height = 160
    MultiSelect = True
    Date = 44044.357865115740000000
    EndDate = 44044.000000000000000000
    MaxSelectRange = 3000
    ShowToday = False
    TabOrder = 2
  end
  object Button2: TButton
    Left = 395
    Top = 8
    Width = 175
    Height = 20
    Caption = 'Ventas por d'#237'a'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 395
    Top = 54
    Width = 175
    Height = 20
    Caption = 'Ventas por horario'
    TabOrder = 4
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 395
    Top = 77
    Width = 175
    Height = 20
    Caption = 'Cobros por d'#237'a'
    TabOrder = 5
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 400
    Top = 107
    Width = 82
    Height = 36
    Caption = 'Comidas mas vendidas'
    TabOrder = 6
    WordWrap = True
    OnClick = Button5Click
  end
  object SpinEdit1: TSpinEdit
    Left = 452
    Top = 149
    Width = 73
    Height = 22
    MaxValue = 150
    MinValue = 1
    TabOrder = 7
    Value = 30
  end
  object Button7: TButton
    Left = 483
    Top = 107
    Width = 82
    Height = 36
    Caption = 'Clientes que mas compraron'
    TabOrder = 9
    WordWrap = True
    OnClick = Button7Click
  end
  object Panel1: TPanel
    Left = 720
    Top = 31
    Width = 328
    Height = 449
    Caption = 'Panel1'
    Color = 12303359
    ParentBackground = False
    ShowCaption = False
    TabOrder = 8
    Visible = False
    object DBGrid2: TDBGrid
      Left = 8
      Top = 8
      Width = 313
      Height = 400
      DataSource = DataSource2
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
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
          Width = 208
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'cantViandas'
          Title.Alignment = taCenter
          Title.Caption = 'Viandas'
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -12
          Title.Font.Name = 'Tahoma'
          Title.Font.Style = [fsBold]
          Width = 71
          Visible = True
        end>
    end
    object Button6: TButton
      Left = 120
      Top = 414
      Width = 91
      Height = 25
      Caption = 'Cerrar'
      TabOrder = 1
      OnClick = Button6Click
    end
  end
  object Button8: TButton
    Left = 395
    Top = 31
    Width = 176
    Height = 20
    Caption = 'Ventas por mes (beta)'
    TabOrder = 10
    OnClick = Button8Click
  end
  object CheckBox1: TCheckBox
    Left = 584
    Top = 32
    Width = 108
    Height = 17
    Caption = 'Grafico de barras'
    Checked = True
    State = cbChecked
    TabOrder = 11
  end
  object CheckBox2: TCheckBox
    Left = 584
    Top = 55
    Width = 108
    Height = 17
    Caption = 'Grafico de lineas'
    TabOrder = 12
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
    Left = 64
    Top = 34
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 128
    Top = 42
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 200
    Top = 42
  end
  object CDS1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    ReadOnly = True
    Left = 240
    Top = 42
    object CDS1repartidor: TWideStringField
      FieldName = 'repartidor'
      Size = 0
    end
    object CDS1cobro: TFMTBCDField
      FieldName = 'cobro'
      DisplayFormat = '$ 0.00'
    end
    object CDS1montoVentas: TFMTBCDField
      FieldName = 'montoVentas'
      DisplayFormat = '$ 0.00'
    end
    object CDS1cantDomicilios: TLargeintField
      FieldName = 'cantDomicilios'
    end
    object CDS1cantViandas: TFMTBCDField
      FieldName = 'cantViandas'
      Size = 15
    end
  end
  object DataSource1: TDataSource
    DataSet = CDS1
    Left = 280
    Top = 42
  end
  object QueryAux: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 256
    Top = 120
  end
  object Query2: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 704
    Top = 104
  end
  object DataSetProvider2: TDataSetProvider
    DataSet = Query2
    Left = 768
    Top = 104
  end
  object CDS2: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider2'
    ReadOnly = True
    Left = 816
    Top = 104
    object CDS2cliente: TWideStringField
      FieldName = 'cliente'
      Size = 45
    end
    object CDS2cantViandas: TFMTBCDField
      FieldName = 'cantViandas'
      DisplayFormat = '0.00'
      Size = 10
    end
  end
  object DataSource2: TDataSource
    DataSet = CDS2
    Left = 856
    Top = 104
  end
end
