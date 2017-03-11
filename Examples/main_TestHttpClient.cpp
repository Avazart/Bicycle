#include <iostream>
#include "Http/HttpClient.h"
#include "IOStream.h"

int main()
{
  try
  {
    Bicycle::HttpClient client;
    client.openSession();
    client.setReadTimeOut(5000);
    client.openUrl(L"https://yandex.ru");

    Bicycle::ulong statusCode = client.statusCode();
    if(statusCode==200) // OK
    {
      std::wstring dataString= client.dateString();
      std::wcout<< dataString << std::endl;

      Bicycle::ulong error= 0;
      while(!error)
      {
        std::string data(256,'\0');
        Bicycle::ulong length=
           client.read(&data[0],data.size(),error);
        if(length)
        {
          data.resize(length);
          std::cout<< data ;
        }
        else
          break;
      }
      std::cout<< std::endl;

      //Bicycle::IOStream stream(&client);
      //while(true)
      //{
      //  std::string line= stream.readLn();
      //  std::cout<< line << std::endl;
      // }

    }
  }
  catch(const Bicycle::WinInetException& e)
  {
    std::cerr<< e.what() << std::endl;
  }

  getchar();
  return 0;
}

