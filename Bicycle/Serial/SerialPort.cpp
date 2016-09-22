// ---------------------------------------------------------------------------
#include "SerialPort.h"

using namespace Bicycle;

//------------------ IODevice -------------------------------------
ulong SerialPort::read(char *data, ulong size, ulong &errorCode)
{
  ulong mask= 0;
  WaitCommEvent(handle_, & mask, &rOverlapped_);
  ulong waitResult=
     WaitForSingleObject(rOverlapped_.hEvent, readTimeOut_);
  switch (waitResult)
  {
    case WAIT_OBJECT_0:	errorCode= SerialError::Success; break;
    case WAIT_TIMEOUT:	errorCode= SerialError::WaitTimeOut; return 0;
    case WAIT_ABANDONED:
    case WAIT_FAILED:   errorCode= GetLastError();	   return 0;
    default:	break;
  }

  if(aborted_)
  {
    errorCode= SerialError::Aborted;
    return 0;
  }

  ulong length= 0;
  BOOL success=
    ReadFile(handle_, data, size, &length,	&rOverlapped_);
  if(!success)
  {
    errorCode= GetLastError();
    if(errorCode==ERROR_IO_PENDING)
    {
      ulong waitResult=
        WaitForSingleObject(rOverlapped_.hEvent,	readTimeOut_);
      switch(waitResult)
      {
        case WAIT_OBJECT_0: errorCode= SerialError::Success; break;
        case WAIT_TIMEOUT:	errorCode= SerialError::WaitTimeOut; return 0;
        case WAIT_ABANDONED:
        case WAIT_FAILED:   errorCode= GetLastError(); return 0;
        default: break;
      }

      if(aborted_)
      {
        errorCode= SerialError::Aborted;
        return 0;
      }
    }
    else
      throw SystemException(errorCode);
  }

  success=
    GetOverlappedResult(handle_, &rOverlapped_,&length, true);

  if(!success)
    errorCode= GetLastError();

  rOverlapped_.Offset+= length;
  return length;
}
// ---------------------------------------------------------------------------
ulong SerialPort::write(const char* data, ulong size, ulong& errorCode)
{
  ulong length= 0;
  BOOL success= WriteFile(handle_,
                          data,
                          size,
                          &length,
                          &wOverlapped_);

  if (!success)
  {
    errorCode= GetLastError();
    if(errorCode==ERROR_IO_PENDING)
    {
      ulong waitResult= WaitForSingleObject(wOverlapped_.hEvent,DEFAULT_TIMEOUT);
      switch(waitResult)
      {
        case WAIT_OBJECT_0:  errorCode= SerialError::Success;      break;
        case WAIT_TIMEOUT:   errorCode= SerialError::WaitTimeOut;  return 0;
        case WAIT_ABANDONED:
        case WAIT_FAILED:    errorCode= GetLastError();            return 0;
        default:break;
      }
    }
    else
      throw SystemException(errorCode);
  }

  if(aborted_)
    return 0;

  success=
    GetOverlappedResult(handle_,&wOverlapped_,&length,true);

  if(!success)
    errorCode= GetLastError();

  wOverlapped_.Offset+= length;
  return length;
}

// ---------------------------------------------------------------------------
void SerialPort::checkErrorCode(ulong code) const
{
   if(code!=SerialError::Success)
       throw SystemException(code);
}
// ------------------------ Serial Port ----------------------------------------
SerialPort::SerialPort(const tstring& portName,
                       ulong baudRate,
                       ulong readTimeOut)
 : aborted_(false),
	 portName_(portName),
	 handle_(INVALID_HANDLE_VALUE),
	 baudRate_(baudRate),
	 readTimeOut_(readTimeOut)
{
	ZeroMemory(& rOverlapped_, sizeof(rOverlapped_));
	ZeroMemory(& wOverlapped_, sizeof(wOverlapped_));
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

	ZeroMemory(& rOverlapped_, sizeof(rOverlapped_));
	rOverlapped_.hEvent= CreateEvent(NULL, true, false, NULL);
	if(rOverlapped_.hEvent== NULL)
		throw SystemException();

	ZeroMemory(& wOverlapped_, sizeof(wOverlapped_));
	wOverlapped_.hEvent= CreateEvent(NULL, true, false, NULL);
	if(wOverlapped_.hEvent== NULL)
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

	ulong mask_flags= EV_RXCHAR;
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

	if (rOverlapped_.hEvent!= NULL)
	{
		CloseHandle(rOverlapped_.hEvent);
		rOverlapped_.hEvent= NULL;
	}

	if (wOverlapped_.hEvent!= NULL)
	{
		CloseHandle(wOverlapped_.hEvent);
		wOverlapped_.hEvent= NULL;
	}

	aborted_= false;
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
ulong SerialPort::readTimeOut() const
{
	return readTimeOut_;
}
// ---------------------------------------------------------------------------
void SerialPort::setReadTimeOut(ulong readTimeOut)
{
	readTimeOut_= readTimeOut;
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
void SerialPort::abort()
{
   aborted_= true;
	 SetEvent(wOverlapped_.hEvent);
	 SetEvent(rOverlapped_.hEvent);
}
//--------------------------------------------------------------------------