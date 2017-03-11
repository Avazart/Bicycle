#ifdef _MSC_VER
  #pragma once
#endif
// ---------------------------------------------------------------------------
#ifndef HttpClientH
#define HttpClientH
// ---------------------------------------------------------------------------
#include "../Global.h"
#include "../NonCopyable.h"
#include "../IODevice.h"
// ---------------------------------------------------------------------------
#include "WinInetException.h"
#include <WinInet.h>
// ---------------------------------------------------------------------------
namespace Bicycle
{
//------------------------------------------------------------------------
class Request
{
   public:
      tstring verb;
      tstring url;
      tstring version;
      tstring referer;
      //  acceptTypes
      ulong flags;
      // context
};
//------------------------------------------------------------------------
class HttpClient: public IODevice, private NonCopyable
{
public:
		HttpClient();

		void openSession(const tstring& userAgent= L"Microsoft Internet Explorer");
		void openUrl(const tstring& url, const tstring& headers= tstring()); 
		
		void closeSession();
		void closeUrl();

		ulong statusCode();
    ulong contentLength();

		SYSTEMTIME date();
		tstring dateString();

    void setConnectTimeOut(ulong connectTimeOut);
    void setReadTimeOut(ulong readTimeOut);


// http://stackoverflow.com/questions/8284615/hep-on-httpopenrequest-and-other-wininet-functions
// http://stackoverflow.com/questions/5557159/post-form-data-using-wininet-c

//    void connect(const tstring& host);  // InternetConnect()

//    void request(const tstring& verb,
//                 const tstring& objectName,
//                 const tstring& version,
//                 const tstring& referer,
//                 ulong flags,
//                 );

    virtual ulong read(char* data, ulong size, ulong& errorCode);
    virtual ulong write(const char* data, ulong size, ulong& errorCode);
    virtual void checkErrorCode(ulong code) const;
 
    ~HttpClient();
private:
     HINTERNET sessionHandle_;
     HINTERNET urlHandle_;
};
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------
#endif
