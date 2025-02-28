object fFacturacionMensual: TfFacturacionMensual
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Lista de clientes para facturaci'#243'n electr'#243'nica mensual'
  ClientHeight = 644
  ClientWidth = 561
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
  object Label1: TLabel
    Left = 314
    Top = 8
    Width = 260
    Height = 14
    Alignment = taCenter
    AutoSize = False
    Caption = 'Per'#237'odo a facturar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 314
    Top = 296
    Width = 171
    Height = 13
    Caption = 'Directorio para guardar las facturas'
    Visible = False
  end
  object Label3: TLabel
    Left = 314
    Top = 331
    Width = 31
    Height = 13
    Caption = 'Label3'
    Visible = False
  end
  object DBGrid1: TDBGrid
    Left = 8
    Top = 8
    Width = 289
    Height = 628
    DataSource = DataSource1
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    PopupMenu = PopupMenu1
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = [fsBold]
    OnDblClick = DBGrid1DblClick
    Columns = <
      item
        Expanded = False
        FieldName = 'cliente'
        Title.Alignment = taCenter
        Title.Caption = 'Cliente'
        Width = 201
        Visible = True
      end
      item
        Alignment = taCenter
        DropDownRows = 4
        Expanded = False
        FieldName = 'tipo'
        PickList.Strings = (
          'O'
          'M'
          'W')
        Title.Alignment = taCenter
        Title.Caption = 'Emisor'
        Width = 53
        Visible = True
      end>
  end
  object MC: TMonthCalendar
    Left = 314
    Top = 24
    Width = 260
    Height = 160
    MultiSelect = True
    Date = 43949.394816365740000000
    EndDate = 43949.000000000000000000
    MaxSelectRange = 500
    PopupMenu = PopupMenu1
    ShowToday = False
    ShowTodayCircle = False
    TabOrder = 1
    OnClick = MCClick
  end
  object Button1: TButton
    Left = 348
    Top = 200
    Width = 191
    Height = 25
    Caption = 'Salir'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 314
    Top = 248
    Width = 239
    Height = 25
    Caption = 'Definir directorio para guardar facturas'
    TabOrder = 3
    Visible = False
    OnClick = Button2Click
  end
  object Memo1: TMemo
    Left = 504
    Top = 608
    Width = 49
    Height = 28
    Lines.Strings = (
      'Memo1')
    TabOrder = 4
    Visible = False
    WordWrap = False
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
    Left = 376
    Top = 378
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 432
    Top = 376
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 496
    Top = 376
  end
  object CDS1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 544
    Top = 376
    object CDS1idCliente: TIntegerField
      FieldName = 'idCliente'
    end
    object CDS1cliente: TWideStringField
      FieldName = 'cliente'
      Size = 40
    end
    object CDS1tipo: TWideStringField
      FieldName = 'tipo'
      OnChange = CDS1tipoChange
      Size = 1
    end
  end
  object DataSource1: TDataSource
    DataSet = CDS1
    Left = 584
    Top = 376
  end
  object QueryAux: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 464
    Top = 448
  end
  object PopupMenu1: TPopupMenu
    Left = 128
    Top = 184
    object Iraemitircomprobante1: TMenuItem
      Caption = 'Ir a emitir comprobante'
      OnClick = Iraemitircomprobante1Click
    end
    object Verdetalledecuenta1: TMenuItem
      Caption = 'Ver detalle de cuenta'
      OnClick = Verdetalledecuenta1Click
    end
    object Agregaruncliente1: TMenuItem
      Caption = 'Agregar un cliente a la lista'
      OnClick = Agregaruncliente1Click
    end
    object Quitaresteclientedelalista1: TMenuItem
      Caption = 'Quitar este cliente de la lista'
      OnClick = Quitaresteclientedelalista1Click
    end
    object EmitirCompMonotributo1: TMenuItem
      Caption = 'Emitir Comp. Monotributo'
      OnClick = EmitirCompMonotributo1Click
    end
  end
  object QueryUpdate: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 344
    Top = 432
  end
end
