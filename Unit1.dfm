object mainForm: TmainForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1064#1080#1092#1088#1072#1090#1086#1088'/'#1044#1077#1096#1080#1092#1088#1072#1090#1086#1088
  ClientHeight = 726
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
  object contSendLabel: TLabel
    Left = 8
    Top = 299
    Width = 151
    Height = 13
    Caption = #1048#1084#1103' '#1082#1086#1085#1090#1077#1081#1085#1077#1088#1072' '#1086#1090#1087#1088#1072#1074#1080#1090#1077#1083#1103
  end
  object pathOpenRespondLabel: TLabel
    Left = 8
    Top = 329
    Width = 155
    Height = 13
    Caption = #1055#1091#1090#1100' '#1086#1090#1082#1088'. '#1082#1083#1102#1095#1072' '#1087#1086#1083#1091#1095#1072#1090#1077#1083#1103
  end
  object pathSymkeyLabel: TLabel
    Left = 8
    Top = 356
    Width = 156
    Height = 13
    Caption = #1055#1091#1090#1100' '#1076#1086' '#1089#1080#1084#1084#1077#1090#1088#1080#1095#1085#1086#1075#1086' '#1082#1083#1102#1095#1072
  end
  object pathEncrSymkeyLabel: TLabel
    Left = 11
    Top = 383
    Width = 171
    Height = 13
    Caption = #1055#1091#1090#1100' '#1076#1086' '#1073#1091#1076#1091#1097'. '#1079#1072#1096#1080#1092#1088'. '#1089#1080#1084'. '#1082#1083'.'
  end
  object pathEncrSymkeyDecrLabel: TLabel
    Left = 11
    Top = 454
    Width = 147
    Height = 13
    Caption = #1055#1091#1090#1100' '#1076#1086' '#1079#1072#1096#1080#1092#1088'. '#1089#1080#1084'. '#1082#1083#1102#1095#1072
  end
  object pathOpenSendLabel: TLabel
    Left = 8
    Top = 481
    Width = 177
    Height = 13
    Caption = #1055#1091#1090#1100' '#1076#1086' '#1086#1090#1082#1088'. '#1082#1083#1102#1095#1072' '#1086#1090#1087#1088#1072#1074#1080#1090#1077#1083#1103
  end
  object contResponderLabel: TLabel
    Left = 11
    Top = 512
    Width = 148
    Height = 13
    Caption = #1048#1084#1103' '#1082#1086#1085#1090#1077#1081#1085#1077#1088#1072'  '#1087#1086#1083#1091#1095#1072#1090#1077#1083#1103
  end
  object pathEncrFileLabel: TLabel
    Left = 8
    Top = 538
    Width = 165
    Height = 13
    Caption = #1055#1091#1090#1100' '#1076#1086' '#1079#1072#1096#1080#1092#1088#1086#1074#1072#1085#1085#1086#1075#1086' '#1092#1072#1081#1083#1072
  end
  object pathDecryptFileLabel: TLabel
    Left = 8
    Top = 563
    Width = 171
    Height = 13
    Caption = #1055#1091#1090#1100' '#1076#1086' '#1088#1072#1089#1096#1080#1092#1088#1086#1074#1072#1085#1085#1086#1075#1086' '#1092#1072#1081#1083#1072
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
    TabOrder = 18
    OnClick = sendButtonClick
  end
  object serverOnButton: TButton
    Left = 196
    Top = 185
    Width = 172
    Height = 33
    Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1100' '#1089#1077#1088#1074#1077#1088
    TabOrder = 19
    OnClick = serverOnButtonClick
  end
  object ipEdit: TEdit
    Left = 8
    Top = 195
    Width = 89
    Height = 21
    TabOrder = 20
    Text = '127.0.0.1'
    OnKeyPress = ipEditKeyPress
  end
  object portEdit: TEdit
    Left = 101
    Top = 195
    Width = 89
    Height = 21
    NumbersOnly = True
    TabOrder = 21
    Text = '4444'
  end
  object serverOffButton: TButton
    Left = 196
    Top = 185
    Width = 172
    Height = 33
    Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1089#1077#1088#1074#1077#1088
    TabOrder = 22
    Visible = False
    OnClick = serverOffButtonClick
  end
  object btnGenerateKeyPair: TButton
    Left = 8
    Top = 256
    Width = 360
    Height = 37
    Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103' '#1082#1083#1102#1095#1077#1074#1086#1081' '#1087#1072#1088#1099
    TabOrder = 6
    OnClick = btnGenerateKeyPairClick
  end
  object btnDecryptSessionKey: TButton
    Left = 8
    Top = 593
    Width = 360
    Height = 37
    Caption = #1056#1072#1089#1096#1080#1092#1088#1086#1074#1072#1090#1100' '#1089#1080#1084#1084#1077#1090#1088#1080#1095#1085#1099#1081' '#1082#1083#1102#1095' '#1080' '#1088#1072#1089#1096#1080#1092#1088#1086#1074#1072#1090#1100' '#1080#1084' '#1092#1072#1081#1083
    TabOrder = 7
    OnClick = btnDecryptSessionKeyClick
  end
  object btnEncSessionKey: TButton
    Left = 8
    Top = 411
    Width = 360
    Height = 37
    Caption = #1064#1080#1092#1088#1086#1074#1072#1085#1080#1077' '#1089#1080#1084#1084#1077#1090#1088#1080#1095#1085#1086#1075#1086' '#1082#1083#1102#1095#1072
    TabOrder = 8
    OnClick = btnEncSessionKeyClick
  end
  object tedSenderContainerName: TEdit
    Left = 189
    Top = 299
    Width = 179
    Height = 21
    TabOrder = 9
    Text = 'cc_send'
  end
  object tedResponderPKPath: TEdit
    Left = 189
    Top = 326
    Width = 179
    Height = 21
    TabOrder = 10
    Text = 'C:\\Users\'#1053#1080#1082#1080#1090#1072'\Desktop\cc_respond.pubkey'
  end
  object tedInSessionKey: TEdit
    Left = 189
    Top = 353
    Width = 179
    Height = 21
    TabOrder = 11
    Text = 'C:\\Users\'#1053#1080#1082#1080#1090#1072'\Desktop\key.symkey'
  end
  object tedOutSessionKey: TEdit
    Left = 189
    Top = 380
    Width = 179
    Height = 21
    TabOrder = 12
    Text = 'C:\\Users\'#1053#1080#1082#1080#1090#1072'\Desktop\key.symkey.encr'
  end
  object encrSymkeyEdit: TEdit
    Left = 189
    Top = 454
    Width = 179
    Height = 21
    TabOrder = 13
    Text = 'C:\\Users\'#1053#1080#1082#1080#1090#1072'\Desktop\key.symkey.encr'
  end
  object pathSendPubEdit: TEdit
    Left = 189
    Top = 481
    Width = 179
    Height = 21
    TabOrder = 14
    Text = 'C:\\Users\'#1053#1080#1082#1080#1090#1072'\Desktop\cc_send.pubkey'
  end
  object contRespondEdit: TEdit
    Left = 189
    Top = 508
    Width = 179
    Height = 21
    TabOrder = 15
    Text = 'cc_respond'
  end
  object encrFileEdit: TEdit
    Left = 189
    Top = 535
    Width = 179
    Height = 21
    TabOrder = 16
    Text = 'C:\\Users\'#1053#1080#1082#1080#1090#1072'\Desktop\Test.txt.enc'
  end
  object decrFileEdit: TEdit
    Left = 189
    Top = 562
    Width = 179
    Height = 21
    TabOrder = 17
    Text = 'C:\\Users\'#1053#1080#1082#1080#1090#1072'\Desktop\Test.txt'
  end
  object inputOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1080#1089#1093#1086#1076#1085#1099#1081' '#1092#1072#1081#1083
    Left = 192
    Top = 643
  end
  object outputOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1082#1086#1085#1077#1095#1085#1099#1081' '#1092#1072#1081#1083
    Left = 128
    Top = 643
  end
  object keyOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1092#1072#1081#1083' '#1082#1083#1102#1095#1072
    Left = 95
    Top = 644
  end
  object sendOpenDialog: TOpenDialog
    Left = 160
    Top = 640
  end
  object sdPublicKeySave: TOpenDialog
    Left = 224
    Top = 640
  end
end
