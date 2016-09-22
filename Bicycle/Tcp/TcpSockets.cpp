//---------------------------------------------------------------------------
#include "TcpSockets.h"
//---------------------------------------------------------------------------
void Bicycle::startup()
{
	WSADATA  data;
	if(WSAStartup(MAKEWORD(2,0),&data))
		throw SocketException();
}
//---------------------------------------------------------------------------
void Bicycle::cleanup(bool nonThrow)
{
	if(WSACleanup() && !nonThrow)
		throw SocketException();
}
//---------------------------------------------------------------------------
