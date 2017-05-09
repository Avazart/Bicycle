#include <iostream>

#include "Win/WinInet/HttpClient.h"
#include "Win/Common/TextStream.h"

int main()
{
  using namespace std;
  using namespace Bicycle;

  try
  {
    HttpClient client;
    client.openSession();
    client.setReadTimeOut(5000);
    client.openUrl(L"https://yandex.ru");

    ulong statusCode = client.statusCode();
    if(statusCode==200) // OK
    {
      wstring dataString= client.dateString();
      wcout<< dataString << endl;

      while(true)
      {
        string data(256,'\0');
        long length= client.read(&data[0],data.size());
        if(length)
        {
          data.resize(length);
          cout<< data ;
        }
        else
          break;
      }
      cout<< endl;

//      TextStream stream(&client);
//      while(true)
//      {
//        string line= stream.readLine();
//        cout<< line << endl;
//      }
    }
  }
  catch(const Exception& e)
  {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cerr<< e.message() << endl;
  }

  cout<<"Done!"<<endl;
  getchar();
  return 0;
}
