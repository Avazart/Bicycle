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
/*             Abstract Pipe                                                */
//---------------------------------------------------------------------------
AbstractPipe::AbstractPipe(const tstring &name):
    name_(name),
    handle_(INVALID_HANDLE_VALUE)
{
}
//---------------------------------------------------------------------------
AbstractPipe::~AbstractPipe()
{
  close();
}
//---------------------------------------------------------------------------
HANDLE AbstractPipe::handle() const
{
  return handle_;
}
//---------------------------------------------------------------------------
bool AbstractPipe::isValide() const
{
  return handle_!=INVALID_HANDLE_VALUE;
}
//---------------------------------------------------------------------------
void AbstractPipe::close()
{
  if(isValide())
  {
    CloseHandle(handle_);
    handle_= INVALID_HANDLE_VALUE;
  }
}
//---------------------------------------------------------------------------
tstring AbstractPipe::name() const
{
  return name_;
}
//---------------------------------------------------------------------------
void AbstractPipe::setName(const tstring &name)
{
  name_= name;
}
//---------------------------------------------------------------------------
void AbstractPipe::checkErrorCode(ulong code) const
{
  if(code)
		throw SystemException(code);
}
//---------------------------------------------------------------------------
/*             Server Pipe                                                 */
//---------------------------------------------------------------------------
ServerPipe::ServerPipe(const tstring& name)
  :AbstractPipe(name),
    pipeMode_(PIPE_TYPE_BYTE),
		maxInstances_(1),

		bufferSize_(DEFAULT_BUFF_SIZE),
		timeOut_(DEFAULT_TIMEOUT)
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
                             timeOut_,
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
void ServerPipe::setTimeOut(ulong msecs)
{
  timeOut_= msecs;
}
//---------------------------------------------------------------------------
ulong ServerPipe::read(char *data, ulong size, ulong &errorCode)
{
	errorCode= 0;
  ulong length= 0;
	BOOL success= ReadFile(handle_,
                         data,
                         size,
                         &length,
												 &overlapped_ );

  if(!success)
  {
		errorCode= GetLastError();
    if (errorCode==ERROR_IO_PENDING)
    {
			ulong waitResult= WaitForSingleObject(handle_, timeOut_);
      switch(waitResult)
      {
      case WAIT_OBJECT_0:  errorCode= PipeError::Success;     break;
      case WAIT_TIMEOUT:   errorCode= PipeError::WaitTimeOut; return 0;
			case WAIT_ABANDONED:
      case WAIT_FAILED:    errorCode= GetLastError();			return 0;
      default: break;
      }
    }
    else
      return 0;
  }

  success=
			GetOverlappedResult(handle_,&overlapped_,&length,false);

	if(!success)
    errorCode= GetLastError();

	overlapped_.Offset+= length;
	return length;
}
//---------------------------------------------------------------------------
ulong ServerPipe::write(const char *data, ulong size, ulong &errorCode)
{
	errorCode= 0;
	ulong length= 0;
	BOOL success= WriteFile(handle_,
													data,
													size,
													&length,
													&overlapped_);

	if (!success)
	{
		errorCode= GetLastError();
		if(errorCode==ERROR_IO_PENDING)
		{
			ulong waitResult= WaitForSingleObject(handle_,timeOut_);
			switch(waitResult)
			{
      case WAIT_OBJECT_0:  errorCode= PipeError::Success;      break;
      case WAIT_TIMEOUT:   errorCode= PipeError::WaitTimeOut; return 0;
			case WAIT_ABANDONED:
			case WAIT_FAILED:    errorCode= GetLastError();     return 0;
			default:break;
			}
		}
		else
			return 0;
	}

	success=
			GetOverlappedResult(handle_,&overlapped_,&length,FALSE);

	if(!success)
		errorCode= GetLastError();

	overlapped_.Offset+= length;
	return length;
}
//---------------------------------------------------------------------------
/*                 Client Pipe                                             */
//---------------------------------------------------------------------------
FictiveClientPipe::FictiveClientPipe(const tstring& name)
	:AbstractPipe(name),

		desiredAccess_(GENERIC_READ),
		sharedMode_(0),
		flagsAndAttributes_(0)
{
}
//---------------------------------------------------------------------------
void FictiveClientPipe::open()
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
void FictiveClientPipe::setFlagsAndAttributes(ulong flagsAndAttr)
{
  flagsAndAttributes_= flagsAndAttr;
}
//---------------------------------------------------------------------------
void FictiveClientPipe::setDesiredAccess(ulong access)
{
  desiredAccess_= access;
}
//---------------------------------------------------------------------------
void FictiveClientPipe::setSharedMode(ulong mode)
{
  sharedMode_= mode;
}
//---------------------------------------------------------------------------
ulong FictiveClientPipe::read(char *, ulong , ulong &)
{
  return 0;
}
//---------------------------------------------------------------------------
ulong FictiveClientPipe::write(const char *, ulong, ulong &)
{
  return 0;
}
//---------------------------------------------------------------------------
