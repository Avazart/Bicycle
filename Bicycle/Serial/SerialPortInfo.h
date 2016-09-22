#ifdef _MSC_VER
#pragma once
#endif
// ---------------------------------------------------------------------------
#ifndef SerialPortInfoH
#define SerialPortInfoH
//---------------------------------------------------------------------------
#include "Global.h"
#include <vector>

#include <setupapi.h>
//#include <cfgmgr32.h>
#include <devguid.h>
// ---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
class SerialPortInfo
{
public:
  SerialPortInfo();

  static std::size_t availablePorts(std::vector<SerialPortInfo> & ports);

  tstring 	portName() const;
  tstring 	systemLocation() const;

  tstring 	manufacturer() const;
  tstring 	description() const;

  uint vendorIdentifier() const;
  uint productIdentifier() const;

  tstring hardwareIds()const;

private:
  static tstring devicePortName(HDEVINFO deviceInfoSet,
                                PSP_DEVINFO_DATA deviceInfoData);

  static tstring deviceRegistryProperty(HDEVINFO deviceInfoSet,
                                        PSP_DEVINFO_DATA deviceInfoData,
                                        DWORD property);

  static tstring portNameToSystemLocation(const tstring& location);

  void parseIdentifiers();

private:
  tstring 	portName_;
  tstring  description_;
  tstring  manufacturer_;
  tstring  device_;

  uint vendorIdentifier_;
  uint	productIdentifier_;

  tstring hardwareIds_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif

