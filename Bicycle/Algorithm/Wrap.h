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
// wrap
//-------------------------------------------------------------------------
template<typename C, typename W>
C wrap_copy(const C& c, const W& left,const W& right)
{
  typedef typename range_const_iterator<W>::type w_iterator;

  iterator_range<w_iterator>  lit_range_left(as_literal(left));
  w_iterator l_first= Bicycle::begin(lit_range_left);
  w_iterator l_last=  Bicycle::end(lit_range_left);

  iterator_range<w_iterator>  lit_range_right(as_literal(right));
  w_iterator r_first= Bicycle::begin(lit_range_right);
  w_iterator r_last=  Bicycle::end(lit_range_right);

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
 typedef typename range_const_iterator<W>::type w_iterator;

  iterator_range<w_iterator>  lit_range_left(as_literal(left));
  w_iterator l_first= Bicycle::begin(lit_range_left);
  w_iterator l_last=  Bicycle::end(lit_range_left);

  iterator_range<w_iterator> lit_range_right(as_literal(right));
  w_iterator r_first= Bicycle::begin(lit_range_right);
  w_iterator r_last=  Bicycle::end(lit_range_right);

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
//             is_wrapped
//-------------------------------------------------------------------------
template<typename C, typename W>
bool is_wrapped(C& c, const W& left,const W& right)
{
  return starts_with(c,left) && ends_with(c,right);
}
//-------------------------------------------------------------------------
template<typename C, typename W>
bool is_wrapped(C& c, const W& w)
{
  return is_wrapped(c,w,w);
}
//-------------------------------------------------------------------------
template<typename C, typename W, typename BinaryPredicate>
bool is_wrapped(C& c, const W& left,const W& right, BinaryPredicate p)
{
  return starts_with(c,left,p) && ends_with(c,right,p);
}
//-------------------------------------------------------------------------
template<typename C, typename W, typename BinaryPredicate>
bool is_wrapped(C& c, const W& w, BinaryPredicate p)
{
  return is_wrapped(c,w,w,p);
}
//-------------------------------------------------------------------------
template<typename C, typename W>
C unwrap_copy(const C& c, const W& left,const W& right)
{
  typedef typename C::const_iterator iterator;

  std::pair<bool,iterator> p1= starts_with_ex_2(c.begin(),c.end(),left);
  std::pair<bool,iterator> p2= ends_with_ex_2(c.begin(),c.end(),right);

  if(p1.first && p2.first)
     return C(p1.second,p2.second);
  return c;
}
//-------------------------------------------------------------------------
template<typename C, typename W, typename BinaryPredicate>
C unwrap_copy(const C& c, const W& left,const W& right, BinaryPredicate p)
{
  typedef typename C::const_iterator iterator;

  std::pair<bool,iterator> p1= starts_with_ex_2(c.begin(),c.end(),left,p);
  std::pair<bool,iterator> p2= ends_with_ex_2(c.begin(),c.end(),right,p);

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
template<typename C, typename W, typename BinaryPredicate>
C unwrap_copy(const C& c, const W& w, BinaryPredicate p)
{
  return unwrap_copy(c,w,w,p);
}
//-------------------------------------------------------------------------
//             unwrap
//-------------------------------------------------------------------------
template<typename C, typename W>
void unwrap(C& c, const W& left,const W& right)
{
	typedef typename C::iterator iterator;

  std::pair<bool,iterator> p1= starts_with_ex_2(c.begin(),c.end(),left);
  std::pair<bool,iterator> p2= ends_with_ex_2(c.begin(),c.end(),right);

  if(p1.first && p2.first)
  {
     c.erase(p2.second,c.end());
     c.erase(c.begin(),p1.second);
  }
}
//-------------------------------------------------------------------------
template<typename C, typename W, typename BinaryPredicate>
void unwrap(C& c, const W& left,const W& right, BinaryPredicate p)
{
  typedef typename C::iterator iterator;

  std::pair<bool,iterator> p1= starts_with_ex_2(c.begin(),c.end(),left,p);
  std::pair<bool,iterator> p2= ends_with_ex_2(c.begin(),c.end(),right,p);

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
template<typename C, typename W, typename BinaryPredicate>
void unwrap(C& c, const W& w)
{
  unwrap(c,w,w,p);
}
//-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
#endif
