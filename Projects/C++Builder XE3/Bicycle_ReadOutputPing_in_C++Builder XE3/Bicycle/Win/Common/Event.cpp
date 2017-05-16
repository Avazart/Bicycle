#include "Event.h"

using namespace Bicycle;
//-------------------------------------------------------
Event::Event(bool manualReset,  /* = true */
             bool initialState, /* = false */
             const tstring& name) /* = tstring() */
  :handle_(0)
{
   handle_= CreateEvent(NULL,
                        manualReset,
                        initialState,
                        name.empty()? 0
                                    : name.c_str());
   if(!handle_)
     throw SystemException();
}
//-------------------------------------------------------
Event::Event(HANDLE handle)
  :handle_(handle)
{
}
//-------------------------------------------------------
void Event::close()
{
  if(handle_)
  {
    CloseHandle(handle_);
    handle_= 0;
  }
}
//-------------------------------------------------------
Event::~Event()
{
  close();
}
//-------------------------------------------------------
HANDLE Event::handle() const
{
  return handle_;
}
//-------------------------------------------------------
void Event::setEvent()
{
  if(!SetEvent(handle_))
     throw SystemException();
}
//-------------------------------------------------------
void Event::resetEvent()
{
  if(!ResetEvent(handle_))
    throw SystemException();
}
//-------------------------------------------------------
bool Event::waitFor(ulong timeOut)
{
  ulong waitResult=
    WaitForSingleObject(handle_,timeOut);

  switch(waitResult)
  {
    case WAIT_OBJECT_0:  return true;
    case WAIT_TIMEOUT:	 return false;
 //   case WAIT_ABANDONED:
    case WAIT_FAILED:    throw SystemException();
    default: break;
  }
  return false;
}
//---------------------------------------------------------------------------
