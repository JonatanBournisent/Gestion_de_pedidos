object fGraficos2: TfGraficos2
  Left = 0
  Top = 0
  Caption = 'fGraficos2'
  ClientHeight = 535
  ClientWidth = 755
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object DBChart1: TDBChart
    Left = 3
    Top = 0
    Width = 744
    Height = 385
    Title.Text.Strings = (
      'CANTIDAD DE VIANDAS EFECTIVAMENTE ENTREGADAS EN CADA D'#205'A DEL MES')
    BottomAxis.Title.Caption = 'D'#205'A DEL MES'
    LeftAxis.Title.Caption = 'CANTIDAD DE VIANDAS ENTREGADAS'
    Panning.MouseWheel = pmwNone
    View3D = False
    View3DOptions.Orthogonal = False
    Zoom.MouseWheel = pmwNormal
    TabOrder = 0
    DefaultCanvas = 'TGDIPlusCanvas'
    PrintMargins = (
      15
      24
      15
      24)
    ColorPaletteIndex = 13
    object Series2: TBarSeries
      Legend.Visible = False
      Selected.Hover.Visible = False
      Marks.Children = <
        item
          Shape.ShapeStyle = fosRectangle
          Shape.Visible = False
          Shape.Style = smsValue
        end>
      Marks.ChildLayout = slLeftRight
      Marks.Frame.Color = 83886080
      Marks.Frame.Visible = False
      Marks.Transparent = True
      Marks.Margins.Left = 27
      Marks.Margins.Top = 27
      Marks.Margins.Right = 26
      Marks.Margins.Bottom = 26
      Marks.Margins.Units = maPixels
      Marks.Style = smsValue
      Marks.Angle = 90
      Marks.Arrow.Color = 16744576
      Marks.Arrow.Visible = False
      Marks.Callout.Style = psTriangle
      Marks.Callout.Arrow.Color = 16744576
      Marks.Callout.Arrow.Visible = False
      Marks.TextAlign = taLeftJustify
      DataSource = CDS2
      SeriesColor = 6730751
      ShowInLegend = False
      XLabelsSource = 'xData'
      BarWidthPercent = 35
      XValues.DateTime = True
      XValues.Name = 'X'
      XValues.Order = loAscending
      XValues.ValueSource = 'xData'
      YValues.Name = 'Bar'
      YValues.Order = loNone
      YValues.ValueSource = 'yData'
    end
    object Series1: TLineSeries
      Marks.Transparency = 8
      Marks.Transparent = True
      DataSource = CDS2
      SeriesColor = clRed
      XLabelsSource = 'xData'
      Brush.BackColor = clDefault
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.DateTime = True
      XValues.Name = 'X'
      XValues.Order = loAscending
      XValues.ValueSource = 'xData'
      YValues.Name = 'Y'
      YValues.Order = loNone
      YValues.ValueSource = 'yData'
    end
  end
  object CDS2: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider2'
    ReadOnly = True
    Left = 306
    Top = 352
    object CDS2yData: TFMTBCDField
      FieldName = 'yData'
      Size = 15
    end
    object CDS2xData: TSQLTimeStampField
      FieldName = 'xData'
      DisplayFormat = 'dd/mmm'
    end
  end
  object DataSetProvider2: TDataSetProvider
    DataSet = Query2
    Left = 240
    Top = 352
  end
  object Query2: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 192
    Top = 352
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
    Left = 80
    Top = 378
  end
end
