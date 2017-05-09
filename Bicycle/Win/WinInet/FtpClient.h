#ifdef _MSC_VER
  #pragma once
#endif
// ---------------------------------------------------------------------------
#ifndef FtpClientH
#define FtpClientH
// ---------------------------------------------------------------------------
#include "Win/Common/Global.h"
#include "Win/Common/NonCopyable.h"
#include "Win/Common/IODevice.h"
// ---------------------------------------------------------------------------
#include "WinInetException.h"
#include <WinInet.h>
// ---------------------------------------------------------------------------
namespace Bicycle
{
//------------------------------------------------------------------------
class FtpClient: public IODevice, private NonCopyable
{
public:
    FtpClient();

    void openSession(const tstring& userAgent= tstring(TEXT("Microsoft Internet Explorer")));
    void connect();
		
		void closeSession();
		void closeUrl();
    void closeTransfer();

    void setHost(const tstring& host);
    void setPort(unsigned port);
    void setUserName(const tstring& userName);
    void setPassword(const tstring& password);

    void setPassiveMode(bool passive); // INTERNET_FLAG_PASSIVE (defalt)
    void setTransferType(ulong transferTypeFlags);// FTP_TRANSFER_TYPE_BINARY(default), FTP_TRANSFER_TYPE_ASCII, FTP_TRANSFER_TYPE_UNKNOWN

    void setCurrentDir(const tstring& dir);

    void openFile(const tstring& fileName);

    void setConnectTimeOut(ulong connectTimeOut);
    void setReadTimeOut(ulong readTimeOut);

    ~FtpClient();

    // IODevice
    virtual ulong read(char* data, ulong size);
    virtual ulong write(const char* data, ulong size);
 
private:
     HINTERNET internetHandle_;
     HINTERNET connectionHandle_;
     HINTERNET transferHandle_;

     tstring host_;
     unsigned port_;
     tstring userName_;
     tstring password_;

     bool passive_;
     ulong transferType_;
};
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------
#endif
