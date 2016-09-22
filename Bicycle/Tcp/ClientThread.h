//---------------------------------------------------------------------------
#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------
#ifndef ClientThreadH
#define ClientThreadH
//---------------------------------------------
#include "../Global.h"
#include "../Thread.h"

#include "TcpClient.h"
//-------------------------------------------------------------------------
// Класс потока для работы обработки сервером клиентов в отдельных потоках
//-------------------------------------------------------------------------
namespace Bicycle
{

class TcpServer; // пред-объявление
//---------------------------------------------
class ClientThread: public Thread
{
public:
  ClientThread(TcpServer* server,SOCKET clientSocket);
  ~ClientThread();

protected:
  virtual void run(); // override

private:
  TcpServer* server_;
  TcpClient* client_;
};
//---------------------------------------------
}
//---------------------------------------------
#endif
