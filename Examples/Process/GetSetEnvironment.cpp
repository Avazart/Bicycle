#include <iostream>

#include "Win/Process/Process.h"
#include "Win/Process/Environment.h"

using namespace std;
using namespace Bicycle;

// --------------------------------------------------------------------------
void print(const Environment& env)
{
  for (size_t i= 0; i< env.strings().size(); ++i)
    wcout<< env.strings()[i]<< std::endl;
}
// --------------------------------------------------------------------------
int main(int argc, char* [])
{
  setlocale(LC_ALL, "");
  try
  {
    if(argc==1)
       ProcessEnvironment::setVariable(L"MyVAR3",L"MyValue3.1");

    Environment env= ProcessEnvironment::environment();

    print(env);

    if(argc==1)
    {
      Process process;
      env.appendVariable(L"MyVAR1", L"MyValue1");
      env.appendVariable(L"MyVAR2", L"MyValue2");
      env.setVariable(L"MyVar3",env.variable(L"MyVaR3")+L";MyValue3.2");

      process.setEnvironment(env);
      process.setShowWindow(SW_NORMAL);
      process.setCreationFlags(process.creationFlags()|CREATE_NEW_CONSOLE);
      process.setCmdLine(appModuleFileName()+ L" -arg");
      process.start();

      wcout<< endl<< L"Create children process..."<< endl;
      process.waitForFinished();
      wcout<<"Children process finished with exit code: "<< process.exitCode()<<endl;
    }
  }
  catch (const SystemException& e)
  {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cerr<< e.message()<< endl;
  }

  getchar();
  return 0;
}
// --------------------------------------------------------------------------
