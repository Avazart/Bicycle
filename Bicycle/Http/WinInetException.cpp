//---------------------------------------------------------------------------
#include "WinInetException.h"

using namespace Bicycle;
//---------------------------------------------------------------------------
#define BI_USE_ERROR_PREFIX
//---------------------------------------------------------------------------
WinInetException::WinInetException()
  :std::exception()
{
  code_= GetLastError();
  message_= formatMessage(code_,L"wininet.dll");
}
//---------------------------------------------------------------------------
WinInetException::WinInetException( ulong errorCode,
                                  const std::string& prefix)
  : code_(errorCode),
#ifdef BI_USE_ERROR_PREFIX
    message_(prefix+formatMessage(errorCode,L"wininet.dll"))
#else
    message_(formatMessage(errorCode,"wininet.dll"))
#endif
{
}
//---------------------------------------------------------------------------
WinInetException::WinInetException(const std::string& prefix)
{
  code_= GetLastError();
#ifdef BI_USE_ERROR_PREFIX
  message_= prefix+formatMessage(code_,L"wininet.dll");
#else
  message_= formatMessage(code_,"wininet.dll");
#endif
}
//---------------------------------------------------------------------------
const char * WinInetException::what() const
{
  return message_.c_str();
}
//---------------------------------------------------------------------------
const std::string WinInetException::message() const
{
  return message_;
}
//---------------------------------------------------------------------------
const std::string WinInetException::systemMessage() const
{
  return formatMessage(code_,L"wininet.dll");
}
//---------------------------------------------------------------------------
const ulong WinInetException::code() const
{
  return code_;
}
//---------------------------------------------------------------------------
void WinInetException::check(ulong errorCode)
{
  if(errorCode!=0)
    throw WinInetException(errorCode);
}
//---------------------------------------------------------------------------
