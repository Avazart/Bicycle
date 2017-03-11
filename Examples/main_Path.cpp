#include <iostream>

#include "Experimental/Path.h"

using namespace std;
namespace Bi= Bicycle;

void print(const Bi::Strings& strings)
{
  for(std::size_t i=0; i<strings.size(); ++i)
    wcout<<i <<". "<< strings[i] << endl;
}

int main()
{
  Bi::tstring path=
    L"D:/Projects/Github/Bicycle/TestProjects/QtCreator_MSVC2010/TestBicycle/TestPath/Test";
  path = Bi::Path::toNativeSeparators(path);
  wcout << path<< endl;
  wcout<< L"-----------------------" <<endl;

  Bi::Strings strings;
  wcout<< Bi::Path::entry(strings,path,L"x-*", Bi::Path::AllEntries) << endl;
  print(strings);

  wcout<< L"=======================" <<endl;
  path= L"D:\\1\\2.3\\4.txt";
  wcout<< path <<endl;
  wcout<< L"-----------------------" <<endl;

  wcout<< Bi::Path::fileName(path) <<endl;
  wcout<< Bi::Path::parent(path) <<endl;
  wcout<< Bi::Path::baseName(path) <<endl;
  wcout<< Bi::Path::extension(path)  <<endl;
  wcout<< Bi::Path::currentDir()  <<endl;
  wcout<< Bi::Path::relativeTo(L"c:\\a\\b\\path",L"c:\\a\\x\\y\\file")<<endl;

  getchar();
  return 0;
}

