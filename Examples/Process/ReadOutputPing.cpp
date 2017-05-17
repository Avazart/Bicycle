#include <iostream>

#include "Win/Process/Process.h"
#include "Win/Process/Pipe.h"

int main()
{
  using namespace std;
  using namespace Bicycle;
  try
  {
    Process process;
    process.setInheritHandle(true);
    process.setSecurityInheritHandle(true);
    process.usePipes(true);
    process.start(L"",L"ping google.com");

    ServerPipe& pipe= process.stdOut();
    pipe.setTimeOut(30000);

    const size_t bufferSize= 256;
    char buffer[bufferSize]={'\0'};
    ulong length= 0;
    do
    {
      length= pipe.read(buffer,bufferSize);
      if(length)
        cout<< string(buffer,length);
    }
    while(length);
  }
  catch(const Exception& e)
  {
      SetConsoleCP(1251);
      SetConsoleOutputCP(1251);
      cerr<< e.message()<<endl;
  }

  getchar();
  return 0;
}
