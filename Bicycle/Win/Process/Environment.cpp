#include "Environment.h"
//---------------------------------------------------------------------
#include <algorithm>
#include "Algorithm/Mismatch.h"
//---------------------------------------------------------------------
using namespace Bicycle;
//---------------------------------------------------------------------
template<typename CharT>
struct CaseInsensitiveCmp
{
   bool operator()(CharT c1,CharT c2) const
   {
      return toupper(c1)==toupper(c2);
   }
};
//---------------------------------------------------------------------
template<typename StringT>
struct ContainsKey
{
  ContainsKey(const StringT& keyName)
    :keyName_(keyName)
  {
  }

  bool operator()(const StringT& line) const
  {
   std::pair<StringT::const_iterator,StringT::const_iterator> p=
   // C++14 std::mismatch
       Bicycle::mismatch( line.begin(), line.end(),
                          keyName_.begin(), keyName_.end(),
                          CaseInsensitiveCmp<typename StringT::value_type>() );

    return p.second==keyName_.end() && p.first!=line.end() && *p.first==TEXT('=');
  }

  private:
    StringT keyName_;
};
//---------------------------------------------------------------------
tstring ProcessEnvironment::variable(const tstring &name)
{
  tstring value(4096,0);

  ulong size = GetEnvironmentVariable(name.c_str(),&value[0],value.size());
  if(size && size>value.size())
  {
    value.resize(size);
    size = GetEnvironmentVariable(name.c_str(),&value[0],value.size());
  }

  if(size==0)
  {
    ulong errorCode= GetLastError();
    if(errorCode= ERROR_ENVVAR_NOT_FOUND)
    {
      return tstring();
    }
    throw SystemException(errorCode);
  }
  value.resize(size);
  return value;
}
//---------------------------------------------------------------------
void ProcessEnvironment::setVariable(const tstring &name, const tstring& value)
{
  if(!SetEnvironmentVariable(name.c_str(),value.c_str()))
  {
    throw SystemException();
  }
}
//---------------------------------------------------------------------
Strings ProcessEnvironment::strings()
{
  LPTCH lpvEnv= GetEnvironmentStrings();
  if(!lpvEnv)
  {
    throw SystemException();
  }

  LPTSTR lpszVariable= (LPTSTR)lpvEnv;
  Strings strings_;

  while(*lpszVariable)
  {
    strings_.push_back(lpszVariable);
    lpszVariable += lstrlen(lpszVariable) + 1;
  }

  FreeEnvironmentStrings(lpvEnv);
  return strings_;
}
//---------------------------------------------------------------------
//  Environment
//---------------------------------------------------------------------
Environment::Environment()
{
}
//---------------------------------------------------------------------
Environment::Environment(const Strings &strings)
  :strings_(strings)
{
}
//---------------------------------------------------------------------
bool Environment::empty() const
{
  return strings_.empty();
}
//---------------------------------------------------------------------
std::size_t Environment::indexOfName(const tstring& name) const
{
 Strings::const_iterator i=
     std::find_if(strings_.begin(),strings_.end(),ContainsKey<tstring>(name));

  return i==strings_.end()
         ? npos
         : std::distance(strings_.begin(),i);
}
//---------------------------------------------------------------------
bool Environment::exists(const tstring &name) const
{
  return indexOfName(name)!=npos;
}
//---------------------------------------------------------------------
void Environment::append(const tstring &line)
{
  strings_.push_back(line);
}
//---------------------------------------------------------------------
void Environment::appendVariable(const tstring &name, const tstring &value)
{
  strings_.push_back(name+TEXT("=")+value);
}
//---------------------------------------------------------------------
void Environment::insertVariable(std::size_t lineIndex,
                                 const tstring &name,
                                 const tstring &value)
{
  strings_.insert(strings_.begin()+lineIndex, name+TEXT("=")+value);
}
//---------------------------------------------------------------------
void Environment::remove(std::size_t lineIndex)
{
  strings_.erase(strings_.begin()+lineIndex);
}
//---------------------------------------------------------------------
void Environment::removeVariable(const tstring &name)
{
  std::size_t index = indexOfName(name);
  if(index != npos)
    remove(index);
}
//---------------------------------------------------------------------
tstring Environment::variable(const tstring &name) const
{
  std::size_t index = indexOfName(name);
  if(index!=npos)
    return strings_[index].substr(name.size()+1);
  return tstring();
}
//---------------------------------------------------------------------
void Environment::setVariable(std::size_t rowIndex, const tstring &value)
{
  std::size_t del_pos = strings_[rowIndex].find(TEXT("="));
  if(del_pos!=tstring::npos)
  {
    strings_[rowIndex].erase(del_pos+1,strings_[rowIndex].size()-del_pos-1);
    strings_[rowIndex].append(value);
  }
  else
  {
    strings_[rowIndex].append(TEXT("=")+value);
  }
}
//---------------------------------------------------------------------
void Environment::setVariable(const tstring &name, const tstring &value)
{
  std::size_t index = indexOfName(name);
  if(index!=npos)
  {
    strings_[index].erase(name.size()+1,strings_[index].size()-name.size()-1);
    strings_[index].append(value);
  }
  else
    appendVariable(name,value);
}
//---------------------------------------------------------------------
const Strings &Environment::strings() const
{
  return strings_;
}
//---------------------------------------------------------------------
void Environment::setStrings(const Strings &strings)
{
  strings_= strings;
}
//---------------------------------------------------------------------
void Environment::clear()
{
  strings_.clear();
}
//---------------------------------------------------------------------
tstring Environment::toEnvironmentString() const
{
  tstring str;

  for(std::size_t i=0; i<strings_.size(); ++i)
    str.append(strings_[i]+TEXT('\0'));

  return str;
}
//---------------------------------------------------------------------
//          ProcessEnvironment
//---------------------------------------------------------------------
Environment ProcessEnvironment::environment()
{
  return Environment(ProcessEnvironment::strings());
}
//---------------------------------------------------------------------
