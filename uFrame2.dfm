object Frame2: TFrame2
  Left = 0
  Top = 0
  Width = 556
  Height = 166
  Color = 11581943
  ParentBackground = False
  ParentColor = False
  TabOrder = 0
  object Label1: TLabel
    Left = 3
    Top = 8
    Width = 36
    Height = 13
    Caption = 'Buscar:'
  end
  object Label2: TLabel
    Left = 225
    Top = 8
    Width = 137
    Height = 13
    Caption = '(doble click para seleccionar)'
  end
  object Edit1: TEdit
    Left = 45
    Top = 5
    Width = 166
    Height = 21
    TabOrder = 0
    OnChange = Edit1Change
    OnKeyDown = Edit1KeyDown
    OnKeyPress = Edit1KeyPress
  end
  object DBGrid1: TDBGrid
    Left = 3
    Top = 32
    Width = 551
    Height = 129
    DataSource = DataSource1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    TabOrder = 1
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
        FieldName = 'calle'
        Title.Alignment = taCenter
        Title.Caption = 'Calle'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 138
        Visible = True
      end
      item
        Alignment = taRightJustify
        Expanded = False
        FieldName = 'numero'
        Title.Alignment = taCenter
        Title.Caption = 'N'#250'mero'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 83
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'nombre'
        Title.Alignment = taCenter
        Title.Caption = 'Nombre'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 143
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'apellido'
        Title.Alignment = taCenter
        Title.Caption = 'Apellido'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 147
        Visible = True
      end>
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 709
    Top = 16
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 669
    Top = 96
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    ReadOnly = True
    Left = 773
    Top = 56
  end
  object DataSource1: TDataSource
    DataSet = ClientDataSet1
    Left = 662
    Top = 48
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
    Left = 589
    Top = 24
  end
end
