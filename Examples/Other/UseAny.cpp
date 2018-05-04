#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#include "Other/Any.h"


int main()
{
  using namespace std;
  using namespace Bicycle;

  Any a1(10);
  assert(a1.isType<int>() && a1.cast<int>() == 10);

  Any a2(string("str"));
  assert(a2.isType<string>() && a2.cast<string>() == "str");

  Any a3(a1);
  assert(a3.isType<int>() && a3.cast<int>() == 10);

  a1 = a2;
  assert(a1.isType<string>() && a1.cast<string>() == "str");


  Any a4("test");
  assert(a4.isType<char[5]>());
  cout <<  a4.cast<char[5]>() << endl;

  int ia[3]= {1,2,3};

  Any a5(ia);
  assert(a5.isType<int[3]>());
  for(size_t i=0; i<3; ++i)
    cout << a5.cast<int[3]>()[i] <<std::endl;

  Any a6;
  a6 = "test";
  assert(a6.isType<char[5]>());

  return 0;
}
