#include <iostream>

#include "Tcp/TcpSockets.h"
#include "Tcp/TcpServer.h"
#include "IOStream.h"

// #pragma comment(lib, "Ws2_32.lib")

using namespace std;
namespace Bi= Bicycle;

class EchoServer: public Bi::TcpServer
{
public:
  void start()
  {
    bind("localhost", 2016);
    listen();
    accept();
  }

protected:
  virtual void workWithClientInThread(Bi::TcpClient* client)  // override
  {
    while(true)
    {
      Bi::ulong error= 0;
      Bi::IOStream stream(client);
      if(stream.writeLine("Welcome to server!",error))
      {
        string line;
        while(stream.readLine(line,error) && !error)
        {
          stream.writeLine(">>"+line,error);
          line.clear();
        }
      }
    }
  }
};

int main()
{
  try
  {
    Bi::Wsa::startup();
    EchoServer server;
    cout<< "Start server..."<< endl;
    server.start();
  }
  catch(const Bi::SocketException& e)
  {
    cerr<< e.code()<< " "<< e.message();
  }
  Bi::Wsa::cleanup(true);

  return 0;
}

