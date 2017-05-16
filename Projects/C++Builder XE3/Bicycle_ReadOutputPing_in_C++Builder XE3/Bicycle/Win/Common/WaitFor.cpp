#include "WaitFor.h"
//-------------------------------------------------------
void Bicycle::waitFor(HANDLE operationEvent,
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
//-------------------------------------------------------
