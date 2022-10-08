object frameMenuOficina: TframeMenuOficina
  Left = 0
  Top = 0
  Width = 781
  Height = 169
  TabOrder = 0
  object Label1: TLabel
    Left = 2
    Top = 1
    Width = 77
    Height = 19
    Caption = 'Miercoles'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object DBGrid1: TDBGrid
    Left = 2
    Top = 24
    Width = 776
    Height = 142
    DataSource = DataSource1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    PopupMenu = PopupMenu1
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
    Columns = <
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'nroOpcion'
        Title.Alignment = taCenter
        Title.Caption = 'Op. N'#176
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 47
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'plato1'
        Title.Alignment = taCenter
        Title.Caption = 'Plato 1'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 290
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'plato2'
        Title.Alignment = taCenter
        Title.Caption = 'Plato 2'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 290
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'esLight'
        Title.Alignment = taCenter
        Title.Caption = 'Light'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 55
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'esVeggie'
        Title.Alignment = taCenter
        Title.Caption = 'Veggie'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 55
        Visible = True
      end>
  end
  object Panel1: TPanel
    Left = 189
    Top = 3
    Width = 545
    Height = 40
    Color = 10723580
    ParentBackground = False
    ShowCaption = False
    TabOrder = 1
    object Button3: TButton
      Left = 7
      Top = 8
      Width = 159
      Height = 25
      Caption = 'Seleccionar plato 1'
      TabOrder = 0
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 172
      Top = 8
      Width = 159
      Height = 25
      Caption = 'Seleccionar plato 2'
      TabOrder = 1
      OnClick = Button4Click
    end
    object CheckBox1: TCheckBox
      Left = 344
      Top = 12
      Width = 57
      Height = 17
      Caption = 'Es Light'
      TabOrder = 2
      OnClick = CheckBox1Click
    end
    object CheckBox2: TCheckBox
      Left = 416
      Top = 12
      Width = 65
      Height = 17
      Caption = 'Es Veggie'
      TabOrder = 3
      OnClick = CheckBox2Click
    end
    object Button5: TButton
      Left = 521
      Top = 3
      Width = 22
      Height = 22
      Caption = 'X'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = Button5Click
    end
  end
  object cerrado: TCheckBox
    Left = 740
    Top = 1
    Width = 38
    Height = 17
    Caption = 'Cerrado'
    TabOrder = 2
    Visible = False
    OnClick = cerradoClick
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
    Left = 640
    Top = 85
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 672
    Top = 85
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 696
    Top = 93
  end
  object CDS1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    ReadOnly = True
    Left = 720
    Top = 101
    object CDS1idMenuOficinas: TIntegerField
      FieldName = 'idMenuOficinas'
    end
    object CDS1plato1: TWideStringField
      FieldName = 'plato1'
      Size = 60
    end
    object CDS1plato2: TWideStringField
      FieldName = 'plato2'
      Size = 60
    end
    object CDS1esLight: TLargeintField
      FieldName = 'esLight'
      OnGetText = CDS1esLightGetText
    end
    object CDS1esVeggie: TLargeintField
      FieldName = 'esVeggie'
      OnGetText = CDS1esVeggieGetText
    end
    object CDS1nroOpcion: TIntegerField
      FieldName = 'nroOpcion'
    end
  end
  object DataSource1: TDataSource
    DataSet = CDS1
    Left = 742
    Top = 96
  end
  object QueryAux: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 664
    Top = 133
  end
  object QueryUpdate: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 696
    Top = 133
  end
  object PopupMenu1: TPopupMenu
    Top = 45
    object Moverhaciaarriba1: TMenuItem
      Caption = 'Mover hacia arriba'
      OnClick = Moverhaciaarriba1Click
    end
    object Moverhacaabajo1: TMenuItem
      Caption = 'Mover hacia abajo'
      OnClick = Moverhacaabajo1Click
    end
    object Agregaropcin1: TMenuItem
      Caption = 'Agregar opci'#243'n'
      OnClick = Agregaropcin1Click
    end
    object Eliminaropcin1: TMenuItem
      Caption = 'Eliminar opci'#243'n'
      OnClick = Eliminaropcin1Click
    end
    object Modificarestaopcin1: TMenuItem
      Caption = 'Modificar esta opci'#243'n'
      OnClick = Modificarestaopcin1Click
    end
  end
end
