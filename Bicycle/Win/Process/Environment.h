#ifdef _MSC_VER
	#pragma once
#endif
//---------------------------------------------------------------------------
#ifndef EnvironmentH
#define EnvironmentH
// ---------------------------------------------------------------------------
#include "../Common/Global.h"
#include "../Common/Exception.h"
#include <vector>
// ---------------------------------------------------------------------------
namespace Bicycle
{
// ---------------------------------------------------------------------------
class Environment
{
public:
enum : std::size_t
   { npos= (std::size_t)-1 };

  Environment();
  explicit Environment(const Strings& strings);

  bool empty() const;

  std::size_t indexOfName(const tstring& name) const;
  bool exists(const tstring& name)const;

  tstring variable(const tstring& name)const;
  void setVariable(std::size_t index,const tstring& value);
  void setVariable(const tstring& name,const tstring& value);

  void remove(std::size_t lineIndex);
  void removeVariable(const tstring& name);

  void append(const tstring& line);
  void appendVariable(const tstring& name,const tstring& value);

  void insertVariable(std::size_t lineIndex,
                      const tstring& name,
                      const tstring& value);

  const Strings& strings()const;
  void  setStrings(const Strings& strings);
  void clear();

  tstring toEnvironmentString()const;

private:
  Strings strings_;
};
// ---------------------------------------------------------------------------
namespace ProcessEnvironment
{
  tstring variable(const tstring& name);
  void setVariable(const tstring& name,const tstring& value);
  Strings strings();

  Environment environment();
}
// ---------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------
#endif // Environment
