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
  KeyPreview = True
  OnKeyPress = FormKeyPress
  TextHeight = 13
  object pnlViewport: TPanel
    Left = 0
    Top = 129
    Width = 718
    Height = 320
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
    ExplicitLeft = 16
    ExplicitTop = 130
    ExplicitWidth = 686
    ExplicitHeight = 303
    DesignSize = (
      718
      320)
    object paintboxViewport: TPaintBox
      Left = 1
      Top = 1
      Width = 716
      Height = 318
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
      Left = 689
      Top = 298
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
      Left = 671
      Top = 298
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
      Top = 298
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
      Left = 707
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
    Top = 0
    Width = 718
    Height = 129
    Align = alTop
    BevelOuter = bvNone
    Caption = 'pnlText'
    ShowCaption = False
    TabOrder = 1
    object Panel2: TPanel
      Left = 0
      Top = 0
      Width = 718
      Height = 51
      Align = alTop
      BevelOuter = bvNone
      Caption = 'Panel2'
      ShowCaption = False
      TabOrder = 0
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
      object checkboxFillArea: TCheckBox
        Left = 503
        Top = 26
        Width = 77
        Height = 17
        Caption = 'Fill Area'
        TabOrder = 3
        OnClick = checkboxFillAreaClick
      end
    end
    object pagecontrolProperties: TPageControl
      AlignWithMargins = True
      Left = 16
      Top = 54
      Width = 686
      Height = 67
      Margins.Left = 16
      Margins.Right = 16
      Margins.Bottom = 8
      Align = alClient
      TabOrder = 1
      object tbshtText: TTabSheet
        Caption = 'tbshtText'
        TabVisible = False
        inline frmeTextData1: TfrmeTextData
          Left = 0
          Top = 0
          Width = 678
          Height = 57
          Align = alClient
          TabOrder = 0
          inherited Label3: TLabel
            Left = 342
            Width = 22
            Height = 13
            StyleElements = [seFont, seClient, seBorder]
            ExplicitLeft = 301
            ExplicitWidth = 22
            ExplicitHeight = 13
          end
          inherited Label1: TLabel
            Width = 22
            Height = 13
            StyleElements = [seFont, seClient, seBorder]
            ExplicitWidth = 22
            ExplicitHeight = 13
          end
          inherited Label4: TLabel
            Left = 535
            Width = 31
            Height = 13
            StyleElements = [seFont, seClient, seBorder]
            ExplicitLeft = 494
            ExplicitWidth = 31
            ExplicitHeight = 13
          end
          inherited edtText: TEdit
            Width = 303
            Height = 21
            StyleElements = [seFont, seClient, seBorder]
            ExplicitWidth = 262
            ExplicitHeight = 21
          end
          inherited checkboxItalic: TCheckBox
            Left = 615
            ExplicitLeft = 574
          end
          inherited checkboxBold: TCheckBox
            Left = 615
            ExplicitLeft = 574
          end
          inherited edtTextSize: TEdit
            Left = 535
            Height = 21
            StyleElements = [seFont, seClient, seBorder]
            ExplicitLeft = 494
            ExplicitHeight = 21
          end
          inherited comboboxFontName: TComboBox
            Left = 342
            Height = 21
            StyleElements = [seFont, seClient, seBorder]
            ExplicitLeft = 301
            ExplicitHeight = 21
          end
        end
      end
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
