#ifndef EndsWithH
#define EndsWithH
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
// Ends With
//----------------------------------------------------------------------
template<class InputIt1, class InputIt2>
  bool ends_with(InputIt1 first1, InputIt1 last1,
                 InputIt2 first2, InputIt2 last2)
{
  typedef std::reverse_iterator<InputIt1> RIter1;
  typedef std::reverse_iterator<InputIt2> RIter2;

  return Bicycle::mismatch(RIter1(last1),RIter1(first1),
                           RIter2(last2),RIter2(first2)).second==RIter2(first2);
}
//----------------------------------------------------------------------
  template<class InputIt1, class InputIt2, class BinaryPredicate>
    bool ends_with(InputIt1 first1, InputIt1 last1,
                   InputIt2 first2, InputIt2 last2, BinaryPredicate p)
{
   typedef std::reverse_iterator<InputIt1> RIter1;
   typedef std::reverse_iterator<InputIt2> RIter2;

   return Bicycle::mismatch(RIter1(last1),RIter1(first1),
                            RIter2(last2),RIter2(first2), p).second==RIter2(first2);
}
//----------------------------------------------------------------------
template<class C1, class C2>
bool ends_with(const C1& c1,const C2& c2)
{
  iterator_range<range_const_iterator<C1>::type>  lit_range1(as_literal(c1));
  iterator_range<range_const_iterator<C2>::type>  lit_range2(as_literal(c2));

  return ends_with( Bicycle::begin(lit_range1),  Bicycle::end(lit_range1),
                    Bicycle::begin(lit_range2),  Bicycle::end(lit_range2) );
}
//----------------------------------------------------------------------
template<class C1, class C2, class BinaryPredicate>
bool ends_with(const C1& c1,const C2& c2, BinaryPredicate p)
{
  iterator_range<range_const_iterator<C1>::type>  lit_range1(as_literal(c1));
  iterator_range<range_const_iterator<C2>::type>  lit_range2(as_literal(c2));

  return ends_with( Bicycle::begin(lit_range1),  Bicycle::end(lit_range1),
                    Bicycle::begin(lit_range2),  Bicycle::end(lit_range2), p);
}
//----------------------------------------------------------------------
// Ends With Ex
//----------------------------------------------------------------------
template<class InputIt1, class InputIt2>
std::pair<bool,InputIt1>
  ends_with_ex(InputIt1 first1, InputIt1 last1,
               InputIt2 first2, InputIt2 last2)
{
  typedef std::reverse_iterator<InputIt1> RIter1;
  typedef std::reverse_iterator<InputIt2> RIter2;

  std::pair<RIter1,RIter2> p=
     Bicycle::mismatch(RIter1(last1),RIter1(first1),
                       RIter2(last2),RIter2(first2));

  return std::make_pair(p.second==RIter2(first2),p.first.base());
}
//----------------------------------------------------------------------
template<class InputIt1, class InputIt2, class BinaryPredicate>
std::pair<bool,InputIt1>
  ends_with_ex(InputIt1 first1, InputIt1 last1,
               InputIt2 first2, InputIt2 last2, BinaryPredicate p)
{
  typedef std::reverse_iterator<InputIt1> RIter1;
  typedef std::reverse_iterator<InputIt2> RIter2;

  std::pair<RIter1,RIter2> p=
     Bicycle::mismatch(RIter1(last1),RIter1(first1),
                       RIter2(last2),RIter2(first2), p);

  return std::make_pair(p.second==RIter2(first2),p.first.base());
}
//----------------------------------------------------------------------
template<class C1, class C2>
std::pair<bool, typename range_const_iterator<C1>::type >
  ends_with_ex(const C1& c1,const C2& c2)
{
    iterator_range<range_const_iterator<C1>::type >
        lit_range1(as_literal(c1));

    iterator_range<range_const_iterator<C2>::type >
        lit_range2(as_literal(c2));

    return ends_with_ex( Bicycle::begin(lit_range1),  Bicycle::end(lit_range1),
                         Bicycle::begin(lit_range2),  Bicycle::end(lit_range2) );
}
//----------------------------------------------------------------------
template<class C1, class C2, class BinaryPredicate>
std::pair<bool, typename range_const_iterator<C1>::type >
  ends_with_ex(const C1& c1,const C2& c2, BinaryPredicate p)
{
    iterator_range<range_const_iterator<C1>::type >
        lit_range1(as_literal(c1));

    iterator_range<range_const_iterator<C2>::type >
        lit_range2(as_literal(c2));

    return ends_with_ex( Bicycle::begin(lit_range1),  Bicycle::end(lit_range1),
                         Bicycle::begin(lit_range2),  Bicycle::end(lit_range2),
                         p);
}
//----------------------------------------------------------------------
template<class InputIt, class C>
  std::pair<bool,InputIt>
    ends_with_ex_2(InputIt first, InputIt last, const C& c)
{
  iterator_range<range_const_iterator<C>::type >
      lit_range(as_literal(c));

  return ends_with_ex(first, last,
                      Bicycle::begin(lit_range), Bicycle::end(lit_range));
}
//----------------------------------------------------------------------
template<class InputIt, class C, class BinaryPredicate>
   std::pair<bool,InputIt>
     ends_with_ex_2(InputIt first, InputIt last, const C& c,BinaryPredicate p)
{
    iterator_range<range_const_iterator<C>::type >
        lit_range(as_literal(c));

    return ends_with_ex(first, last,
                        Bicycle::begin(lit_range), Bicycle::end(lit_range),
                        p);
}
//----------------------------------------------------------------------
}
//----------------------------------------------------------------------
#endif

