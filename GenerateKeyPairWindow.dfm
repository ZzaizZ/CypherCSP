object Form3: TForm3
  Left = 0
  Top = 0
  Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103' '#1082#1083#1102#1095#1077#1081
  ClientHeight = 95
  ClientWidth = 260
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lblContainerName: TLabel
    Left = 15
    Top = 24
    Width = 82
    Height = 13
    Caption = #1048#1084#1103' '#1082#1086#1085#1090#1077#1081#1085#1077#1088#1072
  end
  object tedContainerName: TEdit
    Left = 120
    Top = 21
    Width = 121
    Height = 21
    TabOrder = 0
    TextHint = 'DefaultContainer'
  end
  object btnGenerate: TButton
    Left = 72
    Top = 56
    Width = 97
    Height = 25
    Caption = #1057#1075#1077#1085#1077#1088#1080#1088#1086#1074#1072#1090#1100
    TabOrder = 1
    OnClick = btnGenerateClick
  end
  object keyGenerateDialog: TSaveDialog
    Left = 184
    Top = 48
  end
end
