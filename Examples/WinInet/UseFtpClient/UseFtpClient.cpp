#include <iostream>
#include <fstream>

#include "Win/WinInet/FtpClient.h"

using namespace std;
using namespace Bicycle;

bool saveFile(IODevice& client,
              const tstring& fileName);

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  try
  {
     wstring host=     L"ftp.***";
     wstring userName= L"u216745***";
     wstring password= L"qwerty";
     wstring dir=      L"/public_html/***/";
     wstring fileName= L"***.zip";

     FtpClient client;
     client.setHost(host);
     client.setUserName(userName);
     client.setPassword(password);

     client.setConnectTimeOut(30000);
     client.setReadTimeOut(30000);

     client.openSession();
     client.connect();
     client.setCurrentDir(dir);

     wcout<<L"Downloading: \""<<fileName<<L"\""<<endl;

     client.openFile(fileName);
     if(!saveFile(client,fileName))
       cout<<"Can not download file!"<<endl;

     cout<<"Done!"<<endl;
  }
  catch(const WinInetException& e)
  {
    cout<<"#"<<e.code()<<" "<< e.message() << endl;
  }
  getchar();
  return 0;
}
//---------------------------------------------------------------------------
bool saveFile(IODevice& client,
              const tstring& fileName)
{
  ofstream file(fileName.c_str(),ios::binary);
  if(!file)
     return false;

  const std::size_t buffer_size= 4096;
  char buffer[buffer_size]={0};

  int i=1;
  cout<<"[";

  while(true)
  {
    ulong length= client.read(buffer,buffer_size);
    if(length==0)
      break;

    file.write(buffer,length);

    cout<<".";
    if(++i%50==0)
       cout<<endl;
  }
  cout<<"]"<<endl;
  return true;
}
