//---------------------------------------------------------------------------
#include "Encoding.h"
//---------------------------------------------------------------------------
static Bicycle::Strings codePages_;
//---------------------------------------------------------------------------
BOOL CALLBACK enumCodePages(LPTSTR lpCodePageString)
{
  codePages_.push_back(lpCodePageString);
  return TRUE;
}
//---------------------------------------------------------------------------
Bicycle::Strings Bicycle::systemCodePages(ulong flags)
{
  codePages_.clear();
  EnumSystemCodePages(&enumCodePages,flags);
  return codePages_;
}
//---------------------------------------------------------------------------
std::string Bicycle::encode(const std::string& in,
                       uint sourceCp,
                       uint targetCp)
{
  ulong length1 = MultiByteToWideChar(sourceCp, 0, in.c_str(), in.length(),
                                      NULL,       0);
  std::wstring buf(length1,L'\0');
  MultiByteToWideChar(sourceCp, 0, in.c_str(), in.length(),
                      const_cast<wchar_t*>(buf.data()), length1);

  ulong length2 = WideCharToMultiByte(targetCp, 0,
                                      buf.c_str(), buf.length(),
                                      NULL,       0,
                                      NULL, NULL);
  std::string out(length2,'\0');
  WideCharToMultiByte(targetCp, 0,
                      buf.data(), buf.length(),
                      const_cast<char*>(out.data()), length2, NULL, NULL);
  return out;
}
//---------------------------------------------------------------------------
//   866 - OEM
//   1251 - Windows cp1251
//   CP_UTF8 - UTF8
//---------------------------------------------------------------------------
std::string Bicycle::fromOEM(const std::string& in)
{
  return encode(in,866,1251);
}
//---------------------------------------------------------------------------
std::string Bicycle::fromUTF8(const std::string& in)
{
  return encode(in,CP_UTF8,1251);
}
//---------------------------------------------------------------------------

