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
#include "Environment.h"
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

  void setStartupInfoFlags(ulong startupInfoFlags);
  void setInheritHandle(bool inheritHandle);
  void setSecurityInheritHandle(bool inheritHandle);

  void setShowWindow(unsigned short showWindow);
  void setCreationFlags(ulong flags);
  void setPriority(ulong priority);

  void 	setEnvironment(const Environment& environment);
  const Environment& environment()const;

  // Getters:
  tstring appName()   const;
  tstring cmdLine()   const;
  tstring currentDir()const;

  ulong startupInfoFlags()const;
  bool inheritHandle() const;
  bool securityInheritHandle() const;

  // unsigned short showWindow() const;
  ulong creationFlags() const;
  ulong priority()const;

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

  Environment environment_;

  BOOL   started_;
  ulong  creationFlags_;
  ulong  priority_;
  BOOL   inheritHandle_;
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
