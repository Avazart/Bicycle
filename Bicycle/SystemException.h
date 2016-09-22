#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef SystemExceptionH
#define SystemExceptionH
//---------------------------------------------------------------------------
#include "Global.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
class SystemException: public std::exception
{
	public:
	 explicit SystemException();
	 explicit SystemException( ulong errorCode,
														 const std::string& prefix= std::string());
	 explicit SystemException( const std::string& prefix);

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
