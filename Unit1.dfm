object mainForm: TmainForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1064#1080#1092#1088#1072#1090#1086#1088'/'#1044#1077#1096#1080#1092#1088#1072#1090#1086#1088
  ClientHeight = 518
  ClientWidth = 376
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  PixelsPerInch = 96
  TextHeight = 13
  object passwordLabel: TLabel
    Left = 8
    Top = 44
    Width = 89
    Height = 13
    Caption = #1057#1077#1082#1088#1077#1090#1085#1072#1103' '#1092#1088#1072#1079#1072
  end
  object algorithmLabel: TLabel
    Left = 8
    Top = 1
    Width = 115
    Height = 13
    Caption = #1040#1083#1075#1086#1088#1080#1090#1084' '#1096#1080#1092#1088#1086#1074#1072#1085#1080#1103
  end
  object encryptButton: TButton
    Left = 8
    Top = 90
    Width = 180
    Height = 37
    Caption = #1047#1072#1096#1080#1092#1088#1086#1074#1072#1090#1100
    Enabled = False
    TabOrder = 0
    OnClick = encryptButtonClick
  end
  object decryptButton: TButton
    Left = 189
    Top = 90
    Width = 180
    Height = 37
    Caption = #1056#1072#1089#1096#1080#1092#1088#1086#1074#1072#1090#1100
    Enabled = False
    TabOrder = 1
    OnClick = decryptButtonClick
  end
  object passwordEdit: TEdit
    Left = 8
    Top = 63
    Width = 361
    Height = 21
    TabOrder = 2
    OnChange = passwordEditChange
  end
  object saveKeyButton: TButton
    Left = 8
    Top = 133
    Width = 361
    Height = 37
    Caption = #1057#1075#1077#1085#1077#1088#1080#1088#1086#1074#1072#1090#1100' '#1092#1072#1081#1083' '#1082#1083#1102#1095#1072
    TabOrder = 3
    OnClick = saveKeyButtonClick
  end
  object algorithmComboBox: TComboBox
    Left = 8
    Top = 17
    Width = 361
    Height = 21
    TabOrder = 4
    OnChange = algorithmComboBoxChange
    Items.Strings = (
      #1043#1054#1057#1058' 28147-89 '#1050#1088#1080#1087#1090#1086#1055#1088#1086' CSP')
  end
  object chooseKeyCheckBox: TCheckBox
    Left = 199
    Top = 44
    Width = 170
    Height = 17
    Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1092#1072#1081#1083' '#1082#1083#1102#1095#1072
    TabOrder = 5
    OnClick = chooseKeyCheckBoxClick
  end
  object btnGenerateKeyPair: TButton
    Left = 8
    Top = 248
    Width = 180
    Height = 37
    Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103' '#1082#1083#1102#1095#1077#1074#1086#1081' '#1087#1072#1088#1099
    TabOrder = 6
    OnClick = btnGenerateKeyPairClick
  end
  object btnLoadResponderKey: TButton
    Left = 8
    Top = 291
    Width = 361
    Height = 37
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1086#1090#1082#1088#1099#1090#1099#1081' '#1082#1083#1102#1095' '#1074#1090#1086#1088#1086#1075#1086' '#1072#1073#1086#1085#1077#1085#1090#1072
    TabOrder = 7
    OnClick = btnLoadResponderKeyClick
  end
  object btnLoadKeyPair: TButton
    Left = 189
    Top = 248
    Width = 180
    Height = 37
    Caption = #1047#1072#1075#1088#1091#1079#1082#1072' '#1082#1083#1102#1095#1077#1074#1086#1075#1086' '#1085#1086#1089#1080#1090#1077#1083#1103
    TabOrder = 8
    OnClick = btnLoadKeyPairClick
  end
  object inputOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1080#1089#1093#1086#1076#1085#1099#1081' '#1092#1072#1081#1083
    Left = 128
    Top = 187
  end
  object outputOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1082#1086#1085#1077#1095#1085#1099#1081' '#1092#1072#1081#1083
    Left = 56
    Top = 179
  end
  object keyOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1092#1072#1081#1083' '#1082#1083#1102#1095#1072
    Left = 7
    Top = 180
  end
  object sdPublicKeySave: TOpenDialog
    Left = 304
    Top = 192
  end
end
