﻿#include <iostream>
#include "Process/Process.h"
#include "Console.h"
#include "IOStream.h"

int main()
{
  using namespace std;
  namespace Bi= Bicycle;

  Bi::Console::setTextAttr(Bi::ConsoleColor::lime);

  try
  {
     Bi::Process process;

     wstring progPath= L"ping";
     wstring parms= L"google.com";
     wstring workDir= L".";

     process.setReadTimeOut(30000);
     process.setCurrentDir(workDir);
     process.setInheritHandle(true);
     process.start(L"",progPath+L" "+parms);

     Bi::ulong error;
     Bi::IOStream stream(&process);
     do
     {
       string line;
       if(stream.readLine(line,error) != 0 )
       {
         cout<<"\""<<line<<"\""<<endl;
       }
     }
     while(!error);

     /*
     ulong exitCode= 0;
     if(process.waitForFinished(exitCode,30000))
     {
       std::cout<<"Процесс завершился кодом "<<exitCode<<std::endl;
     }
     */

     if(error==Bi::ProcessError::WaitTimeOut)
     {
         Bi::Console::setTextAttr(Bi::ConsoleColor::blue);
         cout<<"Timeout!"<<endl;
     }
     else
     {
         Bi::Console::changeCp(Bi::Win1251);
         Bi::Console::setTextAttr(Bi::ConsoleColor::red);
         cerr<<Bi::formatMessage(error)<<endl;
     }

  }
  catch(const Bi::SystemException& e)
  {
     cerr<< e.what()<<endl;
  }

	getchar();
  return 0;
}
