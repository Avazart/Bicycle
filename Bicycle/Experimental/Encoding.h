#pragma ones
//---------------------------------------------------------------------------
#ifndef EncodingH
#define EncodingH
//---------------------------------------------------------------------------
#include "Global.h"
#include <vector>
//---------------------------------------------------------------------------
namespace Bicycle
{
	std::string encode(const std::string& in,
										 uint sourceCodePage,
										 uint targetCodePage);

	std::vector<tstring> systemCodePages(ulong flags= CP_SUPPORTED); //CP_INSTALLED, CP_SUPPORTED

	std::string  fromOEM(const std::string& in);
	std::string  fromUTF8(const std::string& in);
}
//---------------------------------------------------------------------------
#endif
