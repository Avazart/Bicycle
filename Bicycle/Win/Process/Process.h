#ifdef _MSC_VER
  #pragma once
#endif
// ---------------------------------------------------------------------------
#ifndef ProcessH
#define ProcessH
// ---------------------------------------------------------------------------
#include "../Common/Global.h"
#include "../Common/IODevice.h"
#include "../Common/Exception.h"
#include "../Common/Event.h"

#include "Pipe.h"
#include "Environment.h"
// ---------------------------------------------------------------------------
namespace Bicycle
{
// ---------------------------------------------------------------------------
std::size_t threadWindows(ulong threadId, std::vector<HWND>& windows);
// ---------------------------------------------------------------------------
struct ProcessError  // enum class
{
enum:ulong
  {
    Success= ERROR_SUCCESS,
    WaitTimeOut= WAIT_TIMEOUT,      // #258 (0x102) The wait operation timed out.
  };
};
// ---------------------------------------------------------------------------
class Process: private NonCopyable
{
public:
  explicit Process(const tstring& appName= tstring(),
                   const tstring& cmdLine= tstring());
  ~Process();

  void start();
  void start(const tstring& appName,
             const tstring& cmdLine);

  void terminate(unsigned exitCode=9); // kill
  void closeWindows(); // post WM_CLOSE all thread windows

  void  detach(); // invoke closeHandles()
  bool  isStarted()  const;
  ulong exitCode() const;
  bool  isFinished() const;

  // Wait Functions
  void waitForInputIdle(ulong msecs= DEFAULT_TIMEOUT);
  void waitForFinished(ulong msecs= DEFAULT_TIMEOUT);

  // Setters
  void usePipes(bool usePipes);

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

  ServerPipe& stdOut();
  ServerPipe& stdIn();

  void cancel();

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

  Event cancelEvent_;

  struct
  {
    ClientPipe client;
    ServerPipe server;
  } stdOut_;

  struct
  {
    ClientPipe client;
    ServerPipe server;
  } stdIn_;
};
// ---------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------
#endif
