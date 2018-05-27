object mainForm: TmainForm
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #1064#1080#1092#1088#1072#1090#1086#1088'/'#1044#1077#1096#1080#1092#1088#1072#1090#1086#1088
  ClientHeight = 240
  ClientWidth = 390
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
  object pcMain: TPageControl
    Left = 8
    Top = 5
    Width = 377
    Height = 228
    ActivePage = TabSheet1
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'TabSheet1'
      object algorithmLabel: TLabel
        Left = 3
        Top = 7
        Width = 115
        Height = 13
        Caption = #1040#1083#1075#1086#1088#1080#1090#1084' '#1096#1080#1092#1088#1086#1074#1072#1085#1080#1103
      end
      object passwordLabel: TLabel
        Left = 3
        Top = 61
        Width = 89
        Height = 13
        Caption = #1057#1077#1082#1088#1077#1090#1085#1072#1103' '#1092#1088#1072#1079#1072
      end
      object algorithmComboBox: TComboBox
        Left = 3
        Top = 26
        Width = 361
        Height = 21
        TabOrder = 0
        OnChange = algorithmComboBoxChange
        Items.Strings = (
          #1043#1054#1057#1058' 28147-89 '#1050#1088#1080#1087#1090#1086#1055#1088#1086' CSP')
      end
      object chooseKeyCheckBox: TCheckBox
        Left = 202
        Top = 61
        Width = 170
        Height = 17
        Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1092#1072#1081#1083' '#1082#1083#1102#1095#1072
        TabOrder = 1
        OnClick = chooseKeyCheckBoxClick
      end
      object decryptButton: TButton
        Left = 189
        Top = 111
        Width = 175
        Height = 37
        Caption = #1056#1072#1089#1096#1080#1092#1088#1086#1074#1072#1090#1100
        Enabled = False
        TabOrder = 2
        OnClick = decryptButtonClick
      end
      object encryptButton: TButton
        Left = 3
        Top = 111
        Width = 180
        Height = 37
        Caption = #1047#1072#1096#1080#1092#1088#1086#1074#1072#1090#1100
        Enabled = False
        TabOrder = 3
        OnClick = encryptButtonClick
      end
      object passwordEdit: TEdit
        Left = 3
        Top = 84
        Width = 361
        Height = 21
        TabOrder = 4
        OnChange = passwordEditChange
      end
      object saveKeyButton: TButton
        Left = 3
        Top = 154
        Width = 361
        Height = 37
        Caption = #1057#1075#1077#1085#1077#1088#1080#1088#1086#1074#1072#1090#1100' '#1092#1072#1081#1083' '#1082#1083#1102#1095#1072
        TabOrder = 5
        OnClick = saveKeyButtonClick
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'TabSheet2'
      ImageIndex = 1
      object ipLabel: TLabel
        Left = 7
        Top = 46
        Width = 87
        Height = 13
        Caption = 'IP '#1072#1076#1088#1077#1089' '#1089#1077#1088#1074#1077#1088#1072
      end
      object portLabel: TLabel
        Left = 110
        Top = 46
        Width = 69
        Height = 13
        Caption = #1055#1086#1088#1090' '#1089#1077#1088#1074#1077#1088#1072
      end
      object lblContainerName: TLabel
        Left = 7
        Top = 14
        Width = 55
        Height = 13
        Caption = #1050#1086#1085#1090#1077#1081#1085#1077#1088
      end
      object ipEdit: TEdit
        Left = 5
        Top = 65
        Width = 89
        Height = 21
        TabOrder = 0
        Text = '127.0.0.1'
        OnKeyPress = ipEditKeyPress
      end
      object portEdit: TEdit
        Left = 100
        Top = 65
        Width = 89
        Height = 21
        NumbersOnly = True
        TabOrder = 1
        Text = '4444'
      end
      object sendButton: TButton
        Left = 5
        Top = 98
        Width = 361
        Height = 33
        Caption = #1055#1077#1088#1077#1076#1072#1090#1100' '#1092#1072#1081#1083
        TabOrder = 2
        OnClick = sendButtonClick
      end
      object serverOffButton: TButton
        Left = 195
        Top = 59
        Width = 171
        Height = 33
        Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1089#1077#1088#1074#1077#1088
        TabOrder = 3
        Visible = False
        OnClick = serverOffButtonClick
      end
      object btnSettings: TButton
        Left = 195
        Top = 7
        Width = 171
        Height = 25
        Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103' '#1082#1083#1102#1095#1077#1081
        TabOrder = 4
        OnClick = btnSettingsClick
      end
      object serverOnButton: TButton
        Left = 195
        Top = 59
        Width = 171
        Height = 33
        Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1100' '#1089#1077#1088#1074#1077#1088
        TabOrder = 5
        OnClick = serverOnButtonClick
      end
      object tedContainerName: TEdit
        Left = 66
        Top = 11
        Width = 121
        Height = 21
        TabOrder = 6
        TextHint = 'DefaultContainer'
      end
      object btnEncrypt: TButton
        Left = 6
        Top = 97
        Width = 361
        Height = 33
        Caption = #1056#1072#1089#1096#1080#1092#1088#1086#1074#1072#1090#1100' '#1087#1086#1083#1091#1095#1077#1085#1085#1086#1077
        TabOrder = 7
        Visible = False
        OnClick = btnEncryptClick
      end
    end
  end
  object inputOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1080#1089#1093#1086#1076#1085#1099#1081' '#1092#1072#1081#1083
    Left = 80
    Top = 467
  end
  object outputOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1082#1086#1085#1077#1095#1085#1099#1081' '#1092#1072#1081#1083
    Left = 88
    Top = 371
  end
  object keyOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1092#1072#1081#1083' '#1082#1083#1102#1095#1072
    Left = 31
    Top = 412
  end
  object sendOpenDialog: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1092#1072#1081#1083' '#1076#1083#1103' '#1087#1077#1088#1077#1076#1072#1095#1080
    Left = 152
    Top = 408
  end
  object odOpenPubKey: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1086#1090#1082#1088#1099#1090#1099#1081' '#1082#1083#1102#1095' '#1087#1086#1083#1091#1095#1072#1090#1077#1083#1103
    Left = 36
    Top = 325
  end
  object odOpenSessionKey: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1082#1083#1102#1095' '#1096#1080#1092#1088#1086#1074#1072#1085#1080#1103
    Left = 116
    Top = 317
  end
  object odResponderPubKey: TOpenDialog
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1086#1090#1082#1088#1099#1090#1099#1081' '#1082#1083#1102#1095' '#1086#1090#1087#1088#1072#1074#1080#1090#1077#1083#1103
    Left = 216
    Top = 328
  end
  object odOpenEncFile: TOpenDialog
    Title = #1059#1082#1072#1078#1080#1090#1077' '#1088#1072#1089#1096#1080#1092#1088#1086#1074#1099#1074#1072#1077#1084#1099#1081' '#1092#1072#1081#1083
    Left = 312
    Top = 328
  end
end
