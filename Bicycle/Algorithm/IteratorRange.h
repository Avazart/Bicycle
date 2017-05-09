// ---------------------------------------------------------------------------
#ifndef IteratorRangeH
#define IteratorRangeH
// ---------------------------------------------------------------------------
#include "IteratorRange.h"
#include "RangeIterator.h"

#include "Begin.h"
#include "End.h"
// ---------------------------------------------------------------------------
namespace Bicycle
{
// ---------------------------------------------------------------------------
template<typename IteratorT>
struct iterator_range_impl
{
  template<class ForwardRange>
  static IteratorT adl_begin(ForwardRange& r)
  {
    return IteratorT(Bicycle::begin(r));
  }

  template<class ForwardRange>
  static IteratorT adl_end(ForwardRange& r)
  {
    return IteratorT(Bicycle::end(r));
  }
};
// -------------------------------------------------------------------------------
struct range_tag{};
struct const_range_tag{};
// -------------------------------------------------------------------------------
template<typename IteratorT>
class iterator_range
{
protected: // Used by sub_range
  // ! implementation class
  typedef iterator_range_impl<IteratorT> impl;

public:
  typedef iterator_range<IteratorT>type;

  //typedef iterator_value<IteratorT>::type value_type;
  // typedef iterator_difference<IteratorT>::type difference_type;
  typedef std::size_t size_type;

  typedef iterator_range<IteratorT> this_type;
  // typedef iterator_reference<IteratorT>::type reference;
  typedef IteratorT const_iterator;
  typedef IteratorT iterator;

  iterator_range()
    : m_Begin(iterator()),
      m_End(iterator())
  {
  }

  template<class Iterator> iterator_range(Iterator Begin, Iterator End)
    : m_Begin(Begin),
      m_End(End)
  {
  }

  template<class Range>	iterator_range(const Range& r)
    : m_Begin(impl::adl_begin(r)),
      m_End(impl::adl_end(r))
  {
  }

  template<class Range>	iterator_range(Range& r)
    : m_Begin(impl::adl_begin(r)),
      m_End(impl::adl_end(r))
  {
  }

  // ! Constructor from a Range
  template<class Range>	iterator_range(const Range& r, const_range_tag)
    : m_Begin(impl::adl_begin(r)),
      m_End(impl::adl_end(r))
  {
  }

  // ! Constructor from a Range
  template<class Range>	iterator_range(Range& r, range_tag)
    : m_Begin(impl::adl_begin(r)),
      m_End(impl::adl_end(r))
  {
  }


  /*difference_type*/ std::size_t size() const
  {
    return m_End - m_Begin;
  }

  IteratorT begin()const
  {
    return m_Begin;
  }

  IteratorT end()const
  {
    return m_End;
  }

private :
  // begin and end iterators
  IteratorT m_Begin; IteratorT m_End;
};
// ---------------------------------------------------------------------------
template<typename IteratorT>
inline iterator_range<IteratorT>
make_iterator_range(IteratorT Begin, IteratorT End)
{
  return iterator_range<IteratorT>(Begin, End);
}

template<class ForwardRange>
inline iterator_range< typename range_iterator<ForwardRange>::type >
make_iterator_range(ForwardRange& r)
{
  return
      iterator_range< typename range_iterator<ForwardRange>::type >(r,range_tag());
}

template<class ForwardRange>
inline iterator_range<typename range_iterator<const ForwardRange>::type>
make_iterator_range(const ForwardRange& r)
{
  return
      iterator_range< typename range_iterator<const ForwardRange>::type>(r,const_range_tag());
}
// ---------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------
#endif
