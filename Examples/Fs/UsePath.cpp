#include <iostream>
#include <fstream>

#include "Win/Fs/Path.h"

using namespace std;
using namespace Bicycle;

void print(const Strings& strings)
{
  for(size_t i=0; i<strings.size(); ++i)
  {
    tstring fileName = strings[i];
    wcout<<i <<". "<< fileName.size()<<" "
        << boolalpha<< Path::exists(fileName)  << endl;
  }
}

int main()
{

  try
  {
    Path::setCurrentDir(L"D:\\Projects\\Orders\\25.01.2018\\decode_file_names\\files\\uploads\\uploads\\2014\\03");

    Path::FileInfoVector fiv;
    wcout<< Path::entry(fiv,L".",L"*", Path::AllEntries) << endl;

    for(size_t i=0; i<fiv.size(); ++i)
    {
      wcout<<i <<". "<< fiv[i].alternateFileName() << endl;
      wcout<<i <<". "<< Path::fullPathName(fiv[i].alternateFileName()) << endl;
    }
  }
  catch(const Exception& e)
  {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cerr<< e.message()<<endl;
  }
  /*
  tstring path=
    L"C:/1/2/3/4/5";
  path = Path::toNativeSeparators(path);
  wcout << path<< endl;
  wcout<< L"-----------------------" <<endl;

  Strings strings;
  wcout<< Path::entry(strings,path,L"x-*", Path::AllEntries) << endl;
  print(strings);

  wcout<< L"=======================" <<endl;
  path= L"D:\\1\\2.3\\4.txt";
  wcout<< path <<endl;
  wcout<< L"-----------------------" <<endl;

  wcout<< Path::fileName(path) <<endl;
  wcout<< Path::parent(path) <<endl;
  wcout<< Path::baseName(path) <<endl;
  wcout<< Path::extension(path)  <<endl;
  wcout<< Path::currentDir()  <<endl;
  wcout<< Path::relativeTo(L"c:\\a\\b\\path",L"c:\\a\\x\\y\\file")<<endl;
*/
  getchar();
  return 0;
}
