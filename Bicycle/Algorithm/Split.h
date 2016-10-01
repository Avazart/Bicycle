#ifndef SplitH
#define SplitH
//----------------------------------------------------------------------
#include <algorithm>

#include "IteratorRange.h"
#include "AsLiteral.h"
#include "RangeConstIterator.h"

#include "Begin.h"
#include "End.h"
//----------------------------------------------------------------------
namespace Bicycle
{
//----------------------------------------------------------------------
template<typename OutT, typename InT, typename PredicateT>
void split(OutT& out, const InT& in,
           PredicateT IsSplitter,
           bool skip_empty_parts= false)
{
  iterator_range< typename range_const_iterator<InT>::type >
      lit_range(as_literal(in));

  range_const_iterator<InT>::type first= Bicycle::begin(lit_range);
  range_const_iterator<InT>::type last=  Bicycle::end(lit_range);
  range_const_iterator<InT>::type cur=   first;

  while(cur != last)
  {
    if(IsSplitter(*cur))
    {
      if(!skip_empty_parts || first!= cur)
        out.push_back(OutT::value_type(first,cur));

      first= ++cur;
    }
    else
      ++cur;
  }
  if(!skip_empty_parts || first!= cur)
    out.push_back(OutT::value_type(first,cur));
}
//----------------------------------------------------------------------
}
//----------------------------------------------------------------------
#endif
