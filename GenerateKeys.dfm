object Form4: TForm4
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103' '#1082#1083#1102#1095#1077#1081
  ClientHeight = 117
  ClientWidth = 273
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 24
    Width = 111
    Height = 13
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1082#1086#1085#1090#1077#1081#1085#1077#1088#1072
  end
  object tedContainerName: TEdit
    Left = 133
    Top = 21
    Width = 121
    Height = 21
    TabOrder = 0
    TextHint = 'Default Container'
  end
  object btnGenerateKeys: TButton
    Left = 64
    Top = 84
    Width = 129
    Height = 25
    Caption = #1057#1075#1077#1085#1077#1088#1080#1088#1086#1074#1072#1090#1100' '#1082#1083#1102#1095#1080
    TabOrder = 1
    OnClick = btnGenerateKeysClick
  end
  object cbGenSessionKey: TCheckBox
    Left = 16
    Top = 54
    Width = 193
    Height = 17
    Caption = #1057#1075#1077#1085#1077#1088#1080#1088#1086#1074#1072#1090#1100' '#1089#1077#1089#1089#1080#1086#1085#1085#1099#1081' '#1082#1083#1102#1095
    TabOrder = 2
  end
  object keyGenerateDialog: TSaveDialog
    Left = 224
    Top = 48
  end
end
