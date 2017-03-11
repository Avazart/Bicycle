#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef WinInetExceptionH
#define WinInetExceptionH
//---------------------------------------------------------------------------
#include "../Global.h"
// ---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
class WinInetException: public std::exception
{
public:
  explicit WinInetException();
  explicit WinInetException( ulong errorCode,
                            const std::string& prefix= std::string());
  explicit WinInetException( const std::string& prefix);

  virtual const ulong code() const;
  virtual const std::string systemMessage() const;
  virtual const std::string message() const;
  virtual const char *what() const;

  static void check(ulong errorCode);

private:
  std::string message_;
  ulong code_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
