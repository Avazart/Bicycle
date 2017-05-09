#include <iostream>

#include "Win/Process/Process.h"
#include "Win/Common/TextStream.h"

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
    process.stdOut().setTimeOut(30000);

    // Используем поток для чтения из пайпа построчно
    TextStream stream(&process.stdOut());
    while(true)
    {
      string line = stream.readLine();
      cout<<"\""<<line<<"\""<<endl;
    }
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
