//---------------------------------------------------------------------------
#include "Exception.h"
//---------------------------------------------------------------------------
using namespace Bicycle;
//---------------------------------------------------------------------------
//                       CancelException
//---------------------------------------------------------------------------
CancelException::CancelException()
{

}
//---------------------------------------------------------------------------
const std::string CancelException::message() const
{
  return "Операция отменена.";
}
//---------------------------------------------------------------------------
//                       SystemException
//---------------------------------------------------------------------------
	SystemException::SystemException()
   :Exception()
{
   code_= GetLastError();
}
//---------------------------------------------------------------------------
SystemException::SystemException(ulong errorCode)
  : code_(errorCode)
{
}
//---------------------------------------------------------------------------
const std::string SystemException::message() const
{
  return formatMessage(code_);
}
//---------------------------------------------------------------------------
const ulong SystemException::code() const
{
	return code_;
}
//---------------------------------------------------------------------------
//                       WaitTimeOutException
//---------------------------------------------------------------------------
WaitTimeOutException::WaitTimeOutException()
  :SystemException(WAIT_TIMEOUT)
{
}
//---------------------------------------------------------------------------
WaitTimeOutException::WaitTimeOutException(ulong errorCode)
  :SystemException(errorCode)
{
}
//---------------------------------------------------------------------------
//                          EOFException
//---------------------------------------------------------------------------
EOFException::EOFException()
  :SystemException(ERROR_HANDLE_EOF)
{

}
//---------------------------------------------------------------------------
EOFException::EOFException(ulong errorCode)
  :SystemException(errorCode)
{

}
//---------------------------------------------------------------------------
