object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'Area'
  ClientHeight = 449
  ClientWidth = 718
  Color = clBtnFace
  Constraints.MinHeight = 250
  Constraints.MinWidth = 480
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object pnlViewport: TPanel
    AlignWithMargins = True
    Left = 16
    Top = 130
    Width = 686
    Height = 303
    Margins.Left = 16
    Margins.Top = 16
    Margins.Right = 16
    Margins.Bottom = 16
    Align = alClient
    BevelOuter = bvLowered
    Caption = 'pnlViewport'
    ShowCaption = False
    TabOrder = 0
    OnResize = pnlViewportResize
    ExplicitWidth = 518
    ExplicitHeight = 200
    DesignSize = (
      686
      303)
    object paintboxViewport: TPaintBox
      Left = 1
      Top = 1
      Width = 684
      Height = 301
      Cursor = crCross
      Align = alClient
      OnMouseDown = paintboxViewportMouseDown
      OnMouseLeave = paintboxViewportMouseLeave
      OnMouseMove = paintboxViewportMouseMove
      OnMouseUp = paintboxViewportMouseUp
      OnPaint = paintboxViewportPaint
      ExplicitTop = 0
      ExplicitWidth = 516
      ExplicitHeight = 198
    end
    object lblHitTest: TLabel
      Left = 657
      Top = 281
      Width = 5
      Height = 13
      Anchors = [akRight, akBottom]
      Caption = '-'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ExplicitLeft = 574
      ExplicitTop = 251
    end
    object Label5: TLabel
      Left = 639
      Top = 281
      Width = 16
      Height = 13
      Alignment = taRightJustify
      Anchors = [akRight, akBottom]
      Caption = 'hit:'
      ExplicitLeft = 556
      ExplicitTop = 251
    end
    object Label6: TLabel
      Left = 9
      Top = 11
      Width = 14
      Height = 13
      Alignment = taRightJustify
      Caption = 'W:'
    end
    object lblWidth: TLabel
      Left = 26
      Top = 11
      Width = 4
      Height = 13
      Caption = '-'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 12
      Top = 22
      Width = 11
      Height = 13
      Alignment = taRightJustify
      Caption = 'H:'
    end
    object lblHeight: TLabel
      Left = 26
      Top = 22
      Width = 4
      Height = 13
      Caption = '-'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object lblCoords: TLabel
      Left = 9
      Top = 281
      Width = 3
      Height = 13
      Anchors = [akLeft, akBottom]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitTop = 178
    end
    object lblBoundingBox: TLabel
      Left = 675
      Top = 11
      Width = 3
      Height = 13
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      ExplicitLeft = 507
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 51
    Width = 718
    Height = 63
    Align = alTop
    BevelOuter = bvNone
    Caption = 'pnlText'
    ShowCaption = False
    TabOrder = 1
    ExplicitWidth = 550
    DesignSize = (
      718
      63)
    object Label1: TLabel
      Left = 19
      Top = 9
      Width = 22
      Height = 13
      Caption = 'Text'
    end
    object Label3: TLabel
      Left = 356
      Top = 9
      Width = 22
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'Font'
      ExplicitLeft = 188
    end
    object Label4: TLabel
      Left = 549
      Top = 9
      Width = 31
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'Height'
      ExplicitLeft = 381
    end
    object checkboxBold: TCheckBox
      Left = 627
      Top = 13
      Width = 71
      Height = 17
      Anchors = [akTop, akRight]
      Caption = 'Bold'
      TabOrder = 0
      OnClick = TextChanged
      ExplicitLeft = 459
    end
    object checkboxItalic: TCheckBox
      Left = 627
      Top = 36
      Width = 57
      Height = 17
      Anchors = [akTop, akRight]
      Caption = 'Italic'
      TabOrder = 1
      OnClick = TextChanged
      ExplicitLeft = 459
    end
    object comboboxFontName: TComboBox
      Left = 354
      Top = 24
      Width = 173
      Height = 21
      Style = csDropDownList
      Anchors = [akTop, akRight]
      TabOrder = 2
      OnChange = TextChanged
      ExplicitLeft = 186
    end
    object edtText: TEdit
      Left = 17
      Top = 24
      Width = 317
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 3
      Text = 'OqgAW'
      OnChange = TextChanged
      ExplicitWidth = 149
    end
    object edtTextSize: TEdit
      Left = 547
      Top = 24
      Width = 65
      Height = 21
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      NumbersOnly = True
      TabOrder = 4
      Text = '180'
      OnExit = TextChanged
      OnKeyPress = edtTextSizeKeyPress
      ExplicitLeft = 379
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 718
    Height = 51
    Align = alTop
    BevelOuter = bvNone
    Caption = 'Panel2'
    ShowCaption = False
    TabOrder = 2
    ExplicitWidth = 550
    DesignSize = (
      718
      51)
    object Label7: TLabel
      Left = 608
      Top = 9
      Width = 32
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'Viewer'
      ExplicitLeft = 440
    end
    object Label2: TLabel
      Left = 114
      Top = 9
      Width = 36
      Height = 13
      Caption = 'Method'
    end
    object Button1: TButton
      Left = 17
      Top = 22
      Width = 75
      Height = 25
      Action = actArea
      TabOrder = 0
    end
    object comboboxRenderer: TComboBox
      Left = 606
      Top = 24
      Width = 96
      Height = 21
      Style = csDropDownList
      Anchors = [akTop, akRight]
      TabOrder = 1
      OnChange = comboboxRendererChange
      ExplicitLeft = 438
    end
    object comboboxAreaMethod: TComboBox
      Left = 112
      Top = 24
      Width = 137
      Height = 21
      Style = csDropDownList
      TabOrder = 2
      OnChange = comboboxAreaMethodChange
    end
  end
  object ActionList1: TActionList
    Left = 208
    Top = 160
    object actArea: TAction
      Caption = 'Area'
      OnExecute = actAreaExecute
      OnUpdate = actAreaUpdate
    end
  end
end
