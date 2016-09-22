//---------------------------------------------------------------------------
#include "SystemException.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#define USE_ERROR_PREFIX
using namespace Bicycle;
//---------------------------------------------------------------------------
	SystemException::SystemException()
	 :std::exception()
{
	 code_= GetLastError();
	 message_= formatMessage(code_);
}
//---------------------------------------------------------------------------
SystemException::SystemException( ulong errorCode,
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
SystemException::SystemException(const std::string& prefix)
{
	code_= GetLastError();
	#ifdef USE_ERROR_PREFIX
		 message_= prefix+formatMessage(code_);
	#else
		 message_= formatMessage(code_);
	#endif
}
//---------------------------------------------------------------------------
const char * SystemException::what() const
{
	return message_.c_str();
}
//---------------------------------------------------------------------------
const std::string SystemException::message() const
{
	return message_;
}
//---------------------------------------------------------------------------
const std::string SystemException::systemMessage() const
{
	return formatMessage(code_);
}
//---------------------------------------------------------------------------
const ulong SystemException::code() const
{
	return code_;
}
//---------------------------------------------------------------------------
void SystemException::check(ulong errorCode)
{
	if(errorCode!=0)
		throw SystemException(errorCode);
}
//---------------------------------------------------------------------------
