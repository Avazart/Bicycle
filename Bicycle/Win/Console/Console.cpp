//---------------------------------------------------------------------------
#include "Console.h"

#include <iostream>
//---------------------------------------------------------------------------
//  http://prog-cpp.ru/api-console/
//  https://msdn.microsoft.com/en-us/library/windows/desktop/ms682073(v=vs.85).aspx
//---------------------------------------------------------------------------
using namespace Bicycle;
//---------------------------------------------------------------------------
//   Console
//---------------------------------------------------------------------------
void Console::setTitle(const tstring& title)
{
  if(!SetConsoleTitle(title.c_str()))
    throw SystemException();
}
//---------------------------------------------------------------------------
tstring Console::title()
{
  tstring text(256,TEXT('\0'));
  ulong size= GetConsoleTitle(&text[0],text.size()*sizeof(tchar));
  if(!size)
    throw SystemException();

  if(size+1>text.size())
  {
    text.resize(size+1);
    size= GetConsoleTitle(&text[0],text.size()*sizeof(tchar));
    if(!size)
      throw SystemException();
  }

  text.resize(size);
  return text;
}
//---------------------------------------------------------------------------
tstring Console::originalTitle()
{
  tstring text(256,TEXT('\0'));
  ulong size= GetConsoleOriginalTitle(&text[0],text.size());
  if(!size)
    throw SystemException();

  if(size+1>text.size())
  {
    text.resize(size+1);
    size= GetConsoleOriginalTitle(&text[0],text.size());
    if(!size)
      throw SystemException();
  }

  text.resize(size);
  return text;
}
//---------------------------------------------------------------------------
void Console::setCp(uint codePageId)
{
  if(!SetConsoleCP(codePageId))
     throw SystemException();
}
//---------------------------------------------------------------------------
void Console::setOutputCp(uint codePageId)
{
  if(!SetConsoleOutputCP(codePageId))
     throw SystemException();
}
//---------------------------------------------------------------------------
void Console::changeCp(uint codePageId)
{
  setCp(codePageId);
  setOutputCp(codePageId);
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
void Console::clear(HANDLE consoleHandle)
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
    throw SystemException();

  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

  /* fill the entire screen with blanks */
  if(!FillConsoleOutputCharacter( consoleHandle, (TCHAR) ' ',
                                  dwConSize, coordScreen, &cCharsWritten ))
    throw SystemException();

  /* get the current text attribute */
  if(!GetConsoleScreenBufferInfo( consoleHandle, &csbi))
    throw SystemException();

  /* now set the buffer's attributes accordingly */
  if(!FillConsoleOutputAttribute( consoleHandle, csbi.wAttributes,
                                  dwConSize, coordScreen, &cCharsWritten ))
    throw SystemException();

  /* put the cursor at (0, 0) */
  if(!SetConsoleCursorPosition(consoleHandle,coordScreen))
    throw SystemException();
}
//---------------------------------------------------------------------------
void Console::setTextAttribute(HANDLE consoleOutput, ushort attributes)
{
  if(!SetConsoleTextAttribute(consoleOutput,attributes))
    throw SystemException();
}
//---------------------------------------------------------------------------
void Console::setCursorPosition(HANDLE hConsoleOutput,COORD cursorPosition)
{
  if(!SetConsoleCursorPosition(hConsoleOutput,cursorPosition))
    throw SystemException();
}
//---------------------------------------------------------------------------
void Console::fillConsoleOutputAttribute(HANDLE  consoleOutput,
    ushort  attribute,
    ulong   length,
    COORD   writeCoord,
    LPDWORD numberOfAttrsWritten)
{
  if(!FillConsoleOutputAttribute(consoleOutput,
                                 attribute,
                                 length,
                                 writeCoord,
                                 numberOfAttrsWritten))
    throw SystemException();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void Console::clear()
{
  Console::clear(stdHandle(STD_OUTPUT_HANDLE));
}
//---------------------------------------------------------------------------
void Console::setTextAttr(Color fg,Color bg)
{
  setTextAttribute(stdHandle(STD_OUTPUT_HANDLE),fg.value()|(bg.value()<<4));
}
//---------------------------------------------------------------------------
void Console::setCursorPos(const COORD& coord)
{
  setCursorPosition(stdHandle(STD_OUTPUT_HANDLE),coord);
}
//---------------------------------------------------------------------------
void Console::setCursorPos(short x,short y)
{
  COORD coord= {x,y};
  setCursorPos(coord);
}
//---------------------------------------------------------------------------
void Console::fill(short x,short y,ulong length,
                   Color fg,Color bg,
                   ulong* filled)
{
  COORD coord= {x,y};
  ulong notused;
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
Console::Font Console::font(bool maximumWindow)
{
  ConsoleFont font_;
  if(!GetCurrentConsoleFontEx(stdHandle(STD_OUTPUT_HANDLE),
                           maximumWindow,
                           &font_.data()))
    throw SystemException();

  return font_;
}
//---------------------------------------------------------------------------
void Console::setFont(const ConsoleFont& font,bool maximumWindow)
{
  if(!SetCurrentConsoleFontEx(stdHandle(STD_OUTPUT_HANDLE),
                              maximumWindow,
                              &const_cast<CONSOLE_FONT_INFOEX&>(font.data())))
    throw SystemException();
}
//---------------------------------------------------------------------------
COORD Console::fontSize(ulong fontIndex)
{
  COORD coord= GetConsoleFontSize(stdHandle(STD_OUTPUT_HANDLE),fontIndex);
  if(coord.X==coord.Y==0)
    throw SystemException();
  return coord;
}
//---------------------------------------------------------------------------
ulong Console::displayMode()
{
  ulong displayMode=0;
  if(!GetConsoleDisplayMode(&displayMode))
    throw SystemException();
  return displayMode;
}
//---------------------------------------------------------------------------
void Console::setDisplayMode(ulong displayMode)
{
  COORD newScreenBufferDimensions={0,0};
  if(!SetConsoleDisplayMode(stdHandle(STD_OUTPUT_HANDLE),
                        displayMode,
                        &newScreenBufferDimensions))
    throw SystemException();
}
//---------------------------------------------------------------------------
Console::Selection Console::selection()
{
  Console::Selection selection;
  if(!GetConsoleSelectionInfo(&selection.data()))
     throw SystemException();
  return selection;
}
//---------------------------------------------------------------------------
//   Console  Color
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
//   Console Font
//---------------------------------------------------------------------------
ConsoleFont::ConsoleFont()
{
  ZeroMemory(&font_,sizeof(CONSOLE_FONT_INFOEX));
  font_.cbSize= sizeof(CONSOLE_FONT_INFOEX);
}
//---------------------------------------------------------------------------
COORD ConsoleFont::size() const
{
  return font_.dwFontSize;
}
//---------------------------------------------------------------------------
void ConsoleFont::setSize(const COORD &size)
{
  font_.dwFontSize= size;
}
//---------------------------------------------------------------------------
void ConsoleFont::setSize(short x, short y)
{
  COORD coord={x,y};
  setSize(coord);
}
//---------------------------------------------------------------------------
ulong ConsoleFont::index() const
{
  return font_.nFont;
}
//---------------------------------------------------------------------------
void ConsoleFont::setIndex(ulong index)
{
  font_.nFont= index;
}
//---------------------------------------------------------------------------
uint ConsoleFont::family() const
{
  return font_.FontFamily;
}
//---------------------------------------------------------------------------
void ConsoleFont::setFamily(uint family)
{
  font_.FontFamily= family;
}
//---------------------------------------------------------------------------
uint ConsoleFont::weight() const
{
  return font_.FontWeight;
}
//---------------------------------------------------------------------------
void ConsoleFont::setWeight(uint weight)
{
  font_.FontWeight= weight;
}
//---------------------------------------------------------------------------
std::wstring ConsoleFont::faceName() const
{
  return std::wstring(font_.FaceName);
}
//---------------------------------------------------------------------------
void ConsoleFont::setFaceName(const std::wstring &name)
{
  #ifdef _MSC_VER
     wcsncpy_s(font_.FaceName,name.c_str(),name.size());
  #else
     wcsncpy(font_.FaceName,name.c_str(),name.size());
  #endif
}
//---------------------------------------------------------------------------
CONSOLE_FONT_INFOEX &ConsoleFont::data()
{
  return font_;
}
//---------------------------------------------------------------------------
const CONSOLE_FONT_INFOEX &ConsoleFont::data() const
{
  return font_;
}
//---------------------------------------------------------------------------
ulong ConsoleFont::dataSize() const
{
  return font_.cbSize;
}
//---------------------------------------------------------------------------
//      Console Selection
//---------------------------------------------------------------------------
ConsoleSelection::ConsoleSelection()
{

}

ulong ConsoleSelection::flags() const
{
  return selection_.dwFlags;
}

const COORD &ConsoleSelection::anchor() const
{
  return selection_.dwSelectionAnchor;
}

const SMALL_RECT &ConsoleSelection::rect() const
{
  return selection_.srSelection;
}

CONSOLE_SELECTION_INFO &ConsoleSelection::data()
{
  return selection_;
}

const CONSOLE_SELECTION_INFO &ConsoleSelection::data() const
{
  return selection_;
}

ulong ConsoleSelection::dataSize() const
{
  return sizeof(CONSOLE_SELECTION_INFO);
}
