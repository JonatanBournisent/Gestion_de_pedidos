object fModificarCliente: TfModificarCliente
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Modificar datos de un cliente'
  ClientHeight = 683
  ClientWidth = 738
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 8
    Top = 9
    Width = 573
    Height = 178
    Brush.Style = bsClear
  end
  object Shape2: TShape
    Left = 8
    Top = 193
    Width = 721
    Height = 453
    Brush.Style = bsClear
  end
  inline Frame11: TFrame1
    Left = 19
    Top = 201
    Width = 700
    Height = 443
    TabOrder = 0
    ExplicitLeft = 19
    ExplicitTop = 201
    ExplicitHeight = 443
  end
  inline Frame21: TFrame2
    Left = 16
    Top = 17
    Width = 556
    Height = 162
    Color = clBtnFace
    ParentBackground = False
    ParentColor = False
    TabOrder = 1
    ExplicitLeft = 16
    ExplicitTop = 17
    ExplicitHeight = 162
    inherited Edit1: TEdit
      OnKeyDown = Frame21Edit1KeyDown
    end
    inherited DBGrid1: TDBGrid
      OnDblClick = Frame21DBGrid1DblClick
    end
  end
  object Button1: TButton
    Left = 61
    Top = 653
    Width = 145
    Height = 25
    Caption = 'Guardar cambios'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 293
    Top = 653
    Width = 145
    Height = 25
    Caption = 'Cancelar cambios'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 523
    Top = 653
    Width = 145
    Height = 25
    Caption = 'Salir'
    TabOrder = 4
    OnClick = Button3Click
  end
end
