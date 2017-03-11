#include <iostream>

#include "File.h"
#include "IOStream.h"
#include "SystemException.h"
#include "Console.h"

using namespace std;
namespace Bi= Bicycle;

int main()
{
  Bi::Console::changeCp(1251);
  try
  {
    Bi::File file(L"1.txt",Bi::File::Read,Bi::File::OpenExisting);
    file.open();

    Bi::IOStream stream(&file);
    while(true)
    {
      string line= stream.readLn();
      cout << line << endl;
    }
  }
  catch(const Bi::SystemException& e)
  {
    cerr<< e.what() <<endl;
  }

  cout<< "Done!"<<endl;
  getchar();
  return 0;
}


