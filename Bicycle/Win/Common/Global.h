#ifdef _MSC_VER
  #pragma once
#endif
// ---------------------------------------------------------------------------
#ifndef GlobalH
#define GlobalH
//---------------------------------------------------------------------------
#ifndef UNICODE
  #define UNICODE // WinApi  FinctionW()
#endif

#ifdef CRLF
  #undef CRLF // Conflict with Indy in C++Builder
#endif

#ifdef _MSC_VER
  #define WIN32_LEAN_AND_MEAN  // winsock2.h conflict with windows.h
  #define NOMINMAX // std::min and std::max conflict with windows.h macros
#endif
//---------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
namespace Bicycle
{
  typedef wchar_t tchar;
  typedef std::basic_string<tchar> tstring;
  typedef std::basic_ostream<tchar> tostream;

  typedef WORD  ushort;
	typedef DWORD ulong;
  typedef UINT  uint;
  typedef unsigned char uchar;

  typedef std::vector<tstring> Strings;

	extern const std::string CRLF; // "\r\n"
  extern const ulong DEFAULT_BUFF_SIZE; // 10 MB
  extern const ulong DEFAULT_TIMEOUT;   // INFINITE

  std::string  formatMessage(ulong code,const tstring& moduleName= tstring()); // error code description
  std::wstring formatMessageW(ulong code, const tstring &moduleName= tstring());

  tstring appModuleFileName();

  enum CodePage: uint
  {
    OEM=  CP_OEMCP/*= 866*/,
    Win1251= 1251,
    Utf8= CP_UTF8/*= 65001*/
	};
}
//---------------------------------------------------------------------------
#endif
