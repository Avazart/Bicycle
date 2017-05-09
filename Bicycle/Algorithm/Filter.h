#ifndef FilterH
#define FilterH
//-------------------------------------------------------------------------
#include <algorithm>
#include <iterator>
//-------------------------------------------------------------------------
#include "IteratorRange.h"
#include "AsLiteral.h"
#include "RangeConstIterator.h"

#include "Begin.h"
#include "End.h"
//-------------------------------------------------------------------------
namespace Bicycle
{
//-------------------------------------------------------------------------
// filter
//-------------------------------------------------------------------------
template<typename SequenceT, typename UnaryPredicate>
SequenceT filter(const SequenceT& in, UnaryPredicate p)
{
  typedef typename range_const_iterator<SequenceT>::type in_iterator;

  iterator_range<in_iterator> lit_range(as_literal(in));
  in_iterator first= Bicycle::begin(lit_range);
  in_iterator last=  Bicycle::end(lit_range);
  
  SequenceT out;
  std::copy_if(first,last,std::back_inserter(out),p);
  return out;
}
//-------------------------------------------------------------------------
// apply
//-------------------------------------------------------------------------
template<typename InSequenceT, typename OutSequenceT, typename UnaryOperation>
void apply(const InSequenceT& in,OutSequenceT& out, UnaryOperation unary_op)
{
  typedef typename range_const_iterator<InSequenceT>::type in_iterator;

  iterator_range<in_iterator> lit_range(as_literal(in));
  in_iterator first= Bicycle::begin(lit_range);
  in_iterator last=  Bicycle::end(lit_range);
  
  std::transform(first,last,std::back_inserter(out),unary_op);
}
//-------------------------------------------------------------------------
template<typename SequenceT, typename UnaryOperation>
SequenceT apply(const SequenceT& in, UnaryOperation unary_op)
{
  typedef typename range_const_iterator<SequenceT>::type in_iterator;

  iterator_range<in_iterator> lit_range(as_literal(in));
  in_iterator first= Bicycle::begin(lit_range);
  in_iterator last=  Bicycle::end(lit_range);
  
  SequenceT out;
  std::transform(first,last,std::back_inserter(out),unary_op);
  return out;
}
//-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
#endif
