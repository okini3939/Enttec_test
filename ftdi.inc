
const
// FT_Result Values
    FT_OK = 0;
    FT_INVALID_HANDLE = 1;
    FT_DEVICE_NOT_FOUND = 2;
    FT_DEVICE_NOT_OPENED = 3;
    FT_IO_ERROR = 4;
    FT_INSUFFICIENT_RESOURCES = 5;
    FT_INVALID_PARAMETER = 6;
    FT_SUCCESS = FT_OK;
    FT_INVALID_BAUD_RATE = 7;
    FT_DEVICE_NOT_OPENED_FOR_ERASE = 8;
    FT_DEVICE_NOT_OPENED_FOR_WRITE = 9;
    FT_FAILED_TO_WRITE_DEVICE = 10;
    FT_EEPROM_READ_FAILED = 11;
    FT_EEPROM_WRITE_FAILED = 12;
    FT_EEPROM_ERASE_FAILED = 13;
    FT_EEPROM_NOT_PRESENT = 14;
    FT_EEPROM_NOT_PROGRAMMED = 15;
    FT_INVALID_ARGS = 16;
    FT_OTHER_ERROR = 17;
// FT_Open_Ex Flags
    FT_OPEN_BY_SERIAL_NUMBER = 1;
    FT_OPEN_BY_DESCRIPTION = 2;
    FT_OPEN_BY_LOCATION = 4;
// FT_List_Devices Flags
    FT_LIST_NUMBER_ONLY = $80000000;
    FT_LIST_BY_INDEX = $40000000;
    FT_LIST_ALL = $20000000;
// Baud Rate Selection
    FT_BAUD_300 = 300;
    FT_BAUD_600 = 600;
    FT_BAUD_1200 = 1200;
    FT_BAUD_2400 = 2400;
    FT_BAUD_4800 = 4800;
    FT_BAUD_9600 = 9600;
    FT_BAUD_14400 = 14400;
    FT_BAUD_19200 = 19200;
    FT_BAUD_38400 = 38400;
    FT_BAUD_57600 = 57600;
    FT_BAUD_115200 = 115200;
    FT_BAUD_230400 = 230400;
    FT_BAUD_460800 = 460800;
    FT_BAUD_921600 = 921600;
// Data Bits Selection
    FT_DATA_BITS_7 = 7;
    FT_DATA_BITS_8 = 8;
// Stop Bits Selection
    FT_STOP_BITS_1 = 0;
    FT_STOP_BITS_2 = 2;
// Parity Selection
    FT_PARITY_NONE = 0;
    FT_PARITY_ODD = 1;
    FT_PARITY_EVEN = 2;
    FT_PARITY_MARK = 3;
    FT_PARITY_SPACE = 4;
// Flow Control Selection
    FT_FLOW_NONE = $0000;
    FT_FLOW_RTS_CTS = $0100;
    FT_FLOW_DTR_DSR = $0200;
    FT_FLOW_XON_XOFF = $0400;
// Purge Commands
    FT_PURGE_RX = 1;
    FT_PURGE_TX = 2;
// Notification Events
    FT_EVENT_RXCHAR = 1;
    FT_EVENT_MODEM_STATUS = 2;
    FT_EVENT_LINE_STATUS = 4;
    FT_EVENT_BREAK = $40;
// Modem Status
    CTS = $10;
    DSR = $20;
    RI = $40;
    DCD = $80;
// IO Buffer Sizes
    FT_In_Buffer_Size = $10000;    // 64k
    FT_In_Buffer_Index = FT_In_Buffer_Size - 1;
    FT_Out_Buffer_Size = $10000;    // 64k
    FT_Out_Buffer_Index = FT_Out_Buffer_Size - 1;
// DLL Name
    FT_DLL_Name = 'FTD2XX.DLL';


type FT_Result = Integer;

type FT_Device_Info_Node = record
  Flags         : DWord;
  DeviceType    : Dword;
  ID            : DWord;
  LocID         : DWord;
  SerialNumber  : array [0..15] of AnsiChar;
  Description   : array [0..63] of AnsiChar;
  DeviceHandle  : DWord;
end;

type TDWordptr = ^DWord;

// Structure to hold EEPROM data for FT_EE_Program function
type TFT_Program_Data = record
  Signature1        : DWord;
  Signature2        : DWord;
  Version           : DWord;
  VendorID          : Word;
  ProductID         : Word;
  Manufacturer      : PAnsiChar;
  ManufacturerID    : PAnsiChar;
  Description       : PAnsiChar;
  SerialNumber      : PAnsiChar;
  MaxPower          : Word;
  PnP               : Word;
  SelfPowered       : Word;
  RemoteWakeup      : Word;
// Rev4 extensions
  Rev4              : Byte;
  IsoIn             : Byte;
  IsoOut            : Byte;
  PullDownEnable    : Byte;
  SerNumEnable      : Byte;
  USBVersionEnable  : Byte;
  USBVersion        : Word;
// FT2232C extensions
  Rev5              : Byte;
  IsoInA            : Byte;
  IsoInB            : Byte;
  IsoOutA           : Byte;
  IsoOutB           : Byte;
  PullDownEnable5   : Byte;
  SerNumEnable5     : Byte;
  USBVersionEnable5 : Byte;
  USBVersion5       : Word;
  AIsHighCurrent    : Byte;
  BIsHighCurrent    : Byte;
  IFAIsFifo         : Byte;
  IFAIsFifoTar      : Byte;
  IFAIsFastSer      : Byte;
  AIsVCP            : Byte;
  IFBIsFifo         : Byte;
  IFBIsFifoTar      : Byte;
  IFBIsFastSer      : Byte;
  BIsVCP            : Byte;
// FT232R extensions
  UseExtOsc         : Byte;
  HighDriveIOs      : Byte;
  EndpointSize      : Byte;
  PullDownEnableR   : Byte;
  SerNumEnableR     : Byte;
  InvertTXD         : Byte;
  InvertRXD         : Byte;
  InvertRTS         : Byte;
  InvertCTS         : Byte;
  InvertDTR         : Byte;
  InvertDSR         : Byte;
  InvertDCD         : Byte;
  InvertRI          : Byte;
  Cbus0             : Byte;
  Cbus1             : Byte;
  Cbus2             : Byte;
  Cbus3             : Byte;
  Cbus4             : Byte;
  RIsVCP            : Byte;
end;


// Win32 API Structs
type TFTCOMSTAT = record
  fCtsHold:Dword;
  fDsrHold:Dword;
  fRlsdHold:Dword;
  fXoffHold:Dword;
  fXoffSent:Dword;
  fEof:Dword;
  fTxim:Dword;
  fReserved:array[0..24] of Dword;
  cbInQue:Dword;
  cbOutQue:Dword;
end;

type TFTDCB = record
    DCBlength:DWORD;      // sizeof(FTDCB)                   */
    BaudRate:DWORD;             // Baudrate at which running       */
    fBinary:DWORD;        // Binary Mode (skip EOF check)    */
    fParity:DWORD;        // Enable parity checking          */
    fOutxCtsFlow:DWORD;   // CTS handshaking on output       */
    fOutxDsrFlow:DWORD;   // DSR handshaking on output       */
    fDtrControl:array[0..1] of DWORD;  // DTR Flow control                */
    fDsrSensitivity:DWORD; // DSR Sensitivity              */
    fTXContinueOnXoff:DWORD; // Continue TX when Xoff sent */
    fOutX:DWORD;          // Enable output X-ON/X-OFF        */
    fInX:DWORD;           // Enable input X-ON/X-OFF         */
    fErrorChar:DWORD;     // Enable Err Replacement          */
    fNull:DWORD;          // Enable Null stripping           */
    fRtsControl:array[0..1] of DWORD;  // Rts Flow control                */
    fAbortOnError:DWORD;  // Abort all reads and writes on Error */
    fDummy2:array[0..16] of DWORD;     // Reserved                        */
    wReserved:Word;       // Not currently used              */
    XonLim:Word;          // Transmit X-ON threshold         */
    XoffLim:Word;         // Transmit X-OFF threshold        */
    ByteSize:byte;        // Number of bits/byte, 4-8        */
    Parity:byte;          // 0-4=None,Odd,Even,Mark,Space    */
    StopBits:byte;        // 0,1,2 = 1, 1.5, 2               */
    XonChar:byte;         // Tx and Rx X-ON character        */
    XoffChar:byte;        // Tx and Rx X-OFF character       */
    ErrorChar:byte;       // Error replacement char          */
    EofChar:byte;         // End of Input character          */
    EvtChar:byte;         // Received Event character        */
    wReserved1:word;      // Fill for now.                   */
end;

type TFTTIMEOUTS = record
    ReadIntervalTimeout:DWORD;          // Maximum time between read chars. */
    ReadTotalTimeoutMultiplier:DWORD;   // Multiplier of characters.        */
    ReadTotalTimeoutConstant:DWORD;     // Constant in milliseconds.        */
    WriteTotalTimeoutMultiplier:DWORD;  // Multiplier of characters.        */
    WriteTotalTimeoutConstant:DWORD;    // Constant in milliseconds.        */
end;


// Exported Functions
//Classic functions
function FT_GetNumDevices(pvArg1:Pointer; pvArg2:Pointer; dwFlags:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_ListDevices';
function FT_ListDevices(pvArg1:Dword; pvArg2:Pointer; dwFlags:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_ListDevices';
function FT_Open(Index:Integer; ftHandle:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_Open';
function FT_OpenEx(pvArg1:Pointer; dwFlags:Dword; ftHandle:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_OpenEx';
function FT_OpenByLocation(pvArg1:DWord; dwFlags:Dword; ftHandle:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_OpenEx';
function FT_Close(ftHandle:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_Close';
function FT_Read(ftHandle:Dword; FTInBuf:Pointer; BufferSize:LongInt; ResultPtr:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_Read';
function FT_Write(ftHandle:Dword; FTOutBuf:Pointer; BufferSize:LongInt; ResultPtr:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_Write';
function FT_ResetDevice(ftHandle:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_ResetDevice';
function FT_SetBaudRate(ftHandle:Dword; BaudRate:DWord):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetBaudRate';
function FT_SetDivisor(ftHandle:Dword; Divisor:DWord):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetDivisor';
function FT_SetDataCharacteristics(ftHandle:Dword; WordLength,StopBits,Parity:Byte):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetDataCharacteristics';
function FT_SetFlowControl(ftHandle:Dword; FlowControl:Word; XonChar,XoffChar:Byte):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetFlowControl';
function FT_SetDtr(ftHandle:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetDtr';
function FT_ClrDtr(ftHandle:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_ClrDtr';
function FT_SetRts(ftHandle:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetRts';
function FT_ClrRts(ftHandle:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_ClrRts';
function FT_GetModemStatus(ftHandle:Dword; ModemStatus:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_GetModemStatus';
function FT_SetChars(ftHandle:Dword; EventChar,EventCharEnabled,ErrorChar,ErrorCharEnabled:Byte):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetChars';
function FT_Purge(ftHandle:Dword; Mask:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_Purge';
function FT_SetTimeouts(ftHandle:Dword; ReadTimeout,WriteTimeout:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetTimeouts';
function FT_GetQueueStatus(ftHandle:Dword; RxBytes:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_GetQueueStatus';
function FT_SetBreakOn(ftHandle:Dword) : FT_Result; stdcall; External FT_DLL_Name name 'FT_SetBreakOn';
function FT_SetBreakOff(ftHandle:Dword) : FT_Result; stdcall; External FT_DLL_Name name 'FT_SetBreakOff';
function FT_GetStatus(ftHandle:DWord; RxBytes,TxBytes,EventStatus:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_GetStatus';
function FT_SetEventNotification(ftHandle:DWord; EventMask:DWord; pvArgs:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetEventNotification';
function FT_GetDeviceInfo(ftHandle:DWord; DevType,ID,SerNum,Desc,pvDummy:Pointer) : FT_Result; stdcall; External FT_DLL_Name name 'FT_GetDeviceInfo';
function FT_SetResetPipeRetryCount(ftHandle:Dword; RetryCount:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetResetPipeRetryCount';
function FT_StopInTask(ftHandle:Dword) : FT_Result; stdcall; External FT_DLL_Name name 'FT_StopInTask';
function FT_RestartInTask(ftHandle:Dword) : FT_Result; stdcall; External FT_DLL_Name name 'FT_RestartInTask';
function FT_ResetPort(ftHandle:Dword) : FT_Result; stdcall; External FT_DLL_Name name 'FT_ResetPort';
function FT_CyclePort(ftHandle:Dword) : FT_Result; stdcall; External 'FTD2XX.DLL' name 'FT_CyclePort';
function FT_CreateDeviceInfoList(NumDevs:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_CreateDeviceInfoList';
function FT_GetDeviceInfoList(pFT_Device_Info_List:Pointer; NumDevs:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_GetDeviceInfoList';
function FT_GetDeviceInfoDetail(Index:DWord; Flags,DevType,ID,LocID,SerialNumber,Description,DevHandle:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_GetDeviceInfoDetail';
function FT_GetDriverVersion(ftHandle:Dword; DrVersion:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_GetDriverVersion';
function FT_GetLibraryVersion(LbVersion:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_GetLibraryVersion';

// EEPROM functions
function FT_EE_Read(ftHandle:DWord; pEEData:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_EE_Read';
function FT_EE_Program(ftHandle:DWord; pEEData:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_EE_Program';
// EEPROM primitives - you need an NDA for EEPROM checksum
function FT_ReadEE(ftHandle:DWord; WordAddr:DWord; WordRead:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_ReadEE';
function FT_WriteEE(ftHandle:DWord; WordAddr:DWord; WordData:word):FT_Result; stdcall; External FT_DLL_Name name 'FT_WriteEE';
function FT_EraseEE(ftHandle:DWord):FT_Result; stdcall; External FT_DLL_Name name 'FT_EraseEE';
function FT_EE_UARead(ftHandle:DWord; Data:Pointer; DataLen:DWord; BytesRead:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_EE_UARead';
function FT_EE_UAWrite(ftHandle:DWord; Data:Pointer; DataLen:DWord):FT_Result; stdcall; External FT_DLL_Name name 'FT_EE_UAWrite';
function FT_EE_UASize(ftHandle:DWord; UASize:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_EE_UASize';

// FT2232C, FT232BM and FT245BM Extended API Functions
function FT_GetLatencyTimer(ftHandle:Dword; Latency:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_GetLatencyTimer';
function FT_SetLatencyTimer(ftHandle:Dword; Latency:Byte):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetLatencyTimer';
function FT_GetBitMode(ftHandle:Dword; BitMode:Pointer):FT_Result; stdcall; External FT_DLL_Name name 'FT_GetBitMode';
function FT_SetBitMode(ftHandle:Dword; Mask,Enable:Byte):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetBitMode';
function FT_SetUSBParameters(ftHandle:Dword; InSize,OutSize:Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_SetUSBParameters';

// FT-Win32 API Functions
function FT_W32_CreateFile(Name: PChar; Access: Dword; ShareMode: Dword; SecurityAttributes: Cardinal; Create: Word; AttrsAndFlags: Cardinal; Template: Cardinal):FT_Result; stdcall; External FT_DLL_Name name 'FT_W32_CreateFile';
function FT_W32_CloseHandle(ftHandle: Dword):boolean; stdcall; External FT_DLL_Name name 'FT_W32_CloseHandle';
function FT_W32_ReadFile(ftHandle:Dword; Buffer: Pointer; BytesToRead: Dword; BytesReturned: Pointer; Overlapped: Pointer):boolean; stdcall; External FT_DLL_Name name 'FT_W32_ReadFile';
function FT_W32_WriteFile(ftHandle: Dword; Buffer: Pointer; BytesToWrite: Dword; BytesWritten: Pointer; Overlapped: Pointer):boolean; stdcall; External FT_DLL_Name name 'FT_W32_WriteFile';
function FT_W32_GetLastError(ftHandle: Dword):FT_Result; stdcall; External FT_DLL_Name name 'FT_W32_GetLastError';
function FT_W32_GetOverlappedResult(ftHandle: Dword; Overlapped: Pointer; BytesTransferred: Pointer; Wait: boolean):boolean; stdcall; External FT_DLL_Name name 'FT_W32_GetOverlappedResult';
function FT_W32_ClearCommBreak(ftHandle: Dword):boolean; stdcall; External FT_DLL_Name name 'FT_W32_ClearCommBreak';
function FT_W32_ClearCommError(ftHandle: Dword; Errors:Pointer; Comstat: Pointer):boolean; stdcall; External FT_DLL_Name name 'FT_W32_ClearCommError';
function FT_W32_EscapeCommFunction(ftHandle: Dword; Func: Dword):boolean; stdcall; External FT_DLL_Name name 'FT_W32_EscapeCommFunction';
function FT_W32_GetCommModemStatus(ftHandle: Dword; Stat: Pointer):boolean; stdcall; External FT_DLL_Name name 'FT_W32_GetCommModemStatus';
function FT_W32_GetCommState(ftHandle: Dword; Dcb: Pointer):boolean; stdcall; External FT_DLL_Name name 'FT_W32_GetCommState';
function FT_W32_GetCommTimeouts(ftHandle: Dword; Timeouts: Pointer):boolean; stdcall; External FT_DLL_Name name 'FT_W32_GetCommTimeouts';
function FT_W32_PurgeComm(ftHandle: Dword; Flags: Dword):boolean; stdcall; External FT_DLL_Name name 'FT_W32_PurgeComm';
function FT_W32_SetCommBreak(ftHandle: Dword):boolean; stdcall; External FT_DLL_Name name 'FT_W32_SetCommBreak';
function FT_W32_SetCommMask(ftHandle: Dword; Mask: Dword):boolean; stdcall; External FT_DLL_Name name 'FT_W32_SetCommMask';
function FT_W32_SetCommState(ftHandle: Dword; Dcb: Pointer):boolean; stdcall; External FT_DLL_Name name 'FT_W32_SetCommState';
function FT_W32_SetCommTimeouts(ftHandle: Dword; Timeouts:Pointer):boolean; stdcall; External FT_DLL_Name name 'FT_W32_SetCommTimeouts';
function FT_W32_SetupComm(ftHandle: Dword; ReadBufferSize: Dword; WriteBufferSize: Dword):boolean; stdcall; External FT_DLL_Name name 'FT_W32_SetupComm';
function FT_W32_WaitCommEvent(ftHandle: Dword; Event: Pointer; Overlapped: Pointer):boolean; stdcall; External FT_DLL_Name name 'FT_W32_WaitCommEvent';


