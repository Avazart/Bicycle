#ifdef _MSC_VER
  #pragma once
#endif
// ---------------------------------------------------------------------------
#ifndef ProcessH
#define ProcessH
// ---------------------------------------------------------------------------
#include "../Global.h"
#include "../IODevice.h"
#include "../SystemException.h"

#include "Pipe.h"
// ---------------------------------------------------------------------------
namespace Bicycle
{
// ---------------------------------------------------------------------------
std::size_t threadWindows(ulong threadId, std::vector<HWND>& windows);
// ---------------------------------------------------------------------------
class Process: public IODevice, private NonCopyable
{
public:
  //  IODevice
  virtual ulong read(char* data, ulong size, ulong& errorCode);
  virtual ulong write(const char* data, ulong size, ulong& errorCode);
  virtual void checkErrorCode(ulong code) const;

  explicit Process(const tstring& appName= tstring(),const tstring& cmdLine= tstring());
  ~Process();

  void start();
  void start(const tstring& appName,
             const tstring& cmdLine);

  bool terminate(unsigned exitCode=9, ulong* errorCode=0); // kill
  void closeWindows(); // post WM_CLOSE all thread windows

  void  detach(); // invoke closeHandles()
  bool  isStarted()  const;
  ulong exitCode(ulong* errorCode=0) const;
  bool  isFinished(ulong* errorCode=0) const;

  // Wait Functions
  void waitForInputIdle(ulong msecs= DEFAULT_TIMEOUT, ulong* erroCode=0);
  void waitForFinished(ulong msecs= DEFAULT_TIMEOUT, ulong* erroCode=0);

  // Setters
  void usePipes(bool usePipes);
  void setReadTimeOut(ulong msecs);
  void setWriteTimeOut(ulong msecs);

  void setAppName(const tstring& appName);
  void setCmdLine(const tstring& cmdLine);
  void setCurrentDir(const tstring& dir);

  void setFlags(ulong flags);
  void setInheritHandle(bool inheritHandle);
  void setShowWindow(unsigned short showWindow);
  void setPriority(ulong priority);
  // void 	setEnvironment(const ... environment)

  // Getters:
  tstring appName()   const;
  tstring cmdLine()   const;
  tstring currentDir()const;

  ulong flags()const;
  // bool inheritHandle() const;
  // unsigned short showWindow() const;
  ulong priority();
  // Enviroment enviroment()const;

  // Process info
  HANDLE processHandle() const;
  HANDLE threadHandle()  const;

  ulong processId()const;
  ulong threadId() const;

private:
  void closeHandles();
  virtual void createPipes();
  virtual void createProcess();

  tstring appName_;
  tstring cmdLine_;
  tstring currentDir_;

  STARTUPINFO startupInfo_;
  PROCESS_INFORMATION processInfo_;
  SECURITY_ATTRIBUTES security_;

  BOOL   started_;
  ulong  priority_;
  bool   usePipes_;

  struct
  {
    ClientPipe client;
    ServerPipe server;
    PipeReader reader;
  } stdOut_;

  struct
  {
    ClientPipe client;
    ServerPipe server;
    PipeWriter writer;
  } stdIn_;
};
// ---------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------
#endif
