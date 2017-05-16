#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef ExceptionH
#define ExceptionH
//---------------------------------------------------------------------------
#include "Global.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
class Exception
{
public:
    virtual const std::string message() const=0;
    virtual ~Exception(){}
};
//---------------------------------------------------------------------------
class CancelException: public Exception
{
public:
  explicit CancelException();
  virtual const std::string message() const;
};
//---------------------------------------------------------------------------
class SystemException: public Exception
{
public:
  SystemException();
  explicit SystemException(ulong errorCode);

  virtual const ulong code() const;
  virtual const std::string message() const;

private:
  ulong code_;
};
//---------------------------------------------------------------------------
class WaitTimeOutException: public SystemException
{
 public:
    WaitTimeOutException();
    explicit WaitTimeOutException(ulong errorCode);
};
// ---------------------------------------------------------------------------
class EOFException: public SystemException
{
  public:
    EOFException();
    explicit EOFException(ulong errorCode);
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
