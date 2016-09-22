//---------------------------------------------------------------------------
#include "Global.h"
//---------------------------------------------------------------------------
const std::string Bicycle::CRLF=std::string("\r\n");
const Bicycle::ulong Bicycle::DEFAULT_BUFF_SIZE= 10*1024*1024; // 10 MB
const Bicycle::ulong Bicycle::DEFAULT_TIMEOUT= INFINITE;
//---------------------------------------------------------------------------
std::string Bicycle::formatMessage(ulong code)
{
	LPSTR errorMsg = NULL;   // will be allocated and filled by FormatMessage
	FormatMessageA(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM, // use windows internal message table
				0,       // 0 since source is internal message table
				code,    // this is the error code
													// Could just as well have been an error code from generic
													// Windows errors from GetLastError()
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),       // auto-determine language to use
				(LPSTR)&errorMsg,
				0,       // min length for buffer
				0);

 return errorMsg;
}
//---------------------------------------------------------------------------
