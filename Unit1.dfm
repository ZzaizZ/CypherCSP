object mainForm: TmainForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1064#1080#1092#1088#1072#1090#1086#1088'/'#1044#1077#1096#1080#1092#1088#1072#1090#1086#1088
  ClientHeight = 209
  ClientWidth = 563
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
  object inputLabel: TLabel
    Left = 8
    Top = 37
    Width = 80
    Height = 13
    Caption = #1048#1089#1093#1086#1076#1085#1099#1081' '#1092#1072#1081#1083
  end
  object outputLabel: TLabel
    Left = 8
    Top = 80
    Width = 103
    Height = 13
    Caption = #1064#1080#1092#1088#1086#1074#1072#1085#1085#1099#1081' '#1092#1072#1081#1083
  end
  object keyLabel: TLabel
    Left = 8
    Top = 161
    Width = 62
    Height = 13
    Caption = #1060#1072#1081#1083' '#1082#1083#1102#1095#1072
    Visible = False
  end
  object passwordLabel: TLabel
    Left = 8
    Top = 121
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
    Left = 375
    Top = 42
    Width = 180
    Height = 35
    Caption = #1047#1072#1096#1080#1092#1088#1086#1074#1072#1090#1100
    Enabled = False
    TabOrder = 0
    OnClick = encryptButtonClick
  end
  object decryptButton: TButton
    Left = 375
    Top = 83
    Width = 180
    Height = 37
    Caption = #1056#1072#1089#1096#1080#1092#1088#1086#1074#1072#1090#1100
    Enabled = False
    TabOrder = 1
    OnClick = decryptButtonClick
  end
  object inputEdit: TEdit
    Left = 8
    Top = 56
    Width = 361
    Height = 21
    Hint = #1055#1088#1080' '#1076#1074#1086#1081#1085#1086#1084' '#1085#1072#1078#1072#1090#1080#1080' '#1086#1090#1082#1088#1086#1077#1090#1089#1103' '#1086#1082#1085#1086' '#1074#1099#1073#1086#1088#1072' '#1092#1072#1081#1083#1072
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnChange = inputEditChange
    OnDblClick = inputEditDblClick
  end
  object outputEdit: TEdit
    Left = 8
    Top = 94
    Width = 361
    Height = 21
    Hint = #1055#1088#1080' '#1076#1074#1086#1081#1085#1086#1084' '#1085#1072#1078#1072#1090#1080#1080' '#1086#1090#1082#1088#1086#1077#1090#1089#1103' '#1086#1082#1085#1086' '#1074#1099#1073#1086#1088#1072' '#1092#1072#1081#1083#1072
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    OnChange = outputEditChange
    OnDblClick = outputEditDblClick
  end
  object keyEdit: TEdit
    Left = 8
    Top = 180
    Width = 361
    Height = 21
    Hint = #1055#1088#1080' '#1076#1074#1086#1080#1085#1086#1084' '#1085#1072#1078#1072#1090#1080#1080' '#1086#1090#1082#1088#1086#1077#1090#1089#1103' '#1086#1082#1085#1086' '#1074#1099#1073#1086#1088#1072' '#1092#1072#1081#1083#1072
    ParentShowHint = False
    ShowHint = True
    TabOrder = 4
    Visible = False
    OnDblClick = keyEditDblClick
  end
  object passwordEdit: TEdit
    Left = 8
    Top = 140
    Width = 361
    Height = 21
    TabOrder = 5
    OnChange = passwordEditChange
  end
  object loadKeyButton: TButton
    Left = 375
    Top = 126
    Width = 180
    Height = 37
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1092#1072#1081#1083' '#1082#1083#1102#1095#1072
    TabOrder = 6
    Visible = False
  end
  object saveKeyButton: TButton
    Left = 375
    Top = 164
    Width = 180
    Height = 37
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1092#1072#1081#1083' '#1082#1083#1102#1095#1072
    TabOrder = 7
    Visible = False
    OnClick = saveKeyButtonClick
  end
  object algorithmComboBox: TComboBox
    Left = 8
    Top = 17
    Width = 361
    Height = 21
    TabOrder = 8
    Items.Strings = (
      #1043#1054#1057#1058' 28147-89 '#1050#1088#1080#1087#1090#1086#1055#1088#1086' CSP')
  end
  object chooseKeyCheckBox: TCheckBox
    Left = 375
    Top = 19
    Width = 170
    Height = 17
    Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1092#1072#1081#1083' '#1082#1083#1102#1095#1072
    Enabled = False
    TabOrder = 9
    OnClick = chooseKeyCheckBoxClick
  end
  object inputOpenDialog: TOpenDialog
    Left = 536
    Top = 195
  end
  object outputOpenDialog: TOpenDialog
    Left = 512
    Top = 195
  end
  object keyOpenDialog: TOpenDialog
    Left = 487
    Top = 195
  end
end
