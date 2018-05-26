object mainForm: TmainForm
  Left = 0
  Top = 0
  Caption = #1064#1080#1092#1088#1072#1090#1086#1088'/'#1044#1077#1096#1080#1092#1088#1072#1090#1086#1088
  ClientHeight = 461
  ClientWidth = 366
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
  object ipLabel: TLabel
    Left = 8
    Top = 176
    Width = 87
    Height = 13
    Caption = 'IP '#1072#1076#1088#1077#1089' '#1089#1077#1088#1074#1077#1088#1072
  end
  object portLabel: TLabel
    Left = 101
    Top = 176
    Width = 69
    Height = 13
    Caption = #1055#1086#1088#1090' '#1089#1077#1088#1074#1077#1088#1072
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
  object sendButton: TButton
    Left = 7
    Top = 224
    Width = 361
    Height = 33
    Caption = #1055#1077#1088#1077#1076#1072#1090#1100' '#1092#1072#1081#1083
    TabOrder = 6
    OnClick = sendButtonClick
  end
  object serverOnButton: TButton
    Left = 196
    Top = 185
    Width = 172
    Height = 33
    Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1100' '#1089#1077#1088#1074#1077#1088
    TabOrder = 7
    OnClick = serverOnButtonClick
  end
  object ipEdit: TEdit
    Left = 8
    Top = 195
    Width = 89
    Height = 21
    TabOrder = 8
    Text = '127.0.0.1'
    OnKeyPress = ipEditKeyPress
  end
  object portEdit: TEdit
    Left = 101
    Top = 195
    Width = 89
    Height = 21
    NumbersOnly = True
    TabOrder = 9
    Text = '4444'
  end
  object serverOffButton: TButton
    Left = 196
    Top = 185
    Width = 172
    Height = 33
    Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1089#1077#1088#1074#1077#1088
    TabOrder = 10
    Visible = False
    OnClick = serverOffButtonClick
  end
  object Button1: TButton
    Left = 152
    Top = 360
    Width = 175
    Height = 25
    Caption = 'Button1'
    TabOrder = 11
    OnClick = Button1Click
  end
  object inputOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1080#1089#1093#1086#1076#1085#1099#1081' '#1092#1072#1081#1083
    Left = 56
    Top = 267
  end
  object outputOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1082#1086#1085#1077#1095#1085#1099#1081' '#1092#1072#1081#1083
    Left = 32
    Top = 267
  end
  object keyOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1092#1072#1081#1083' '#1082#1083#1102#1095#1072
    Left = 7
    Top = 268
  end
  object sendOpenDialog: TOpenDialog
    Left = 88
    Top = 272
  end
end
