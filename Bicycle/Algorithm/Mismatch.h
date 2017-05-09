//----------------------------------------------------------------------
#ifndef MismatchH
#define MismatchH
//----------------------------------------------------------------------
namespace Bicycle
{
// std::mismatch from C++14
//----------------------------------------------------------------------
template<class InputIt1, class InputIt2>
std::pair<InputIt1, InputIt2>
  mismatch(InputIt1 first1, InputIt1 last1,
           InputIt2 first2, InputIt2 last2 )
{
  while(first1!=last1 &&
        first2!=last2 &&
        *first1==*first2)
  {
    ++first1, ++first2;
  }
  return std::make_pair(first1, first2);
}
//----------------------------------------------------------------------
template< class InputIt1, class InputIt2, class BinaryPredicate >
std::pair<InputIt1,InputIt2>
  mismatch( InputIt1 first1, InputIt1 last1,
            InputIt2 first2, InputIt2 last2,
            BinaryPredicate p )
{
  while (first1!= last1 &&
         first2!= last2 &&
         p(*first1,*first2))
  {
    ++first1, ++first2;
  }
  return std::make_pair(first1, first2);
}
//----------------------------------------------------------------------
}
//----------------------------------------------------------------------
#endif // MismatchH

