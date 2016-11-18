#ifndef JoinH
#define JoinH
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
template<typename Container,typename Splitter>
typename Container::value_type
  join(const Container& container,const Splitter& splitter)
{
  typedef typename Container::value_type Element;

  Container::const_iterator first=  container.begin();
  Container::const_iterator last=   container.end();

  if(first==last)
    return Element();

  iterator_range< typename range_const_iterator<Splitter>::type >
  lit_range(as_literal(splitter));

  range_const_iterator<Splitter>::type sp_first= Bicycle::begin(lit_range);
  range_const_iterator<Splitter>::type sp_last=  Bicycle::end(lit_range);

  Element result= *first;
  for(++first; first!=last; ++first)
  {
    std::copy(sp_first,sp_last,std::back_inserter(result));
    std::copy(first->begin(),first->end(),std::back_inserter(result));
  }
  return result;
}
//----------------------------------------------------------------------
}
//----------------------------------------------------------------------
#endif
