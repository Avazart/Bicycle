#ifndef SplitH
#define SplitH
//----------------------------------------------------------------------
#include <algorithm>
#include <iterator>

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
  typedef typename range_const_iterator<InT>::type in_iterator;
  iterator_range<in_iterator> lit_range(as_literal(in));

  in_iterator first= Bicycle::begin(lit_range);
  in_iterator last=  Bicycle::end(lit_range);
  in_iterator cur=   first;

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
} // Bicycle ::
//----------------------------------------------------------------------
#endif
