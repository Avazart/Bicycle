#ifndef WAITFOR_H
#define WAITFOR_H
//-------------------------------------------------------
#include "../Common/Exception.h"
//-------------------------------------------------------
namespace Bicycle
{
  void waitFor(HANDLE operationEvent,HANDLE cancelEvent,ulong timeOut);
}
//-------------------------------------------------------
#endif // WAITFOR_H
