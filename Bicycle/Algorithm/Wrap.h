#ifndef WrapH
#define WrapH
//-------------------------------------------------------------------------
#include <algorithm>
#include <iterator>
#include <iostream>
//-------------------------------------------------------------------------
#include "IteratorRange.h"
#include "AsLiteral.h"
#include "RangeConstIterator.h"

#include "Begin.h"
#include "End.h"

#include "StartsWith.h"
#include "EndsWith.h"
//-------------------------------------------------------------------------
namespace Bicycle
{
//-------------------------------------------------------------------------
// Wrap 
//-------------------------------------------------------------------------
template<typename C, typename W>
C wrap_copy(const C& c, const W& left,const W& right)
{
  iterator_range< typename range_const_iterator<W>::type >
    lit_range_left(as_literal(left));

  range_const_iterator<W>::type l_first= Bicycle::begin(lit_range_left);
  range_const_iterator<W>::type l_last=  Bicycle::end(lit_range_left);

  iterator_range< typename range_const_iterator<W>::type >
    lit_range_right(as_literal(right));

  range_const_iterator<W>::type r_first= Bicycle::begin(lit_range_right);
  range_const_iterator<W>::type r_last=  Bicycle::end(lit_range_right);

  C out(c);
  std::copy(l_first,l_last,std::inserter(out,out.begin()));
  std::copy(r_first,r_last,std::back_inserter(out));
  return out;
}
//-------------------------------------------------------------------------
template<typename C, typename W>
C wrap_copy(const C& c, const W& w)
{
  return wrap_copy(c,w,w);
}
//-------------------------------------------------------------------------
template<typename C, typename W>
void wrap(C& c, const W& left,const W& right)
{
  iterator_range< typename range_const_iterator<W>::type >
    lit_range_left(as_literal(left));

  range_const_iterator<W>::type l_first= Bicycle::begin(lit_range_left);
  range_const_iterator<W>::type l_last=  Bicycle::end(lit_range_left);

  iterator_range< typename range_const_iterator<W>::type >
    lit_range_right(as_literal(right));

  range_const_iterator<W>::type r_first= Bicycle::begin(lit_range_right);
  range_const_iterator<W>::type r_last=  Bicycle::end(lit_range_right);

  std::copy(l_first,l_last,std::inserter(c,c.begin()));
  std::copy(r_first,r_last,std::back_inserter(c));
}
//-------------------------------------------------------------------------
template<typename C, typename W>
void wrap(C& c, const W& w)
{
  wrap(c,w,w);
}
//-------------------------------------------------------------------------
template<typename C, typename W>
C unwrap_copy(const C& c, const W& left,const W& right)
{
  typedef typename C::const_iterator iterator;

  std::pair<bool,iterator> p1= starts_with_ex(c.begin(),c.end(),left);
  std::pair<bool,iterator> p2= ends_with_ex(c.begin(),c.end(),right);

  if(p1.first && p2.first)
     return C(p1.second,p2.second);
  return c;
}
//-------------------------------------------------------------------------
template<typename C, typename W>
C unwrap_copy(const C& c, const W& w)
{
  return unwrap_copy(c,w,w);
}
//-------------------------------------------------------------------------
template<typename C, typename W>
void unwrap(C& c, const W& left,const W& right)
{
  typedef typename C::const_iterator iterator;

  std::pair<bool,iterator> p1= starts_with_ex(c.begin(),c.end(),left);
  std::pair<bool,iterator> p2= ends_with_ex(c.begin(),c.end(),right);

  if(p1.first && p2.first)
  {
     c.erase(p2.second,c.end());
     c.erase(c.begin(),p1.second);
  }
}
//-------------------------------------------------------------------------
template<typename C, typename W>
void unwrap(C& c, const W& w)
{
  unwrap(c,w,w);
}
//-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
#endif
