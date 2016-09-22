//---------------------------------------------------------------------------
#ifndef RangeConstIteratorH
#define RangeConstIteratorH
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
// range_const_iterator  container/c-array
//---------------------------------------------------------------------------
	template< typename C >
	struct range_const_iterator
	//			: extract_const_iterator<C>
	{
    typedef typename C::const_iterator type;
	};

	template<typename Iterator>
	struct range_const_iterator<std::pair<Iterator, Iterator> >
	{
		typedef Iterator type;
	};

	template<typename T, std::size_t N>
	struct range_const_iterator< T[N]>
	{
		typedef const T* type;
	};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
