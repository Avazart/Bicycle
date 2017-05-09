//---------------------------------------------------------------------------
#ifndef BeginH
#define BeginH
//---------------------------------------------------------------------------
namespace Bicycle
{
// ---------------------------------------------------------------------------
//  begin()
// ---------------------------------------------------------------------------
template<class C>
typename C::iterator begin(C& c)
{
  return c.begin();
}

template<class C>
typename C::const_iterator begin(const C& c)
{
  return c.begin();
}

template<typename A, std::size_t N>
inline const A* begin(const A(& array)[N])
{
  return array;
}

template<typename A, std::size_t N>
inline A* begin(A(& array)[N])
{
  return array;
}
// ---------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------
#endif
