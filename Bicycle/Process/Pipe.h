﻿#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef PipeH
#define PipeH
//---------------------------------------------------------------------------
#include "Global.h"
#include "SystemException.h"
#include "NonCopyable.h"
#include "IODevice.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
struct PipeError  // enum class
{
enum:
  ulong
  {
    Success= ERROR_SUCCESS,
    WaitTimeOut= WAIT_TIMEOUT,      // #258 (0x102) The wait operation timed out.

    Broken=  ERROR_BROKEN_PIPE, // [Error #109 Канал был закрыт.]  The pipe has been ended.
    NoData=  ERROR_NO_DATA,     // [Error #232 Идет закрытие канала.] The pipe is being closed.
    Incomplete= ERROR_IO_INCOMPLETE // 996  Overlapped I/O event is not in a signaled state.
  };
};
//---------------------------------------------------------------------------
class AbstractPipe: public IODevice,private NonCopyable
{
public:
  AbstractPipe(const tstring& name= tstring());
  virtual ~AbstractPipe();

  HANDLE handle()const;
  bool isValide()const;
  void close();

  tstring name()const;
  void setName(const tstring& name);


  // IODevice
  virtual void checkErrorCode(ulong code)const;

protected:
  tstring name_;
  HANDLE handle_;
};
//---------------------------------------------------------------------------
class ServerPipe: public AbstractPipe
{
public:
  ServerPipe(const tstring& name= tstring());
  ~ServerPipe();

  void create();
  void connect();
  void disconnect(ulong& errorCode);

  void setOpenMode(ulong mode);
  void setPipeMode(ulong mode);
  void setBufferSize(ulong size);

  void setTimeOut(ulong msecs);

  // IODevice
  virtual ulong read(char* data, ulong size, ulong& errorCode);
  virtual ulong write(const char* data, ulong size, ulong& errorCode);

private:
  OVERLAPPED overlapped_;
  ulong timeOut_;

  ulong openMode_;
  ulong pipeMode_;
  ulong maxInstances_;
  ulong	bufferSize_;
};
//---------------------------------------------------------------------------
class FictiveClientPipe: public AbstractPipe
{
public:
  FictiveClientPipe(const tstring& name= tstring());

  void open();

  void setDesiredAccess(ulong access);
  void setSharedMode(ulong mode);
  void setFlagsAndAttributes(ulong flagsAndAttr);

  // IODevice
  virtual ulong read(char* data, ulong size, ulong& errorCode);
  virtual ulong write(const char* data, ulong size, ulong& errorCode);

private:
  ulong desiredAccess_;
  ulong sharedMode_;
  ulong flagsAndAttributes_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
