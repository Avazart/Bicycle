#include "FtpClient.h"

using namespace Bicycle;
//-----------------------------------------------------------------------------------------
FtpClient::FtpClient()
  :internetHandle_(0),
   connectionHandle_(0),
   transferHandle_(0),
   port_(INTERNET_DEFAULT_FTP_PORT),
   passive_(true),
   transferType_(FTP_TRANSFER_TYPE_BINARY)
{
}


FtpClient::~FtpClient()
{
  closeSession();
  closeUrl();
  closeTransfer();
}

void FtpClient::closeSession()
{
  if(internetHandle_)
  {
    InternetCloseHandle(internetHandle_);
    internetHandle_= 0;
  }
}

void FtpClient::closeUrl()
{
  if(connectionHandle_)
  {
    InternetCloseHandle(connectionHandle_)	;
    connectionHandle_= 0;
  }
}

void FtpClient::closeTransfer()
{
  if(transferHandle_)
  {
    InternetCloseHandle(transferHandle_);
    connectionHandle_= 0;
  }
}

void FtpClient::setHost(const tstring &host)
{
  host_= host;
}

void FtpClient::setPort(unsigned port)
{
  port_ = port;
}

void FtpClient::setUserName(const tstring &userName)
{
  userName_= userName;
}

void FtpClient::setPassword(const tstring &password)
{
  password_= password;
}

void FtpClient::setPassiveMode(bool passive)
{
  passive_= passive;
}

void FtpClient::setTransferType(ulong transferTypeFlags)
{
  transferType_= transferTypeFlags;
}

void FtpClient::openSession(const tstring& userAgent)
{

  closeSession();
  internetHandle_=
      InternetOpen(userAgent.c_str(),
                   INTERNET_OPEN_TYPE_PRECONFIG,
                   NULL,
                   NULL,
                   0);

  if(!internetHandle_)
    throw WinInetException();
}

void FtpClient::connect()
{
  connectionHandle_=
      InternetConnect(internetHandle_,
                      host_.c_str(),
                      port_,
                      userName_.c_str(),
                      password_.c_str(),
                      INTERNET_SERVICE_FTP,
                      passive_?INTERNET_FLAG_PASSIVE:0,
                      0);

  if(!connectionHandle_)
    throw WinInetException();
}

void FtpClient::setCurrentDir(const tstring &dir)
{
  if(!FtpSetCurrentDirectory(connectionHandle_,dir.c_str()))
  {
    throw WinInetException();
  }
}


void FtpClient::openFile(const tstring &fileName)
{
  transferHandle_ =
     FtpOpenFile( connectionHandle_,
                  fileName.c_str(),
                  GENERIC_READ,
                  transferType_,
                  0);

  if(!transferHandle_)
  {
    throw WinInetException();
  }
}

void FtpClient::setConnectTimeOut(ulong connectTimeOut)
{
  if(!InternetSetOption(internetHandle_,
                        INTERNET_OPTION_CONNECT_TIMEOUT,
                        &connectTimeOut,
                        sizeof(connectTimeOut)))
  {
    throw WinInetException();
  }
}


void FtpClient::setReadTimeOut(ulong readTimeOut)
{
  if(!InternetSetOption(internetHandle_,
                        INTERNET_OPTION_RECEIVE_TIMEOUT,
                        &readTimeOut,
                        sizeof(readTimeOut)))
  {
    throw WinInetException();
  }
}


ulong FtpClient::read(char* data, ulong size)
{ 
  ulong length= 0;
  if(!InternetReadFile(transferHandle_, (LPVOID)data,size, &length))
     throw WinInetException();
  return length;
}

ulong FtpClient::write(const char*, ulong)
{
  return 0;
}


