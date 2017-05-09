// ---------------------------------------------------------------------------
#include "SerialPort.h"


#include <iostream>

using namespace Bicycle;

// ---------------------------------------------------------------------------
void SerialPort::waitEvent(ulong& mask, OVERLAPPED &overlapped)
{
  if(!WaitCommEvent(handle_, & mask, &overlapped))
    waitFor(overlapped.hEvent,cancelEvent_.handle(),timeOut_);
}
// ---------------------------------------------------------------------------
ulong SerialPort::waitEvent()
{
  OVERLAPPED overlapped={0};
  Event event;
  overlapped.hEvent= event.handle();
  ulong mask=0;
  waitEvent(mask,overlapped);
  return mask;
}
//------------------ IODevice -------------------------------------
ulong SerialPort::read(char *data, ulong size)
{
  OVERLAPPED overlapped= {0};
  Event event;
  overlapped.hEvent= event.handle();

  ulong mask= 0;
  waitEvent(mask,overlapped);

  if(mask & EV_RXCHAR)
  {
     ulong errors;
     COMSTAT stat;
     ClearCommError(handle_, &errors, &stat);

     if(!ReadFile(handle_, data, stat.cbInQue, &size, &overlapped))
       throw SystemException();

     return stat.cbInQue;
  }
  return 0;
}
// ---------------------------------------------------------------------------
ulong SerialPort::write(const char* data, ulong size)
{
  OVERLAPPED overlapped= {0};
  Event event;
  overlapped.hEvent= event.handle();

  ulong length= 0;
  if(!WriteFile(handle_, data, size, &length, &overlapped))
  {
    ulong errorCode = GetLastError();
    if(errorCode != ERROR_IO_PENDING)
       throw SystemException(errorCode);

    waitFor(overlapped.hEvent,cancelEvent_.handle(),timeOut_);
  }
  return length;
}
// ------------------------ Serial Port ----------------------------------------
SerialPort::SerialPort(const tstring& portName,
                       ulong baudRate,
                       ulong timeOut)
 : portName_(portName),
   handle_(INVALID_HANDLE_VALUE),
   baudRate_(baudRate),
   timeOut_(timeOut)
{

}
// ---------------------------------------------------------------------------
SerialPort::~SerialPort()
{
  close();
}
// ---------------------------------------------------------------------------
void SerialPort::setDefaultSettings(HANDLE portHandle)
{
  ZeroMemory(& dcb_, sizeof(dcb_));
  dcb_.DCBlength= sizeof(dcb_);

  GetCommState(portHandle, & dcb_);

  dcb_.BaudRate= baudRate_;
  dcb_.ByteSize= 8;
  dcb_.Parity= NOPARITY;
  dcb_.StopBits= ONESTOPBIT;
  dcb_.fAbortOnError= TRUE;
//	dcb_.fDtrControl= DTR_CONTROL_DISABLE;
  dcb_.fDtrControl= DTR_CONTROL_ENABLE;     //DTR_CONTROL_HANDSHAKE

  dcb_.fRtsControl= RTS_CONTROL_DISABLE;
  dcb_.fBinary= TRUE;
  dcb_.fParity= FALSE;
  dcb_.fInX= FALSE;
  dcb_.fOutX= FALSE;
  dcb_.XonChar= 0;
  dcb_.XoffChar= (unsigned char)0xFF;
//	dcb_.EvtChar= '\n';
  dcb_.fErrorChar= FALSE;
  dcb_.fNull= FALSE;
  dcb_.fOutxCtsFlow= FALSE;
  dcb_.fOutxDsrFlow= FALSE;
  dcb_.XonLim= 128;
  dcb_.XoffLim= 128;

  ZeroMemory(& commTimeOuts_, sizeof(commTimeOuts_));
  commTimeOuts_.ReadIntervalTimeout= 0xFFFFFFFF;
  commTimeOuts_.ReadTotalTimeoutMultiplier= 0;
  commTimeOuts_.ReadTotalTimeoutConstant= 300000;
  commTimeOuts_.WriteTotalTimeoutMultiplier= 0;
  commTimeOuts_.WriteTotalTimeoutConstant= 300000;
}
// ---------------------------------------------------------------------------
void SerialPort::open()
{
  close();

  handle_= CreateFile(portName_.c_str(), GENERIC_READ| GENERIC_WRITE, 0, NULL,
      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL| FILE_FLAG_OVERLAPPED, NULL);

  if (handle_== INVALID_HANDLE_VALUE)
    throw SystemException();

  if (!SetupComm(handle_, 1024, 1024))
    throw SystemException();

  ulong purgeFlags= PURGE_TXABORT| PURGE_RXABORT| PURGE_TXCLEAR| PURGE_RXCLEAR;
  if (!PurgeComm(handle_, purgeFlags))
    throw SystemException();

  setDefaultSettings(handle_);

  if (!SetCommState(handle_, & dcb_))
    throw SystemException();

  if(!SetCommTimeouts(handle_, &commTimeOuts_))
   throw SystemException();

  ulong mask_flags= EV_RXCHAR |
   EV_BREAK|EV_CTS|EV_DSR|EV_ERR|EV_RING|EV_RLSD|EV_RXCHAR|EV_RXFLAG|EV_TXEMPTY;
  if (!SetCommMask(handle_, mask_flags))
    throw SystemException();
}
// ---------------------------------------------------------------------------
void SerialPort::close()
{
  if (handle_!= INVALID_HANDLE_VALUE)
  {
    CloseHandle(handle_);
    handle_= INVALID_HANDLE_VALUE;
  }

  cancelEvent_.resetEvent();
}
// ---------------------------------------------------------------------------
HANDLE SerialPort::handle() const
{
  return handle_;
}
// ---------------------------------------------------------------------------
const tstring& SerialPort::portName() const
{
  return portName_;
}
// ---------------------------------------------------------------------------
void SerialPort::setPortName(const tstring& portName)
{
  portName_= portName;
}
// ---------------------------------------------------------------------------
ulong SerialPort::timeOut() const
{
  return timeOut_;
}
// ---------------------------------------------------------------------------
void SerialPort::setTimeOut(ulong readTimeOut)
{
  timeOut_= readTimeOut;
}
// ---------------------------------------------------------------------------
ulong SerialPort::baudRate() const
{
  return baudRate_;
}
// ---------------------------------------------------------------------------
void SerialPort::setBaudRate(ulong baudRate)
{
  baudRate_= baudRate;
}
//--------------------------------------------------------------------------
void SerialPort::cancel()
{
   cancelEvent_.setEvent();
}
//--------------------------------------------------------------------------
/*
ulong SerialPort::read(char *data, ulong size, ulong &errorCode)
{
  OVERLAPPED overlapped= {0};
  SimpleEvent event;
  overlapped.hEvent= event.handle();

  ulong length= 0;

  // event
  ulong mask=0;
  if(!waitEvent(mask))
  {
    errorCode= SerialError::WaitTimeOut;
    return 0;
  }

  // read
  if(readOverlapped(data,size,length,overlapped))
  {
    errorCode = SerialError::Success;
    return length;
  }

  if(!waitOverlappedResult(overlapped))
  {
    errorCode= SerialError::WaitTimeOut;
    return 0;
  }

  if(!GetOverlappedResult(handle_, &overlapped, &length, true))
     throw SystemException();

  errorCode = SerialError::Success;
  return length;
}
*/
