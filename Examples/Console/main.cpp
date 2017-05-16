#include <iostream>

#include "Win/Console/Console.h"

using namespace std;
using namespace Bicycle;


void progress(int line,int maxCount);

int main()
{
  try
  {
    Console::changeCp(1251);

    Console::setTextAttr(ConsoleColor::blue,ConsoleColor::red);
    cout<<"Hello";
    Console::setTextAttr(ConsoleColor::lime,ConsoleColor::yellow);
    cout<<"world!"<<endl;
    Console::setTextAttr(ConsoleColor::lime);

    wcout <<L"Title: "<<Console::title() << endl;
    Console::setTitle(Console::originalTitle()+L" - Hello world!");

    ConsoleFont font = Console::font();

    cout <<"Font Size: "<<font.size().X<<"*"<< font.size().Y<<endl;
    wcout<<"Font Name: "<<font.faceName()<<endl;

    font.setSize(8,13);
    font.setFaceName(L"Lucida Console");

    Console::setFont(font);

    Console::setTextAttr(ConsoleColor::blue);
    progress(4,50);

    Console::clear();
  }
  catch(const SystemException& e)
  {
    cout<< e.message() << endl;
  }
  return 0;
}

void progress(int line, int maxCount)
{
  cout<< "[";
  Console::setCursorPos(maxCount+1,line);
  cout<< "]";
  Console::setCursorPos(1,line);

  int a= 1;
  int b= maxCount;
  int k= +1;
  int i= a;

  for(int s=3; s>0; --s)
  {
    for(; i>=a && i<=b; i+=k)
    {
      Console::setCursorPos(i,line);
      cout<< (k>0?"#":" ");
      Sleep(s*100);
    }
    k*= -1;
    i+= k;
    Sleep(100);
  }
}
