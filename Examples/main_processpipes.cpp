#include <iostream>
#include <algorithm>

#include "Process/Process.h"
#include "Console.h"
#include "IOStream.h"

int main(int argc, char *argv[])
{
  using namespace std;
  namespace Bi= Bicycle;

  Bi::Console::setTextAttr(Bi::ConsoleColor::lime);

  if(argc>1 && strcmp(argv[1],"-echo")==0) // child process "echo"
  {
    string line;
    while(getline(cin,line))
    {
      if(line=="quit")
         break;

      std::reverse(line.begin(),line.end());
      cout<<line<<endl;
    }
  }
  else// main process
  {
    try
    {
      Bi::Process process;

      process.setInheritHandle(true);
      process.setSecurityInheritHandle(true);
      process.usePipes(true);
      process.setCmdLine(Bi::appModuleFileName()+ L" -echo");
      process.start();

      Bi::IOStream inStream(&process.stdIn());
      Bi::IOStream outStream(&process.stdOut());

			string line;
      while(getline(cin,line))
      {
        inStream.writeLn(line);
        line= outStream.readLn();
        cout<<"\""<< line<<"\"" << endl;
      }
		}
    catch(const Bi::SystemException& e)
    {
      Bi::Console::setTextAttr(Bi::ConsoleColor::red);
      Bi::Console::changeCp(Bi::Win1251);
			cerr<< e.what()<<endl;
    }
    getchar();
  }
  return 0;
}

