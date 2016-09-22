#ifndef SplitH
#define SplitH
//----------------------------------------------------------------------
#include <algorithm>

#include "Utils.h"
#include "Begin.h"
#include "End.h"
//----------------------------------------------------------------------
namespace My
{
//----------------------------------------------------------------------
	template<class InputIt1, class InputIt2>
	std::pair<InputIt1, InputIt2>
		mismatch(InputIt1 first1, InputIt1 last1,
						 InputIt2 first2, InputIt2 last2 )  // C++14 !?
	{
		while (first1!= last1 &&
					 first2!= last2 &&
					 *first1== *first2)
		{
			++first1, ++first2;
		}
		return std::make_pair(first1, first2);
	}
//----------------------------------------------------------------------
	template<class InputIt1, class InputIt2>
	std::pair<bool,InputIt1>
		 starts_with(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2)
	{
		std::pair<InputIt1,InputIt2> 
				p= mismatch(first1,last1,first2,last2);
		return std::make_pair(p.second==last2,p.first);
	}
//----------------------------------------------------------------------
	template<class C1, class C2>
	std::pair<bool, typename range_const_iterator<C1>::type >

		starts_with(const C1& c1,const C2& c2)
	{
		iterator_range< range_const_iterator<C1>::type >
			 lit_range1(as_literal(c1));

		iterator_range< range_const_iterator<C2>::type >
			 lit_range2(as_literal(c2));

		return starts_with( begin(lit_range1),  end(lit_range1),
												begin(lit_range2),  end(lit_range2) );
	}
//----------------------------------------------------------------------
	template<class InputIt, class C>
	std::pair<bool,InputIt>
		starts_with(InputIt first, InputIt last, const C& c)
	{
		iterator_range< range_const_iterator<C>::type >
			 lit_range(as_literal(c));

		return starts_with( first, last,
												begin(lit_range), end(lit_range));
	}
//----------------------------------------------------------------------
	template<typename SourseT, typename TargetT>  // std::tuple ??
	struct search_result
	{
		SourseT first;
		SourseT last;
		TargetT found;

		search_result(SourseT first_,SourseT last_,TargetT found_)
		: first(first_),
			last(last_),
			found(found_)
		{}
	};
//----------------------------------------------------------------------
	template<typename X, typename Y>
	search_result<X,Y>
			make_search_result(X first,X last,Y found)
	{
		return search_result<X,Y>(first,last,found);
	}
//----------------------------------------------------------------------
	template<typename InputIt1, typename InputIt2>
	search_result<InputIt1, InputIt2>
		 search(InputIt1 first1, InputIt1 last1,
						InputIt2 first2, InputIt2 last2)
	{
		for(; first1!=last1; ++first1)
		{
			for(InputIt2 cur= first2; cur!=last2; ++cur)
			{
				std::pair<bool,InputIt1> p=
					starts_with(first1,last1,*cur);
				if(p.first)
					return make_search_result(first1,p.second,cur);
			}
		}
		return make_search_result(first1,last1,last2);
	}
	//----------------------------------------------------------------------
	template<typename InputIt, typename C>
	search_result< InputIt, typename range_const_iterator<C>::type>
		search(InputIt first, InputIt last,const C& c)
	{
		iterator_range< typename range_const_iterator<C>::type >
			 lit_range(as_literal(c));

		return
		 search< InputIt, typename range_const_iterator<C>::type >
				( first,last,	begin(lit_range),end(lit_range));
	}
//----------------------------------------------------------------------
	template<typename C1, typename C2>
	search_result< typename range_const_iterator<C1>::type ,
								 typename range_const_iterator<C2>::type>
		search(const C1& c1,const C2& c2)
	{
		iterator_range< typename range_const_iterator<C1>::type >
			 lit_range1(as_literal(c1));

		iterator_range< typename range_const_iterator<C2>::type >
			 lit_range2(as_literal(c2));

		return
		 search< typename range_const_iterator<C1>::type,
						 typename range_const_iterator<C2>::type >
				( begin(lit_range1),end(lit_range1),
					begin(lit_range2),end(lit_range2) );
	}
//----------------------------------------------------------------------
	template<typename OutT, typename InT, typename SplittersT>
	void split2(OutT& out, const InT& in,const SplittersT& splitters, bool skip_empty_parts= false)
	{
		iterator_range< typename range_const_iterator<InT>::type >
			 lit_range(as_literal(in));

		typename range_const_iterator<InT>::type first= begin(lit_range);
		typename range_const_iterator<InT>::type last=  end(lit_range);

		for( ;first!=last; )
		{
			search_result< 	typename range_const_iterator<InT>::type,
											typename range_const_iterator<SplittersT>::type >
				r= search(first,last,splitters);

			if(!skip_empty_parts || first!=r.first)
				out.push_back(OutT::value_type(first,r.first));
			first= r.last;
		}
	}
//----------------------------------------------------------------------
	template<typename OutT, typename InT, typename PredicateT>
	void split(OutT& out, const InT& in,
						 PredicateT IsSplitter,
						 bool skip_empty_parts= false)
	{
		iterator_range< typename range_const_iterator<InT>::type >
			 lit_range(as_literal(in));

		range_const_iterator<InT>::type first= begin(lit_range);
		range_const_iterator<InT>::type last=  end(lit_range);
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
//	template<typename OutT, typename InT>
//	void join(OutT& out,const InT& in,const InT splitter)
//	{
//		InT::const_iterator first= in.begin();
//		InT::const_iterator last= in.end();
//		for( ; first!=last; ++first)
//		{
//			out.push_back(*first);
//		}
//	}
//----------------------------------------------------------------------
}
//----------------------------------------------------------------------
#endif
