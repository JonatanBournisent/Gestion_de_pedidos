object fMensajes: TfMensajes
  Left = 0
  Top = 0
  Caption = 'Mensajes'
  ClientHeight = 449
  ClientWidth = 559
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 84
    Height = 13
    Caption = 'T'#237'tulo de mensaje'
  end
  object CB: TComboBox
    Left = 8
    Top = 24
    Width = 145
    Height = 21
    TabOrder = 0
  end
  object Memo1: TMemo
    Left = 8
    Top = 64
    Width = 545
    Height = 377
    Lines.Strings = (
      'Memo1')
    TabOrder = 1
  end
  object Button1: TButton
    Left = 178
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Abrir'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 278
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Guardar'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 378
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Cancelar'
    TabOrder = 4
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 478
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Nuevo'
    TabOrder = 5
    OnClick = Button4Click
  end
  object Panel1: TPanel
    Left = 138
    Top = 104
    Width = 263
    Height = 105
    Caption = 'Panel1'
    ShowCaption = False
    TabOrder = 6
    object Edit1: TEdit
      Left = 14
      Top = 24
      Width = 235
      Height = 21
      TabOrder = 0
      Text = 'Edit1'
    end
    object Button5: TButton
      Left = 40
      Top = 64
      Width = 75
      Height = 25
      Caption = 'Aceptar'
      TabOrder = 1
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 144
      Top = 64
      Width = 75
      Height = 25
      Caption = 'Cancelar'
      TabOrder = 2
      OnClick = Button6Click
    end
  end
  object Panel2: TPanel
    Left = 138
    Top = 111
    Width = 263
    Height = 105
    Caption = 'Panel1'
    ShowCaption = False
    TabOrder = 7
    object Edit2: TEdit
      Left = 14
      Top = 24
      Width = 235
      Height = 21
      TabOrder = 0
      Text = 'Edit2'
    end
    object Button7: TButton
      Left = 40
      Top = 64
      Width = 75
      Height = 25
      Caption = 'Aceptar'
      TabOrder = 1
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = 144
      Top = 64
      Width = 75
      Height = 25
      Caption = 'Cancelar'
      TabOrder = 2
      OnClick = Button8Click
    end
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
      'User_Name=elsembrador'
      'Password=*-elsembrador63/*'
      'ServerCharSet=utf8mb4'
      'BlobSize=-1'
      'ErrorResourceFile='
      'LocaleCode=0000'
      'Compressed=False'
      'Encrypted=False'
      'ConnectTimeout=60')
    Left = 415
    Top = 143
  end
  object Query: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 463
    Top = 133
  end
  object MainMenu1: TMainMenu
    Left = 168
    Top = 65520
    object Acciones1: TMenuItem
      Caption = 'Acciones'
      object Modificartitulo1: TMenuItem
        Caption = 'Modificar titulo'
        OnClick = Modificartitulo1Click
      end
    end
  end
end
