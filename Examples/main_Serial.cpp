#include <iostream>
#include <vector>

#include "Serial/SerialPort.h"
#include "Serial/SerialPortInfo.h"
#include "IOStream.h"
#include "Console.h"

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
        wcout<< ports[i].portName()<<L" "<< ports[i].hardwareIds()<< endl;
    }

    Bi::SerialPort serial;
    serial.setPortName(L"COM5");
		serial.setReadTimeOut(30000);
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

