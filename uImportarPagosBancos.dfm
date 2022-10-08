object fImportarPagosBancos: TfImportarPagosBancos
  Left = 0
  Top = 0
  Caption = 'Importar pagos por .CSV'
  ClientHeight = 694
  ClientWidth = 585
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid1: TDBGrid
    Left = 8
    Top = 8
    Width = 569
    Height = 593
    DataSource = DataSource1
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
        FieldName = 'fecha'
        Title.Alignment = taCenter
        Title.Caption = 'Fecha'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 81
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'cliente'
        Title.Alignment = taCenter
        Title.Caption = 'Cliente'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 372
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'valor'
        Title.Alignment = taCenter
        Title.Caption = 'Pago'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 78
        Visible = True
      end>
  end
  object RadioGroup1: TRadioGroup
    Left = 8
    Top = 607
    Width = 185
    Height = 82
    Caption = 'Cuenta bancaria'
    ItemIndex = 0
    Items.Strings = (
      'Banco Oscar'
      'Banco Monica'
      'Banco Williams')
    TabOrder = 1
  end
  object FDMemTable1: TFDMemTable
    FetchOptions.AssignedValues = [evMode]
    FetchOptions.Mode = fmAll
    ResourceOptions.AssignedValues = [rvSilentMode]
    ResourceOptions.SilentMode = True
    UpdateOptions.AssignedValues = [uvCheckRequired]
    UpdateOptions.CheckRequired = False
    Left = 472
    Top = 360
    object FDMemTable1fecha: TDateField
      FieldName = 'fecha'
      DisplayFormat = 'dd/mm/yyyy'
    end
    object FDMemTable1cliente: TWideStringField
      FieldName = 'cliente'
      Size = 100
    end
    object FDMemTable1valor: TFMTBCDField
      FieldName = 'valor'
      DisplayFormat = '$ #.00'
      Size = 0
    end
    object FDMemTable1idCliente: TIntegerField
      FieldName = 'idCliente'
    end
  end
  object DataSource1: TDataSource
    DataSet = FDMemTable1
    Left = 392
    Top = 368
  end
end
