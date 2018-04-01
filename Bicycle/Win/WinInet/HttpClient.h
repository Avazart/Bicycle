#ifdef _MSC_VER
  #pragma once
#endif
// ---------------------------------------------------------------------------
#ifndef HttpClientH
#define HttpClientH
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

    void openSession(const tstring& userAgent= tstring(TEXT("Microsoft Internet Explorer")));
		void openUrl(const tstring& url, const tstring& headers= tstring()); 
		
		void closeSession();
		void closeUrl();

		ulong statusCode();
        ulong contentLength();

		static void setCookie(const tstring& url, const tstring& cookieName, const tstring& cookieData);
		static void setCookie(const tstring& url, const tstring& cookieNameData);

		static tstring cookie(const tstring& url, const tstring& cookieName= tstring());

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

    virtual ulong read(char* data, ulong size);
    virtual ulong write(const char* data, ulong size); // NOT_USED
 
    ~HttpClient();
private:
     HINTERNET sessionHandle_;
     HINTERNET urlHandle_;
};
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------
#endif
