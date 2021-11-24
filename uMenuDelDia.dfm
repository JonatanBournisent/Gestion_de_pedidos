object fMenuDelDia: TfMenuDelDia
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Seleccionar men'#250' del d'#237'a'
  ClientHeight = 530
  ClientWidth = 536
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
  object Bevel3: TBevel
    Left = 6
    Top = 8
    Width = 523
    Height = 513
  end
  object Bevel1: TBevel
    Left = 18
    Top = 33
    Width = 503
    Height = 276
  end
  object Bevel2: TBevel
    Left = 18
    Top = 361
    Width = 503
    Height = 85
  end
  object Label1: TLabel
    Left = 168
    Top = 14
    Width = 80
    Height = 13
    Caption = 'Plato principal'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 168
    Top = 342
    Width = 79
    Height = 13
    Caption = 'Complemento'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
  end
  object Comida1: TDBLookupComboBox
    Left = 26
    Top = 41
    Width = 368
    Height = 21
    DataField = 'refComida1'
    DataSource = DataSource1
    KeyField = 'idComida'
    ListField = 'nombre'
    ListSource = DataSource2
    TabOrder = 11
    OnClick = Comida1Click
  end
  object Comida2: TDBLookupComboBox
    Left = 26
    Top = 88
    Width = 368
    Height = 21
    DataField = 'refComida2'
    DataSource = DataSource1
    KeyField = 'idComida'
    ListField = 'nombre'
    ListSource = DataSource2
    TabOrder = 12
    OnClick = Comida2Click
  end
  object Comida3: TDBLookupComboBox
    Left = 26
    Top = 136
    Width = 368
    Height = 21
    DataField = 'refComida3'
    DataSource = DataSource1
    KeyField = 'idComida'
    ListField = 'nombre'
    ListSource = DataSource2
    TabOrder = 13
    OnClick = Comida3Click
  end
  object Comida4: TDBLookupComboBox
    Left = 26
    Top = 184
    Width = 368
    Height = 21
    DataField = 'refComida4'
    DataSource = DataSource1
    KeyField = 'idComida'
    ListField = 'nombre'
    ListSource = DataSource2
    TabOrder = 14
    OnClick = Comida4Click
  end
  object Comida5: TDBLookupComboBox
    Left = 26
    Top = 232
    Width = 368
    Height = 21
    DataField = 'refComida5'
    DataSource = DataSource1
    KeyField = 'idComida'
    ListField = 'nombre'
    ListSource = DataSource2
    TabOrder = 15
    OnClick = Comida5Click
  end
  object Comida6: TDBLookupComboBox
    Left = 26
    Top = 280
    Width = 368
    Height = 21
    DataField = 'refComida6'
    DataSource = DataSource1
    KeyField = 'idComida'
    ListField = 'nombre'
    ListSource = DataSource2
    TabOrder = 16
    OnClick = Comida6Click
  end
  object Comida7: TDBLookupComboBox
    Left = 26
    Top = 368
    Width = 368
    Height = 21
    DataField = 'refComida7'
    DataSource = DataSource1
    KeyField = 'idComida'
    ListField = 'nombre'
    ListSource = DataSource2
    TabOrder = 17
    OnClick = Comida7Click
  end
  object Comida8: TDBLookupComboBox
    Left = 26
    Top = 417
    Width = 368
    Height = 21
    DataField = 'refComida8'
    DataSource = DataSource1
    KeyField = 'idComida'
    ListField = 'nombre'
    ListSource = DataSource2
    TabOrder = 18
    OnClick = Comida8Click
  end
  object Button1: TButton
    Left = 34
    Top = 474
    Width = 113
    Height = 27
    Caption = 'Guardar cambios'
    TabOrder = 8
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 210
    Top = 474
    Width = 113
    Height = 27
    Caption = 'Descartar cambios'
    TabOrder = 9
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 392
    Top = 474
    Width = 113
    Height = 27
    Caption = 'Borrar este men'#250
    TabOrder = 10
    OnClick = Button3Click
  end
  object Button7: TButton
    Left = 400
    Top = 40
    Width = 113
    Height = 23
    Caption = 'Seleccionar'
    TabOrder = 0
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 400
    Top = 87
    Width = 113
    Height = 23
    Caption = 'Seleccionar'
    TabOrder = 1
    OnClick = Button8Click
  end
  object Button9: TButton
    Left = 400
    Top = 135
    Width = 113
    Height = 23
    Caption = 'Seleccionar'
    TabOrder = 2
    OnClick = Button9Click
  end
  object Button10: TButton
    Left = 400
    Top = 183
    Width = 113
    Height = 23
    Caption = 'Seleccionar'
    TabOrder = 3
    OnClick = Button10Click
  end
  object Button11: TButton
    Left = 400
    Top = 231
    Width = 113
    Height = 23
    Caption = 'Seleccionar'
    TabOrder = 4
    OnClick = Button11Click
  end
  object Button12: TButton
    Left = 400
    Top = 279
    Width = 113
    Height = 23
    Caption = 'Seleccionar'
    TabOrder = 5
    OnClick = Button12Click
  end
  object Button13: TButton
    Left = 400
    Top = 367
    Width = 113
    Height = 23
    Caption = 'Seleccionar'
    TabOrder = 6
    OnClick = Button13Click
  end
  object Button14: TButton
    Left = 400
    Top = 416
    Width = 113
    Height = 23
    Caption = 'Seleccionar'
    TabOrder = 7
    OnClick = Button14Click
  end
  object Panel1: TPanel
    Left = 82
    Top = 135
    Width = 368
    Height = 259
    Caption = 'Panel1'
    Color = 12040191
    ParentBackground = False
    ShowCaption = False
    TabOrder = 19
    Visible = False
    object Label3: TLabel
      Left = 16
      Top = 5
      Width = 335
      Height = 37
      Alignment = taCenter
      AutoSize = False
      Caption = 
        'Las siguientes comidas se encuentran al menos una vez en las '#250'lt' +
        'imas dos semanas'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      WordWrap = True
    end
    object ListBox1: TListBox
      Left = 16
      Top = 46
      Width = 336
      Height = 180
      ItemHeight = 13
      TabOrder = 0
    end
    object Button5: TButton
      Left = 40
      Top = 230
      Width = 123
      Height = 25
      Caption = 'Corregir men'#250
      TabOrder = 1
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 202
      Top = 230
      Width = 123
      Height = 25
      Caption = 'Salir de todos modos'
      TabOrder = 2
      OnClick = Button6Click
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
    Left = 760
    Top = 104
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
    Top = 168
    object ClientDataSet1refComida1: TIntegerField
      FieldName = 'refComida1'
    end
    object ClientDataSet1refComida2: TIntegerField
      FieldName = 'refComida2'
    end
    object ClientDataSet1refComida3: TIntegerField
      FieldName = 'refComida3'
    end
    object ClientDataSet1refComida4: TIntegerField
      FieldName = 'refComida4'
    end
    object ClientDataSet1refComida5: TIntegerField
      FieldName = 'refComida5'
    end
    object ClientDataSet1refComida6: TIntegerField
      FieldName = 'refComida6'
    end
    object ClientDataSet1refComida7: TIntegerField
      FieldName = 'refComida7'
    end
    object ClientDataSet1refComida8: TIntegerField
      FieldName = 'refComida8'
    end
    object ClientDataSet1idMenuDelDia: TIntegerField
      FieldName = 'idMenuDelDia'
    end
  end
  object DataSource1: TDataSource
    DataSet = ClientDataSet1
    Left = 855
    Top = 168
  end
  object SQLTable1: TSQLTable
    MaxBlobSize = -1
    SQLConnection = SQLConnection1
    TableName = 'menudeldia'
    Left = 696
    Top = 168
  end
  object DataSetProvider2: TDataSetProvider
    DataSet = Query1
    Left = 744
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
    Left = 847
    Top = 224
  end
  object QueryAux: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 696
    Top = 288
  end
end
