#include <iostream>
#include <algorithm>

#include "Win/Process/Process.h"
#include "Win/Common/TextStream.h"
#include "Win/Experimental/Console.h"

int main(int argc, char *argv[])
{
  using namespace std;
  using namespace Bicycle;

  if(argc>1 && strcmp(argv[1],"-echo")==0) // эхо режим для дочернего.процесса
  {
    string line;
    while(getline(cin,line))
    {
      if(line=="quit")
        break;

      reverse(line.begin(),line.end()); // переворачиваем строку
      cout<<line<<endl;
    }
  }
  else// главный процесс
  {
    try
    {
      Process process;

      process.setInheritHandle(true);
      process.setSecurityInheritHandle(true);
      process.usePipes(true);
      // Запускаем себя с эхо режиме
      process.setCmdLine(appModuleFileName()+ L" -echo");
      process.start();

      TextStream inStream(&process.stdIn());
      TextStream outStream(&process.stdOut());

      string line;
      while(getline(cin,line))
      {
        inStream.writeLine(line);
        line= outStream.readLine();
        cout<<"\""<< line<<"\"" << endl;
      }
    }
    catch(const Exception& e)
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        cerr<< e.message()<<endl;
    }
    getchar();
  }
  return 0;
}


