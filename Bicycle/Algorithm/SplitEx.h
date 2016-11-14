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
void split_ex(OutT& out, const InT& in,const SplittersT& splitters,
              bool skip_empty_parts= false)
{
  iterator_range< typename range_const_iterator<InT>::type >
      lit_range(as_literal(in));

  typename range_const_iterator<InT>::type first= Bicycle::begin(lit_range);
  typename range_const_iterator<InT>::type last=  Bicycle::end(lit_range);

  for( ;first!=last; )
  {
    search_result< 	typename range_const_iterator<InT>::type,
        typename range_const_iterator<SplittersT>::type >
        r= search_ex(first,last,splitters);

    if(!skip_empty_parts || first!=r.first)
      out.push_back(OutT::value_type(first,r.first));
    first= r.last;
  }
}
//----------------------------------------------------------------------
}
//----------------------------------------------------------------------
#endif

