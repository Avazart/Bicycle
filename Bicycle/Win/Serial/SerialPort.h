#ifdef _MSC_VER
#pragma once
#endif
// ---------------------------------------------------------------------------
#ifndef SerialPortH
#define SerialPortH
//---------------------------------------------------------------------------
#include <vector>
#include <string>

#include "../Common/Global.h"
#include "../Common/NonCopyable.h"
#include "../Common/IODevice.h"
#include "../Common/Exception.h"
#include "../Common/WaitFor.h"
#include "../Common/Event.h"
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
  ulong waitEvent();

  //  IODevice:
  virtual ulong read(char* data, ulong size);
  virtual ulong write(const char* data, ulong size);

  //
  explicit SerialPort(const tstring& portName= tstring(),
                      ulong baudRate= CBR_9600,
                      ulong timeOut=  DEFAULT_TIMEOUT);

  virtual ~SerialPort();

  void open();
  void close();

  const tstring& portName() const;
  void  setPortName(const tstring& portName);

  ulong timeOut()const;
  void  setTimeOut(ulong timeOut);

  ulong baudRate()const;
  void  setBaudRate(ulong baudrate);

  HANDLE handle()const;

  void cancel();  // THREAD_SAFE

private:
  void setDefaultSettings(HANDLE portHandle);
  void waitEvent(ulong &mask, OVERLAPPED& overlapped);

private:
  Event cancelEvent_;

  tstring portName_;
  HANDLE handle_;

  ulong baudRate_;
  DCB dcb_;
  COMMTIMEOUTS commTimeOuts_;

  ulong timeOut_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
