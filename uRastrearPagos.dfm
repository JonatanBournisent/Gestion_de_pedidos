object fRastrearPagos: TfRastrearPagos
  Left = 0
  Top = 0
  Caption = 'Rastreo de pagos ingresados'
  ClientHeight = 625
  ClientWidth = 1119
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 16
    Width = 260
    Height = 14
    Alignment = taCenter
    AutoSize = False
    Caption = 'Rango de fechas'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 288
    Top = 16
    Width = 153
    Height = 14
    AutoSize = False
    Caption = 'Monto del pago buscado'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 288
    Top = 88
    Width = 128
    Height = 14
    AutoSize = False
    Caption = 'Comentario del pago'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 453
    Top = 48
    Width = 151
    Height = 13
    Caption = '($ 0,00 para omitir este campo)'
  end
  object Label5: TLabel
    Left = 623
    Top = 111
    Width = 200
    Height = 13
    Caption = '(Borrar contenido para omitir este campo)'
  end
  object MC: TMonthCalendar
    Left = 8
    Top = 42
    Width = 260
    Height = 160
    MultiSelect = True
    Date = 43949.580062210650000000
    EndDate = 43949.000000000000000000
    MaxSelectRange = 500
    ShowToday = False
    ShowTodayCircle = False
    TabOrder = 0
  end
  object DBGrid1: TDBGrid
    Left = 8
    Top = 208
    Width = 1103
    Height = 411
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
        FieldName = 'cliente'
        Title.Alignment = taCenter
        Title.Caption = 'Cliente'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 182
        Visible = True
      end
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
        Width = 62
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
  object Edit1: TEdit
    Left = 288
    Top = 42
    Width = 153
    Height = 27
    Alignment = taCenter
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    Text = 'Edit1'
    OnClick = Edit1Click
    OnEnter = Edit1Enter
    OnExit = Edit1Exit
    OnKeyPress = Edit1KeyPress
  end
  object Button2: TButton
    Left = 288
    Top = 158
    Width = 121
    Height = 25
    Caption = 'Buscar'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Edit2: TEdit
    Left = 288
    Top = 108
    Width = 321
    Height = 21
    TabOrder = 4
    Text = 'Edit2'
  end
  object QueryAux: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 954
    Top = 96
  end
  object DataSource1: TDataSource
    DataSet = CDS
    Left = 914
    Top = 96
  end
  object CDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 806
    Top = 16
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
      DisplayFormat = '0.00'
    end
    object CDSpagoRealizado: TFMTBCDField
      FieldName = 'pagoRealizado'
      DisplayFormat = '$ 0.00'
    end
    object CDSvalorUnidad: TFMTBCDField
      FieldName = 'valorUnidad'
      DisplayFormat = '$ 0.00'
    end
    object CDSobs: TWideStringField
      FieldName = 'obs'
      Size = 100
    end
    object CDSrep: TWideStringField
      FieldName = 'rep'
      Size = 5
    end
    object CDScliente: TWideStringField
      FieldName = 'cliente'
      Size = 45
    end
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 698
    Top = 16
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
    Left = 720
    Top = 8
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 738
    Top = 16
  end
end
