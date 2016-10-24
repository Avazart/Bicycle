#include <iostream>

#include "Experimental/Format.h"

int main()
{
  using namespace std;
  using namespace Bicycle;

	string s1= format("%0, %1, %2, %0")% "s" % 15 % 20.667;
	string s2=
			format("%0, %1, %2, %0").arg("s")
                              .arg(15,0,16) // hex
                              .arg(20.667,10,'s',2,'0'); //scientific



  cout<<s1<<endl<<s2<<endl;

  getchar();
  return 0;
}

