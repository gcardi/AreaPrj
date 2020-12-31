object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'Area'
  ClientHeight = 346
  ClientWidth = 550
  Color = clBtnFace
  Constraints.MinHeight = 250
  Constraints.MinWidth = 480
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object pnlViewport: TPanel
    AlignWithMargins = True
    Left = 16
    Top = 130
    Width = 518
    Height = 200
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
    DesignSize = (
      518
      200)
    object paintboxViewport: TPaintBox
      Left = 1
      Top = 1
      Width = 516
      Height = 198
      Cursor = crCross
      Align = alClient
      OnMouseDown = paintboxViewportMouseDown
      OnMouseLeave = paintboxViewportMouseLeave
      OnMouseMove = paintboxViewportMouseMove
      OnMouseUp = paintboxViewportMouseUp
      OnPaint = paintboxViewportPaint
      ExplicitLeft = 80
      ExplicitTop = -64
      ExplicitWidth = 105
      ExplicitHeight = 105
    end
    object lblHitTest: TLabel
      Left = 489
      Top = 178
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
      Left = 471
      Top = 178
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
      Top = 178
      Width = 3
      Height = 13
      Anchors = [akLeft, akBottom]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object lblBoundingBox: TLabel
      Left = 507
      Top = 11
      Width = 3
      Height = 13
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 51
    Width = 550
    Height = 63
    Align = alTop
    BevelOuter = bvNone
    Caption = 'pnlText'
    ShowCaption = False
    TabOrder = 1
    DesignSize = (
      550
      63)
    object Label1: TLabel
      Left = 17
      Top = 9
      Width = 27
      Height = 13
      Caption = 'Testo'
    end
    object Label3: TLabel
      Left = 186
      Top = 9
      Width = 22
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'Font'
      ExplicitLeft = 269
    end
    object Label4: TLabel
      Left = 379
      Top = 9
      Width = 35
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'Altezza'
      ExplicitLeft = 462
    end
    object checkboxBold: TCheckBox
      Left = 459
      Top = 13
      Width = 71
      Height = 17
      Anchors = [akTop, akRight]
      Caption = 'Grassetto'
      TabOrder = 0
      OnClick = TextChanged
    end
    object checkboxItalic: TCheckBox
      Left = 459
      Top = 36
      Width = 57
      Height = 17
      Anchors = [akTop, akRight]
      Caption = 'Corsivo'
      TabOrder = 1
      OnClick = TextChanged
    end
    object comboboxFontName: TComboBox
      Left = 186
      Top = 24
      Width = 173
      Height = 21
      Style = csDropDownList
      Anchors = [akTop, akRight]
      TabOrder = 2
      OnChange = TextChanged
    end
    object edtText: TEdit
      Left = 17
      Top = 24
      Width = 149
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 3
      Text = 'OqgAW'
      OnChange = TextChanged
    end
    object edtTextSize: TEdit
      Left = 379
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
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 550
    Height = 51
    Align = alTop
    BevelOuter = bvNone
    Caption = 'Panel2'
    ShowCaption = False
    TabOrder = 2
    DesignSize = (
      550
      51)
    object Label7: TLabel
      Left = 438
      Top = 9
      Width = 65
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'Visualizzatore'
      ExplicitLeft = 552
    end
    object Label2: TLabel
      Left = 112
      Top = 9
      Width = 36
      Height = 13
      Caption = 'Metodo'
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
      Left = 438
      Top = 24
      Width = 96
      Height = 21
      Style = csDropDownList
      Anchors = [akTop, akRight]
      TabOrder = 1
      OnChange = comboboxRendererChange
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
