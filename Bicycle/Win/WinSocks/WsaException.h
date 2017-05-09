#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef WsaExceptionH
#define WsaExceptionH
//---------------------------------------------------------------------------
#include <string>
#include <stdexcept>

#include "Win/Common/Global.h"
#include "Win/Common/Exception.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
// Класс для исключений
// для обработки ошибок WinSoks ( WSAGetLastError() )
//---------------------------------------------------------------------------
class WsaException: public Exception
{
public:
  WsaException();
  explicit WsaException(ulong errorCode);

  virtual const ulong code() const;
  virtual const std::string message() const;

  virtual const char *what() const;

private:
  std::string message_;
  ulong code_;
};
//---------------------------------------------------------------------------
class WsaTimeOutException: public WsaException
{
  public:
     WsaTimeOutException();
     explicit WsaTimeOutException(ulong errorCode);
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
