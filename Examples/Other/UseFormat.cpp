#include <iostream>

#include "Other/Format.h"


int main()
{
  using namespace std;
  using namespace Bicycle;

  std::string  str= format("{0} a={a} b={b} c={c} {3}")
                    .arg("e")
                    .arg("c",3.3)
                    .arg("b","22")
                    .arg("a",1)
                    .arg("d");

  cout<< str <<endl;

  return 0;
}
