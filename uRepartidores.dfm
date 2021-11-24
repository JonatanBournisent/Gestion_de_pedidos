object fRepartidores: TfRepartidores
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Administrar repartidores'
  ClientHeight = 338
  ClientWidth = 559
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
  object Button3: TButton
    Left = 330
    Top = 303
    Width = 161
    Height = 25
    Caption = 'Salir'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button1: TButton
    Left = 56
    Top = 303
    Width = 161
    Height = 25
    Caption = 'Agregar un repartidor'
    TabOrder = 1
    OnClick = Button1Click
  end
  object DBGrid1: TDBGrid
    Left = 5
    Top = 8
    Width = 550
    Height = 289
    Hint = 'Tildar "S" si el repartidor tambi'#233'n reparte los s'#225'bados'
    DataSource = DataSource1
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnColExit = DBGrid1ColExit
    OnDrawColumnCell = DBGrid1DrawColumnCell
    OnKeyDown = DBGrid1KeyDown
    Columns = <
      item
        Expanded = False
        FieldName = 'descripcion'
        Title.Alignment = taCenter
        Title.Caption = 'Nombre'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 151
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'nombreCorto'
        Title.Alignment = taCenter
        Title.Caption = 'Nombre corto'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 101
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'horario1'
        Title.Alignment = taCenter
        Title.Caption = '1'#176' Rep.'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 126
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'horario2'
        Title.Alignment = taCenter
        Title.Caption = '2'#176' Rep.'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 115
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'reparteSabados'
        Title.Alignment = taCenter
        Title.Caption = 'S'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 19
        Visible = True
      end>
  end
  object CB: TDBCheckBox
    Left = 518
    Top = 28
    Width = 14
    Height = 17
    DataField = 'reparteSabados'
    DataSource = DataSource1
    TabOrder = 4
    ValueChecked = '1'
    ValueUnchecked = '0'
    Visible = False
    OnClick = CBClick
  end
  object Panel1: TPanel
    Left = 3
    Top = 4
    Width = 553
    Height = 330
    Caption = 'Panel1'
    Color = 16706003
    ParentBackground = False
    ShowCaption = False
    TabOrder = 2
    Visible = False
    object Label1: TLabel
      Left = 88
      Top = 102
      Width = 37
      Height = 13
      Caption = 'Nombre'
    end
    object Label2: TLabel
      Left = 88
      Top = 174
      Width = 65
      Height = 13
      Caption = 'Nombre corto'
    end
    object Label3: TLabel
      Left = 3
      Top = 16
      Width = 529
      Height = 57
      Alignment = taCenter
      AutoSize = False
      Caption = 
        'ATENCI'#211'N: Los repartidores no se pueden eliminar. Agregar solo c' +
        'uando sea requerido'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      WordWrap = True
    end
    object Button2: TButton
      Left = 56
      Top = 264
      Width = 177
      Height = 25
      Caption = 'Confirmar'
      TabOrder = 0
      OnClick = Button2Click
    end
    object Edit1: TEdit
      Left = 176
      Top = 99
      Width = 177
      Height = 21
      MaxLength = 15
      TabOrder = 1
      Text = 'Edit1'
    end
    object Edit2: TEdit
      Left = 176
      Top = 171
      Width = 121
      Height = 21
      MaxLength = 5
      TabOrder = 2
      Text = 'Edit2'
    end
    object Button4: TButton
      Left = 295
      Top = 264
      Width = 177
      Height = 25
      Caption = 'Cancelar'
      TabOrder = 3
      OnClick = Button4Click
    end
  end
  object DataSource1: TDataSource
    DataSet = CDS
    Left = 338
    Top = 264
  end
  object CDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    OnNewRecord = CDSNewRecord
    Left = 250
    Top = 248
    object CDSidRepartidor: TIntegerField
      FieldName = 'idRepartidor'
    end
    object CDSdescripcion: TWideStringField
      FieldName = 'descripcion'
      OnChange = CDSdescripcionChange
    end
    object CDSnombreCorto: TWideStringField
      DisplayWidth = 5
      FieldName = 'nombreCorto'
      OnChange = CDSnombreCortoChange
      Size = 5
    end
    object CDShorario1: TSQLTimeStampField
      FieldName = 'horario1'
      OnChange = CDShorario1Change
      DisplayFormat = 'HH:mm'
      EditMask = '!90:00;1;_'
    end
    object CDShorario2: TSQLTimeStampField
      FieldName = 'horario2'
      OnChange = CDShorario2Change
      DisplayFormat = 'HH:mm'
      EditMask = '!90:00;1;_'
    end
    object CDSreparteSabados: TByteField
      FieldName = 'reparteSabados'
    end
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 186
    Top = 256
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 122
    Top = 256
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
    Top = 248
  end
  object QueryUpdate: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 426
    Top = 248
  end
end
