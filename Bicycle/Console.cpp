//---------------------------------------------------------------------------
#include "Console.h"
//---------------------------------------------------------------------------
//  http://prog-cpp.ru/api-console/
//  https://msdn.microsoft.com/en-us/library/windows/desktop/ms682073(v=vs.85).aspx
//---------------------------------------------------------------------------
using namespace Bicycle;
//---------------------------------------------------------------------------
const std::string colorNames[16] =
{
  "black", "navy", "green", "teal","maroon", "purple", "olive",  "silver",
  "gray", "blue",  "lime", "aqua",  "red", "fuchia", "yellow", "white"
};
//---------------------------------------------------------------------------
ConsoleColor::ConsoleColor(uchar value)
  :value_(value)
{
}
//---------------------------------------------------------------------------
ConsoleColor::ConsoleColor(const std::string& name)
  :value_(0)
{
  for(int i=0; i<16; ++i)
    if(colorNames[i]==name)
      value_= i;
}
//---------------------------------------------------------------------------
uchar ConsoleColor::value()const
{
  return value_;
}
//---------------------------------------------------------------------------
std::string ConsoleColor::name()const
{
  return (value_<16)?colorNames[value_]: std::string();
}
//---------------------------------------------------------------------------
bool Console::setCp(uint codePageId)
{
  return SetConsoleCP(codePageId)==1;
}
//---------------------------------------------------------------------------
bool Console::setOutputCp(uint codePageId)
{
  return SetConsoleOutputCP(codePageId)==1;
}
//---------------------------------------------------------------------------
bool Console::changeCp(uint codePageId)
{
  return setCp(codePageId) && setOutputCp(codePageId);
}
//---------------------------------------------------------------------------
bool Console::setTitle(const tstring& title)
{
  return SetConsoleTitle(title.c_str())==1;
}
//---------------------------------------------------------------------------
/*
		STD_INPUT_HANDLE = -10;  // устройство ввода
		STD_OUTPUT_HANDLE = -11;  // устройство вывода
		STD_ERROR_HANDLE = -12;  // ошибка
*/
//---------------------------------------------------------------------------
HANDLE Console::stdHandle(ulong stdHandle)
{
  return GetStdHandle(stdHandle);
}
//---------------------------------------------------------------------------
HWND Console::windowHandle()
{
  return GetConsoleWindow();
}
//---------------------------------------------------------------------------
bool Console::clear(HANDLE consoleHandle)
{
  //  https://support.microsoft.com/ru-ru/kb/99261
  COORD coordScreen = { 0, 0 };    /* here's where we'll home the
                                        cursor */
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
  DWORD dwConSize;                 /* number of character cells in
                                        the current buffer */

  /* get the number of character cells in the current buffer */
  if(!GetConsoleScreenBufferInfo( consoleHandle, &csbi))
    return false;

  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

  /* fill the entire screen with blanks */
  if(!FillConsoleOutputCharacter( consoleHandle, (TCHAR) ' ',
                                  dwConSize, coordScreen, &cCharsWritten ))
    return false;

  /* get the current text attribute */
  if(!GetConsoleScreenBufferInfo( consoleHandle, &csbi))
    return false;

  /* now set the buffer's attributes accordingly */
  if(!FillConsoleOutputAttribute( consoleHandle, csbi.wAttributes,
                                  dwConSize, coordScreen, &cCharsWritten ))
    return false;

  /* put the cursor at (0, 0) */
  if(!SetConsoleCursorPosition(consoleHandle,coordScreen))
    return false;

  return true;
}
//---------------------------------------------------------------------------
bool Console::setTextAttribute(HANDLE consoleOutput, ushort attributes)
{
  return SetConsoleTextAttribute(consoleOutput,attributes)==1;
}

//---------------------------------------------------------------------------
bool Console::setCursorPosition(HANDLE hConsoleOutput,COORD cursorPosition)
{
  return SetConsoleCursorPosition(hConsoleOutput,cursorPosition)==1;
}
//---------------------------------------------------------------------------
bool Console::fillConsoleOutputAttribute(HANDLE  consoleOutput,
    ushort  attribute,
    ulong   length,
    COORD   writeCoord,
    LPDWORD numberOfAttrsWritten)
{
  return
    FillConsoleOutputAttribute(consoleOutput,attribute,length,writeCoord,numberOfAttrsWritten)==1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
bool Console::clear()
{
  return Console::clear(stdHandle(STD_OUTPUT_HANDLE));
}
//---------------------------------------------------------------------------
bool Console::setTextAttr(Color fg,Color bg)
{
  return
    setTextAttribute(stdHandle(STD_OUTPUT_HANDLE),fg.value()|(bg.value()<<4));
}
//---------------------------------------------------------------------------
bool Console::setCursorPos(short x,short y)
{
  COORD coord= {x,y};
  return setCursorPosition(stdHandle(STD_OUTPUT_HANDLE),coord);
}
//---------------------------------------------------------------------------
bool Console::fill(short x,short y,ulong length,
                   Color fg,Color bg,
                   ulong* filled)
{
  COORD coord= {x,y};
  ulong notused;
  return
    fillConsoleOutputAttribute(stdHandle(STD_OUTPUT_HANDLE),
                               fg.value()|(bg.value()<<4),
                               length,
                               coord,
                               filled?filled:&notused);
}
//---------------------------------------------------------------------------
COORD Console::cursorPos()
{
  CONSOLE_SCREEN_BUFFER_INFO Info;
  GetConsoleScreenBufferInfo(stdHandle(STD_OUTPUT_HANDLE), &Info);
  return Info.dwCursorPosition;
}
//---------------------------------------------------------------------------
