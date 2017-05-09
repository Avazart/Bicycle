#ifdef _MSC_VER
  #pragma once
#endif
// ---------------------------------------------------------------------------
#ifndef SerialPortInfoH
#define SerialPortInfoH
//---------------------------------------------------------------------------
#include "../Common/Global.h"
#include <vector>

#include <setupapi.h>
//#include <cfgmgr32.h>
#include <devguid.h>

#define BI_USE_ALGORITHM  // use trim from Bicycle/Algorithm
// ---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
namespace Hardware
{
	enum Id{ vid, pid, dev, ven, rev , func , subsys, prot };

	extern const std::size_t idSize;
	extern const tstring idPrefixes[];

	tstring prefix(Hardware::Id id);
}
//---------------------------------------------------------------------------
class SerialPortInfo
{
public:
	static std::size_t availablePorts(std::vector<SerialPortInfo> & ports);

	SerialPortInfo();

	tstring portName() const;
	tstring systemLocation() const;

	tstring manufacturer() const;
	tstring description() const;
	tstring friendlyName() const;
	tstring classGuid()const;
	// ulong   devType() const;

	tstring hardwareIds()const;

	uint parseId(const tstring& prefix, std::size_t length=4,bool* ok= 0)const;
	uint parseId(Hardware::Id id, std::size_t length=4,bool* ok= 0)const;

	static tstring portNameToSystemLocation(const tstring& location);
private:
	static tstring devicePortName(HDEVINFO deviceInfoSet,
																PSP_DEVINFO_DATA deviceInfoData);

  void parseIdentifiers();

private:
  tstring 	portName_;
  tstring  description_;
  tstring  manufacturer_;
	tstring  device_;
	tstring  hardwareIds_;

	tstring friendlyName_;
	ulong devType_;
	tstring classGuid_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif

