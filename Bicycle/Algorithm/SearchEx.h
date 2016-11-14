#ifndef Split2H
#define Split2H
//----------------------------------------------------------------------
#include <algorithm>

#include "Begin.h"
#include "End.h"

#include "Mismatch.h"

#include "RangeConstIterator.h"
#include "IteratorRange.h"
#include "AsLiteral.h"

#include "Utils.h"
#include "StartsWith.h"
//----------------------------------------------------------------------
namespace Bicycle
{
//----------------------------------------------------------------------
template<typename SourseT, typename TargetT>  // std::tuple ??
struct search_result
{
  SourseT first;
  SourseT last;
  TargetT found;

  search_result(SourseT first_,SourseT last_,TargetT found_)
    : first(first_),
      last(last_),
      found(found_)
  {}
};
//----------------------------------------------------------------------
template<typename X, typename Y>
  search_result<X,Y>
    make_search_result(X first,X last,Y found)
{
  return search_result<X,Y>(first,last,found);
}
//----------------------------------------------------------------------
template<typename InputIt1, typename InputIt2>
  search_result<InputIt1, InputIt2>
    search_ex(InputIt1 first1, InputIt1 last1,
           InputIt2 first2, InputIt2 last2)
{
  for(; first1!=last1; ++first1)
  {
    for(InputIt2 cur= first2; cur!=last2; ++cur)
    {
      std::pair<bool,InputIt1> p=
          starts_with_ex(first1,last1,*cur);
      if(p.first)
        return make_search_result(first1,p.second,cur);
    }
  }
  return make_search_result(first1,last1,last2);
}
//----------------------------------------------------------------------
template<typename InputIt, typename C>
  search_result< InputIt, typename range_const_iterator<C>::type>
    search_ex(InputIt first, InputIt last,const C& c)
{
  iterator_range< typename range_const_iterator<C>::type >
      lit_range(as_literal(c));

  return
      search_ex< InputIt, typename range_const_iterator<C>::type >
      ( first,last,	Bicycle::begin(lit_range),Bicycle::end(lit_range));
}
//----------------------------------------------------------------------
template<typename C1, typename C2>
   search_result< typename range_const_iterator<C1>::type ,
                  typename range_const_iterator<C2>::type >
     search_ex(const C1& c1,const C2& c2)
{
  iterator_range< typename range_const_iterator<C1>::type >
      lit_range1(as_literal(c1));

  iterator_range< typename range_const_iterator<C2>::type >
      lit_range2(as_literal(c2));

  return
      search_ex< typename range_const_iterator<C1>::type,
      typename range_const_iterator<C2>::type >
      ( Bicycle::begin(lit_range1),Bicycle::end(lit_range1),
        Bicycle::begin(lit_range2),Bicycle::end(lit_range2) );
}
//----------------------------------------------------------------------
}
//----------------------------------------------------------------------
#endif

