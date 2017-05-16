object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Ping google'
  ClientHeight = 377
  ClientWidth = 475
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object PanelBottom: TPanel
    Left = 0
    Top = 336
    Width = 475
    Height = 41
    Align = alBottom
    TabOrder = 0
    ExplicitLeft = -133
    ExplicitTop = 171
    ExplicitWidth = 551
    DesignSize = (
      475
      41)
    object ButtonPing: TButton
      Left = 264
      Top = 6
      Width = 104
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Ping google'
      TabOrder = 0
      OnClick = ButtonPingClick
    end
    object ButtonCancel: TButton
      Left = 375
      Top = 6
      Width = 93
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      Enabled = False
      TabOrder = 1
      OnClick = ButtonCancelClick
      ExplicitLeft = 374
    end
  end
  object RichEditOutput: TRichEdit
    Left = 0
    Top = 0
    Width = 475
    Height = 336
    Align = alClient
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    HideSelection = False
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
    ExplicitLeft = 24
    ExplicitTop = 80
    ExplicitWidth = 185
    ExplicitHeight = 89
  end
end
