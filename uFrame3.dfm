object Frame3: TFrame3
  Left = 0
  Top = 0
  Width = 579
  Height = 275
  TabOrder = 0
  object Label3: TLabel
    Left = 3
    Top = 6
    Width = 37
    Height = 13
    Caption = 'Nombre'
  end
  object Label4: TLabel
    Left = 3
    Top = 51
    Width = 33
    Height = 13
    Caption = 'C'#243'digo'
  end
  object Label5: TLabel
    Left = 3
    Top = 97
    Width = 47
    Height = 13
    Caption = 'Categor'#237'a'
  end
  object Label7: TLabel
    Left = 3
    Top = 160
    Width = 58
    Height = 13
    Caption = 'Descripci'#243'n:'
  end
  object Label9: TLabel
    Left = 273
    Top = 5
    Width = 140
    Height = 13
    Caption = 'Comidas similares existentes:'
  end
  object DBEdNombre: TDBEdit
    Left = 56
    Top = 3
    Width = 193
    Height = 21
    DataField = 'nombre'
    DataSource = DataSource1
    TabOrder = 0
    OnChange = DBEdNombreChange
  end
  object DBEdCodigo: TDBEdit
    Left = 56
    Top = 48
    Width = 193
    Height = 21
    DataField = 'codigo'
    DataSource = DataSource1
    MaxLength = 7
    TabOrder = 1
    OnChange = DBEdCodigoChange
  end
  object DBCategoria: TDBLookupComboBox
    Left = 56
    Top = 93
    Width = 193
    Height = 21
    DataField = 'refCategoriaComida'
    DataSource = DataSource1
    KeyField = 'idCategoriaComida'
    ListField = 'descripcion'
    ListSource = DataSource2
    TabOrder = 2
  end
  object DBGrid1: TDBGrid
    Left = 272
    Top = 24
    Width = 304
    Height = 241
    DataSource = DataSource4
    Enabled = False
    ReadOnly = True
    TabOrder = 4
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'nombre'
        Title.Alignment = taCenter
        Title.Caption = 'Nombre'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 199
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'codigo'
        Title.Alignment = taCenter
        Title.Caption = 'C'#243'digo'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 70
        Visible = True
      end>
  end
  object DBMemo1: TDBMemo
    Left = 3
    Top = 176
    Width = 246
    Height = 89
    DataField = 'descripcion'
    DataSource = DataSource1
    TabOrder = 3
  end
  object DBCheckBox1: TDBCheckBox
    Left = 14
    Top = 129
    Width = 131
    Height = 17
    Caption = 'Permite doble porci'#243'n'
    DataField = 'admiteDoble'
    DataSource = DataSource1
    TabOrder = 5
    ValueChecked = '1'
    ValueUnchecked = '0'
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
    Left = 776
    Top = 112
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 696
    Top = 224
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = SQLTable1
    Left = 752
    Top = 168
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 808
    Top = 176
  end
  object DataSource1: TDataSource
    DataSet = ClientDataSet1
    Left = 855
    Top = 168
  end
  object SQLTable1: TSQLTable
    MaxBlobSize = -1
    SQLConnection = SQLConnection1
    TableName = 'comidas'
    Left = 696
    Top = 168
  end
  object DataSetProvider2: TDataSetProvider
    DataSet = Query1
    Left = 776
    Top = 224
  end
  object ClientDataSet2: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider2'
    ReadOnly = True
    Left = 808
    Top = 224
  end
  object DataSource2: TDataSource
    DataSet = ClientDataSet2
    Left = 815
    Top = 224
  end
  object DataSetProvider4: TDataSetProvider
    DataSet = Query3
    Left = 776
    Top = 296
  end
  object ClientDataSet4: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider4'
    ReadOnly = True
    Left = 808
    Top = 296
  end
  object DataSource4: TDataSource
    DataSet = ClientDataSet4
    Left = 823
    Top = 296
  end
  object Query3: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 696
    Top = 296
  end
  object QueryAux: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 200
    Top = 104
  end
end
