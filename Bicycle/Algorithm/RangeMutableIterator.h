// ---------------------------------------------------------------------------
#ifndef RangeMutableIteratorH
#define RangeMutableIteratorH
// ---------------------------------------------------------------------------
namespace Bicycle
{
// ---------------------------------------------------------------------------
template<typename C>
struct range_mutable_iterator
{
  typedef typename C::iterator type;
};

template<typename Iterator>
struct range_mutable_iterator<std::pair<Iterator, Iterator> >
{
  typedef Iterator type;
};

template<typename T, std::size_t sz>
struct range_mutable_iterator< T[sz]>
{
  typedef T* type;
};
// ---------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------
#endif
