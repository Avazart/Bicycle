#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef FormatH
#define FormatH
//---------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "../NonCopyable.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//----------------------- stringReplace -------------------------------------
template<typename CharT>
void stringReplace(std::basic_string<CharT>& src,
                   const std::basic_string<CharT>& target,
                   const std::basic_string<CharT>& replacement)
{
  typename std::basic_string<CharT>::iterator it= src.begin();
  while(true)
  {
    it= std::search(src.begin(), src.end(), target.begin(), target.end());
    if(it==src.end())
       return;

    src.erase(it, it+ target.size());
    std::size_t d= std::distance(src.begin(),it);
    src.insert(it, replacement.begin(), replacement.end());
    it= src.begin()+d+replacement.size();
  }
}
//-------------------------- To String --------------------------------------
template< typename StringT,typename CharT>
std::basic_string<CharT>
stringToString(const StringT& value,
               int fieldWidth= 0,
               CharT fillChar=' ')
{
  std::basic_stringstream<CharT> ss;
  ss << std::setw(fieldWidth)
     << std::setfill(fillChar)
     << value;
  return ss.str();
}
//---------------------------------------------------------------------------
template< typename IntT,typename CharT>
std::basic_string<CharT>
intToString(IntT value,
            int fieldWidth = 0,
            int base = 10,
            CharT fillChar=' ')
{
  std::basic_stringstream<CharT> ss;
  ss << std::setw(fieldWidth)
     << std::setbase(base)
     << std::setfill(fillChar)
     << value;
  return ss.str();
}
//---------------------------------------------------------------------------
template< typename FloatT,typename CharT>
std::basic_string<CharT>
floatToString(FloatT value,
              int fieldWidth = 0,
              char format = 'd', // d/f/s
              int precision = -1,
              CharT fillChar=' ')
{
  std::basic_stringstream<CharT> ss;

  if(format=='f')
    ss.setf(std::ios_base::fixed);
  else if(format=='s')
    ss.setf(std::ios_base::scientific);

  ss << std::setw(fieldWidth)
     << std::setprecision(precision)
     << std::setfill(fillChar)
     << value;
  return ss.str();
}
//--------------------------------------------------------------------------------
template<typename CharT>
class Format;

template< typename CharT>
Format<CharT> format(const std::basic_string<CharT>& str,std::size_t n=0);

template< typename CharT>
Format<CharT> format(const CharT* str,std::size_t n=0);
//------------------------------- Format -----------------------------------------
template<typename CharT>
class Format: private NonCopyable
{
public:
  typedef std::basic_string<CharT> StringT;

  // format
  friend Format format<CharT>(const StringT& str, std::size_t n);
  friend Format format<CharT>(const CharT* str, std::size_t n);

  // String
  Format& arg(const StringT& a);
  Format& arg(const StringT& a, int fieldWidth, CharT fillChar=' ');

  // Int
  Format& arg(short a, int fieldWidth = 0, int base = 10, CharT fillChar=' ');
  Format& arg(unsigned short a, int fieldWidth = 0, int base = 10, CharT fillChar=' ');

  Format& arg(int a, int fieldWidth = 0, int base = 10, CharT fillChar=' ');
  Format& arg(unsigned int a,int fieldWidth = 0, int base = 10, CharT fillChar=' ');

  Format& arg(long a, int fieldWidth = 0, int base = 10, CharT fillChar=' ');
  Format& arg(unsigned long a, int fieldWidth = 0, int base = 10, CharT fillChar=' ');

  Format& arg(long long a, int fieldWidth = 0, int base = 10, CharT fillChar=' ');
  Format& arg(unsigned long long a, int fieldWidth = 0, int base = 10, CharT fillChar=' ');

  Format& arg(char a, int fieldWidth = 0, int base = 10, CharT fillChar=' ');
//  Format& arg(bool a, int fieldWidth = 0, int base = 10, CharT fillChar=' ');

  // Float
  Format& arg(float a, int fieldWidth = 0, char format = 'd', int precision = -1, CharT fillChar=' ');
  Format& arg(double a, int fieldWidth = 0, char format = 'd', int precision = -1, CharT fillChar=' ');
  Format& arg(long double a, int fieldWidth = 0, char format = 'd', int precision = -1, CharT fillChar=' ');

  // %
  Format& operator%(const StringT& a);

  template<typename T>
  Format& operator%(T a);

  operator StringT() const;

private:
  Format(const StringT& str, std::size_t firstArgNumber=0);

private:
  StringT str_;
  std::size_t argNumber_;
};
//----------------------- friend format() -----------------------------------------
template< typename CharT>
Format<CharT> format(const std::basic_string<CharT>& str,std::size_t n)
{
  return Format<CharT>(str,n);
}
//---------------------------------------------------------------------------------
template< typename CharT>
Format<CharT> format(const CharT* c_str,std::size_t n)
{
  return Format<CharT>(c_str,n);
}
//-------------------------- String ------------------------------------------------
template<typename CharT>
Format<CharT>& Format<CharT>::arg(const typename Format<CharT>::StringT& a)
{
  std::basic_stringstream<CharT> place;
  place<<'%'<< (argNumber_);
  stringReplace(str_, place.str(), a);
  ++argNumber_;
  return *this;
}

template<typename CharT>
Format<CharT>& Format<CharT>::arg(const typename Format<CharT>::StringT& a,
                                 int fieldWidth,
                                 CharT fillChar)
{
  return arg(stringToString(a,fieldWidth,fillChar));
}
//--------------------------- Int ------------------------------------------
template<typename CharT>
Format<CharT>& Format<CharT>::arg(short a, int fieldWidth, int base, CharT fillChar)
{
  return arg(intToString(a,fieldWidth,base,fillChar));
}

template<typename CharT>
Format<CharT>& Format<CharT>::arg(unsigned short a, int fieldWidth, int base, CharT fillChar)
{
  return arg(intToString(a,fieldWidth,base,fillChar));
}

template<typename CharT>
Format<CharT>& Format<CharT>::arg(int a, int fieldWidth, int base, CharT fillChar)
{
  return arg(intToString(a,fieldWidth,base,fillChar));
}

template<typename CharT>
Format<CharT>& Format<CharT>::arg(unsigned int a,int fieldWidth, int base, CharT fillChar)
{
  return arg(intToString(a,fieldWidth,base,fillChar));
}

template<typename CharT>
Format<CharT>& Format<CharT>::arg(long a, int fieldWidth, int base, CharT fillChar)
{
  return arg(intToString(a,fieldWidth,base,fillChar));
}

template<typename CharT>
Format<CharT>& Format<CharT>::arg(unsigned long a, int fieldWidth, int base, CharT fillChar)
{
  return arg(intToString(a,fieldWidth,base,fillChar));
}

template<typename CharT>
Format<CharT>& Format<CharT>::arg(long long a, int fieldWidth, int base, CharT fillChar)
{
  return arg(intToString(a,fieldWidth,base,fillChar));
}

template<typename CharT>
Format<CharT>& Format<CharT>::arg(unsigned long long a, int fieldWidth, int base, CharT fillChar)
{
  return arg(intToString(a,fieldWidth,base,fillChar));
}

template<typename CharT>
Format<CharT>& Format<CharT>::arg(char a, int fieldWidth, int base, CharT fillChar)
{
  return arg(intToString(a,fieldWidth,base,fillChar));
}

//template<typename CharT>
//Format<CharT>& Format<CharT>::arg(bool a, int fieldWidth, int base, CharT fillChar)
//{
//  return arg(intToString(a,fieldWidth,base,fillChar));
//}
//--------------------------- Float ----------------------------------------
template<typename CharT>
Format<CharT>& Format<CharT>::arg(float a,
                                 int fieldWidth,
                                 char format,
                                 int precision,
                                 CharT fillChar)
{
  return arg(floatToString(a, fieldWidth, format, precision, fillChar));
}

template<typename CharT>
Format<CharT>& Format<CharT>::arg(double a,
                                 int fieldWidth,
                                 char format,
                                 int precision,
                                 CharT fillChar)
{
  return arg(floatToString(a, fieldWidth, format, precision, fillChar));
}

template<typename CharT>
Format<CharT>& Format<CharT>::arg(long double a,
                                 int fieldWidth,
                                 char format,
                                 int precision,
                                 CharT fillChar)
{
  return arg(floatToString(a, fieldWidth, format, precision, fillChar));
}
//----------------------------------------------------------------------------
template<typename CharT>
template<typename T>
Format<CharT>& Format<CharT>::operator%(T a)
{
   return arg(a);
}

template<typename CharT>
Format<CharT>& Format<CharT>::operator%(const typename Format<CharT>::StringT& a)
{
   return arg(a);
}
//----------------------------------------------------------------------------
template<typename CharT>
Format<CharT>::operator StringT() const
{
  return str_;
}
//---------------------------------------------------------------------------
template<typename CharT>
Format<CharT>::Format(const typename Format<CharT>::StringT &str,
                      size_t firstArgNumber)
  : str_(str),
    argNumber_(firstArgNumber)
{
}
//---------------------------------------------------------------------------
} // Bicycle
//---------------------------------------------------------------------------
#endif // StringFormaterH
