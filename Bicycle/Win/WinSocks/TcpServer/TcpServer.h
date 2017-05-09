//---------------------------------------------------------------------------
#ifndef TcpServerH
#define TcpServerH
//---------------------------------------------------------------------------
#include "../Win/WinSocks/Sockets.h"

#include "../Win/Common/Global.h"
#include "../Win/Common/Buffer.h"

#include "../WsaException.h"
#include "ClientThread.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TcpServer: private NonCopyable
{
public:
  TcpServer();
  virtual ~TcpServer();

  std::string host()const;
  std::string ip()  const;
  unsigned short port() const;

  void setAddr(const std::string& addr);
  void setPort(unsigned short port);

  void bind();
  void bind(const std::string& addr,unsigned short port);
  void listen(int backlog=256);
  void accept();
  void close(bool nonTrow= false);

  virtual void workWithClientInThread(TcpClient* client)=0;

private:
  SOCKET      socket_;
  HOSTENT*    hostent_;
  sockaddr_in addr_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
