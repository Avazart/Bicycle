#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef IODeviceH
#define IODeviceH
//---------------------------------------------------------------------------
#include "Global.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class IODevice
{
  public:
    virtual ~IODevice() {}
    virtual ulong read(char* data, ulong size, ulong& errorCode)=0;
    virtual ulong write(const char* data, ulong size, ulong& errorCode)=0;
    virtual void checkErrorCode(ulong code) const=0;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
