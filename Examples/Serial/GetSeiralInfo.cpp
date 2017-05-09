#include <iostream>
#include <vector>

#include "Win/Serial/SerialPortInfo.h"
#include "Win/Common/Exception.h"

int main()
{
  using namespace std;
  using namespace Bicycle;

  setlocale(0,""); // Обязательно иначе будут проблемы
                   // с описанием устройств в кириллице
  try
  {
    // Перечисляем доступные COM-порты и выводим информацию о них:
    vector<SerialPortInfo> ports;
    if(SerialPortInfo::availablePorts(ports))
    {
        for(size_t i=0; i<ports.size(); ++i)
        {
          wcout<< L"port name: " << ports[i].portName() << endl;
          wcout<< L"hardware ids: "<< ports[i].hardwareIds()<< endl;
          wcout<< L"vid: "<<hex << ports[i].parseId(L"vid_")<< endl;
          wcout<< L"pid: "<<hex << ports[i].parseId(L"pid_")<< endl;
          wcout<< L"manufacturer:" <<ports[i].manufacturer()<< endl;
          wcout<< L"description: "<< ports[i].description() << endl;
          wcout<< L"friendly name: "<<ports[i].friendlyName()<< endl;
          wcout<< L"class guid: "<<ports[i].classGuid()<< endl;
          wcout<<endl;
        }
    }
  }
  catch(const Exception& e)
  {
      SetConsoleCP(1251);
      SetConsoleOutputCP(1251);
      cerr<< e.message()<<endl;
  }

  getchar();
  return 0;
}

