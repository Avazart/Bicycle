//---------------------------------------------------------------------------
#include "WinInetException.h"
//---------------------------------------------------------------------------
using namespace Bicycle;
//---------------------------------------------------------------------------
const tstring Bicycle::wininetLib= TEXT("wininet.dll");
//---------------------------------------------------------------------------
WinInetException::WinInetException()
  :SystemException()
{
}
//---------------------------------------------------------------------------
WinInetException::WinInetException(ulong errorCode)
  :SystemException(errorCode)
{
}
//---------------------------------------------------------------------------
const std::string WinInetException::message() const
{
  return formatMessage(code(),wininetLib);
}
//---------------------------------------------------------------------------
