//---------------------------------------------------------------------------
#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef ConsoleH
#define ConsoleH
//---------------------------------------------------------------------------
#include "Global.h"
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
class Console
{
public:
  typedef ConsoleColor Color;

  static bool setTitle(const tstring& title);

  static bool setCp(uint codePageId);
  static bool setOutputCp(uint codePageId);
  static bool changeCp(uint codePageId);

  static HANDLE stdHandle(ulong stdHandle);
  static HWND   windowHandle();

  static bool clear();
  static bool setTextAttr(Color fg, Color bg= Color::black);
  static bool fill(short x,short y,
                   ulong length,
                   Color fg,Color bg= Color::black,
                   ulong* filled=0);

  static bool setCursorPos(short x,short y);
  static bool setCursorPos(const COORD& coord);
  static COORD cursorPos();

protected:
  static bool clear(HANDLE console);
  static bool setTextAttribute(HANDLE consoleOutput, ushort attributes);
  static bool setCursorPosition(HANDLE hConsoleOutput,COORD cursorPosition);
  static bool fillConsoleOutputAttribute(HANDLE  consoleOutput,
                                         ushort  attribute,
                                         ulong   length,
                                         COORD   writeCoord,
                                         ulong*  numberOfAttrsWritten);
};
//---------------------------------------------------------------------------
} // Bicycle
//---------------------------------------------------------------------------
#endif
