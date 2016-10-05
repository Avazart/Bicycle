//---------------------------------------------------------------------------
#include "TcpClient.h"
//---------------------------------------------------------------------------
using namespace Bicycle;
//--------------------- IODevice --------------------------------------------
ulong TcpClient::read(char *data, ulong size, ulong &errorCode)
{
  int length= ::recv(socket_, data, size, NULL);
  if(length == SOCKET_ERROR)
  {
    errorCode= WSAGetLastError();
    length= 0;
  }
  return length;
}
// ---------------------------------------------------------------------------
ulong TcpClient::write(const char* data, ulong size, ulong& errorCode)
{
  errorCode= SocketError::Success;
  int length = ::send(socket_, data, size, NULL);
  if(length == SOCKET_ERROR)
  {
    errorCode= WSAGetLastError();
    length= 0;
  }
  return length;
}
// ---------------------------------------------------------------------------
void TcpClient::checkErrorCode(ulong code) const
{
  if(code!=SocketError::Success)
    throw SocketException(code);
}
//----------------------- TcpClient -----------------------------------------
TcpClient::TcpClient()
  : socket_(INVALID_SOCKET),
    hostent_(0),
    timeOut_(DEFAULT_TIMEOUT)
{
  addr_.sin_family= AF_INET;
  socket_= ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if(socket_==INVALID_SOCKET)
    throw SocketException();
}
//---------------------------------------------------------------------------
TcpClient::TcpClient(SOCKET socket)
  :socket_(socket),
    hostent_(0),
    timeOut_(0)
{
  if(socket_==INVALID_SOCKET)
    throw Bicycle::SocketException();
}
//---------------------------------------------------------------------------
TcpClient::~TcpClient()
{
  close(true);
}
//---------------------------------------------------------------------------
void TcpClient::connect(const std::string& addr,unsigned short port)
{
  setPort(port);
  setAddr(addr);
  TcpClient::connect();
}
//---------------------------------------------------------------------------
void TcpClient::connect()
{
  if(::connect(socket_,
               (sockaddr*)&addr_,
               sizeof(addr_)) == SOCKET_ERROR)
  {
    throw SocketException();
  }

  if(timeOut_==INFINITE)
    return;

  if(setsockopt( socket_,
                 SOL_SOCKET,
                 SO_RCVTIMEO,
                 (char *)&timeOut_,
                 sizeof(timeOut_) ) == SOCKET_ERROR)
    throw SocketException();

  if(setsockopt( socket_,
                 SOL_SOCKET,
                 SO_SNDTIMEO,
                 (char *)&timeOut_,
                 sizeof(timeOut_) ) == SOCKET_ERROR)
    throw SocketException();
}
//---------------------------------------------------------------------------
void TcpClient::close(bool nonThrow)
{
  if(shutdown(socket_,SD_BOTH)==SOCKET_ERROR && !nonThrow)
  {
    throw SocketException();
  }
  if(closesocket(socket_)==SOCKET_ERROR && !nonThrow)
  {
    throw SocketException();
  }
}
//---------------------------------------------------------------------------
std::string TcpClient::host()const
{
  return hostent_?hostent_->h_name:"";
}
//---------------------------------------------------------------------------
std::string TcpClient::ip()  const
{
  return inet_ntoa(addr_.sin_addr);
}
//---------------------------------------------------------------------------
unsigned short TcpClient::port() const
{
  return ntohs(addr_.sin_port);
}
//---------------------------------------------------------------------------
ulong TcpClient::timeOut() const
{
  return timeOut_;
}
//---------------------------------------------------------------------------
void TcpClient::setTimeOut(ulong timeOut)
{
  if(timeOut_ != timeOut)
  {
    timeOut_= timeOut;

    if(socket_==INVALID_SOCKET)
      return;

    if(setsockopt( socket_,
                   SOL_SOCKET,
                   SO_RCVTIMEO,
                   (char *)&timeOut_,
                   sizeof(timeOut_) ) == SOCKET_ERROR)
      throw SocketException();

    if(setsockopt(socket_,
                  SOL_SOCKET,
                  SO_SNDTIMEO,
                  (char *)&timeOut_,
                  sizeof(timeOut_) ) == SOCKET_ERROR)
      throw SocketException();
  }
}
//---------------------------------------------------------------------------
void TcpClient::setPort(unsigned short port)
{
  addr_.sin_port= htons(port);
}
//---------------------------------------------------------------------------
void TcpClient::setAddr(const std::string& addr)
{
  if (inet_addr(addr.c_str())!=INADDR_NONE)
    addr_.sin_addr.s_addr= inet_addr(addr.c_str());
  else
  {
    hostent_= gethostbyname(addr.c_str());
    if(hostent_)
    {
      memcpy(&addr_.sin_addr, hostent_->h_addr_list[0], hostent_->h_length);
    }
    else
    {
      throw SocketException();
    }
  }
}
//---------------------------------------------------------------------------


