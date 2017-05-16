#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef PipeH
#define PipeH
//---------------------------------------------------------------------------
#include "../Common/Global.h"
#include "../Common/Exception.h"
#include "../Common/NonCopyable.h"
#include "../Common/IODevice.h"
#include "../Common/Event.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
struct PipeError  // enum class
{
  enum:ulong
  {
    Success= ERROR_SUCCESS,
    WaitTimeOut= WAIT_TIMEOUT,      // #258 (0x102) The wait operation timed out.

    Broken=  ERROR_BROKEN_PIPE, // [Error #109 Канал был закрыт.]  The pipe has been ended.
    NoData=  ERROR_NO_DATA,     // [Error #232 Идет закрытие канала.] The pipe is being closed.
    Incomplete= ERROR_IO_INCOMPLETE, // 996  Overlapped I/O event is not in a signaled state.

    Busy = ERROR_PIPE_BUSY
  };
};
//---------------------------------------------------------------------------
class AbstractNamedPipe: public IODevice,private NonCopyable
{
public:
  AbstractNamedPipe(const tstring& name= tstring());
  virtual ~AbstractNamedPipe();

  HANDLE handle()const;
  bool isValide()const;
  void close();

  tstring name()const;
  void setName(const tstring& name);

  void setTimeOut(ulong msecs);

  static bool wait(const tstring& pipeName,ulong msec= DEFAULT_TIMEOUT);

  void cancel();  // THREAD_SAFE

  // IODevice
  virtual ulong read(char* data, ulong size);
  virtual ulong write(const char* data, ulong size);

protected:
  tstring name_;
  HANDLE handle_;
  ulong timeOut_;

  Event cancelEvent_;
};
//---------------------------------------------------------------------------
class ServerPipe: public AbstractNamedPipe
{
public:
  ServerPipe(const tstring& name= tstring());
  ~ServerPipe();

  void create();
  void connect();
  void disconnect(ulong& errorCode);

  void setOpenMode(ulong mode);
  void setPipeMode(ulong mode);
  void setMaxInstances(ulong maxInstances);
  void setBufferSize(ulong size);

private:
  ulong openMode_;
  ulong pipeMode_;
  ulong maxInstances_;
  ulong	bufferSize_;
};
//---------------------------------------------------------------------------
class ClientPipe: public AbstractNamedPipe
{
public:
  ClientPipe(const tstring& name= tstring());

  void open();

  void setState(ulong mode);

 // void state();

  void setDesiredAccess(ulong access);
  void setSharedMode(ulong mode);
  void setFlagsAndAttributes(ulong flagsAndAttr);

private:
  ulong desiredAccess_;
  ulong sharedMode_;
  ulong flagsAndAttributes_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
