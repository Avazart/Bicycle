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
// Wrap copy_if
//-------------------------------------------------------------------------
template<typename SequenceT, typename UnaryPredicate>
SequenceT filter(const SequenceT& in, UnaryPredicate p)
{
  iterator_range< typename range_const_iterator<SequenceT>::type >
  lit_range(as_literal(in));

  range_const_iterator<SequenceT>::type first= Bicycle::begin(lit_range);
  range_const_iterator<SequenceT>::type last=  Bicycle::end(lit_range);
  
  SequenceT out;
  std::copy_if(first,last,std::back_inserter(out),p);
  return out;
}
//-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
#endif
