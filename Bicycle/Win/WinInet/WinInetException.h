#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef WinInetExceptionH
#define WinInetExceptionH
//---------------------------------------------------------------------------
#include "Win/Common/Global.h"
#include "Win/Common/Exception.h"
// ---------------------------------------------------------------------------
namespace Bicycle
{
extern const tstring wininetLib;
//---------------------------------------------------------------------------
class WinInetException: public SystemException
{
public:
  WinInetException();
  explicit WinInetException(ulong errorCode);

  virtual const std::string message() const;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
