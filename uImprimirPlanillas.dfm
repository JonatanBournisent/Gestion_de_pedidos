object fImprimirPlanillas: TfImprimirPlanillas
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Imprimir planillas'
  ClientHeight = 443
  ClientWidth = 871
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
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 287
    Height = 427
  end
  object Button1: TButton
    Left = 57
    Top = 350
    Width = 191
    Height = 25
    Caption = 'Imprimir planillas'
    TabOrder = 0
    OnClick = Button1Click
  end
  object ComboBox1: TComboBox
    Left = 57
    Top = 206
    Width = 191
    Height = 22
    Style = csOwnerDrawFixed
    DropDownCount = 15
    TabOrder = 1
    OnChange = ComboBox1Change
  end
  object MC: TMonthCalendar
    Left = 24
    Top = 25
    Width = 260
    Height = 160
    Date = 43928.805878773150000000
    TabOrder = 2
    OnClick = MCClick
  end
  object Button2: TButton
    Left = 57
    Top = 309
    Width = 191
    Height = 25
    Caption = 'Previsualizar'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 57
    Top = 390
    Width = 191
    Height = 25
    Caption = 'Salir'
    TabOrder = 4
    OnClick = Button3Click
  end
  object CBxViernes: TCheckBox
    Left = 58
    Top = 240
    Width = 191
    Height = 15
    Caption = 'Incluir pagos viernes'
    TabOrder = 5
  end
  object CBxSabado: TCheckBox
    Left = 58
    Top = 262
    Width = 191
    Height = 15
    Caption = 'Incluir pagos s'#225'bado'
    TabOrder = 6
  end
  object CBxDeshabilitar: TCheckBox
    Left = 58
    Top = 282
    Width = 191
    Height = 17
    Caption = 'Deshabilitar pagos'
    TabOrder = 7
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
    Left = 680
    Top = 144
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 568
    Top = 200
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 632
    Top = 200
  end
  object CDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 720
    Top = 200
    object CDScalle: TWideStringField
      FieldName = 'calle'
    end
    object CDSnumero: TWideStringField
      FieldName = 'numero'
    end
    object CDScomp: TWideStringField
      FieldName = 'comp'
    end
    object CDSbandGrand: TIntegerField
      FieldName = 'bandGrand'
      DisplayFormat = '- ##'
    end
    object CDSunid: TFMTBCDField
      FieldName = 'unid'
      DisplayFormat = '(#.00)'
    end
    object CDSdeuda: TFMTBCDField
      FieldName = 'deuda'
      OnGetText = CDSdeudaGetText
      Size = 10
    end
    object CDSvalorPedido: TFMTBCDField
      FieldName = 'valorPedido'
      OnGetText = CDSvalorPedidoGetText
      Size = 10
    end
    object CDSsaldoTotal: TFMTBCDField
      FieldName = 'saldoTotal'
      OnGetText = CDSsaldoTotalGetText
      Size = 10
    end
    object CDSmedioPago: TWideStringField
      FieldName = 'medioPago'
      Size = 1
    end
    object CDSdiaPago: TIntegerField
      FieldName = 'diaPago'
    end
    object CDSfrecuenciaPago: TIntegerField
      FieldName = 'frecuenciaPago'
    end
    object CDSvar_dummy: TFMTBCDField
      FieldName = 'var_dummy'
      OnGetText = CDSvar_dummyGetText
      Size = 10
    end
    object CDSmenuImpreso: TLargeintField
      FieldName = 'menuImpreso'
      OnGetText = CDSmenuImpresoGetText
    end
    object CDSpagoAdelantado: TWideStringField
      FieldName = 'pagoAdelantado'
      Size = 1
    end
    object CDSunidAyer: TFMTBCDField
      FieldName = 'unidAyer'
      Size = 5
    end
  end
  object DataSource1: TDataSource
    DataSet = CDS
    Left = 799
    Top = 200
  end
  object QueryAux: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 672
    Top = 280
  end
  object frxReport1: TfrxReport
    Version = '6.9.3'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    PrintOptions.ShowDialog = False
    ReportOptions.CreateDate = 43926.507441562500000000
    ReportOptions.LastChange = 44801.798863842600000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      ''
      'begin'
      ''
      'end.')
    Left = 592
    Top = 352
    Datasets = <
      item
        DataSet = frxDBDataset1
        DataSetName = 'frxDBDataset1'
      end>
    Variables = <>
    Style = <
      item
        Name = 'Title'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Frame.Typ = []
        Fill.BackColor = 14211288
      end
      item
        Name = 'Header'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Frame.Typ = []
        Fill.BackColor = 15790320
      end
      item
        Name = 'Group header'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Frame.Typ = []
        Fill.BackColor = 15790320
      end
      item
        Name = 'Data'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = []
        Frame.Typ = []
      end
      item
        Name = 'Group footer'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = []
        Frame.Typ = [ftTop]
      end
      item
        Name = 'Header line'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = []
        Frame.Typ = []
        Frame.Width = 2.000000000000000000
      end>
    object Data: TfrxDataPage
      Height = 1000.000000000000000000
      Width = 1000.000000000000000000
    end
    object Page1: TfrxReportPage
      PaperWidth = 210.000000000000000000
      PaperHeight = 297.000000000000000000
      PaperSize = 9
      LeftMargin = 9.000000000000000000
      RightMargin = 10.000000000000000000
      TopMargin = 4.500000000000000000
      BottomMargin = 5.000000000000000000
      Columns = 2
      ColumnWidth = 100.000000000000000000
      ColumnPositions.Strings = (
        '0'
        '100')
      Frame.Typ = []
      MirrorMode = []
      object ReportTitle1: TfrxReportTitle
        FillType = ftBrush
        Frame.Typ = []
        Height = 45.354330710000000000
        Top = 18.897650000000000000
        Width = 721.890230000000000000
        object Memo1: TfrxMemoView
          Align = baWidth
          AllowVectorExport = True
          Width = 721.890230000000000000
          Height = 37.795275590000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = []
          Fill.BackColor = 14211288
          HAlign = haCenter
          Memo.UTF8W = (
            'Report')
          ParentFont = False
          Style = 'Title'
          VAlign = vaCenter
        end
      end
      object MasterData1: TfrxMasterData
        FillType = ftBrush
        Frame.Typ = []
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = []
        Height = 37.795275590000000000
        ParentFont = False
        Top = 124.724490000000000000
        Width = 377.953000000000000000
        DataSet = frxDBDataset1
        DataSetName = 'frxDBDataset1'
        RowCount = 0
        object Memo9: TfrxMemoView
          AllowVectorExport = True
          Top = 3.779527560000000000
          Width = 75.409400000000000000
          Height = 18.897650000000000000
          AutoWidth = True
          DataField = 'calle'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          Memo.UTF8W = (
            '[frxDBDataset1."calle"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo10: TfrxMemoView
          AllowVectorExport = True
          Left = 233.787260000000000000
          Top = 3.779527560000000000
          Width = 47.787725000000000000
          Height = 18.897630470000000000
          AutoWidth = True
          DataField = 'numero'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          HAlign = haRight
          Memo.UTF8W = (
            '[frxDBDataset1."numero"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo2: TfrxMemoView
          AllowVectorExport = True
          Left = 94.488250000000000000
          Top = 4.913385830000000000
          Width = 134.716915000000000000
          Height = 18.897630470000000000
          DataField = 'comp'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = []
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxDBDataset1."comp"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo3: TfrxMemoView
          AllowVectorExport = True
          Left = 279.685039370000000000
          Top = 3.779527560000000000
          Width = 21.331015000000000000
          Height = 18.897630470000000000
          AutoWidth = True
          DataField = 'bandGrand'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = []
          Memo.UTF8W = (
            '[frxDBDataset1."bandGrand"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo4: TfrxMemoView
          AllowVectorExport = True
          Left = 345.826781420000000000
          Top = 5.157480310000000000
          Width = 28.890075000000000000
          Height = 18.897630470000000000
          AutoWidth = True
          DataField = 'unid'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = []
          HAlign = haRight
          Memo.UTF8W = (
            '[frxDBDataset1."unid"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo6: TfrxMemoView
          AllowVectorExport = True
          Top = 20.677180000000000000
          Width = 49.133890000000000000
          Height = 11.338590000000000000
          AutoWidth = True
          DataField = 'deuda'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -8
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          Memo.UTF8W = (
            '[frxDBDataset1."deuda"]')
          ParentFont = False
        end
        object Memo7: TfrxMemoView
          AllowVectorExport = True
          Left = 94.488250000000000000
          Top = 20.677180000000000000
          Width = 147.401670000000000000
          Height = 11.338590000000000000
          DataField = 'saldoTotal'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -8
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxDBDataset1."saldoTotal"]')
          ParentFont = False
        end
        object Memo11: TfrxMemoView
          AllowVectorExport = True
          Left = 235.008040000000000000
          Top = 20.677180000000000000
          Width = 45.354360000000000000
          Height = 11.338590000000000000
          AutoWidth = True
          DataField = 'valorPedido'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -8
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          HAlign = haRight
          Memo.UTF8W = (
            '[frxDBDataset1."valorPedido"]')
          ParentFont = False
        end
        object Memo12: TfrxMemoView
          AllowVectorExport = True
          Left = 300.362400000000000000
          Top = 3.779530000000000000
          Width = 45.354360000000000000
          Height = 18.897650000000000000
          AutoWidth = True
          DataField = 'var_dummy'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          Memo.UTF8W = (
            '[frxDBDataset1."var_dummy"]')
          ParentFont = False
          VAlign = vaCenter
        end
        object Memo13: TfrxMemoView
          AllowVectorExport = True
          Left = 207.874150000000000000
          Top = 3.779530000000000000
          Width = 30.236240000000000000
          Height = 18.897650000000000000
          AutoWidth = True
          DataField = 'menuImpreso'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -21
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = []
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxDBDataset1."menuImpreso"]')
          ParentFont = False
          VAlign = vaCenter
        end
      end
      object Memo5: TfrxMemoView
        AllowVectorExport = True
        Left = 434.645950000000000000
        Top = 891.969080000000000000
        Width = 166.299320000000000000
        Height = 192.756030000000000000
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -15
        Font.Name = 'Arial'
        Font.Style = []
        Frame.Typ = []
        HAlign = haRight
        Memo.UTF8W = (
          'CAMBIO:'
          ''
          'RECAUDACI'#211'N:'
          ''
          'TOTAL:'
          ''
          'DECUENTO:'
          ''
          'FINAL:'
          ''
          'VIANDAS:')
        ParentFont = False
        VAlign = vaCenter
      end
    end
  end
  object frxDBDataset1: TfrxDBDataset
    UserName = 'frxDBDataset1'
    CloseDataSource = False
    FieldAliases.Strings = (
      'calle=calle'
      'numero=numero'
      'comp=comp'
      'bandGrand=bandGrand'
      'unid=unid'
      'deuda=deuda'
      'valorPedido=valorPedido'
      'saldoTotal=saldoTotal'
      'medioPago=medioPago'
      'diaPago=diaPago'
      'frecuenciaPago=frecuenciaPago'
      'var_dummy=var_dummy'
      'menuImpreso=menuImpreso')
    DataSource = DataSource1
    BCDToCurrency = False
    Left = 512
    Top = 352
  end
end
