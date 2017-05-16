//---------------------------------------------------------------------------
#include "Process.h"
//---------------------------------------------------------------------------
using namespace Bicycle;
//------------------- Process --------------------------------------------
Process::Process(const tstring& appName,
                 const tstring& cmdLine)
  : appName_(appName),
    cmdLine_(cmdLine),

    started_(false),
    priority_(NORMAL_PRIORITY_CLASS),
    creationFlags_(0),
    usePipes_(false)
{
  security_.nLength= sizeof(security_);
  security_.bInheritHandle = inheritHandle_ = false;
  security_.lpSecurityDescriptor= NULL;

  ZeroMemory(&startupInfo_, sizeof(startupInfo_));
  startupInfo_.cb= sizeof(startupInfo_);
  startupInfo_.wShowWindow= SW_NORMAL;
  startupInfo_.dwFlags= STARTF_USESHOWWINDOW;

  ZeroMemory(&processInfo_, sizeof(processInfo_));
}
//---------------------------------------------------------------------------
Process::~Process()
{
  if(processInfo_.hProcess && processInfo_.hThread)
  {
    if(isStarted() && !isFinished())
      terminate(9);

    closeHandles();
  }
}
//---------------------------------------------------------------------------
void Process::detach()
{
  closeHandles();
}
//---------------------------------------------------------------------------
void Process::closeHandles()
{
  if(processInfo_.hProcess && processInfo_.hThread)
  {
    CloseHandle(processInfo_.hProcess);
    CloseHandle(processInfo_.hThread);
    ZeroMemory(&processInfo_, sizeof(processInfo_)); // = NULL
  }

  if(started_ && usePipes_)
  {
    stdOut_.client.close();
    stdOut_.server.close();

    stdIn_.client.close();
    stdIn_.server.close();
  }
}
//---------------------------------------------------------------------------
void Process::createPipes()
{
  // OUT
  stdOut_.server.setPipeMode(PIPE_TYPE_BYTE | PIPE_WAIT );
  stdOut_.server.setOpenMode(FILE_FLAG_OVERLAPPED | PIPE_ACCESS_INBOUND);
  stdOut_.server.create();

  stdOut_.client.setName(stdOut_.server.name());
  stdOut_.client.setDesiredAccess(GENERIC_WRITE);
  stdOut_.client.open();

  // IN
  stdIn_.server.setPipeMode(PIPE_TYPE_BYTE | PIPE_WAIT );
  stdIn_.server.setOpenMode(FILE_FLAG_OVERLAPPED | PIPE_ACCESS_OUTBOUND);
  stdIn_.server.create();

  stdIn_.client.setName(stdIn_.server.name());
  stdIn_.client.setDesiredAccess(GENERIC_READ);
  stdIn_.client.open();

  startupInfo_.dwFlags |= STARTF_USESTDHANDLES;
  startupInfo_.hStdOutput= stdOut_.client.handle();
  startupInfo_.hStdError=  stdOut_.client.handle();
  startupInfo_.hStdInput=  stdIn_.client.handle();
}
//---------------------------------------------------------------------------
void Process::start()
{
  cancelEvent_.resetEvent();

  started_= false;
  closeHandles();

  if(usePipes_)
    createPipes();

  createProcess();

  if(usePipes_)
  {
    stdOut_.client.close();
    stdIn_.client.close();
  }

  started_= true;
}
//---------------------------------------------------------------------------
void Process::start(const tstring& appName,
                    const tstring& cmdLine)
{
  setAppName(appName);
  setCmdLine(cmdLine);
  start();
}
//---------------------------------------------------------------------------
void Process::createProcess()
{
  tstring envStr =
    environment_.empty()
    ? tstring()
    : environment_.toEnvironmentString();

#ifdef UNICODE
  creationFlags_ |= CREATE_UNICODE_ENVIRONMENT;
#endif

  started_=
    CreateProcess( appName_.empty()? 0 : appName_.c_str(), // _In_opt_ LPCTSTR lpApplicationName,
                   cmdLine_.empty()? 0 : const_cast<tchar*>(cmdLine_.c_str()), // _Inout_opt_ LPTSTR lpCommandLine,
                   &security_,        // _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
                   &security_,        // _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
                   inheritHandle_,    // _In_  BOOL  bInheritHandles,
                   creationFlags_|priority_,    //  _In_ DWORD dwCreationFlags,
                   envStr.empty()? 0 : (LPVOID)envStr.c_str(), // _In_opt_ LPVOID lpEnvironment,
                   currentDir_.empty()? 0: currentDir_.c_str(),// _In_opt_ LPCTSTR lpCurrentDirectory,
                   &startupInfo_, // _In_  LPSTARTUPINFO lpStartupInfo,
                   &processInfo_); //  _Out_ LPPROCESS_INFORMATION lpProcessInformation

  if(!started_)
    throw SystemException();
}
//---------------------------------------------------------------------------
void Process::waitForInputIdle(ulong msecs)
{
  ulong waitResult= WaitForInputIdle(processInfo_.hProcess,msecs);
  switch(waitResult)
  {
     case 0:  return;
     case WAIT_TIMEOUT: throw WaitTimeOutException(); break;
     case WAIT_FAILED:  throw SystemException();  break;
     default:  break;
  }
}
//---------------------------------------------------------------------------
void Process::waitForFinished(ulong msecs)
{
   HANDLE handles[2]= { processInfo_.hProcess,cancelEvent_.handle()};

   ulong waitResult=
       WaitForMultipleObjects(2,handles,false, msecs);

   switch(waitResult)
   {
     case WAIT_OBJECT_0:	  return;
     case WAIT_OBJECT_0+1: throw CancelException();
     case WAIT_TIMEOUT:	  throw WaitTimeOutException();
     case WAIT_FAILED:     throw SystemException();
     default:	break;
   }
   return;
}
//---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------
void Process::usePipes(bool usePipes)
{
  usePipes_= usePipes;
}
// ---------------------------------------------------------------------------
void Process::setAppName(const tstring& appName)
{
  appName_= appName;
}
//---------------------------------------------------------------------------
void Process::setCmdLine(const tstring& cmdLine)
{
  cmdLine_= cmdLine;
}
//---------------------------------------------------------------------------
void Process::setCurrentDir(const tstring& dir)
{
  currentDir_= dir;
}
//---------------------------------------------------------------------------
void Process::setInheritHandle(bool inheritHandle)
{
  inheritHandle_= inheritHandle;
}
//---------------------------------------------------------------------------
void Process::setSecurityInheritHandle(bool inheritHandle)
{
  security_.bInheritHandle= inheritHandle;
}
//---------------------------------------------------------------------------
void Process::setShowWindow(unsigned short showWindow)
{
  startupInfo_.wShowWindow= showWindow;
}
//---------------------------------------------------------------------------
void Process::setCreationFlags(ulong flags)
{
  creationFlags_= flags;
}
//---------------------------------------------------------------------------
void Process::setPriority(ulong priority)
{
  priority_ = priority;
}
//---------------------------------------------------------------------------
void Process::setEnvironment(const Environment &environment)
{
  environment_= environment;
}
//---------------------------------------------------------------------------
const Environment &Process::environment() const
{
  return environment_;
}
//---------------------------------------------------------------------------
ulong Process::creationFlags()const
{
  return creationFlags_;
}
//---------------------------------------------------------------------------
ulong Process::priority() const
{
  return priority_;
}
//---------------------------------------------------------------------------
void Process::setStartupInfoFlags(ulong flags)
{
  startupInfo_.dwFlags= flags;
}
//---------------------------------------------------------------------------
ulong Process::startupInfoFlags() const
{
  return startupInfo_.dwFlags;
}
//---------------------------------------------------------------------------
bool Process::inheritHandle() const
{
  return inheritHandle_ == TRUE;
}
//--------------------------------------------------------------------------
bool Process::securityInheritHandle() const
{
  return security_.bInheritHandle == TRUE;
}
//---------------------------------------------------------------------------
tstring Process::appName()const
{
  return appName_;
}
//---------------------------------------------------------------------------
tstring Process::cmdLine()const
{
  return cmdLine_;
}
//---------------------------------------------------------------------------
tstring Process::currentDir()const
{
  return currentDir_;
}
//---------------------------------------------------------------------------
HANDLE Process::processHandle()const
{
  return processInfo_.hProcess;
}
//---------------------------------------------------------------------------
HANDLE Process::threadHandle()const
{
  return processInfo_.hThread;
}
//---------------------------------------------------------------------------
ulong Process::processId()const
{
  return processInfo_.dwProcessId;
}
//---------------------------------------------------------------------------
ulong Process::threadId()const
{
  return processInfo_.dwThreadId;
}
//---------------------------------------------------------------------------
ServerPipe &Process::stdOut()
{
  return stdOut_.server;
}
//---------------------------------------------------------------------------
ServerPipe &Process::stdIn()
{
  return stdIn_.server;
}
//---------------------------------------------------------------------------
void Process::cancel()
{
  cancelEvent_.setEvent();
}
//---------------------------------------------------------------------------
bool Process::isStarted()const
{
  return started_!=0;
}
//-----------------------------------------------------------------------------
void Process::terminate(unsigned exitCode)
{
  if(!TerminateProcess(processInfo_.hProcess,exitCode))
     throw  SystemException();
}
//---------------------------------------------------------------------------
ulong Process::exitCode()const
{
  ulong exit_= 0;
  if(!GetExitCodeProcess(processInfo_.hProcess, &exit_))
     throw  SystemException();
  return exit_;
}
//---------------------------------------------------------------------------
bool Process::isFinished()const
{
  return exitCode()!=STILL_ACTIVE;
}
//---------------------------------------------------------------------------
void Process::closeWindows()
{
  if(isStarted() && !isFinished())
  {
    std::vector<HWND> windows;
    if(threadWindows(threadId(),windows))
    {
      for(std::size_t i=0; i<windows.size(); ++i)
        if(IsWindow(windows[i]))
          ::PostMessage(windows[i],WM_CLOSE,NULL,NULL);
    }
  }
}
//---------------------------------------------------------------------------
BOOL CALLBACK enumThreadWndProc(HWND hwnd,LPARAM lParam)
{
  std::vector<HWND>* windows=
    reinterpret_cast<std::vector<HWND>*>(lParam);
  windows->push_back(hwnd);
  return TRUE;
}
//---------------------------------------------------------------------------
std::size_t Bicycle::threadWindows(Bicycle::ulong threadId,
                                   std::vector<HWND>& windows)
{
  windows.clear();
  EnumThreadWindows(threadId,&enumThreadWndProc,(LPARAM)&windows);
  return windows.size();
}
//---------------------------------------------------------------------------

