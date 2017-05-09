//---------------------------------------------------------------------------
#ifndef AsLiteralH
#define AsLiteralH
//---------------------------------------------------------------------------
#include <cwchar>
#include <cstring>

#include "IteratorRange.h"
#include "RangeIterator.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------  length() -------------------------------------------
inline std::size_t length(const char* s)
{
  return strlen(s);
}

inline std::size_t length(const wchar_t* s)
{
  return wcslen(s);
}
//----------------  bool is_char_ptr() --------------------------------------
template<class T>
inline long is_char_ptr(T /* r */)
{
  return 0L; // false
}

inline bool is_char_ptr(char*)
{
  return true;
}

inline bool is_char_ptr(const char*)
{
  return true;
}

inline bool is_char_ptr(wchar_t*)
{
  return true;
}

inline bool is_char_ptr(const wchar_t*)
{
  return true;
}
//--------------   make range ------------------------------------------
template<class T>
inline iterator_range<T*>
make_range(T* const r, bool)
{
  return iterator_range<T*>(r, r+ length(r));
}

template<class T>
inline iterator_range<typename range_iterator<T>::type >
make_range(T& r, long)
{
  return make_iterator_range(r);
}
//-------------  as_literal ------------------------------------------------
template<class Range>
inline iterator_range< typename range_iterator<Range>::type >
as_literal(Range& r)
{
  return make_range(r,is_char_ptr(r));
}

template<class Range>
inline iterator_range< typename range_iterator<const Range	>::type>
as_literal(const Range& r)
{
  return make_range(r,is_char_ptr(r));
}

template<class Char, std::size_t N>
inline iterator_range<Char*>
as_literal(Char(& arr)[N])
{
  return make_range(arr,is_char_ptr(arr));
}

template<class Char, std::size_t N>
inline iterator_range< const Char*>
as_literal(const Char(& arr)[N])
{
  return make_range(arr, is_char_ptr(arr));
}
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
