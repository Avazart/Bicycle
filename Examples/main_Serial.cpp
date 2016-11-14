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
				wcout<< ports[i].portName()   << endl
						 << ports[i].hardwareIds()<< endl
						 << hex << ports[i].parseId(L"vID_")<< endl
						 << hex << ports[i].parseId(L"Prot_")<< endl
 						 << hex << ports[i].parseId(L"MI_") << endl
						 << ports[i].manufacturer()<< endl
						 << ports[i].description()<< endl
						 << ports[i].friendlyName()<< endl
						 << ports[i].classGuid()<< endl
						 << endl;
		}

//		Bi::SerialPort serial;
//		serial.setPortName(L"COM5");
//		serial.setReadTimeOut(60000);
//		serial.setBaudRate(CBR_9600);
//		serial.open();
//
//		Bi::ulong error;
//		Bi::IOStream stream(&serial);
//
//		stream.writeLine("AT+CUSD=1,\"2A192C3602\",15",error);
//		do
//		{
//			string line;
//			if(stream.readLine(line,error) != 0 )
//			{
//				cout<<"\""<<line<<"\""<<endl;
//			}
//		}
//		while(!error);
//
//		if(error == Bi::SerialError::WaitTimeOut)
//		{
//			Bi::Console::setTextAttr(Bi::ConsoleColor::blue);
//			cout<< "TimeOut!" <<endl;
//		}
//		else
//		{
//			Bi::Console::changeCp(1251);
//			Bi::Console::setTextAttr(Bi::ConsoleColor::red);
//			cout<< Bi::formatMessage(error)<<endl;
//		}
	}
	catch(const Bi::SystemException& e)
	{
		cerr<< e.what()<<endl;
	}

	getchar();
  return 0;
}

