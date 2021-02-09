object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 389
  ClientWidth = 522
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 8
    Top = 16
    Width = 321
    Height = 361
    TabOrder = 0
  end
  object Button1: TButton
    Left = 343
    Top = 14
    Width = 75
    Height = 25
    Caption = 'TX'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 432
    Top = 14
    Width = 75
    Height = 25
    Caption = 'RX'
    TabOrder = 2
    OnClick = Button2Click
  end
  object TrackBar1: TTrackBar
    Left = 360
    Top = 64
    Width = 45
    Height = 201
    Max = 255
    Orientation = trVertical
    Frequency = 16
    Position = 255
    TabOrder = 3
    OnChange = TrackBar1Change
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 456
    Top = 72
  end
end
