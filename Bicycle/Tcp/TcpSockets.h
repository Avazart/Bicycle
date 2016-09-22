//---------------------------------------------------------------------------
#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef TcpSocketsH
#define TcpSocketsH
//---------------------------------------------------------------------------
#include "Global.h"

#include <winsock2.h>
#include "SocketException.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
  namespace Wsa
  {
    void startup();
    void cleanup(bool nonThrow= false);
  }

	struct SocketError
	{
			enum:ulong
			{
				Success= ERROR_SUCCESS,
				WsaTimeOut= WSAETIMEDOUT,  // 10060 Connection timed out.
			};
	};
}
//---------------------------------------------------------------------------
#endif
