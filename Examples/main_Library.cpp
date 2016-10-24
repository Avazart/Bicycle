#include <iostream>

#include "Experimental/Library.h"
#include "Console.h"

using namespace std;
namespace Bi= Bicycle;

typedef unsigned long (*FGetCurrentThreadId)(void);

int main()
{
  Bi::Console::changeCp(1251);
  Bi::Console::setTextAttr(Bi::ConsoleColor::lime);

  try
  {
    Bi::Library lib("Kernel32.dll");

    FGetCurrentThreadId getCurrentThreadId=
      lib.procAddress<FGetCurrentThreadId>("GetCurrentThreadId");

    cout<< getCurrentThreadId() <<std::endl;
  }
  catch(const Bi::SystemException & e)
  {
    Bi::Console::setTextAttr(Bi::ConsoleColor::red);
    cerr<< e.what()<< endl;
  }

  getchar();
  return 0;
}

