//---------------------------------------------------------------------------
#ifndef EndH
#define EndH
//---------------------------------------------------------------------------
namespace Bicycle
{
// ---------------------------------------------------------------------------
//  end()
// ---------------------------------------------------------------------------
template<class C>
typename C::iterator end(C& c)
{
  return c.end();
}

template<class C>
typename C::const_iterator end(const C& c)
{
  return c.end();
}

template<typename A, std::size_t N>
inline const A* end(const A(& array)[N])
{
  return array+N;
}

template<typename A, std::size_t N>
inline A* end(A(& array)[N])
{
  return array+N;
}
// ---------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------
#endif
