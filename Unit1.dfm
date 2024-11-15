object Form1: TForm1
  Left = 144
  Top = 167
  Width = 1689
  Height = 727
  Caption = #1055#1040#1050' "'#1040#1090#1083#1072#1089'-'#1057#1064#1055'". '#1062#1080#1092#1088#1086#1074#1086#1081' '#1076#1074#1086#1081#1085#1080#1082'. '#1054#1054#1054' "'#1048#1053#1058#1045#1061#1069#1050#1057#1055#1045#1056#1058#1048#1047#1040'"'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 16
    Top = 16
    Width = 1100
    Height = 576
  end
  object SaveResult: TButton
    Left = 32
    Top = 608
    Width = 209
    Height = 25
    Caption = 'SaveResult'
    TabOrder = 0
    OnClick = SaveResultClick
  end
  object GroupBox1: TGroupBox
    Left = 1152
    Top = 16
    Width = 473
    Height = 297
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1089#1080#1075#1085#1072#1083#1072
    TabOrder = 1
    object GroupBox2: TGroupBox
      Left = 32
      Top = 32
      Width = 201
      Height = 73
      Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1080#1089#1090#1086#1095#1085#1080#1082#1086#1074
      TabOrder = 0
      object SinNumWin: TEdit
        Left = 16
        Top = 24
        Width = 121
        Height = 21
        TabOrder = 0
        Text = '4'
      end
    end
    object GroupBox3: TGroupBox
      Left = 240
      Top = 32
      Width = 201
      Height = 73
      Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1072#1103' '#1095#1072#1089#1090#1086#1090#1072', %'
      TabOrder = 1
      object MaxFreWin: TEdit
        Left = 16
        Top = 24
        Width = 121
        Height = 21
        TabOrder = 0
        Text = '80'
      end
    end
    object GroupBox4: TGroupBox
      Left = 32
      Top = 120
      Width = 201
      Height = 73
      Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1072#1103' '#1072#1084#1087#1083#1080#1090#1091#1076#1072
      TabOrder = 2
      object MaxAmpWin: TEdit
        Left = 16
        Top = 24
        Width = 121
        Height = 21
        TabOrder = 0
        Text = '4'
      end
    end
    object GroupBox5: TGroupBox
      Left = 240
      Top = 120
      Width = 201
      Height = 73
      Caption = #1059#1088#1086#1074#1077#1085#1100' '#1096#1091#1084#1072
      TabOrder = 3
      object NoisLevWin: TEdit
        Left = 16
        Top = 24
        Width = 121
        Height = 21
        TabOrder = 0
        Text = '0'
      end
    end
    object NewSigCheck: TCheckBox
      Left = 40
      Top = 224
      Width = 97
      Height = 17
      Caption = #1053#1086#1074#1099#1081' '#1089#1080#1075#1085#1072#1083
      Checked = True
      State = cbChecked
      TabOrder = 4
    end
    object GroupBox6: TGroupBox
      Left = 240
      Top = 200
      Width = 201
      Height = 73
      Caption = #1055#1086#1088#1086#1075' '#1087#1086' '#1089#1087#1077#1082#1090#1088#1091
      TabOrder = 5
      object SPorogWin: TEdit
        Left = 16
        Top = 24
        Width = 121
        Height = 21
        TabOrder = 0
        Text = '12'
      end
    end
  end
  object Test: TButton
    Left = 800
    Top = 616
    Width = 137
    Height = 25
    Caption = #1058#1077#1089#1090
    TabOrder = 2
    OnClick = TestClick
  end
  object OscilView: TRadioButton
    Left = 984
    Top = 608
    Width = 113
    Height = 17
    Caption = 'OscilView'
    TabOrder = 3
    OnClick = OscilViewClick
  end
  object SpectrView: TRadioButton
    Left = 984
    Top = 632
    Width = 113
    Height = 17
    Caption = 'SpectrView'
    Checked = True
    TabOrder = 4
    TabStop = True
    OnClick = SpectrViewClick
  end
  object GroupBox7: TGroupBox
    Left = 1152
    Top = 336
    Width = 201
    Height = 73
    Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1075#1072#1088#1084#1086#1085#1080#1082
    TabOrder = 5
    object HarmNumWin: TEdit
      Left = 16
      Top = 24
      Width = 121
      Height = 21
      TabOrder = 0
    end
  end
  object GroupBox8: TGroupBox
    Left = 1384
    Top = 336
    Width = 201
    Height = 73
    Caption = #1069#1092#1092#1077#1082#1090#1080#1074#1085#1086#1089#1090#1100' '#1087#1086' '#1089#1087#1077#1082#1090#1088#1091
    TabOrder = 6
    object SpectrEffWin: TEdit
      Left = 16
      Top = 24
      Width = 121
      Height = 21
      TabOrder = 0
    end
  end
  object GroupBox9: TGroupBox
    Left = 1152
    Top = 424
    Width = 201
    Height = 105
    Caption = #1052#1086#1097#1085#1086#1089#1090#1100' '#1080#1079#1083#1091#1095#1077#1085#1080#1103', '#1042#1090
    TabOrder = 7
    object PowerWin: TEdit
      Left = 16
      Top = 24
      Width = 121
      Height = 21
      TabOrder = 0
    end
    object Power0Win: TEdit
      Left = 16
      Top = 56
      Width = 121
      Height = 21
      TabOrder = 1
    end
  end
  object GroupBox10: TGroupBox
    Left = 560
    Top = 600
    Width = 201
    Height = 57
    Caption = #1055#1088#1086#1094#1077#1089#1089' '#1074#1086#1089#1089#1090#1072#1085#1086#1074#1083#1077#1085#1080#1103
    TabOrder = 8
    object ProcSelBox: TComboBox
      Left = 16
      Top = 24
      Width = 169
      Height = 21
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 0
      Text = #1055#1088#1086#1094#1077#1089#1089' 0'
      Items.Strings = (
        #1055#1088#1086#1094#1077#1089#1089' 0'
        #1055#1088#1086#1094#1077#1089#1089' 1')
    end
  end
  object GroupBox11: TGroupBox
    Left = 1384
    Top = 424
    Width = 201
    Height = 105
    Caption = #1050#1086#1088#1088#1077#1083#1103#1094#1080#1103
    TabOrder = 9
    object Label1: TLabel
      Left = 8
      Top = 32
      Width = 57
      Height = 13
      Caption = #1055#1086' '#1089#1087#1077#1082#1090#1088#1091
    end
    object Label2: TLabel
      Left = 8
      Top = 56
      Width = 61
      Height = 13
      Caption = #1055#1086' '#1074#1088#1077#1084#1077#1085#1080
    end
    object SCorrWin: TEdit
      Left = 96
      Top = 24
      Width = 81
      Height = 21
      TabOrder = 0
    end
    object TCorrWin: TEdit
      Left = 96
      Top = 56
      Width = 81
      Height = 21
      TabOrder = 1
    end
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Left = 1624
    Top = 344
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'csv'
    FileName = 'Result.csv'
    Filter = 'Excel|*.csv'
    Left = 1608
    Top = 400
  end
end
