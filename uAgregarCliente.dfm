object fAgregarCliente: TfAgregarCliente
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Agregar un nuevo cliente'
  ClientHeight = 520
  ClientWidth = 729
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 8
    Top = 8
    Width = 713
    Height = 454
    Brush.Style = bsClear
  end
  inline Frame11: TFrame1
    Left = 14
    Top = 14
    Width = 699
    Height = 440
    TabOrder = 0
    ExplicitLeft = 14
    ExplicitTop = 14
    ExplicitWidth = 699
    ExplicitHeight = 440
    inherited SQLTable1: TSQLTable
      Left = 640
      Top = 104
    end
    inherited Query3: TSQLQuery
      Left = 648
      Top = 232
    end
  end
  object Button1: TButton
    Left = 78
    Top = 479
    Width = 150
    Height = 25
    Caption = 'Guardar'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 286
    Top = 479
    Width = 150
    Height = 25
    Caption = 'Cancelar'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 494
    Top = 479
    Width = 150
    Height = 25
    Caption = 'Salir'
    TabOrder = 3
    OnClick = Button3Click
  end
end
