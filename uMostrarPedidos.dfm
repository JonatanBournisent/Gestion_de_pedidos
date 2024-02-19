object fMostrarPedidos: TfMostrarPedidos
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Mostrar todos los pedidos de la fecha seleccionada'
  ClientHeight = 688
  ClientWidth = 890
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
  object Label1: TLabel
    Left = 211
    Top = 12
    Width = 667
    Height = 13
    Caption = 
      'E: Indica si la etiqueta esta tildada como impresa | C: Indica s' +
      'i la etiqueta del complemento esta tildada como impresa'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object DBGrid1: TDBGrid
    Left = 8
    Top = 62
    Width = 873
    Height = 619
    DataSource = DataSource2
    PopupMenu = PopupMenu1
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnColExit = DBGrid1ColExit
    OnDrawColumnCell = DBGrid1DrawColumnCell
    Columns = <
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'hora'
        Title.Alignment = taCenter
        Title.Caption = 'Hora'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 90
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'cliente'
        Title.Alignment = taCenter
        Title.Caption = 'Cliente'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 160
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'com1'
        Title.Alignment = taCenter
        Title.Caption = 'C'#243'digo 1'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 90
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'com2'
        Title.Alignment = taCenter
        Title.Caption = 'C'#243'digo 2'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 90
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'com3'
        Title.Alignment = taCenter
        Title.Caption = 'C'#243'digo 3'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 90
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'com4'
        Title.Alignment = taCenter
        Title.Caption = 'C'#243'digo 4'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 90
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'Comentario'
        Title.Alignment = taCenter
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 185
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'etiquetaImpresa'
        Title.Alignment = taCenter
        Title.Caption = 'E'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 18
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'complementoImpreso'
        Title.Alignment = taCenter
        Title.Caption = 'C'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 18
        Visible = True
      end>
  end
  object DTP: TDateTimePicker
    Left = 8
    Top = 8
    Width = 186
    Height = 21
    Date = 44010.714507303240000000
    Time = 44010.714507303240000000
    TabOrder = 1
    OnChange = DTPChange
  end
  object CBE: TDBCheckBox
    Left = 824
    Top = 56
    Width = 14
    Height = 17
    DataField = 'etiquetaImpresa'
    DataSource = DataSource2
    TabOrder = 2
    ValueChecked = '1'
    ValueUnchecked = '0'
    Visible = False
  end
  object CBC: TDBCheckBox
    Left = 844
    Top = 56
    Width = 14
    Height = 17
    DataField = 'complementoImpreso'
    DataSource = DataSource2
    TabOrder = 3
    ValueChecked = '1'
    ValueUnchecked = '0'
    Visible = False
  end
  object ComboBox1: TComboBox
    Left = 8
    Top = 35
    Width = 186
    Height = 22
    Style = csOwnerDrawFixed
    ItemIndex = 0
    TabOrder = 4
    Text = 'Todos'
    OnChange = ComboBox1Change
    Items.Strings = (
      'Todos'
      'Viandas normales'
      'Viandas oficina')
  end
  object DataSource2: TDataSource
    DataSet = CDS2
    Left = 691
    Top = 272
  end
  object QueryPedidos: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 715
    Top = 320
  end
  object DataSetProvider2: TDataSetProvider
    DataSet = QueryPedidos
    Left = 627
    Top = 312
  end
  object CDS2: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider2'
    Left = 659
    Top = 360
    object CDS2hora: TTimeField
      FieldName = 'hora'
    end
    object CDS2cliente: TWideStringField
      FieldName = 'cliente'
      Size = 0
    end
    object CDS2com1: TWideStringField
      FieldName = 'com1'
      Size = 0
    end
    object CDS2com2: TWideStringField
      FieldName = 'com2'
      Size = 0
    end
    object CDS2com3: TWideStringField
      FieldName = 'com3'
      Size = 0
    end
    object CDS2com4: TWideStringField
      FieldName = 'com4'
      Size = 0
    end
    object CDS2Comentario: TWideStringField
      FieldName = 'Comentario'
      Size = 0
    end
    object CDS2etiquetaImpresa: TByteField
      FieldName = 'etiquetaImpresa'
      OnChange = CDS2etiquetaImpresaChange
    end
    object CDS2complementoImpreso: TByteField
      FieldName = 'complementoImpreso'
      OnChange = CDS2complementoImpresoChange
    end
    object CDS2idPedido: TIntegerField
      FieldName = 'idPedido'
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
    Left = 435
    Top = 339
  end
  object QueryUpdate: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 723
    Top = 328
  end
  object PopupMenu1: TPopupMenu
    Left = 272
    Top = 288
    object Pedidosreparto11: TMenuItem
      Caption = 'Pedidos reparto 1'
      object Marcarcomoimpreso1: TMenuItem
        Caption = 'Marcar como impreso'
        OnClick = Marcarcomoimpreso1Click
      end
      object Marcarcomonoimpreso1: TMenuItem
        Caption = 'Marcar como no impreso'
        OnClick = Marcarcomonoimpreso1Click
      end
    end
    object Pedidosreparto21: TMenuItem
      Caption = 'Pedidos reparto 2'
      object Marcarcomoimpreso2: TMenuItem
        Caption = 'Marcar como impreso'
        OnClick = Marcarcomoimpreso2Click
      end
      object Marcarcomonoimpreso2: TMenuItem
        Caption = 'Marcar como no impreso'
        OnClick = Marcarcomonoimpreso2Click
      end
    end
    object Complementos1: TMenuItem
      Caption = 'Complementos'
      object Marcarcomoimpreso3: TMenuItem
        Caption = 'Marcar como impreso'
        OnClick = Marcarcomoimpreso3Click
      end
      object Marcarcomonoimpreso3: TMenuItem
        Caption = 'Marcar como no impreso'
        OnClick = Marcarcomonoimpreso3Click
      end
    end
  end
end
