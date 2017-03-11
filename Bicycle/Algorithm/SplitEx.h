#ifndef SplitExH
#define SplitExH
//----------------------------------------------------------------------
#include <algorithm>

#include "Begin.h"
#include "End.h"

#include "RangeConstIterator.h"
#include "IteratorRange.h"

#include "Utils.h"
#include "SearchEx.h"
//----------------------------------------------------------------------
namespace Bicycle
{
//----------------------------------------------------------------------
template<typename OutT, typename InT, typename SplittersT>
void split_ex(OutT& out, const InT& in,
              const SplittersT& splitters,
              bool skip_empty_parts= false)
{
  typedef typename range_const_iterator<InT>::type iterator;
  iterator_range<iterator>  lit_range(as_literal(in));

  iterator first= Bicycle::begin(lit_range);
  iterator last=  Bicycle::end(lit_range);

  for( ;first!=last; )
  {
    search_result<iterator,typename range_const_iterator<SplittersT>::type >
        r= search_ex_2(first,last,splitters);

    if(!skip_empty_parts || first!=r.first)
      out.push_back(OutT::value_type(first,r.first));
    first= r.last;
  }
}
//----------------------------------------------------------------------
template<typename OutT, typename InT, typename SplittersT,typename BinaryPredicate>
void split_ex(OutT& out, const InT& in,
              const SplittersT& splitters,
              BinaryPredicate p, bool skip_empty_parts)
{
  typedef typename range_const_iterator<InT>::type in_iterator;
  iterator_range<in_iterator>  lit_range(as_literal(in));

  in_iterator first= Bicycle::begin(lit_range);
  in_iterator last=  Bicycle::end(lit_range);

  for( ;first!=last; )
  {
    search_result<in_iterator, typename range_const_iterator<SplittersT>::type >
        r= search_ex_2(first,last,splitters,p);

    if(!skip_empty_parts || first!=r.first)
      out.push_back(OutT::value_type(first,r.first));
    first= r.last;
  }
}
//----------------------------------------------------------------------
}
//----------------------------------------------------------------------
#endif

