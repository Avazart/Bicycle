#ifdef _MSC_VER
#pragma once
#endif
// ---------------------------------------------------------------------------
#ifndef SerialPortH
#define SerialPortH
//---------------------------------------------------------------------------
#include <vector>
#include <string>

#include "Global.h"
#include "IODevice.h"
#include "SystemException.h"
#include "Sync/AtomicCounter.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
struct SerialError  // enum class
{
  enum:ulong
    {
    Success= ERROR_SUCCESS,
    WaitTimeOut= WAIT_TIMEOUT,          // #258 (0x102) The wait operation timed out.
    Incomplete=  ERROR_IO_INCOMPLETE,   // #996  Overlapped I/O event is not in a signaled state.  // Операция ввода/вывода была прервана из-за завершения потока команд или по запросу приложения.
    PortNotFound= ERROR_FILE_NOT_FOUND, // #2 The system cannot find the file specified.
    Aborted= ERROR_OPERATION_ABORTED    // #995  Операция ввода/вывода была прервана из-за завершения потока команд или по запросу приложения.
    };
};
//---------------------------------------------------------------------------
class SerialPort: public IODevice, private NonCopyable
{
public:
  //  IODevice:
  virtual ulong read(char* data, ulong size, ulong& errorCode);
  virtual ulong write(const char* data, ulong size, ulong& errorCode);
  virtual void checkErrorCode(ulong code) const;

  //
  explicit SerialPort(const tstring& portName= tstring(),
                      ulong baudRate= CBR_9600,
                      ulong readTimeOut=  DEFAULT_TIMEOUT);

  virtual ~SerialPort();

  void open();
  void close();

  const tstring& portName() const;
  void  setPortName(const tstring& portName);

  ulong readTimeOut()const;
  void setReadTimeOut(ulong readTimeOut);

  ulong baudRate()const;
  void  setBaudRate(ulong baudrate);

  HANDLE handle()const;

  void abort();  // THREAD_SAFE

private:
  void setDefaultSettings(HANDLE portHandle);

private:
  AtomicCounter aborted_;

  tstring portName_;
  HANDLE handle_;

  OVERLAPPED rOverlapped_;
  OVERLAPPED wOverlapped_;

  ulong baudRate_;
  DCB dcb_;
  COMMTIMEOUTS commTimeOuts_;

  ulong readTimeOut_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
