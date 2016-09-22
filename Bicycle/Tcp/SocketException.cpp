//---------------------------------------------------------------------------
#include "SocketException.h"
//---------------------------------------------------------------------------
#include <winsock2.h>
#include <windows.h>
//---------------------------------------------------------------------------
using namespace Bicycle;
//---------------------------------------------------------------------------
#define USE_ERROR_PREFIX
//---------------------------------------------------------------------------
SocketException::SocketException()
  :std::exception()
{
  code_= WSAGetLastError();
	message_= formatMessage(code_);
}
//---------------------------------------------------------------------------
SocketException::SocketException( const ulong errorCode,
                                  const std::string& prefix)
  : code_(errorCode),
#ifdef USE_ERROR_PREFIX
    message_(prefix+formatMessage(errorCode))
#else
		message_(formatMessage(errorCode))
#endif
{
}
//---------------------------------------------------------------------------
SocketException::SocketException(const std::string& prefix)
{
  code_= GetLastError();
#ifdef USE_ERROR_PREFIX
	message_= prefix+formatMessage(code_);
#else
	message_= formatMessage(code_);
#endif
}
//---------------------------------------------------------------------------
const char * SocketException::what() const
{
  return message_.c_str();
}
//---------------------------------------------------------------------------
const std::string SocketException::message() const
{
  return message_;
}
//---------------------------------------------------------------------------
const std::string SocketException::systemMessage() const
{
	return Bicycle::formatMessage(code_);
}
//---------------------------------------------------------------------------
const ulong SocketException::code() const
{
  return code_;
}
//---------------------------------------------------------------------------

