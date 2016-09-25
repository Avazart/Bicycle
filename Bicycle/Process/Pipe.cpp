//---------------------------------------------------------------------------
#include "Pipe.h"
#include <sstream>

using namespace Bicycle;
//---------------------------------------------------------------------------
tstring genName()
{
  std::basic_stringstream<tchar> tss;
  tss<<TEXT("\\\\.\\pipe\\MyProccesPipe-")<<std::hex<<rand();
  return tss.str();
}
//---------------------------------------------------------------------------
/*             Server Pipe                                                 */
//---------------------------------------------------------------------------
ServerPipe::ServerPipe(const tstring& name)
  :NonCopyable(),
    name_(name),
    pipeMode_(PIPE_TYPE_BYTE),
    maxInstances_(1),
    defaultTimeOut_(DEFAULT_TIMEOUT),
    handle_(INVALID_HANDLE_VALUE)
{
  if(name_.empty())
    name_= genName();
}
//---------------------------------------------------------------------------
/*virtual*/ServerPipe::~ServerPipe()
{
  ulong ec;
  disconnect(ec);
  close();
}
//---------------------------------------------------------------------------
void ServerPipe::create()
{
  close();
  ZeroMemory(&overlapped_, sizeof(overlapped_));

  SECURITY_ATTRIBUTES secAtt = { sizeof(SECURITY_ATTRIBUTES), 0, false };
  handle_ = CreateNamedPipe( name_.c_str(),
                             openMode_,
                             pipeMode_,
                             maxInstances_,
                             bufferSize_,
                             bufferSize_,
                             defaultTimeOut_,
                             &secAtt);

  if(handle_==INVALID_HANDLE_VALUE)
    throw SystemException("void ServerPipe::create() ");
}
//---------------------------------------------------------------------------
void ServerPipe::connect()
{
  ulong success= ConnectNamedPipe(handle_,&overlapped_);
  if(!success)
  {
    ulong code= GetLastError();
    if(code==ERROR_IO_PENDING)
    {
      ulong waitResult= WaitForSingleObject(handle_,INFINITE);
      if(waitResult!=WAIT_OBJECT_0)
        throw SystemException("void ServerPipe::connect() ");
    }
    else
      throw SystemException("void ServerPipe::connect() ");
  }
}
//---------------------------------------------------------------------------
void ServerPipe::setOpenMode(ulong mode)
{
  openMode_= mode;
}
//---------------------------------------------------------------------------
void ServerPipe::setPipeMode(ulong mode)
{
  pipeMode_= mode;
}
//---------------------------------------------------------------------------
OVERLAPPED& ServerPipe::overlapped()
{
  return overlapped_;
}
//---------------------------------------------------------------------------
HANDLE ServerPipe::handle()const
{
  return handle_;
}
//---------------------------------------------------------------------------
bool ServerPipe::isValide()const
{
  return handle_!=INVALID_HANDLE_VALUE;
}
//---------------------------------------------------------------------------
void ServerPipe::disconnect(ulong& ec)
{
  if(isValide())
  {
    if(!DisconnectNamedPipe(handle_))
      ec= GetLastError();
  }
}
//---------------------------------------------------------------------------
void ServerPipe::close()
{
  if(isValide())
  {
    CloseHandle(handle_);
    handle_= INVALID_HANDLE_VALUE;
  }
}
//---------------------------------------------------------------------------
void ServerPipe::setBufferSize(ulong size)
{
  bufferSize_= size;
}
//---------------------------------------------------------------------------
tstring ServerPipe::name()const
{
  return name_;
}
//---------------------------------------------------------------------------
/*                 Client Pipe                                             */
//---------------------------------------------------------------------------
ClientPipe::ClientPipe(const tstring& name)
  :NonCopyable(),
    name_(name),
    desiredAccess_(GENERIC_READ),
    sharedMode_(0),

    flagsAndAttributes_(0),
    handle_(INVALID_HANDLE_VALUE)
{
}
//---------------------------------------------------------------------------
/*virtual*/ClientPipe::~ClientPipe()
{
  close();
}
//---------------------------------------------------------------------------
void ClientPipe::open()
{
  close();

  SECURITY_ATTRIBUTES secAtt= { sizeof(SECURITY_ATTRIBUTES), 0,true};
  handle_= CreateFile( name_.c_str(),
                       desiredAccess_,
                       0,
                       &secAtt,
                       OPEN_EXISTING,
                       flagsAndAttributes_,
                       NULL );
  if(handle_==INVALID_HANDLE_VALUE)
    throw SystemException("void ClientPipe::open() ");
}
//---------------------------------------------------------------------------
void ClientPipe::setFlagsAndAttributes(ulong flagsAndAttr)
{
  flagsAndAttributes_= flagsAndAttr;
}
//---------------------------------------------------------------------------
void ClientPipe::setDesiredAccess(ulong access)
{
  desiredAccess_= access;
}
//---------------------------------------------------------------------------
void ClientPipe::setSharedMode(ulong mode)
{
  sharedMode_= mode;
}
//---------------------------------------------------------------------------
tstring ClientPipe::name()const
{
  return name_;
}
//---------------------------------------------------------------------------
void ClientPipe::setName(const tstring& name)
{
  name_= name;
}
//---------------------------------------------------------------------------
void ClientPipe::close()
{
  if(isValide())
  {
    CloseHandle(handle_);
    handle_= INVALID_HANDLE_VALUE;
  }
}
//---------------------------------------------------------------------------
HANDLE ClientPipe::handle()const
{
  return handle_;
}
//---------------------------------------------------------------------------
bool ClientPipe::isValide()const
{
  return handle_!=INVALID_HANDLE_VALUE;
}
//---------------------------------------------------------------------------
/*                      PipeReader                                         */
//---------------------------------------------------------------------------
PipeReader::PipeReader(ServerPipe* pipe)
  :pipe_(pipe),
    timeOut_(INFINITE)
{
}
//---------------------------------------------------------------------------
PipeReader::~PipeReader()
{
}
//---------------------------------------------------------------------------
void PipeReader::setPipe(ServerPipe* pipe)
{
  pipe_= pipe;
}
//---------------------------------------------------------------------------
void PipeReader::setTimeOut(ulong msecs)
{
  timeOut_= msecs;
}
//---------------------------------------------------------------------------
ulong PipeReader::read(char* data, ulong size, ulong& errorCode)
{    // Read From Pipe only
  errorCode= 0;
  ulong length= 0;
  BOOL success= ReadFile(pipe_->handle(),
                         data,
                         size,
                         &length,
                         &pipe_->overlapped() );

  if(!success)
  {
    errorCode= GetLastError();
    if (errorCode==ERROR_IO_PENDING)
    {
      ulong waitResult= WaitForSingleObject(pipe_->handle_, timeOut_);
      switch(waitResult)
      {
      case WAIT_OBJECT_0:  errorCode= ProcessError::Success;     break;
      case WAIT_TIMEOUT:   errorCode= ProcessError::WaitTimeOut; return 0;
      case WAIT_ABANDONED:
      case WAIT_FAILED:    errorCode= GetLastError();			return 0;
      default: break;
      }
    }
    else
      return 0;
  }

  success=
      GetOverlappedResult(pipe_->handle_,&pipe_->overlapped_,&length,false);

  if(!success)
    errorCode= GetLastError();

  pipe_->overlapped().Offset+= length;
  return length;
}
//---------------------------------------------------------------------------
/*                          PipeWriter                                     */
//---------------------------------------------------------------------------
PipeWriter::PipeWriter(ServerPipe* pipe)
  :pipe_(pipe),
   timeOut_(INFINITE)
{
}
//---------------------------------------------------------------------------
PipeWriter::~PipeWriter()
{
}
//---------------------------------------------------------------------------
void PipeWriter::setPipe(ServerPipe* pipe)
{
  pipe_= pipe;
}
//---------------------------------------------------------------------------
void PipeWriter::setTimeOut(ulong msecs)
{
  timeOut_= msecs;
}
//---------------------------------------------------------------------------
ulong PipeWriter::write(const char* data, ulong size, ulong& errorCode)
{
  // FIX: create another structure OVERLOPPAD and evetn for writting

  ulong length= 0;
  BOOL success= WriteFile(pipe_->handle(),
                          data,
                          size,
                          &length,
                          &pipe_->overlapped());

  if (!success)
  {
    errorCode= GetLastError();
    if(errorCode==ERROR_IO_PENDING)
    {
      ulong waitResult= WaitForSingleObject(pipe_->handle(),timeOut_);
      switch(waitResult)
      {
      case WAIT_OBJECT_0:  errorCode= ProcessError::Success;      break;
      case WAIT_TIMEOUT:   errorCode= ProcessError::WaitTimeOut; return 0;
      case WAIT_ABANDONED:
      case WAIT_FAILED:    errorCode= GetLastError();     return 0;
      default:break;
      }
    }
    else
      return 0;
  }

  success=
      GetOverlappedResult(pipe_->handle(),&pipe_->overlapped(),&length,FALSE);

  if(!success)
    errorCode= GetLastError();

  pipe_->overlapped().Offset+= length;
  return length;
}
//---------------------------------------------------------------------------

