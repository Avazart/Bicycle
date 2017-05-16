#include <iostream>

#include "Win/Serial/SerialPort.h"
#include "Win/TextStream/TextStream.h"

int main()
{
  using namespace std;
  using namespace Bicycle;
  try
  {
    SerialPort serial;
    serial.setPortName(L"COM9");
    serial.setTimeOut(60000);
    serial.setBaudRate(CBR_9600);
    serial.open();
    serial.waitEvent();

    TextStream stream(&serial);
    while(true)
    {
      string line= stream.readLine();
      cout<<"\""<<line<<"\""<<endl;
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

