object fAgregarComida: TfAgregarComida
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Agregar una nueva comida.'
  ClientHeight = 346
  ClientWidth = 615
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 9
    Top = 7
    Width = 597
    Height = 290
    Brush.Style = bsClear
  end
  inline Frame31: TFrame3
    Left = 18
    Top = 19
    Width = 577
    Height = 270
    TabOrder = 0
    ExplicitLeft = 18
    ExplicitTop = 19
    ExplicitWidth = 577
    ExplicitHeight = 270
  end
  object Button1: TButton
    Left = 47
    Top = 309
    Width = 130
    Height = 25
    Caption = 'Guardar'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 240
    Top = 309
    Width = 130
    Height = 25
    Caption = 'Cancelar'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 434
    Top = 309
    Width = 130
    Height = 25
    Caption = 'Salir'
    TabOrder = 3
    OnClick = Button3Click
  end
end
