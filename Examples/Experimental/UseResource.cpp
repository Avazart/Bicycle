#include <iostream>
#include <sstream>

#include "Win/Experimental/Resource.h"
#include "Win/Fs/Path.h"
#include "Win/Process/Process.h"

using namespace Bicycle;

std::string getRcData(std::ostream& log)
{
  using namespace Bicycle;
  try
  {
    ResourceReader r;
    r.loadFile();
    r.findResource(L"ID_RESOURCE_DATA",RT_RCDATA);
    r.loadResource();
    const char* data= r.lockResource();
    return std::string(data,r.sizeResource());
  }
  catch(const Bicycle::Exception & e)
  {
    log<<"Can not get resources:\""
       << e.message()
       <<"\""<<std::endl;
  }
  return std::string();
}

bool updateRcData(const std::wstring& fileName,
                  const std::string& data,
                  std::ostream& log)
{
  using namespace Bicycle;
  try
  {
    Bicycle::ResourceUpdater r;
    r.beginUpdate(fileName);
    r.update(RT_RCDATA,L"ID_RESOURCE_DATA",(void*)data.data(),data.size());
    r.endUpdate();
    return true;
  }
  catch(const Bicycle::Exception & e)
  {
    log<<"Can not update resources:\""
       << e.message()
       <<"\""<<std::endl;
    return false;
  }
  return false;
}

template<typename CharT,typename IntT>
void strToInt(const std::basic_string<CharT>& str,IntT& value)
{
   std::basic_stringstream<CharT> ss(str);
   ss>> value;
}

template<typename IntT, typename CharT>
void intToStr(IntT value,std::basic_string<CharT>& str)
{
  std::basic_stringstream<CharT> ss(str);
  ss<< value;
  str= ss.str();
}

void waitProcessByPid(ulong pid)
{
  HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
  WaitForSingleObject(handle,INFINITE);
  CloseHandle(handle);
}

int main(int argc, char *argv[])
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  tstring appName= appModuleFileName();
  tstring base=  Path::baseName(appName);
  tstring dir=   Path::parent(appName);
  tstring tempAppName = Path::join(dir,L"~"+base+L".exe");

  if(argc>1)
  {
    ulong pid=0;
    strToInt(std::string(argv[1]),pid);

    waitProcessByPid(pid);
    Path::deleteFile(tempAppName);
    Sleep(10000);
  }

  std::string data = getRcData(std::cout);
  int count= 0;
  strToInt(data,count);
  std::cout<<"["<<count<<"]"<<std::endl;
  ++count;
  intToStr(count,data);

  Path::renameFile(appName,tempAppName);
  Path::copyFile(tempAppName,appName);

  for(int i=0; !Path::exists(appName) && i<10; ++i)
     Sleep(200);

  updateRcData(appName,data,std::cout);

  ulong pid= GetCurrentProcessId();
  tstring param;
  intToStr(pid,param);

  Process p;
  p.setShowWindow(SW_NORMAL);
  p.setCreationFlags(p.creationFlags()|CREATE_NEW_CONSOLE);
  p.start(L"",appName+L" "+param);
  p.detach();
  return 0;
}
