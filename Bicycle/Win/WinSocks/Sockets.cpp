//---------------------------------------------------------------------------
#include "Sockets.h"
//---------------------------------------------------------------------------
void Bicycle::Wsa::startup()
{
  WSADATA  data;
  if(WSAStartup(MAKEWORD(2,0),&data))
    throw WsaException();
}
//---------------------------------------------------------------------------
void Bicycle::Wsa::cleanup(bool nonThrow)
{
  if(WSACleanup() && !nonThrow)
    throw WsaException();
}
//---------------------------------------------------------------------------
