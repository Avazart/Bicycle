// ---------------------------------------------------------------------------
#ifndef RangeIteratorH
#define RangeIteratorH
// ---------------------------------------------------------------------------
#include "RangeMutableIterator.h"
#include "RangeConstIterator.h"
// ---------------------------------------------------------------------------
namespace Bicycle
{
// ---------------------------------------------------------------------------
template< class T > struct remove_const          { typedef T type; };
template< class T > struct remove_const<const T> { typedef T type; };
// ---------------------------------------------------------------------------
template< class T > struct is_const          { enum { value= false }; };
template< class T > struct is_const<const T> { enum { value= true  }; };

// ---------------------------------------------------------------------------
template<bool C, typename T1, typename T2>
struct if_c
{
  typedef T1 type;
};

template<typename T1, typename T2>
struct if_c<false, T1, T2>
{
  typedef T2 type;
};
// ---------------------------------------------------------------------------
template<bool C, typename F1, typename F2>
struct eval_if_c
{
  typedef typename if_c<C,F1,F2>::type f_;
  typedef typename f_::type type;
};
// ---------------------------------------------------------------------------
template<typename C, typename Sig= void>
struct range_iterator
{
  typedef typename
  eval_if_c< is_const<C>::value,
  range_const_iterator< typename remove_const<C>::type >,
  range_mutable_iterator<C>
  >::type type;

  //				typedef typename
  //						boost::mpl::eval_if_c< boost::is_const<C>::value,
  //																	 boost::range_const_iterator< typename remove_const<C>::type >,
  //																	 boost::range_mutable_iterator<C>
  //																 >::type type;
};

template<typename C, typename T>
struct range_iterator< C, void(T[])>
{
  typedef T* type;
};
// ---------------------------------------------------------------------------
};
// ---------------------------------------------------------------------------
#endif
