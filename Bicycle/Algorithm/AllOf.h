#ifndef AllOfH
#define AllOfH
//----------------------------------------------------------------------
namespace Bicycle
{
//----------------------------------------------------------------------
// from C++11
//----------------------------------------------------------------------
template< class InputIt, class UnaryPredicate >
bool all_of(InputIt first, InputIt last, UnaryPredicate p)
{
    for (; first != last; ++first) {
        if (!p(*first)) return false;
    }
    return true;
}


template< class InputIt, class UnaryPredicate >
bool any_of(InputIt first, InputIt last, UnaryPredicate p)
{
    for (; first != last; ++first) {
        if (p(*first)) return true;
    }
    return false;
}

template< class InputIt, class UnaryPredicate >
bool none_of(InputIt first, InputIt last, UnaryPredicate p)
{
    for (; first != last; ++first) {
        if (p(*first)) return false;
    }
    return true;
}
//----------------------------------------------------------------------
}
//----------------------------------------------------------------------
#endif
