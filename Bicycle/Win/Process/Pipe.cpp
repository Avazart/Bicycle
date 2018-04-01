//---------------------------------------------------------------------------
#include "Pipe.h"
#include <sstream>

using namespace Bicycle;
//---------------------------------------------------------------------------
void waitFor(HANDLE operationEvent,
             HANDLE cancelEvent,
             ulong timeOut)
{
  HANDLE handles[2]= { operationEvent, cancelEvent };

  ulong waitResult=
      WaitForMultipleObjects(2,handles,false, timeOut);

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
tstring genName()
{
  std::basic_stringstream<tchar> tss;
  tss<<TEXT("\\\\.\\pipe\\MyProccesPipe-")<<std::hex<<rand();
  return tss.str();
}
//---------------------------------------------------------------------------
/*             Abstract Pipe                                                */
//---------------------------------------------------------------------------
AbstractNamedPipe::AbstractNamedPipe(const tstring &name):
    name_(name),
    handle_(INVALID_HANDLE_VALUE),
    timeOut_(DEFAULT_TIMEOUT)
{
}
//---------------------------------------------------------------------------
AbstractNamedPipe::~AbstractNamedPipe()
{
  close();
}
//---------------------------------------------------------------------------
HANDLE AbstractNamedPipe::handle() const
{
  return handle_;
}
//---------------------------------------------------------------------------
bool AbstractNamedPipe::isValide() const
{
  return handle_!=INVALID_HANDLE_VALUE;
}
//---------------------------------------------------------------------------
void AbstractNamedPipe::close()
{
  if(isValide())
  {
    CloseHandle(handle_);
    handle_= INVALID_HANDLE_VALUE;
  }

  cancelEvent_.resetEvent();
}
//---------------------------------------------------------------------------
tstring AbstractNamedPipe::name() const
{
  return name_;
}
//---------------------------------------------------------------------------
void AbstractNamedPipe::setName(const tstring &name)
{
  name_= name;
}
//---------------------------------------------------------------------------
void AbstractNamedPipe::setTimeOut(ulong msecs)
{
  timeOut_= msecs;
}
//---------------------------------------------------------------------------
bool AbstractNamedPipe::wait(const tstring &pipeName, ulong msec)
{
  return !WaitNamedPipe(pipeName.c_str(), msec);
}
//---------------------------------------------------------------------------
void AbstractNamedPipe::cancel()
{
  cancelEvent_.setEvent();
}
//---------------------------------------------------------------------------
ulong AbstractNamedPipe::read(char *data, ulong size)
{
  OVERLAPPED overlapped={0};
  Event event;
  overlapped.hEvent=  event.handle();

  ulong length= 0;
  BOOL done= ReadFile(handle_,
                       data,
                       size,
                       &length,
                       &overlapped );
  ulong error = GetLastError();

  if(!done && error==ERROR_IO_PENDING)
  {
    waitFor(overlapped.hEvent,cancelEvent_.handle(),timeOut_);
    done= true;
  }

  if(done)
  {
    if(overlapped.Internal!=0)
       throw SystemException(overlapped.Internal);
    return overlapped.InternalHigh; // length
  }
  else
  {
    throw SystemException(error);
  }

  return length;
}
//---------------------------------------------------------------------------
ulong AbstractNamedPipe::write(const char *data, ulong size)
{
  OVERLAPPED overlapped={0};
  Event event;
  overlapped.hEvent=  event.handle();

  ulong length= 0;
  BOOL done= WriteFile(handle_,
                          data,
                          size,
                          &length,
                          &overlapped);

  ulong error = GetLastError();

  if(!done && error==ERROR_IO_PENDING)
  {
    waitFor(overlapped.hEvent,cancelEvent_.handle(),timeOut_);
    done= true;
  }

  if(done)
  {
    if(overlapped.Internal!=0)
       throw SystemException(overlapped.Internal);
    return overlapped.InternalHigh; // length
  }
  else
  {
    throw SystemException(error);
  }
}
//---------------------------------------------------------------------------
/*             Server Pipe                                                 */
//---------------------------------------------------------------------------
ServerPipe::ServerPipe(const tstring& name)
  :AbstractNamedPipe(name),
    pipeMode_(PIPE_TYPE_BYTE),
    maxInstances_(1),

    bufferSize_(DEFAULT_BUFF_SIZE)
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

  SECURITY_ATTRIBUTES secAtt = { sizeof(SECURITY_ATTRIBUTES), 0, false };
  handle_ = CreateNamedPipe( name_.c_str(),
                             openMode_,  // PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED read/write access, overlapped mode
                             pipeMode_, // PIPE_TYPE_MESSAGE|PIPE_READMODE_MESSAGE|PIPE_WAIT, //  // message-type pipe, message read mode, blocking mode
                             maxInstances_,
                             bufferSize_,
                             bufferSize_,
                             DEFAULT_TIMEOUT, // timeOut_,
                             &secAtt);

  if(handle_==INVALID_HANDLE_VALUE)
    throw SystemException();
}
//---------------------------------------------------------------------------
void ServerPipe::connect()
{
  OVERLAPPED overlapped={0};
  Event event;
  overlapped.hEvent=  event.handle();

  ulong success= ConnectNamedPipe(handle_,&overlapped);
  if(!success)
  {
    ulong error= GetLastError();
    if(error==ERROR_IO_PENDING)
       waitFor(overlapped.hEvent,cancelEvent_.handle(),timeOut_);
    else
       throw SystemException(error);
  }
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
void ServerPipe::setBufferSize(ulong size)
{
  bufferSize_= size;
}
//---------------------------------------------------------------------------
void ServerPipe::setMaxInstances(ulong maxInstances)
{
  maxInstances_= maxInstances;
}
//---------------------------------------------------------------------------
/*                 Client Pipe                                             */
//---------------------------------------------------------------------------
ClientPipe::ClientPipe(const tstring& name)
	:AbstractNamedPipe(name),

		desiredAccess_(GENERIC_READ),
		sharedMode_(0),
    flagsAndAttributes_(FILE_ATTRIBUTE_NORMAL)
{
}
//---------------------------------------------------------------------------
void ClientPipe::open()
{
  close();

  SECURITY_ATTRIBUTES secAtt= { sizeof(SECURITY_ATTRIBUTES), 0,true};
  handle_= CreateFile( name_.c_str(),
                       desiredAccess_,
                       sharedMode_,
                       &secAtt,
											 OPEN_EXISTING,
                       flagsAndAttributes_,
                       NULL );
  if(handle_==INVALID_HANDLE_VALUE)
    throw SystemException();
}
//---------------------------------------------------------------------------
void ClientPipe::setState(ulong mode)
{
  // PIPE_READMODE_MESSAGE;
  BOOL success = SetNamedPipeHandleState(
       handle_,    // pipe handle
       &mode,      // new pipe mode
       NULL,       // don't set maximum bytes
       NULL);      // don't set maximum time

   if(!success)
      throw SystemException();
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
