//---------------------------------------------------------------------------
#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef EventH
#define EventH
//---------------------------------------------------------------------------
#include "../Common/Global.h"
#include "../Common/NonCopyable.h"
#include "../Common/Exception.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
class Event: private NonCopyable
{
  public:
     explicit Event(bool manualReset=  true,
                    bool initialState= false,
                    const tstring& name= tstring() );

     explicit Event(HANDLE handle);

     void close();
     ~Event();

     HANDLE handle()const;

     void setEvent();
     void resetEvent();

     bool waitFor(ulong timeOut= INFINITE);

  private:
     HANDLE handle_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif 
