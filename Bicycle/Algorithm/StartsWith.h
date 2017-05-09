#ifndef StartsWithH
#define StartsWithH
//----------------------------------------------------------------------
#include <algorithm>

#include "Begin.h"
#include "End.h"

#include "Mismatch.h"

#include "RangeConstIterator.h"
#include "IteratorRange.h"
#include "AsLiteral.h"

#include "Utils.h"
//----------------------------------------------------------------------
namespace Bicycle
{
//----------------------------------------------------------------------
// Starts With
//----------------------------------------------------------------------
template<class InputIt1, class InputIt2>
bool starts_with(InputIt1 first1, InputIt1 last1,
                 InputIt2 first2, InputIt2 last2)
{
  return Bicycle::mismatch(first1,last1,first2,last2).second==last2;
}
//----------------------------------------------------------------------
template< class InputIt1, class InputIt2, class BinaryPredicate >
bool starts_with(InputIt1 first1, InputIt1 last1,
                 InputIt2 first2, InputIt2 last2, BinaryPredicate p)
{
  return Bicycle::mismatch(first1,last1,first2,last2,p).second==last2;
}
//----------------------------------------------------------------------
template<class C1, class C2>
bool starts_with(const C1& c1,const C2& c2)
{
  iterator_range<range_const_iterator<C1>::type> lit_range1(as_literal(c1));
  iterator_range<range_const_iterator<C2>::type> lit_range2(as_literal(c2));

  return starts_with( Bicycle::begin(lit_range1), Bicycle::end(lit_range1),
                      Bicycle::begin(lit_range2), Bicycle::end(lit_range2) );
}
 //----------------------------------------------------------------------
template<class C1, class C2, class BinaryPredicate>
 bool starts_with(const C1& c1,const C2& c2,BinaryPredicate p)
{
   iterator_range<range_const_iterator<C1>::type> lit_range1(as_literal(c1));
   iterator_range<range_const_iterator<C2>::type> lit_range2(as_literal(c2));

   return starts_with( Bicycle::begin(lit_range1), Bicycle::end(lit_range1),
                       Bicycle::begin(lit_range2), Bicycle::end(lit_range2),
                       p);
}
//----------------------------------------------------------------------
// Starts With Ex
//----------------------------------------------------------------------
template<class InputIt1, class InputIt2>
  std::pair<bool,InputIt1>
    starts_with_ex(InputIt1 first1, InputIt1 last1,
                   InputIt2 first2, InputIt2 last2)
{
  std::pair<InputIt1,InputIt2>
      p= Bicycle::mismatch(first1,last1,first2,last2);
  return std::make_pair(p.second==last2,p.first);
}
  //----------------------------------------------------------------------
template< class InputIt1, class InputIt2, class BinaryPredicate >
    std::pair<bool,InputIt1>
      starts_with_ex(InputIt1 first1, InputIt1 last1,
                     InputIt2 first2, InputIt2 last2,
                     BinaryPredicate p)
 {
   std::pair<InputIt1,InputIt2>
        p= Bicycle::mismatch(first1,last1,first2,last2, p);
   return std::make_pair(p.second==last2,p.first);
 }
//----------------------------------------------------------------------
template<class C1, class C2>
  std::pair<bool, typename range_const_iterator<C1>::type >
    starts_with_ex(const C1& c1,const C2& c2)
{
  iterator_range<range_const_iterator<C1>::type> lit_range1(as_literal(c1));
  iterator_range<range_const_iterator<C2>::type> lit_range2(as_literal(c2));

  return starts_with_ex( Bicycle::begin(lit_range1), Bicycle::end(lit_range1),
                         Bicycle::begin(lit_range2), Bicycle::end(lit_range2) );
}
//----------------------------------------------------------------------
template<class C1, class C2, class BinaryPredicate>
    std::pair<bool, typename range_const_iterator<C1>::type >
      starts_with_ex(const C1& c1,const C2& c2,BinaryPredicate p)
{
  iterator_range<range_const_iterator<C1>::type> lit_range1(as_literal(c1));
  iterator_range<range_const_iterator<C2>::type> lit_range2(as_literal(c2));

   return starts_with_ex( Bicycle::begin(lit_range1),  Bicycle::end(lit_range1),
                          Bicycle::begin(lit_range2),  Bicycle::end(lit_range2),
                          p );
}
//----------------------------------------------------------------------
template<class InputIt, class C>
  std::pair<bool,InputIt>
    starts_with_ex_2(InputIt first, InputIt last, const C& c)
{
  iterator_range<range_const_iterator<C>::type> lit_range(as_literal(c));

  return starts_with_ex( first, last,
                      Bicycle::begin(lit_range), Bicycle::end(lit_range));
}
//----------------------------------------------------------------------
template<class InputIt, class C,class BinaryPredicate>
   std::pair<bool,InputIt>
     starts_with_ex_2(InputIt first, InputIt last, const C& c, BinaryPredicate p)
{
    iterator_range<range_const_iterator<C>::type> lit_range(as_literal(c));

    return starts_with_ex( first, last,
                           Bicycle::begin(lit_range), Bicycle::end(lit_range),
                           p);
}
//----------------------------------------------------------------------
}
//----------------------------------------------------------------------
#endif

