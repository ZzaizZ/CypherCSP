object Form2: TForm2
  Left = 0
  Top = 0
  Caption = #1057#1086#1093#1088#1072#1085#1077#1085#1080#1077' '#1082#1083#1102#1095#1072' '#1074' '#1092#1072#1081#1083
  ClientHeight = 105
  ClientWidth = 298
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lblPassPhrase: TLabel
    Left = 24
    Top = 16
    Width = 89
    Height = 13
    Caption = #1055#1072#1088#1086#1083#1100#1085#1072#1103' '#1092#1088#1072#1079#1072
  end
  object lblApprovePassPhrase: TLabel
    Left = 24
    Top = 48
    Width = 83
    Height = 13
    Caption = #1055#1086#1076#1090#1074#1077#1088#1078#1076#1077#1085#1080#1077
  end
  object tedPassPhrase: TEdit
    Left = 136
    Top = 16
    Width = 137
    Height = 21
    TabOrder = 0
    TextHint = #1055#1072#1088#1086#1083#1100
  end
  object tedApprovePassPhrase: TEdit
    Left = 136
    Top = 45
    Width = 137
    Height = 21
    TabOrder = 1
    TextHint = #1055#1086#1076#1090#1074#1077#1088#1078#1076#1077#1085#1080#1077' '#1087#1072#1088#1086#1083#1103
  end
  object btnSaveKey: TButton
    Left = 112
    Top = 72
    Width = 75
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 2
    OnClick = btnSaveKeyClick
  end
  object keySaveDialog: TSaveDialog
    Left = 208
    Top = 72
  end
end
