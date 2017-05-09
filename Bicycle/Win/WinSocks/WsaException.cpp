//---------------------------------------------------------------------------
#include "WsaException.h"
//---------------------------------------------------------------------------
#include <winsock2.h>
#include <windows.h>
//---------------------------------------------------------------------------
using namespace Bicycle;
//---------------------------------------------------------------------------
WsaException::WsaException()
{
  code_= WSAGetLastError();
  message_= formatMessage(code_);
}
//---------------------------------------------------------------------------
WsaException::WsaException(ulong errorCode)
  : code_(errorCode),
    message_(formatMessage(errorCode))
{
}
//---------------------------------------------------------------------------
const char * WsaException::what() const
{
  return message_.c_str();
}
//---------------------------------------------------------------------------
const std::string WsaException::message() const
{
  return message_;
}
//---------------------------------------------------------------------------
const ulong WsaException::code() const
{
  return code_;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
WsaTimeOutException::WsaTimeOutException()
  :WsaException(WSAETIMEDOUT)
{

}
//---------------------------------------------------------------------------
WsaTimeOutException::WsaTimeOutException(ulong errorCode)
  :WsaException(errorCode)
{

}
//---------------------------------------------------------------------------
