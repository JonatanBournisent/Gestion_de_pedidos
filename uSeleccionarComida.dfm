object fSeleccionarComida: TfSeleccionarComida
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Seleccionar una comida'
  ClientHeight = 351
  ClientWidth = 576
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  inline Frame41: TFrame4
    Left = -1
    Top = 0
    Width = 574
    Height = 169
    Color = 11581943
    ParentBackground = False
    ParentColor = False
    TabOrder = 0
    ExplicitLeft = -1
    ExplicitWidth = 574
    inherited DBGrid1: TDBGrid
      Top = 30
      OnDblClick = Frame41DBGrid1DblClick
      OnKeyDown = Frame41DBGrid1KeyDown
    end
  end
  object Button1: TButton
    Left = 453
    Top = 3
    Width = 119
    Height = 25
    Caption = 'Agregar una comida'
    TabOrder = 1
    OnClick = Button1Click
  end
end
