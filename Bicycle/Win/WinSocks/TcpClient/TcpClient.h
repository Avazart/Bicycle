#ifdef _MSC_VER
  #pragma once
#endif
//------------------------------------------------------------------------
#ifndef TcpClientH
#define TcpClientH
//------------------------------------------------------------------------
#include "Win/Common/Global.h"
#include "Win/Common/IODevice.h"
#include "Win/Common/NonCopyable.h"

#include "Win/WinSocks/Sockets.h"
#include "Win/WinSocks/WsaException.h"
//------------------------------------------------------------------------
namespace Bicycle
{
//------------------------------------------------------------------------
class TcpClient: public IODevice, private NonCopyable
{
public:
  //  IODevice:
  virtual ulong read(char* data, ulong size);
  virtual ulong write(const char* data, ulong size);

  TcpClient();
  explicit TcpClient(SOCKET socket);
  ~TcpClient();

  std::string host()const;
  std::string ip()  const;
  unsigned short port() const;

  ulong timeOut()const;
  void setTimeOut(ulong timeOut);

  void setAddr(const std::string& addr);
  void setPort(int unsigned short);

  void connect();
  void connect(const std::string& addr,unsigned short port);
  void close(bool nonThrow= false);

  SOCKET      socket_;
  HOSTENT*    hostent_;
  sockaddr_in addr_;
  ulong timeOut_;
};
//---------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
