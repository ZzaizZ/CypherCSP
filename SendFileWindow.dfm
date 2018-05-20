object sendForm: TsendForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1042#1099#1073#1086#1088' '#1089#1077#1088#1074#1077#1088#1072' '#1076#1083#1103' '#1087#1077#1088#1077#1076#1072#1095#1080
  ClientHeight = 110
  ClientWidth = 192
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object ipLabel: TLabel
    Left = 16
    Top = 8
    Width = 150
    Height = 13
    Caption = 'IP '#1072#1076#1088#1077#1089' '#1091#1076#1072#1083#1077#1085#1085#1086#1075#1086' '#1089#1077#1088#1074#1077#1088#1072
  end
  object ipEdit: TEdit
    Left = 16
    Top = 27
    Width = 150
    Height = 21
    TabOrder = 0
    Text = '127.0.0.1'
  end
  object connectButton: TButton
    Left = 16
    Top = 54
    Width = 150
    Height = 35
    Caption = #1055#1077#1088#1077#1076#1072#1090#1100' '#1092#1072#1081#1083
    TabOrder = 1
    OnClick = connectButtonClick
  end
end
