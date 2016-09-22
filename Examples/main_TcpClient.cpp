#include <iostream>

#include "Tcp/TcpClient.h"
#include "IOStream.h"

// #pragma comment(lib, "Ws2_32.lib")

int main()
{
  using namespace std;
  namespace Bi= Bicycle;

  try
  {
    Bi::startup();
    Bi::TcpClient client;
    client.connect("www.cyberforum.ru",80);
    client.setTimeOut(5000);

    Bi::IOStream stream(&client);
    Bi::ulong error= Bi::SocketError::Success;
    stream.writeLine("GET / HTTP/1.1",error);
    stream.writeLine("Host: www.cyberforum.ru",error);
    stream.writeLine("User-Agent: Mozilla/5.0 (Windows NT 6.1; rv:47.0) Gecko/20100101 Firefox/47.0",error);
    stream.writeLine("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",error);
    stream.writeLine("Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3",error);
    stream.writeLine("Accept-Encoding: gzip, deflate",error);
    stream.writeLine("Connection: keep-alive",error);
    stream.writeLine("",error);

    do
    {
      std::string line;
      if(stream.readLine(line,error) != 0 )
      {
        std::cout<<"\""<<line<<"\""<<std::endl;
      }
    }
    while(!error);

    if(error!=Bi::SocketError::Success)
    {
      if(error==Bi::SocketError::WsaTimeOut)
        std::cout<<"TimeOut!"<<std::endl;
      else
        std::cerr<<"Ошибка #"<< error<<std::endl;
    }
  }
  catch(const Bi::SocketException& e)
  {
    std::cerr<<"Ошибка #"<< e.code()<<" "<< e.message()<<std::endl;
  }
  Bi::cleanup(true);

  getchar();
  return 0;
}

