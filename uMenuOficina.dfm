object fMenuOficina: TfMenuOficina
  Left = 0
  Top = 0
  Caption = 'Men'#250' semanal para oficinas'
  ClientHeight = 547
  ClientWidth = 1032
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnMouseWheelDown = FormMouseWheelDown
  OnMouseWheelUp = FormMouseWheelUp
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 14
    Top = 175
    Width = 75
    Height = 25
    Caption = 'Anterior'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 111
    Top = 175
    Width = 81
    Height = 25
    Caption = 'Siguiente'
    TabOrder = 1
    OnClick = Button2Click
  end
  object MC1: TMonthCalendar
    Left = 8
    Top = 8
    Width = 191
    Height = 160
    MultiSelect = True
    Date = 44841.440608773150000000
    EndDate = 44841.000000000000000000
    TabOrder = 2
  end
  object ScrollBox1: TScrollBox
    Left = 205
    Top = 8
    Width = 820
    Height = 539
    HorzScrollBar.Smooth = True
    HorzScrollBar.Style = ssHotTrack
    HorzScrollBar.Tracking = True
    VertScrollBar.Smooth = True
    VertScrollBar.Tracking = True
    TabOrder = 3
    inline frameMenuOficina1: TframeMenuOficina
      Left = 10
      Top = 3
      Width = 798
      Height = 169
      TabOrder = 0
      ExplicitLeft = 10
      ExplicitTop = 3
      ExplicitWidth = 798
    end
    inline frameMenuOficina2: TframeMenuOficina
      Left = 10
      Top = 184
      Width = 798
      Height = 169
      TabOrder = 1
      ExplicitLeft = 10
      ExplicitTop = 184
      ExplicitWidth = 798
    end
    inline frameMenuOficina3: TframeMenuOficina
      Left = 10
      Top = 366
      Width = 798
      Height = 169
      TabOrder = 2
      ExplicitLeft = 10
      ExplicitTop = 366
      ExplicitWidth = 798
    end
    inline frameMenuOficina4: TframeMenuOficina
      Left = 10
      Top = 552
      Width = 798
      Height = 169
      TabOrder = 3
      ExplicitLeft = 10
      ExplicitTop = 552
      ExplicitWidth = 798
    end
    inline frameMenuOficina5: TframeMenuOficina
      Left = 10
      Top = 736
      Width = 798
      Height = 169
      TabOrder = 4
      ExplicitLeft = 10
      ExplicitTop = 736
      ExplicitWidth = 798
    end
  end
end
