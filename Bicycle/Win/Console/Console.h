//---------------------------------------------------------------------------
#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef ConsoleH
#define ConsoleH
//---------------------------------------------------------------------------
#include "Win/Common/Global.h"
#include "Win/Common/Exception.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
class ConsoleColor
{
public:

enum:
  uchar
  {
    black= 0,
    navy=  FOREGROUND_BLUE,   // 1
    green= FOREGROUND_GREEN|FOREGROUND_INTENSITY, //2
    teal=  3,
    maroon= FOREGROUND_RED,  // 4
    purple= 5,
    olive=  6,
    silver= 7,
    gray=   8,
    blue=  FOREGROUND_BLUE|FOREGROUND_INTENSITY, // 9
    lime=  10,
    aqua=  11,
    red=   FOREGROUND_RED|FOREGROUND_INTENSITY, // 12
    fuchia = 13,
    yellow= 14,
    white= 15
  };

  ConsoleColor(uchar value);
  ConsoleColor(const std::string& name);
  uchar value()const;
  std::string name()const;

private:
  uchar value_;
};
//---------------------------------------------------------------------------
class ConsoleFont
{
   public:
     ConsoleFont();

     COORD size()const;
     void setSize(const COORD& size);
     void setSize(short x,short y);

     ulong index()const;
     void  setIndex(ulong index);

     uint family()const;
     void setFamily(uint family);

     uint weight()const;
     void setWeight(uint weight);

     std::wstring faceName()const;
     void setFaceName(const std::wstring& name); // "Lucida Console"

     CONSOLE_FONT_INFOEX& data();
     const CONSOLE_FONT_INFOEX& data()const;
     ulong dataSize()const;

   private:
     CONSOLE_FONT_INFOEX font_;
};
//---------------------------------------------------------------------------
class ConsoleSelection
{
public:
  ConsoleSelection();

  ulong flags()const;
  const COORD& anchor()const;
  const SMALL_RECT &rect()const;

  CONSOLE_SELECTION_INFO& data();
  const CONSOLE_SELECTION_INFO& data()const;
  ulong dataSize()const;
private:
  CONSOLE_SELECTION_INFO selection_;
};
//---------------------------------------------------------------------------
class Console
{
public:
  typedef ConsoleColor Color;
  typedef ConsoleFont Font;
  typedef ConsoleSelection Selection;

  static void setTitle(const tstring& title);
  static tstring title();
  static tstring originalTitle();

  static void setCp(uint codePageId);
  static void setOutputCp(uint codePageId);
  static void changeCp(uint codePageId);

  static HANDLE stdHandle(ulong stdHandle);
  static HWND   windowHandle();

  static void clear();

  static void setTextAttr(Color fg=Color::green, Color bg= Color::black);

  static void fill(short x,short y,
                   ulong length,
                   Color fg,Color bg= Color::black,
                   ulong* filled=0);

  static void  setCursorPos(short x,short y);
  static void  setCursorPos(const COORD& coord);
  static COORD cursorPos();

  static Font font(bool maximumWindow=false);
  static void setFont(const ConsoleFont &font, bool maximumWindow=false);

  static COORD fontSize(ulong fontIndex);

  static ulong displayMode(); // CONSOLE_FULLSCREEN, CONSOLE_FULLSCREEN_HARDWARE
  static void setDisplayMode(ulong displayMode);

  static Selection selection();

protected:
  static void clear(HANDLE console);
  static void setTextAttribute(HANDLE consoleOutput, ushort attributes);
  static void setCursorPosition(HANDLE hConsoleOutput,COORD cursorPosition);
  static void fillConsoleOutputAttribute(HANDLE  consoleOutput,
                                         ushort  attribute,
                                         ulong   length,
                                         COORD   writeCoord,
                                         ulong*  numberOfAttrsWritten);
};
//---------------------------------------------------------------------------
} // Bicycle
//---------------------------------------------------------------------------
#endif
