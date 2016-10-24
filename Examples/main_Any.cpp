#include <iostream>
#include <string>

#include "Experimental/Any.h"

using namespace std;
namespace Bi= Bicycle;

class Test
{
   public:
      Test(int value=0):value_(value){ cout<<"Test()"<<endl; }

      Test(const Test& t)
      {
        value_= t.value_;
        cout<<"Test(const Test&)"<<endl;
      }

      int test()const{ return value_; }

      ~Test(){ cout<<"~Test()"<<endl; }
   private:
      int value_;
};

int main()
{
  Bi::Any a1= 10;
  Bi::Any a2= string("str1");
  Bi::Any a3(a1);

  a1= a2;
  a2= string("str2");

  try
  {
    cout << a1.cast<string>() << endl;
    cout << a2.cast<string>() << endl;

    Bi::swap(a1,a2);

    cout << Bi::any_cast<string>(a1) << endl;
    cout << Bi::any_cast<string>(a2) << endl;

    if(a3.isType<int>())
    {
      const int& i=  Bi::any_cast<int>(a3);
      cout << i << endl;
    }

    a3= Test(11);
    cout << a3.cast<Test>().test() << endl;

    a3= 5.4;

    double x= 0;
    if(a3.tryCast(x))
       cout <<"x= "<< x << endl;

    Bi::Value<double> v= a3.value<double>();
    if(v.isValid())
      cout <<"v= "<< v << endl;
  }
  catch(const std::bad_cast& e)
  {
    cerr << e.what() << endl;
  }

  getchar();
  return 0;
}


