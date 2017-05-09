#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef EncodingH
#define EncodingH
//---------------------------------------------------------------------------
#include "Win/Common/Global.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
  std::string encode(const std::string& in,
                     uint sourceCodePage,
                     uint targetCodePage);

  Strings systemCodePages(ulong flags= CP_SUPPORTED); //CP_INSTALLED // not thread-safe

  std::string  fromOEM(const std::string& in);
  std::string  fromUTF8(const std::string& in);
}
//---------------------------------------------------------------------------
#endif
