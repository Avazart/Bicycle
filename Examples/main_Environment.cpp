#include <iostream>

#include "Process/Process.h"
#include "Process/Environment.h"

#include "Algorithm/Split.h"
#include "Algorithm/Trim.h"
#include "Algorithm/IsAnyOf.h"

#include "Console.h"
#include "IOStream.h"

using namespace std;

namespace Bi= Bicycle;

// --------------------------------------------------------------------------
void print(const Bi::Environment& env)
{
  for (std::size_t i= 0; i< env.strings().size(); ++i)
    wcout<< env.strings()[i]<< std::endl;
}
// --------------------------------------------------------------------------
Bi::tstring appFilePath()
{
  Bi::tstring filePath(MAX_PATH,L'\0');
  Bi::ulong length= GetModuleFileName(0, &filePath[0], filePath.size());
  filePath.resize(length);
  return filePath;
}
// --------------------------------------------------------------------------
int main(int argc, char* [])
{
  // setlocale(LC_ALL, "");
  try
  {
    Bi::Console::setTextAttr(argc==1
                             ? Bi::ConsoleColor::lime
                             : Bi::ConsoleColor::aqua);

    if(argc==1)
       Bi::ProcessEnvironment::setVariable(L"MyVAR3",L"MyValue3.1");

    Bi::Environment env= Bi::ProcessEnvironment::environment();

    print(env);

    if(argc==1)
    {
      Bi::Process process;
      env.appendVariable(L"MyVAR1", L"MyValue1");
      env.appendVariable(L"MyVAR2", L"MyValue2");
      env.setVariable(L"MyVar3",env.variable(L"MyVaR3")+L";MyValue3.2");

      process.setEnvironment(env);

      process.setShowWindow(SW_NORMAL);
      process.setCreationFlags(process.creationFlags()|CREATE_NEW_CONSOLE);

      process.setCmdLine(appFilePath()+ L" -arg");
      process.start();

      Bi::Console::setTextAttr(Bi::ConsoleColor::blue);
      wcout<< endl<< L"Create children process..."<< endl;
      process.waitForFinished();
      wcout<<"Children process finished with exit code: "<< process.exitCode()<<endl;


      // Example how use Bi::split() and Bi::trim()
      Bi::Console::setTextAttr(Bi::ConsoleColor::yellow);
      wcout<<endl<<L"PATH:"<<endl;
      Bi::tstring path_variable= env.variable(L"PATH");

      // split string by ";"
      Bi::Strings values;
      Bi::split(values,path_variable,Bi::is_any_of(L";"));

      for(size_t i=0; i<values.size(); ++i)
        wcout<< // trim separator '/' in end path
               Bi::trim_right_copy_if(values[i],Bi::is_any_of(L"/\\"))
             <<endl;
    }
  }
  catch (const Bi::SystemException& e)
  {
    Bi::Console::changeCp(Bi::Win1251);
    Bi::Console::setTextAttr(Bi::ConsoleColor::red);
    cerr<< e.what()<< endl;
  }

  getchar();
  return 0;
}
// --------------------------------------------------------------------------
