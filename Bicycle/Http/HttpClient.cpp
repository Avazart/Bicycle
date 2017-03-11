#include "HttpClient.h"

using namespace Bicycle;
//-----------------------------------------------------------------------------------------
HttpClient::HttpClient()
  :sessionHandle_(0),
    urlHandle_(0)
{
}


HttpClient::~HttpClient()
{
  closeSession();
  closeUrl();
}

void HttpClient::closeSession()
{
  if(sessionHandle_)
  {
    InternetCloseHandle(sessionHandle_);
    sessionHandle_= 0;
  }
}

void HttpClient::closeUrl()
{
  if(urlHandle_)
  {
    InternetCloseHandle(urlHandle_)	;
    urlHandle_= 0;
  }
}

void HttpClient::openSession(const tstring& userAgent)
{
  closeSession();
  sessionHandle_=
      InternetOpen(userAgent.c_str(),
                   INTERNET_OPEN_TYPE_PRECONFIG,
                   NULL,
                   NULL,
                   0);

  if(!sessionHandle_)
    throw WinInetException();
}

void HttpClient::openUrl(const tstring& url, const tstring& headers)
{
  closeUrl();
  urlHandle_=
      InternetOpenUrl(sessionHandle_,
                      url.c_str(),
                      headers.empty()?NULL:headers.c_str(),
                      0,
                      0,
                      0);

  if(!urlHandle_)
    throw WinInetException();
}

ulong HttpClient::statusCode()
{
  ulong code= 0;
  ulong length = sizeof(code);
  if(!HttpQueryInfo(urlHandle_,
                    HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
                    &code,
                    &length,
                    NULL))
  {
    throw WinInetException();
  }
  return code;
}

ulong HttpClient::contentLength()
{
  ulong contentLength= 0;
  ulong length = sizeof(contentLength);
  if(!HttpQueryInfo(urlHandle_,
                    HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER,
                    &contentLength,
                    &length,
                    NULL))
  {
    throw WinInetException();
  }
  return contentLength;
}

tstring HttpClient::dateString()
{
  ulong length= 256;
  tstring date_str(length,L'\0');

  if(!HttpQueryInfo(urlHandle_,
                    HTTP_QUERY_DATE,
                    (LPVOID)date_str.data(),
                    &length,
                    0))
  {
    throw WinInetException();
  }
  date_str.resize(length/2);
  return date_str;
}


void HttpClient::setConnectTimeOut(ulong connectTimeOut)
{
  if(!InternetSetOption(sessionHandle_,
                        INTERNET_OPTION_CONNECT_TIMEOUT,
                        &connectTimeOut,
                        sizeof(connectTimeOut)))
  {
    throw WinInetException();
  }
}


void HttpClient::setReadTimeOut(ulong readTimeOut)
{
  if(!InternetSetOption(sessionHandle_,
                        INTERNET_OPTION_RECEIVE_TIMEOUT,
                        &readTimeOut,
                        sizeof(readTimeOut)))
  {
    throw WinInetException();
  }
}

SYSTEMTIME HttpClient::date()
{
  SYSTEMTIME sysDate= {0};
  ulong length= sizeof(sysDate);
  if(!HttpQueryInfo(urlHandle_,
                    HTTP_QUERY_DATE| HTTP_QUERY_FLAG_SYSTEMTIME,
                    (LPVOID)&sysDate,
                    &length,
                    0))
  {
    throw WinInetException();
  }
  return sysDate;
}

ulong HttpClient::read(char* data, ulong size, ulong& errorCode)
{ 
  errorCode = 0;
  ulong length= 0;
  if(!InternetReadFile(urlHandle_, (LPVOID)data,size, &length))
  {
    errorCode= GetLastError();
  }
  return length;
}

ulong HttpClient::write(const char*, ulong, ulong &)
{
  return 0;
}

void HttpClient::checkErrorCode(ulong code) const
{
  if(code!=0)
    throw WinInetException(code);
}
