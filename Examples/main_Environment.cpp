#include <iostream>

#include "Process/Process.h"
#include "Process/Environment.h"

#include "Console.h"
#include "IOStream.h"

using namespace std;
namespace Bi= Bicycle;

void print(const Bi::Environment& env);
void readOutput(Bi::Process& process);

int main(int argc, char *[])
{
  //setlocale(LC_ALL, "");

  Bi::Console::setTextAttr(Bi::ConsoleColor::lime);
  try
  {
    Bi::Environment env = Bi::ProcessEnvironment::environment();
    print(env);

    Bi::tstring filePath(MAX_PATH,L'0');
    Bi::ulong length= GetModuleFileName(0,&filePath[0],filePath.size());
    filePath.resize(length);

    if(argc==1)
    {
			Bi::Process process;

      env.appendVariable(L"MyVAR1",L"MyValue2");
      env.appendVariable(L"MyVAR2",L"MyValue2");
      process.setEnvironment(env);

      process.setCmdLine(filePath+L" -arg");
      process.start();

      Bi::Console::setTextAttr(Bi::ConsoleColor::navy);
      wcout<<endl<<L"Children process:"<<endl;
      Bi::Console::setTextAttr(Bi::ConsoleColor::aqua);
      readOutput(process);

      process.waitForFinished();
    }
  }
  catch(const Bi::SystemException& e)
	{
    Bi::Console::changeCp(Bi::Win1251);
    Bi::Console::setTextAttr(Bi::ConsoleColor::red);
    cerr<< e.what()<<endl;
  }

  getchar();
  return 0;
}
//--------------------------------------------------------------------------
void print(const Bi::Environment& env)
{
	for(std::size_t i=0; i< env.strings().size(); ++i)
	{
		wcout << env.strings()[i] << std::endl;
	}
}
//--------------------------------------------------------------------------
void readOutput(Bi::Process& process)
{
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

  if(error==Bi::ProcessError::WaitTimeOut) // Read TimeOut
  {
    Bi::Console::setTextAttr(Bi::ConsoleColor::blue);
    cout<<"Timeout!"<<endl;
  }
  else if(error==Bi::ProcessError::Broken)// Pipe closed (App Finished)
  {
    Bi::Console::setTextAttr(Bi::ConsoleColor::yellow);
    cout<<"Exit code: "<< process.exitCode() <<endl;
  }
  else// Error
  {
    Bi::Console::changeCp(Bi::Win1251);
    Bi::Console::setTextAttr(Bi::ConsoleColor::red);
    cerr<<Bi::formatMessage(error)<<endl;
  }
}
//--------------------------------------------------------------------------


