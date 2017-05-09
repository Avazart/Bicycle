#ifdef _MSC_VER
  #pragma once
#endif
//----------------------------------------------------------
#ifndef LibraryH
#define LibraryH
//----------------------------------------------------------
#include "../Global.h"
#include "../SystemException.h"
#include "../NonCopyable.h"
//----------------------------------------------------------
namespace Bicycle
{
//----------------------------------------------------------
class Library: private NonCopyable
{
public:
  explicit Library(const std::wstring& modulePath);
  explicit Library(const std::string&  modulePath);

  ~Library();

  void load(const std::string &modulePath);
  void load(const std::wstring &modulePath);

  void free(bool throwException= true);

  bool isLoaded()const;

  template<typename A>
  A procAddress(const std::string& procName)const;

  template<typename A>
  bool tryGetProcAddress(const std::string& procName, A& address)const;

private:
  HMODULE module_;
};
//----------------------------------------------------------
template<typename A>
A Library::procAddress(const std::string& procName)const
{
  A address= reinterpret_cast<A>(GetProcAddress(module_, procName.c_str()));
  if(!address)
     throw SystemException("Library: \""+procName+"\" ");
  return address;
}
//---------------------------------------------------------------------
template<typename A>
bool Library::tryGetProcAddress(const std::string& procName, A& address)const
{
  address= reinterpret_cast<A>(GetProcAddress(module_, procName.c_str()));
  return address != 0;
}
//---------------------------------------------------------------------
} // Bicycle
//---------------------------------------------------------------------
#endif
