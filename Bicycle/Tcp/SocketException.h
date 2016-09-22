#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef SocketExceptionH
#define SocketExceptionH
//---------------------------------------------------------------------------
#include <string>
#include <stdexcept>

#include "Global.h"
// Класс для исключений
// для обработки ошибок WinSoks ( WSAGetLastError() )
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
class SocketException: public std::exception
{
	public:
	 explicit SocketException();
	 explicit SocketException( const ulong errorCode,
														 const std::string& prefix= std::string());
	 explicit SocketException( const std::string& prefix);

	 virtual const ulong code() const; // код ошибки
	 virtual const std::string systemMessage() const;
	 virtual const std::string message() const; // сообщение об ошибке (текст)
	 virtual const char *what() const;

	 private:
			std::string message_;
			ulong code_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
