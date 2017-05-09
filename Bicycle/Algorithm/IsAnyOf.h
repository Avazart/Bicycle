#ifndef IsAnyOfH
#define IsAnyOfH
//-------------------------------------------------------------------------
#include <algorithm>
#include <iterator>
#include <vector>
#include <functional>
//-------------------------------------------------------------------------
#include "Utils.h"
#include "Begin.h"
#include "End.h"
//-------------------------------------------------------------------------
namespace Bicycle
{
//-------------------------------------------------------------------------
// is_any_of
//---------------------------------------------------------------------------
	template<typename T>
  class is_any_ofF: public std::unary_function<T, bool>
	{
	public:
    typedef typename value_type<T>::type value_type;

		is_any_ofF(const T& s)
		{
      std::copy(Bicycle::begin(s), Bicycle::end(s), std::back_inserter(c_));
			std::sort(c_.begin(), c_.end());
		}

		bool operator()(value_type v)
		{
			return std::binary_search(c_.begin(), c_.end(), v);
		}

	private:
		std::vector<value_type>c_;
	};
//---------------------------------------------------------------------------
	template<typename T>
	is_any_ofF<T> is_any_of(const T& s)
	{
		return is_any_ofF<T>(s);
	}
//-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
#endif
