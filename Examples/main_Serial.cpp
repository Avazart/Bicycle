#include <iostream>
#include <vector>

#include <fstream>

#include "Serial/SerialPort.h"
#include "Serial/SerialPortInfo.h"
#include "IOStream.h"
#include "Console.h"

#include "Experimental/Path.h"

int main()
{
  using namespace std;
  namespace Bi= Bicycle;

  Bi::Console::changeCp(Bi::Win1251);
  Bi::Console::setTextAttr(Bi::ConsoleColor::lime);

  try
  {
    std::vector<Bi::SerialPortInfo> ports;
    if(Bi::SerialPortInfo::availablePorts(ports))
    {
      for(std::size_t i=0; i<ports.size(); ++i)
       wcout<< L"port name: " << ports[i].portName()   << endl
            << L"hardware ids: " << ports[i].hardwareIds()<< endl
            << L"vid: "<<hex << ports[i].parseId(L"vid_")<< endl
            << L"pid: "<<hex << ports[i].parseId(L"pid_")<< endl
            << L"manufacturer:" <<ports[i].manufacturer()<< endl
            << L"description: "<<ports[i].description()<< endl
            << L"friendly name: "<<ports[i].friendlyName()<< endl
            << L"class guid: "<<ports[i].classGuid()<< endl
            << endl;
    }

    Bi::SerialPort serial;
    serial.setPortName(L"COM5");
    serial.setReadTimeOut(60000);
    serial.setBaudRate(CBR_9600);
    serial.open();

    Bi::ulong error;
    Bi::IOStream stream(&serial);
    do
    {
      string line;
      if(stream.readLine(line,error) != 0 )
      {
        cout<<"\""<<line<<"\""<<endl;
      }
    }
    while(!error);

    if(error == Bi::SerialError::WaitTimeOut)
    {
      Bi::Console::setTextAttr(Bi::ConsoleColor::blue);
      cout<< "TimeOut!" <<endl;
    }
    else
    {
      Bi::Console::changeCp(1251);
      Bi::Console::setTextAttr(Bi::ConsoleColor::red);
      cout<< Bi::formatMessage(error)<<endl;
    }
  }
  catch(const Bi::SystemException& e)
  {
    cerr<< e.what()<<endl;
  }

  getchar();
  return 0;
}

