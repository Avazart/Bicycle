#if defined(_MSC_VER)
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef UtilsH
#define UtilsH
//---------------------------------------------------------------------------
#include <locale>
#include <functional>
//---------------------------------------------------------------------------
namespace Bicycle
{
// ---------------------------------------------------------------------------
// is space
//---------------------------------------------------------------------------
template<typename T>
class is_space: public std::unary_function<T, bool>
{
public:
  is_space(const std::locale& loc)
    :loc_(loc)
  {
  }

  bool operator()(T c) const
  {
    return isspace(c,loc_);
  }

private:
  std::locale loc_;
};
// ---------------------------------------------------------------------------
//  value_type    container/c-array
// ---------------------------------------------------------------------------
template<typename T>
struct value_type
{
  typedef typename T::value_type type;
};
// ---------------------------------------------------------------------------
template<typename T>
struct value_type<T*>
{
  typedef T type;
};
// ---------------------------------------------------------------------------
template<typename T>
struct value_type<const T*>
{
  typedef T type;
};
// ---------------------------------------------------------------------------
template<typename T, std::size_t N>
struct value_type<T[N]>
{
  typedef T type;
};
//---------------------------------------------------------------------
template<typename CharT>
struct CaseInsensitiveCmp
{
   bool operator()(CharT c1,CharT c2) const
   {
      return toupper(c1)==toupper(c2);
   }
};
//---------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------
#endif
