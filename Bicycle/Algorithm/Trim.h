//---------------------------------------------------------------------------
#ifndef TrimH
#define TrimH

#include <algorithm>
#include <vector>
#include <locale>

#include "Utils.h"
#include "RangeConstIterator.h"
#include "RangeIterator.h"
#include "AsLiteral.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
// trim  end  select
//---------------------------------------------------------------------------
template<typename ForwardIteratorT, typename PredicateT>
inline ForwardIteratorT
trim_end_iter_select(ForwardIteratorT inBegin,	ForwardIteratorT inEnd,
                     PredicateT isSpace,
                     std::forward_iterator_tag)
{
  ForwardIteratorT trimIt= inBegin;
  for (ForwardIteratorT it= inBegin; it!= inEnd; ++it)
  {
    if (!isSpace(*it))
    {
      trimIt= it;
      ++trimIt;
    }
  }
  return trimIt;
}
//---------------------------------------------------------------------------
template<typename ForwardIteratorT, typename PredicateT>
inline ForwardIteratorT trim_end_iter_select(ForwardIteratorT inBegin,
                                             ForwardIteratorT inEnd, PredicateT isSpace,
                                             std::bidirectional_iterator_tag)
{
  for (ForwardIteratorT it= inEnd; it!= inBegin;)
  {
    if (!isSpace(*(--it)))
      return++it;
  }

  return inBegin;
}
//---------------------------------------------------------------------------
// trim begin
//---------------------------------------------------------------------------
template<typename ForwardIteratorT, typename PredicateT>
inline ForwardIteratorT
trim_begin(ForwardIteratorT inBegin, ForwardIteratorT inEnd,
           PredicateT isSpace )
{
  ForwardIteratorT it= inBegin;
  for(; it!= inEnd; ++it)
  {
    if (!isSpace(* it))
      return it;
  }

  return it;
}
//---------------------------------------------------------------------------
// trim  end
//---------------------------------------------------------------------------
template<typename ForwardIteratorT, typename PredicateT>
inline ForwardIteratorT trim_end(ForwardIteratorT inBegin,
                                 ForwardIteratorT inEnd, PredicateT isSpace)
{
  return trim_end_iter_select(inBegin, inEnd, isSpace,
                              std::forward_iterator_tag() );
}
//---------------------------------------------------------------------------
//   trim left
//---------------------------------------------------------------------------
template<typename OutputIteratorT, typename RangeT, typename PredicateT>
inline OutputIteratorT trim_left_copy_if(OutputIteratorT output,
                                         const RangeT& input, PredicateT isSpace)
{
  iterator_range< range_const_iterator<RangeT>::type >
      lit_range(as_literal(Input));

  std::copy(
        trim_begin(Bicycle::begin(lit_range),Bicycle::end(lit_range), isSpace),
        end(lit_range), output);

  return output;
}
//---------------------------------------------------------------------------
template<typename SequenceT, typename PredicateT>
inline SequenceT trim_left_copy_if(const SequenceT& input, PredicateT isSpace)
{
  return SequenceT(trim_begin(Bicycle::begin(input),Bicycle::end(input),isSpace),
                              Bicycle::end(input));
}
//---------------------------------------------------------------------------
template<typename SequenceT>
inline SequenceT trim_left_copy(const SequenceT& input,
                                const std::locale& loc=std::locale()	)
{
  return trim_left_copy_if(input,is_space<SequenceT::value_type>(loc));
}

//---------------------------------------------------------------------------
template<typename SequenceT, typename PredicateT>
inline void trim_left_if(SequenceT& input, PredicateT isSpace)
{
  input.erase(input.begin(),
              trim_begin( input.begin(), input.end(),isSpace));
}
//---------------------------------------------------------------------------
template<typename SequenceT>
inline void trim_left(SequenceT& input,
                      const std::locale& loc=std::locale())
{
  trim_left_if(input,is_space<SequenceT::value_type>(loc));
}
//---------------------------------------------------------------------------
// trim right
//---------------------------------------------------------------------------
template<typename OutputIteratorT, typename RangeT, typename PredicateT>
inline OutputIteratorT trim_right_copy_if(OutputIteratorT output,
                                          const RangeT& input,
                                          PredicateT isSpace)
{
  iterator_range< range_const_iterator<RangeT>::type >
      lit_range(as_literal(Input));

  std::copy(begin(lit_range),
            trim_end(Bicycle::begin(lit_range), Bicycle::end(lit_range), isSpace),
            output);

  return output;
}
//---------------------------------------------------------------------------
template<typename SequenceT, typename PredicateT>
inline SequenceT trim_right_copy_if(const SequenceT& input,
                                    PredicateT isSpace)
{
  return SequenceT(Bicycle::begin(input),
                   trim_end(Bicycle::begin(input), Bicycle::end(input),isSpace));
}
//---------------------------------------------------------------------------
template<typename SequenceT>
inline SequenceT trim_right_copy(const SequenceT& input,
                                 const std::locale& loc=std::locale())
{
  return trim_right_copy_if(input, is_space<SequenceT::value_type>(loc));
}
//---------------------------------------------------------------------------
template<typename SequenceT, typename PredicateT>
inline void trim_right_if(SequenceT& input, PredicateT isSpace)
{
  input.erase(
        trim_end(input.begin(),input.end(),isSpace),
        input.end()  );
}
//---------------------------------------------------------------------------
template<typename SequenceT>
inline void trim_right(SequenceT& input, const std::locale& loc=std::locale())
{
  trim_right_if(input,is_space<SequenceT::value_type>(loc));
}
//---------------------------------------------------------------------------
template<typename OutputIteratorT, typename RangeT, typename PredicateT>
inline OutputIteratorT
trim_copy_if(OutputIteratorT output,const RangeT& input, PredicateT isSpace)
{
  iterator_range<range_const_iterator<RangeT>::type>
      lit_range(as_literal(input));

  range_const_iterator<RangeT>::type
      trimEnd= trim_end(Bicycle::begin(lit_range),
                        Bicycle::end(lit_range),
                        isSpace);

  std::copy(trim_begin(Bicycle::begin(lit_range),trimEnd,isSpace),
            trimEnd,
            output);

  return output;
}
//---------------------------------------------------------------------------
template<typename SequenceT, typename PredicateT>
inline SequenceT trim_copy_if(const SequenceT& input, PredicateT isSpace)
{
  range_const_iterator<SequenceT>::type
      trimEnd= trim_end(Bicycle::begin(input),Bicycle::end(input), isSpace);

  return SequenceT(trim_begin(Bicycle::begin(input), trimEnd,	isSpace), trimEnd);
}
//---------------------------------------------------------------------------
template<typename SequenceT>
inline SequenceT trim_copy(const SequenceT& input, const std::locale& loc=std::locale())
{
  return trim_copy_if(input,is_space<SequenceT::value_type>(loc));
}
//---------------------------------------------------------------------------
// trim
//---------------------------------------------------------------------------
template<typename SequenceT, typename PredicateT>
inline void trim_if(SequenceT& input, PredicateT isSpace)
{
  trim_right_if(input, isSpace);
  trim_left_if(input, isSpace);
}
//---------------------------------------------------------------------------
template<typename SequenceT>
inline void trim(SequenceT& input, const std::locale& loc=std::locale())
{
  trim_if(input, is_space<SequenceT::value_type>(loc) );
}
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
