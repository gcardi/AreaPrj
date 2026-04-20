object frmeTextData: TfrmeTextData
  Left = 0
  Top = 0
  Width = 637
  Height = 66
  Align = alClient
  TabOrder = 0
  DesignSize = (
    637
    66)
  object Label3: TLabel
    Left = 301
    Top = 8
    Width = 24
    Height = 15
    Anchors = [akTop, akRight]
    Caption = 'Font'
    ExplicitLeft = 446
  end
  object Label1: TLabel
    Left = 19
    Top = 8
    Width = 21
    Height = 15
    Caption = 'Text'
  end
  object Label4: TLabel
    Left = 494
    Top = 8
    Width = 36
    Height = 15
    Anchors = [akTop, akRight]
    Caption = 'Height'
    ExplicitLeft = 639
  end
  object edtText: TEdit
    Left = 17
    Top = 24
    Width = 262
    Height = 23
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 0
    Text = 'OqgAW'
    ExplicitWidth = 407
  end
  object checkboxItalic: TCheckBox
    Left = 574
    Top = 35
    Width = 57
    Height = 17
    Anchors = [akTop, akRight]
    Caption = 'Italic'
    TabOrder = 1
    ExplicitLeft = 719
  end
  object checkboxBold: TCheckBox
    Left = 574
    Top = 12
    Width = 71
    Height = 17
    Anchors = [akTop, akRight]
    Caption = 'Bold'
    TabOrder = 2
    ExplicitLeft = 719
  end
  object edtTextSize: TEdit
    Left = 494
    Top = 23
    Width = 65
    Height = 23
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    NumbersOnly = True
    TabOrder = 3
    Text = '180'
    ExplicitLeft = 639
  end
  object comboboxFontName: TComboBox
    Left = 301
    Top = 23
    Width = 173
    Height = 23
    Style = csDropDownList
    Anchors = [akTop, akRight]
    TabOrder = 4
    ExplicitLeft = 446
  end
end
