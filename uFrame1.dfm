object Frame1: TFrame1
  Left = 0
  Top = 0
  Width = 703
  Height = 444
  TabOrder = 0
  object Label1: TLabel
    Left = 0
    Top = 61
    Width = 37
    Height = 13
    Caption = 'Nombre'
  end
  object Label2: TLabel
    Left = 0
    Top = 87
    Width = 37
    Height = 13
    Caption = 'Apellido'
  end
  object Label3: TLabel
    Left = 0
    Top = 8
    Width = 23
    Height = 13
    Caption = 'Calle'
  end
  object Label4: TLabel
    Left = 0
    Top = 34
    Width = 37
    Height = 13
    Caption = 'N'#250'mero'
  end
  object Label5: TLabel
    Left = 1
    Top = 219
    Width = 94
    Height = 13
    Caption = 'Frecuencia de pago'
  end
  object Label6: TLabel
    Left = 1
    Top = 272
    Width = 114
    Height = 13
    Caption = 'Lista de precio asociada'
  end
  object Label7: TLabel
    Left = 322
    Top = 360
    Width = 78
    Height = 13
    Caption = 'Bonificacion [%]'
  end
  object Label9: TLabel
    Left = 322
    Top = 5
    Width = 138
    Height = 13
    Caption = 'Clientes similares existentes:'
  end
  object Label10: TLabel
    Left = 1
    Top = 246
    Width = 104
    Height = 13
    Caption = 'Dia para emitir detalle'
  end
  object Label8: TLabel
    Left = 0
    Top = 113
    Width = 60
    Height = 13
    Caption = 'Raz'#243'n Social'
  end
  object Label11: TLabel
    Left = 0
    Top = 140
    Width = 69
    Height = 13
    Caption = 'Domicilio Fiscal'
  end
  object Label12: TLabel
    Left = 1
    Top = 193
    Width = 24
    Height = 13
    Caption = 'CUIT'
  end
  object Label13: TLabel
    Left = 1
    Top = 166
    Width = 110
    Height = 13
    Caption = 'Condicion frente al IVA'
  end
  object Label14: TLabel
    Left = 1
    Top = 300
    Width = 86
    Height = 13
    Caption = 'Nombre Banco (*)'
  end
  object Label15: TLabel
    Left = 1
    Top = 325
    Width = 69
    Height = 13
    Caption = 'Nombre Banco'
  end
  object Label16: TLabel
    Left = 1
    Top = 350
    Width = 69
    Height = 13
    Caption = 'Nombre Banco'
  end
  object Label17: TLabel
    Left = 544
    Top = 368
    Width = 60
    Height = 13
    Caption = 'Facturaci'#243'n:'
  end
  object Label18: TLabel
    Left = 512
    Top = 396
    Width = 121
    Height = 13
    Caption = 'Medio de pago preferido:'
  end
  object Label19: TLabel
    Left = 3
    Top = 416
    Width = 173
    Height = 13
    Caption = '(*) Admite multiples separados por |'
  end
  object DBEdNombre: TDBEdit
    Left = 128
    Top = 60
    Width = 187
    Height = 21
    DataField = 'nombre'
    DataSource = DataSource1
    TabOrder = 2
    OnChange = DBEdNombreChange
  end
  object DBEdApellido: TDBEdit
    Left = 128
    Top = 87
    Width = 187
    Height = 21
    DataField = 'apellido'
    DataSource = DataSource1
    TabOrder = 3
    OnChange = DBEdApellidoChange
  end
  object DBEdCalle: TDBEdit
    Left = 128
    Top = 8
    Width = 187
    Height = 21
    DataField = 'calle'
    DataSource = DataSource1
    TabOrder = 0
    OnChange = DBEdCalleChange
  end
  object DBEdNumero: TDBEdit
    Left = 128
    Top = 34
    Width = 187
    Height = 21
    DataField = 'numero'
    DataSource = DataSource1
    TabOrder = 1
    OnChange = DBEdNumeroChange
  end
  object DBFrecPago: TDBLookupComboBox
    Left = 129
    Top = 219
    Width = 144
    Height = 21
    DataField = 'refFrecuenciaPago'
    DataSource = DataSource1
    KeyField = 'idFrecuenciaPago'
    ListField = 'descripcion'
    ListSource = DataSource2
    TabOrder = 8
  end
  object DBListaPrecio: TDBLookupComboBox
    Left = 129
    Top = 272
    Width = 144
    Height = 21
    DataField = 'refListaPrecio'
    DataSource = DataSource1
    KeyField = 'idListaPrecio'
    ListField = 'descripcion'
    ListSource = DataSource3
    TabOrder = 10
  end
  object DBEdBonificacion: TDBEdit
    Left = 409
    Top = 357
    Width = 57
    Height = 21
    DataField = 'bonificacion'
    DataSource = DataSource1
    TabOrder = 11
    OnKeyPress = DBEdBonificacionKeyPress
  end
  object DBGrid1: TDBGrid
    Left = 321
    Top = 24
    Width = 377
    Height = 327
    DataSource = DataSource4
    Enabled = False
    ReadOnly = True
    TabOrder = 13
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
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
        Width = 107
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
        Width = 67
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
        Width = 82
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
        Width = 84
        Visible = True
      end>
  end
  object DBDiaPago: TDBLookupComboBox
    Left = 129
    Top = 245
    Width = 144
    Height = 21
    DataField = 'refDiaPago'
    DataSource = DataSource1
    KeyField = 'idDiaPago'
    ListField = 'descripcion'
    ListSource = DataSource5
    TabOrder = 9
  end
  object DBCheckBox1: TDBCheckBox
    Left = 322
    Top = 403
    Width = 161
    Height = 17
    Caption = 'Imprimir detalle de cuentas'
    DataField = 'imprimirDetalle'
    DataSource = DataSource1
    TabOrder = 12
    ValueChecked = '1'
    ValueUnchecked = '0'
  end
  object DBRazonSocial: TDBEdit
    Left = 128
    Top = 113
    Width = 187
    Height = 21
    DataField = 'razonSocial'
    DataSource = DataSource1
    TabOrder = 4
  end
  object DBDomicilioFiscal: TDBEdit
    Left = 128
    Top = 140
    Width = 187
    Height = 21
    DataField = 'domicilioFiscal'
    DataSource = DataSource1
    TabOrder = 5
  end
  object DBCUIT: TDBEdit
    Left = 129
    Top = 193
    Width = 144
    Height = 21
    DataField = 'CUIT'
    DataSource = DataSource1
    TabOrder = 7
    OnExit = DBCUITExit
    OnKeyDown = DBCUITKeyDown
    OnKeyPress = DBCUITKeyPress
    OnKeyUp = DBCUITKeyUp
  end
  object CBCondicionFrenteIVA: TComboBox
    Left = 129
    Top = 166
    Width = 144
    Height = 22
    Style = csOwnerDrawFixed
    TabOrder = 6
    OnChange = CBCondicionFrenteIVAChange
  end
  object DBCheckBox2: TDBCheckBox
    Left = 322
    Top = 423
    Width = 161
    Height = 17
    Caption = 'Generar factura electr'#243'nica'
    DataField = 'generarFactura'
    DataSource = DataSource1
    TabOrder = 14
    ValueChecked = '1'
    ValueUnchecked = '0'
  end
  object DBEdBanco1: TDBEdit
    Left = 129
    Top = 298
    Width = 121
    Height = 21
    DataField = 'nombreBanco1'
    DataSource = DataSource1
    TabOrder = 15
  end
  object DBEdBanco2: TDBEdit
    Left = 129
    Top = 323
    Width = 121
    Height = 21
    DataField = 'nombreBanco2'
    DataSource = DataSource1
    TabOrder = 16
  end
  object DBEdBanco3: TDBEdit
    Left = 129
    Top = 348
    Width = 121
    Height = 21
    DataField = 'nombreBanco3'
    DataSource = DataSource1
    TabOrder = 17
  end
  object CBFacturar: TComboBox
    Left = 624
    Top = 365
    Width = 33
    Height = 22
    Style = csOwnerDrawFixed
    TabOrder = 18
    OnChange = CBFacturarChange
    Items.Strings = (
      'O'
      'M'
      'W'
      'C')
  end
  object CBmp: TComboBox
    Left = 512
    Top = 413
    Width = 145
    Height = 21
    TabOrder = 19
    Text = 'A- Efectivo'
    OnChange = CBmpChange
    Items.Strings = (
      'A- Efectivo'
      'B - Banco Oscar'
      'C - Banco Monica'
      'D - Banco Williams'
      'E - Banco Carolina'
      'M - MercadoPago Oscar'
      'N - MercadoPago Monica')
  end
  object DBCheckBox3: TDBCheckBox
    Left = 322
    Top = 383
    Width = 162
    Height = 17
    Caption = 'Este cliente paga adelantado'
    DataField = 'pagoAdelantado'
    DataSource = DataSource1
    TabOrder = 20
    ValueChecked = 'S'
    ValueUnchecked = 'N'
  end
  object DBCheckBox5: TDBCheckBox
    Left = 3
    Top = 375
    Width = 150
    Height = 17
    Caption = 'Enviar men'#250' impreso'
    DataField = 'menuImpreso'
    DataSource = DataSource1
    TabOrder = 21
    ValueChecked = 'S'
    ValueUnchecked = 'N'
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
    Left = 752
    Top = 40
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 704
    Top = 128
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = SQLTable1
    Left = 736
    Top = 80
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 768
    Top = 80
    object ClientDataSet1calle: TWideStringField
      FieldName = 'calle'
    end
    object ClientDataSet1numero: TWideStringField
      FieldName = 'numero'
      Size = 8
    end
    object ClientDataSet1nombre: TWideStringField
      FieldName = 'nombre'
    end
    object ClientDataSet1apellido: TWideStringField
      FieldName = 'apellido'
      Size = 15
    end
    object ClientDataSet1refFrecuenciaPago: TIntegerField
      FieldName = 'refFrecuenciaPago'
    end
    object ClientDataSet1refDiaPago: TIntegerField
      FieldName = 'refDiaPago'
    end
    object ClientDataSet1idCliente: TIntegerField
      FieldName = 'idCliente'
    end
    object ClientDataSet1refListaPrecio: TIntegerField
      FieldName = 'refListaPrecio'
    end
    object ClientDataSet1esVisible: TIntegerField
      FieldName = 'esVisible'
    end
    object ClientDataSet1saldo: TFMTBCDField
      FieldName = 'saldo'
      Size = 21
    end
    object ClientDataSet1imprimirDetalle: TByteField
      FieldName = 'imprimirDetalle'
    end
    object ClientDataSet1bonificacion: TFMTBCDField
      Alignment = taCenter
      FieldName = 'bonificacion'
      DisplayFormat = '0.00 %'
      EditFormat = '0.00'
    end
    object ClientDataSet1CUIT: TWideStringField
      FieldName = 'CUIT'
      Size = 13
    end
    object ClientDataSet1razonSocial: TWideStringField
      FieldName = 'razonSocial'
      Size = 70
    end
    object ClientDataSet1domicilioFiscal: TWideStringField
      FieldName = 'domicilioFiscal'
      Size = 70
    end
    object ClientDataSet1refCondicionFrenteIVA: TIntegerField
      FieldName = 'refCondicionFrenteIVA'
    end
    object ClientDataSet1acumuladoGlobal: TFMTBCDField
      FieldName = 'acumuladoGlobal'
      Size = 10
    end
    object ClientDataSet1acumuladoParcial: TFMTBCDField
      FieldName = 'acumuladoParcial'
      Size = 10
    end
    object ClientDataSet1generarFactura: TByteField
      FieldName = 'generarFactura'
    end
    object ClientDataSet1tipo: TWideStringField
      FieldName = 'tipo'
      Size = 1
    end
    object ClientDataSet1nombreBanco1: TWideStringField
      FieldName = 'nombreBanco1'
      Size = 250
    end
    object ClientDataSet1nombreBanco2: TWideStringField
      FieldName = 'nombreBanco2'
    end
    object ClientDataSet1nombreBanco3: TWideStringField
      FieldName = 'nombreBanco3'
    end
    object ClientDataSet1medioPagoDefecto: TWideStringField
      FieldName = 'medioPagoDefecto'
      Size = 1
    end
    object ClientDataSet1pagoAdelantado: TWideStringField
      FieldName = 'pagoAdelantado'
      Size = 1
    end
    object ClientDataSet1menuImpreso: TWideStringField
      FieldName = 'menuImpreso'
      Size = 1
    end
  end
  object DataSource1: TDataSource
    DataSet = ClientDataSet1
    Left = 800
    Top = 80
  end
  object SQLTable1: TSQLTable
    MaxBlobSize = -1
    SQLConnection = SQLConnection1
    TableName = 'clientes'
    Left = 704
    Top = 80
  end
  object DataSetProvider2: TDataSetProvider
    DataSet = Query1
    Left = 736
    Top = 128
  end
  object ClientDataSet2: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider2'
    ReadOnly = True
    Left = 768
    Top = 128
  end
  object DataSource2: TDataSource
    DataSet = ClientDataSet2
    Left = 800
    Top = 128
  end
  object DataSetProvider3: TDataSetProvider
    DataSet = Query2
    Left = 736
    Top = 176
  end
  object ClientDataSet3: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider3'
    ReadOnly = True
    Left = 768
    Top = 176
  end
  object DataSource3: TDataSource
    DataSet = ClientDataSet3
    Left = 800
    Top = 176
  end
  object Query2: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 704
    Top = 176
  end
  object DataSetProvider4: TDataSetProvider
    DataSet = Query3
    Left = 728
    Top = 248
  end
  object ClientDataSet4: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider4'
    ReadOnly = True
    Left = 760
    Top = 248
  end
  object DataSource4: TDataSource
    DataSet = ClientDataSet4
    Left = 792
    Top = 248
  end
  object Query3: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 696
    Top = 248
  end
  object DataSetProvider5: TDataSetProvider
    DataSet = Query4
    Left = 720
    Top = 336
  end
  object ClientDataSet5: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider5'
    ReadOnly = True
    Left = 760
    Top = 328
  end
  object DataSource5: TDataSource
    DataSet = ClientDataSet5
    Left = 816
    Top = 328
  end
  object Query4: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 664
    Top = 344
  end
  object QueryUpdate: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 632
    Top = 272
  end
  object QueryAux: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 640
    Top = 392
  end
end
