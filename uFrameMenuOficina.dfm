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
    Left = 3
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
    Left = 406
    Top = 3
    Width = 372
    Height = 84
    Color = 10723580
    ParentBackground = False
    ShowCaption = False
    TabOrder = 1
    object Button3: TButton
      Left = 7
      Top = 11
      Width = 124
      Height = 25
      Caption = 'Seleccionar plato 1'
      TabOrder = 0
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 137
      Top = 11
      Width = 120
      Height = 25
      Caption = 'Seleccionar plato 2'
      TabOrder = 1
      OnClick = Button4Click
    end
    object CheckBox1: TCheckBox
      Left = 272
      Top = 15
      Width = 57
      Height = 17
      Caption = 'Es Light'
      TabOrder = 2
      OnClick = CheckBox1Click
    end
    object CheckBox2: TCheckBox
      Left = 272
      Top = 38
      Width = 65
      Height = 17
      Caption = 'Es Veggie'
      TabOrder = 3
      OnClick = CheckBox2Click
    end
    object Button5: TButton
      Left = 343
      Top = 9
      Width = 24
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
    object Button1: TButton
      Left = 343
      Top = 29
      Width = 24
      Height = 23
      Caption = '+'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 32
      Top = 42
      Width = 75
      Height = 25
      Caption = 'Elegir'
      TabOrder = 6
      OnClick = Button2Click
    end
    object Button6: TButton
      Left = 160
      Top = 40
      Width = 75
      Height = 25
      Caption = 'Elegir'
      TabOrder = 7
      OnClick = Button6Click
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
  object Memo1: TMemo
    Left = 549
    Top = 77
    Width = 185
    Height = 89
    Lines.Strings = (
      'Memo1')
    TabOrder = 3
    Visible = False
    WordWrap = False
  end
  object Panel2: TPanel
    Left = 152
    Top = 2
    Width = 248
    Height = 161
    Caption = 'Panel2'
    ParentBackground = False
    ShowCaption = False
    TabOrder = 4
    object DBGrid2: TDBGrid
      Left = 0
      Top = 0
      Width = 248
      Height = 161
      DataSource = DataSource2
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnDblClick = DBGrid2DblClick
      Columns = <
        item
          Expanded = False
          FieldName = 'nombre'
          Title.Alignment = taCenter
          Title.Caption = 'Comida'
          Width = 214
          Visible = True
        end>
    end
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
    Left = 750
    Top = 72
  end
  object QueryAux: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 560
    Top = 109
  end
  object QueryUpdate: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 696
    Top = 133
  end
  object PopupMenu1: TPopupMenu
    Left = 16
    Top = 61
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
    object Copiarestemen1: TMenuItem
      Caption = 'Copiar este men'#250
      OnClick = Copiarestemen1Click
    end
  end
  object QueryMenuNormal: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 480
    Top = 117
  end
  object CDS2: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider2'
    ReadOnly = True
    Left = 336
    Top = 101
    object CDS2idComida: TIntegerField
      FieldName = 'idComida'
    end
    object CDS2nombre: TWideStringField
      FieldName = 'nombre'
      Size = 100
    end
  end
  object DataSetProvider2: TDataSetProvider
    DataSet = QueryMenuNormal
    Left = 400
    Top = 109
  end
  object DataSource2: TDataSource
    DataSet = CDS2
    Left = 289
    Top = 112
  end
end
