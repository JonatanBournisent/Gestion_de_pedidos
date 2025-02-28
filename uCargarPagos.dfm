object fCargarPagos: TfCargarPagos
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Cargar datos de planillas de reparto'
  ClientHeight = 702
  ClientWidth = 920
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
    Left = 708
    Top = 14
    Width = 169
    Height = 14
    Alignment = taCenter
    AutoSize = False
    Caption = 'Fecha de planillas'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Shape1: TShape
    Left = 384
    Top = 336
    Width = 65
    Height = 65
  end
  object Shape2: TShape
    Left = 696
    Top = 8
    Width = 193
    Height = 73
    Brush.Style = bsClear
  end
  object Shape3: TShape
    Left = 696
    Top = 137
    Width = 193
    Height = 106
    Brush.Style = bsClear
  end
  object Label2: TLabel
    Left = 707
    Top = 145
    Width = 122
    Height = 14
    Alignment = taCenter
    Caption = 'Planilla seleccionada'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Shape4: TShape
    Left = 696
    Top = 267
    Width = 193
    Height = 330
    Brush.Style = bsClear
  end
  object DBGrid1: TDBGrid
    Left = 3
    Top = 3
    Width = 670
    Height = 697
    DataSource = DataSource1
    Enabled = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Calibri'
    Font.Style = []
    ParentFont = False
    PopupMenu = PopupMenu1
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDrawColumnCell = DBGrid1DrawColumnCell
    OnKeyPress = DBGrid1KeyPress
    OnKeyUp = DBGrid1KeyUp
    Columns = <
      item
        ButtonStyle = cbsEllipsis
        Color = 16439761
        Expanded = False
        FieldName = 'calle'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Calibri'
        Font.Style = [fsBold]
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = 'Calle'
        Title.Color = 16439761
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -19
        Title.Font.Name = 'Calibri'
        Title.Font.Style = [fsBold]
        Width = 180
        Visible = True
      end
      item
        Alignment = taRightJustify
        ButtonStyle = cbsEllipsis
        Color = 16439761
        Expanded = False
        FieldName = 'numero'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Calibri'
        Font.Style = [fsBold]
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = 'Numero'
        Title.Color = 16439761
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -19
        Title.Font.Name = 'Calibri'
        Title.Font.Style = [fsBold]
        Width = 85
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'unidades'
        Title.Alignment = taCenter
        Title.Caption = 'Unid.'
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -19
        Title.Font.Name = 'Calibri'
        Title.Font.Style = [fsBold]
        Width = 92
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'pagoRealizado'
        Title.Alignment = taCenter
        Title.Caption = 'Pago'
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -19
        Title.Font.Name = 'Calibri'
        Title.Font.Style = [fsBold]
        Width = 85
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'valorUnidad'
        Title.Alignment = taCenter
        Title.Caption = 'Valor/Unid.'
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -19
        Title.Font.Name = 'Calibri'
        Title.Font.Style = [fsBold]
        Width = 104
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'deudaEfectivo'
        Title.Alignment = taCenter
        Title.Caption = 'Deuda'
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -19
        Title.Font.Name = 'Calibri'
        Title.Font.Style = [fsBold]
        Visible = True
      end>
  end
  object ComboBox1: TComboBox
    Left = 708
    Top = 165
    Width = 169
    Height = 22
    Style = csOwnerDrawFixed
    DropDownCount = 15
    TabOrder = 1
    OnChange = ComboBox1Change
  end
  object Button1: TButton
    Left = 707
    Top = 204
    Width = 169
    Height = 25
    Caption = 'Mostrar esta planilla'
    TabOrder = 2
    OnClick = Button1Click
  end
  object DTP: TDateTimePicker
    Left = 708
    Top = 34
    Width = 169
    Height = 27
    Date = 43826.673470416670000000
    Time = 43826.673470416670000000
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnChange = DTPChange
  end
  object Button2: TButton
    Left = 708
    Top = 557
    Width = 169
    Height = 25
    Caption = 'Totalizar'
    TabOrder = 4
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 708
    Top = 361
    Width = 169
    Height = 25
    Caption = 'A'#241'adir un cometario'
    TabOrder = 5
    OnClick = Button3Click
  end
  object Panel1: TPanel
    Left = 144
    Top = 339
    Width = 281
    Height = 161
    Caption = 'Panel1'
    Color = 8240895
    ParentBackground = False
    ShowCaption = False
    TabOrder = 6
    Visible = False
    object Memo1: TMemo
      Left = 16
      Top = 8
      Width = 249
      Height = 113
      Lines.Strings = (
        'Memo1')
      MaxLength = 100
      TabOrder = 0
    end
    object Button4: TButton
      Left = 40
      Top = 127
      Width = 75
      Height = 25
      Caption = 'Guardar'
      TabOrder = 1
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 160
      Top = 127
      Width = 75
      Height = 25
      Caption = 'Cancelar'
      TabOrder = 2
      OnClick = Button5Click
    end
  end
  object Button6: TButton
    Left = 707
    Top = 287
    Width = 169
    Height = 25
    Caption = 'Agregar otro cliente'
    TabOrder = 7
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 708
    Top = 436
    Width = 169
    Height = 25
    Caption = 'Poner en cero todos los valores'
    TabOrder = 8
    OnClick = Button7Click
  end
  object Panel2: TPanel
    Left = 8
    Top = 137
    Width = 575
    Height = 425
    Caption = 'Panel2'
    Color = 10790143
    ParentBackground = False
    ShowCaption = False
    TabOrder = 9
    object Button8: TButton
      Left = 226
      Top = 391
      Width = 137
      Height = 25
      Caption = 'Cerrar este cuadro'
      TabOrder = 0
      OnClick = Button8Click
    end
    object Memo2: TMemo
      Left = 8
      Top = 8
      Width = 559
      Height = 377
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Consolas'
      Font.Style = []
      Lines.Strings = (
        'Memo2')
      ParentFont = False
      ParentShowHint = False
      ReadOnly = True
      ShowHint = True
      TabOrder = 1
    end
  end
  object Button9: TButton
    Left = 696
    Top = 87
    Width = 193
    Height = 25
    Caption = 'Ver "Pedidos vs. entregas"'
    TabOrder = 10
    OnClick = Button9Click
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
    Left = 877
    Top = 216
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 1005
    Top = 216
  end
  object CDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    OnNewRecord = CDSNewRecord
    Left = 1061
    Top = 216
    object CDSpagoRealizado: TFMTBCDField
      Alignment = taCenter
      FieldName = 'pagoRealizado'
      OnChange = CDSpagoRealizadoChange
      DisplayFormat = '$ 0.00'
      EditFormat = '0.00'
      Size = 0
    end
    object CDSidCuenta: TIntegerField
      FieldName = 'idCuenta'
    end
    object CDSunidades: TFMTBCDField
      Alignment = taCenter
      FieldName = 'unidades'
      OnChange = CDSunidadesChange
      DisplayFormat = '0.00'
    end
    object CDSvalorUnidad: TFMTBCDField
      Alignment = taCenter
      FieldName = 'valorUnidad'
      OnChange = CDSvalorUnidadChange
      DisplayFormat = '$ 0.00'
      EditFormat = '0.00'
    end
    object CDScalle: TWideStringField
      FieldName = 'calle'
    end
    object CDSnumero: TWideStringField
      FieldName = 'numero'
    end
    object CDSrefCliente: TIntegerField
      FieldName = 'refCliente'
    end
    object CDSrefFrecuenciaPago: TLargeintField
      FieldName = 'refFrecuenciaPago'
    end
    object CDSdeudaEfectivo: TFMTBCDField
      FieldName = 'deudaEfectivo'
      Size = 10
    end
  end
  object DataSource1: TDataSource
    DataSet = CDS
    Left = 1118
    Top = 216
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 936
    Top = 216
  end
  object QueryAux: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 888
    Top = 400
  end
  object QueryUpdate: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 952
    Top = 280
  end
  object PopupMenu1: TPopupMenu
    Left = 232
    Top = 88
    object Aadiruncomentario1: TMenuItem
      Caption = 'A'#241'adir un comentario'
      OnClick = Aadiruncomentario1Click
    end
    object Verestadodecuentadelcliente1: TMenuItem
      Caption = 'Ver estado de cuenta del cliente'
      OnClick = Verestadodecuentadelcliente1Click
    end
  end
end
