#include <iostream>

#include "Win/WinSocks/TcpClient/TcpClient.h"
#include "Win/Common/TextStream.h"

// #pragma comment(lib, "Ws2_32.lib")

int main()
{
  using namespace std;
  using namespace Bicycle;

  try
  {
    Wsa::startup();
    TcpClient client;
    client.connect("www.cyberforum.ru",80);
    client.setTimeOut(30000);

    TextStream stream(&client);
    stream.writeLine("GET / HTTP/1.1");
    stream.writeLine("Host: www.cyberforum.ru");
    stream.writeLine("User-Agent: Mozilla/5.0 (Windows NT 6.1; rv:47.0) Gecko/20100101 Firefox/47.0");
    stream.writeLine("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    stream.writeLine("Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3");
    stream.writeLine("Connection: keep-alive");
    stream.writeLine("");

    string line;
    do
    {
      line= stream.readLine();
      cout<<"\""<<line<<"\""<<endl;
    }
    while(true); // line!="0"
  }
  catch(const SystemException& e)
  {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cerr<<"SystemError #"<< e.code()<<" :"<< e.message()<<endl;
  }
  catch(const Exception& e)
  {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cerr<<"Error: "<< e.message()<<endl;
  }

  cout<<"Done!"<<endl;
  Wsa::cleanup(true);
  getchar();
  return 0;
}
