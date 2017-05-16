#include <iostream>

#include "Win/Fs/File.h"
#include "Win/TextStream/TextStream.h"
#include "Win/Common/Exception.h"

int main()
{
  using namespace std;
  using namespace Bicycle;

  try
  {
    File file(L"1.txt",File::Read,File::OpenExisting);
    file.open();

    TextStream stream(&file);
    while(true)
    {
      string line= stream.readLine();
      cout << line << endl;
    }
  }
  catch(const Exception& e)
  {
      SetConsoleCP(1251);
      SetConsoleOutputCP(1251);
      cerr<< e.message()<<endl;
  }

  cout<< "Done!"<<endl;
  getchar();
  return 0;
}
