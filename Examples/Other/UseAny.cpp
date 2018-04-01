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

  Any a4= a3;

  assert(a4==a3);

  a4 = 20;
  assert(a4>a3);

  vector<Any> va;
  for(size_t i=0; i<10; ++i)
    va.push_back(rand()%10);

  sort(va.begin(),va.end());
  for(size_t i=0; i<va.size(); ++i)
    cout<< va[i].cast<int>() <<endl;

  return 0;
}
