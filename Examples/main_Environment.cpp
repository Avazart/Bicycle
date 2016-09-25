#include <iostream>

#include "Process/Process.h"
#include "Process/Environment.h"

#include "Console.h"
#include "IOStream.h"

using namespace std;

namespace Bi= Bicycle;

void print(const Bi::Environment& env);

int main(int argc, char* [])
{
  // setlocale(LC_ALL, "");
  try
  {
    Bi::Environment env= Bi::ProcessEnvironment::environment();

    if(argc==1)  Bi::Console::setTextAttr(Bi::ConsoleColor::lime);
    else         Bi::Console::setTextAttr(Bi::ConsoleColor::aqua);

    print(env);

    Bi::tstring filePath(MAX_PATH,L'\0');
    Bi::ulong length= GetModuleFileName(0, &filePath[0], filePath.size());
    filePath.resize(length);

    if(argc==1)
    {
      Bi::Process process;

      env.appendVariable(L"MyVAR1", L"MyValue1");
      env.appendVariable(L"MyVAR2", L"MyValue2");
      env.setVariable(L"Path",env.variable(L"Path")+L";MyValue3");
      process.setEnvironment(env);

      process.setShowWindow(SW_NORMAL);
      process.setCreationFlags(process.creationFlags()|CREATE_NEW_CONSOLE);

      process.setCmdLine(filePath+ L" -arg");
      process.start();

      wcout<< endl<< L"Create children process..."<< endl;
      process.waitForFinished();
      wcout<<"Children process finished."<<endl;
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
void print(const Bi::Environment& env)
{
  for (std::size_t i= 0; i< env.strings().size(); ++i)
  {
    wcout<< env.strings()[i]<< std::endl;
  }
}
// --------------------------------------------------------------------------
