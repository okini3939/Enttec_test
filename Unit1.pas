unit Unit1;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ExtCtrls, Vcl.ComCtrls;

{$i ftdi.inc}

const
  GET_WIDGET_PARAMS = 3;
  GET_WIDGET_SN     = 10;
  GET_WIDGET_PARAMS_REPLY = 3;
  SET_WIDGET_PARAMS = 4;
  SET_DMX_RX_MODE   = 5;
  SET_DMX_TX_MODE   = 6;
  SEND_DMX_RDM_TX   = 7;
  RECEIVE_DMX_ON_CHANGE   = 8;
  RECEIVED_DMX_COS_TYPE   = 9;
  DMX_START_CODE    = $7E;
  DMX_END_CODE      = $E7;
  DMX_HEADER_LENGTH = 4;
  HEADER_RDM_LABEL  = 5;
  DMX_PACKET_SIZE   = 512;
  DEVICE_NAME       = 'DMX USB PRO';

type TDMXUSBPROParams = packed record
  FirmwareLSB: Byte;
  FirmwareMSB: Byte;
  BreakTime: Byte;
  MaBTime: Byte;
  RefreshRate: Byte;
end;

type TDMXUSBPROSetParams = packed record
  UserSizeLSB: Byte;
  UserSizeMSB: Byte;
  BreakTime: Byte;
  MaBTime: Byte;
  RefreshRate: Byte;
end;

type ReceivedDmxCosStruct = record
	start_changed_byte_number: Byte;
	changed_byte_array: array[0..4] of Byte;
	changed_byte_data: array[0..39] of Byte;
end;

type
  TForm1 = class(TForm)
    Memo1: TMemo;
    Button1: TButton;
    Button2: TButton;
    Timer1: TTimer;
    TrackBar1: TTrackBar;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure TrackBar1Change(Sender: TObject);
  private
    { Private êÈåæ }
    ftHandle: Dword;
  public
    { Public êÈåæ }
    function FTDI_OpenDevice(device_num: integer): integer;
    function FTDI_SendData(prolabel: integer; data: array of byte; len: integer): integer;
    function FTDI_ReceiveData(prolabel: integer; var data: array of byte; expected_len: integer): integer;
    function FTDI_TxDMX(prolabel: integer; data: array of byte; len: integer): integer;
    function FTDI_RxDMX(prolabel: integer; var data: array of byte; expected_len: integer): integer;
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

function TForm1.FTDI_OpenDevice(device_num: integer): integer;
var
  buf_size: array[0..1] of byte;
  res: integer;
  PRO_Params: ^TDMXUSBPROParams;
  buf: array[0..256] of byte;
begin
  result := -1;
  if (device_num < 0) then
  begin
    if FT_OpenEx(PAnsiChar(DEVICE_NAME), FT_OPEN_BY_DESCRIPTION, @ftHandle) <> FT_OK then
    begin
      ftHandle := 0;
      memo1.Lines.add('cant open');
      exit;
    end;
  end
  else
  begin
    if FT_Open(device_num, @ftHandle) <> FT_OK then
    begin
      ftHandle := 0;
      memo1.Lines.add('cant open');
      exit;
    end;
  end;
  memo1.Lines.add('open ' + inttostr(ftHandle));

  FT_SetTimeouts(ftHandle, 10, 100);
  FT_Purge(ftHandle, FT_PURGE_RX);

  // Send Get Widget Params to get Device Info
  buf_size[0] := 0;
  buf_size[1] := 0;
  memo1.Lines.add('Sending GET_WIDGET_PARAMS packet...');
  res := FTDI_SendData(GET_WIDGET_PARAMS, buf_size, 2);
  if (res <> 0) then
  begin
    FT_Purge(ftHandle, FT_PURGE_TX);
    exit;
  end;
  memo1.Lines.add('PRO Connected Succesfully ' + inttostr(ord(buf_size[0])) + ' ' + inttostr(ord(buf_size[1])));

  // Receive Widget Response
  sleep(100);
  res := FTDI_ReceiveData(GET_WIDGET_PARAMS_REPLY, buf, sizeof(TDMXUSBPROParams));
  PRO_Params := @buf;
  if (res <> 0) then
  begin
    FT_Purge(ftHandle, FT_PURGE_TX);
    exit;
  end;

  memo1.Lines.add('version ' + inttostr(PRO_Params.FirmwareMSB) + '.' + inttostr(PRO_Params.FirmwareLSB));
  memo1.Lines.add('BREAK TIME ' + inttostr(PRO_Params.BreakTime * 10670 + 100000));
  memo1.Lines.add('MAB TIME ' + inttostr(PRO_Params.MaBTime * 10670));
  result := 0;
end;

function TForm1.FTDI_SendData(prolabel: integer; data: array of byte; len: integer): integer;
var
  header: array[0..DMX_HEADER_LENGTH] of byte;
  end_code: array[0..1] of byte;
	res: FT_Result;
  bytes_written: Dword;
begin
  result := -1;
	// Form Packet Header
	header[0] := DMX_START_CODE;
	header[1] := prolabel;
	header[2] := len and $ff;
	header[3] := len shr 8;
  end_code[0] := DMX_END_CODE;
	// Write The Header
  res := FT_Write(ftHandle, @header, DMX_HEADER_LENGTH, @bytes_written);
  if (bytes_written <> DMX_HEADER_LENGTH) then
    exit;
	// Write The Data
  res := FT_Write(ftHandle, @data, len, @bytes_written);
  if (bytes_written <> len) then
    exit;
	// Write End Code
  res := FT_Write(ftHandle, @end_code, 1, @bytes_written);
  if (bytes_written <> 1) then
    exit;
  if (res = FT_OK) then
    result := 0;
end;

function TForm1.FTDI_ReceiveData(prolabel: integer; var data: array of byte; expected_len: integer): integer;
var
	res: FT_Result;
  bytes_read: Dword;
  buf_byte: array[0..1] of byte;
  len: integer;
  buffer: array[0..600] of byte;
begin
  result := -1;
	// Check for Start Code and matching Label
	while (true) do
  begin
		while (true) do
    begin
			res := FT_Read(ftHandle, @buf_byte, 1, @bytes_read);
			if (bytes_read = 0) then exit;
      if (buf_byte[0] = DMX_START_CODE) then break;
		end;
		res := FT_Read(ftHandle, @buf_byte, 1, @bytes_read);
  	if (bytes_read = 0) then exit;
    memo1.Lines.add(inttostr(buf_byte[0]));
    if (buf_byte[0] = prolabel) then break;
	end;
	// Read the rest of the Header Byte by Byte -- Get Length
	res := FT_Read(ftHandle, @buf_byte, 2, @bytes_read);
	if (bytes_read = 0) then exit;
	len := buf_byte[0] or (buf_byte[1] shl 8);
	// Check Length is not greater than allowed
	if (len > DMX_PACKET_SIZE) then exit;
	// Read the actual Response Data
	res := FT_Read(ftHandle, @buffer, len, @bytes_read);
	if(bytes_read <> len) then exit;
	// Check The End Code
	res := FT_Read(ftHandle, @buf_byte, 1, @bytes_read);
	if (bytes_read = 0) then exit;
	if (buf_byte[0] <> DMX_END_CODE) then exit;
	// Copy The Data read to the buffer passed
	CopyMemory(@data, @buffer, expected_len);
  result := 0;
end;

function TForm1.FTDI_TxDMX(prolabel: integer; data: array of byte; len: integer): integer;
var
  DMX_Data: array[0..512] of byte;
begin
  // Send DMX
  DMX_Data[0] := $1e;
  CopyMemory(@DMX_Data[1], @data, len);
  FTDI_SendData(SET_DMX_TX_MODE, DMX_Data, sizeof(DMX_Data));
end;

function TForm1.FTDI_RxDMX(prolabel: integer; var data: array of byte; expected_len: integer): integer;
var
	res: FT_Result;
  bytes_read: Dword;
  buf_byte: array[0..1] of byte;
  header: array[0..3] of byte;
  len: integer;
  buffer: array[0..600] of byte;
begin
  result := -1;
	// Check for Start Code and matching Label
  while (true) do
  begin
    res := FT_Read(ftHandle, @buf_byte, 1, @bytes_read);
    if (bytes_read = 0) then exit;
    if (buf_byte[0] = DMX_START_CODE) then break;
  end;
	// Read the rest of the Header Byte by Byte -- Get Length
	res := FT_Read(ftHandle, @header, 3, @bytes_read);
	if (bytes_read <> 3) then exit;
  if (header[0] <> prolabel) then exit;
	len := header[1] or (header[2] shl 8);
	// Check Length is not greater than allowed
	if (len > DMX_PACKET_SIZE + 2) then exit;
	inc(len);
	// Read the actual Response Data
	res := FT_Read(ftHandle, @buffer, len, @bytes_read);
	if (bytes_read <> len) then exit;
	// Check The End Code
	if (buffer[len - 1] <> DMX_END_CODE) then exit;
	// Copy The Data read to the buffer passed
	CopyMemory(@data, @buffer[1], expected_len);
  result := 0;
end;


procedure TForm1.Button1Click(Sender: TObject);
var
  i: integer;
  data: array[0..512] of byte;
  res: integer;
begin
  data[0] := 0;
  for i := 1 to 512 do
    data[i] := i and $ff;
  res := FTDI_SendData(SET_DMX_TX_MODE, data, 513);
  memo1.Lines.add('TX ' + inttostr(res));
end;

procedure TForm1.Button2Click(Sender: TObject);
var
  send_on_change_flag: array[0..1] of byte;
  res: integer;
begin
  send_on_change_flag[0] := 1;
  res := FTDI_SendData(RECEIVE_DMX_ON_CHANGE, send_on_change_flag, 1);
  if (res < 0) then
  begin
    memo1.Lines.add('FAILED');
    exit;
  end;
  memo1.Lines.add('RX mode');

  Timer1.Enabled := true;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
var
  i, n: integer;
  data: array[0..512] of byte;
  res: integer;
  s: string;
begin
  for n := 0 to 100 do
  begin
    res := FTDI_RxDMX(SET_DMX_RX_MODE, data, 513);
    if (res < 0) then
    begin
      exit;
    end;

    s := '';
    for i := 0 to 10 do
      s := s + ' ' + inttostr(data[i]);
    memo1.Lines.add('RX' + s);
  end;
end;

procedure TForm1.TrackBar1Change(Sender: TObject);
var
  i: integer;
  data: array[0..512] of byte;
  res: integer;
begin
  data[0] := 0;
  for i := 1 to 512 do
    data[i] := 255 - TrackBar1.Position;
  res := FTDI_SendData(SET_DMX_TX_MODE, data, 513);
end;

procedure TForm1.FormCreate(Sender: TObject);
var
	ftStatus: FT_Result;
	numDevs: Dword;
  i: integer;
begin

  ftStatus := FT_ListDevices(cardinal(@numDevs), nil, FT_LIST_NUMBER_ONLY);
  if (ftStatus = FT_OK) then
  begin
    memo1.Lines.add('devices ' + inttostr(numDevs));
    for i := 0 to numDevs - 1 do
    begin
      memo1.Lines.add(inttostr(i));
      if (FTDI_OpenDevice(i) = 0) then
        break;
    end;
  end;

end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
  if (ftHandle <> 0) then
    FT_Close(ftHandle);
end;

end.
