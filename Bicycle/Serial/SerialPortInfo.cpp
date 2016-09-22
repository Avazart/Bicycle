// ---------------------------------------------------------------------------
#include "SerialPortInfo.h"

#include <sstream>
#include <algorithm>

#include "Algorithm/Trim.h"
#include "Algorithm/IsAnyOf.h"

using namespace Bicycle;
// ---------------------------------------------------------------------------
static const GUID guidsArray[]=
{
  // Windows Ports Class GUID
  {0x4D36E978, 0xE325, 0x11CE, {0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03,	0x18}},
  // Virtual Ports Class GUID (i.e. com0com and etc)
  {0xDF799E12, 0x3C56, 0x421B, {0xB2, 0x98, 0xB6, 0xD3, 0x64, 0x2B, 0xC8,	0x78}},
  // Windows Modems Class GUID
//	{0x4D36E96D, 0xE325, 0x11CE, {0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18}},
  // Eltima Virtual Serial Port Driver v4 GUID
  {0xCC0EF009, 0xB820, 0x42F4, {0x95, 0xA9, 0x9B, 0xFA, 0x6A, 0x5A, 0xB7,  0xAB}},
  // Advanced Virtual COM Port GUID
  {0x9341CD95, 0x4371, 0x4A37, {0xA5, 0xAF, 0xFD, 0xB0, 0xA9, 0xD1, 0x96,	0x31}},
};
// ---------------------------------------------------------------------------
inline uint toUInt(const tstring& str)
{
  std::basic_stringstream<tchar> ss(str);
  uint value;
  ss>>std::hex>> value;
  return value;
}
// ---------------------------------------------------------------------------
SerialPortInfo::SerialPortInfo()
{
}
// ---------------------------------------------------------------------------
tstring SerialPortInfo::deviceRegistryProperty(HDEVINFO deviceInfoSet,
    PSP_DEVINFO_DATA deviceInfoData,
    DWORD property)
{
  DWORD dataType= 0;
  DWORD dataSize= 0;

  ::SetupDiGetDeviceRegistryProperty(deviceInfoSet,
                                     deviceInfoData,
                                     property,
                                     & dataType,
                                     NULL,
                                     0,
                                     &dataSize);

  tstring data(dataSize/sizeof(tchar),0);
  if (!::SetupDiGetDeviceRegistryProperty(
        deviceInfoSet,
        deviceInfoData,
        property,
        NULL,
        reinterpret_cast<unsigned char*>(&data[0]),
        dataSize,
        NULL) || !dataSize)
  {
    return tstring();
  }

  switch (dataType)
  {
  case REG_EXPAND_SZ:
  case REG_SZ:
  {
    data.resize((dataSize/sizeof(tchar))?(dataSize/sizeof(tchar)-1):0);
    return data;
  }
  case REG_MULTI_SZ:
  {
    std::replace(data.begin(),data.end(),TEXT('\0'),TEXT(';'));
    data = trim_copy_if(data,is_any_of(TEXT(";")));
    return data;
  }
  default:
    break;
  }
  return tstring();
}
// ---------------------------------------------------------------------------
tstring SerialPortInfo::devicePortName(HDEVINFO deviceInfoSet,
                                       PSP_DEVINFO_DATA deviceInfoData)
{
  static const tchar portKeyName[]= TEXT("PortName");

  const HKEY key= ::SetupDiOpenDevRegKey(deviceInfoSet,
                                         deviceInfoData,
                                         DICS_FLAG_GLOBAL,
                                         0,
                                         DIREG_DEV, KEY_READ);
  if(key== INVALID_HANDLE_VALUE)
    return tstring();

  DWORD dataSize;
  if(::RegQueryValueEx(key,portKeyName, NULL, NULL, NULL,&dataSize)!= ERROR_SUCCESS)
  {
    ::RegCloseKey(key);
    return tstring();
  }

  tstring data(dataSize/sizeof(tchar),0);
  if(::RegQueryValueEx( key,
                        portKeyName,
                        NULL,
                        NULL,
                        reinterpret_cast<unsigned char*>(&data[0]),
                        &dataSize)!= ERROR_SUCCESS)
  {
    ::RegCloseKey(key);
    return tstring();
  }
  ::RegCloseKey(key);

  data.resize((dataSize/sizeof(tchar))?(dataSize/sizeof(tchar)-1):0);
  return data;
}
// ---------------------------------------------------------------------------
std::size_t SerialPortInfo::availablePorts(
  std::vector<SerialPortInfo>& ports)
{
  static const int guidCount= sizeof(guidsArray)/ sizeof(guidsArray[0]);

  for (int i= 0; i< guidCount; ++i)
  {
    const HDEVINFO deviceInfoSet=
      ::SetupDiGetClassDevs(&guidsArray[i], NULL, 0, DIGCF_PRESENT);

    if (deviceInfoSet== INVALID_HANDLE_VALUE)
      return ports.size();

    SP_DEVINFO_DATA deviceInfoData= {0};
    deviceInfoData.cbSize= sizeof(deviceInfoData);

    DWORD index= 0;

    while(::SetupDiEnumDeviceInfo(deviceInfoSet, index++, &deviceInfoData))
    {
      SerialPortInfo serialPortInfo;

      tstring portName= devicePortName(deviceInfoSet, &deviceInfoData);
      if (portName.empty()|| (portName.find(TEXT("LPT"))!= tstring::npos))
        continue;

      serialPortInfo.portName_= portName;
      serialPortInfo.device_ =  portNameToSystemLocation(portName);

      serialPortInfo.description_=
        deviceRegistryProperty(deviceInfoSet,&deviceInfoData, SPDRP_DEVICEDESC);

      serialPortInfo.manufacturer_=
        deviceRegistryProperty(deviceInfoSet,	&deviceInfoData, SPDRP_MFG);

      serialPortInfo.hardwareIds_=
        deviceRegistryProperty(deviceInfoSet, &deviceInfoData,SPDRP_HARDWAREID);

      serialPortInfo.parseIdentifiers();

      ports.push_back(serialPortInfo);
    }
    ::SetupDiDestroyDeviceInfoList(deviceInfoSet);
  }
  return ports.size();
}
// ---------------------------------------------------------------------------
void SerialPortInfo::parseIdentifiers()
{
  static const tstring usbVendorIdentifierPrefix(TEXT("VID_"));
  static const tstring usbProductIdentifierPrefix(TEXT("PID_"));
  static const tstring pciVendorIdentifierPrefix(TEXT("VEN_"));
  static const tstring pciDeviceIdentifierPrefix(TEXT("DEV_"));

  static const int vendorIdentifierSize=  4;
  static const int productIdentifierSize= 4;

  // VID/VEN
  std::size_t p= hardwareIds_.find(usbVendorIdentifierPrefix);
  if(p!= tstring::npos)
  {
    vendorIdentifier_=
      toUInt(hardwareIds_.substr(p+usbVendorIdentifierPrefix.size(),
                                 vendorIdentifierSize));
  }
  else
  {
    p= hardwareIds_.find(pciVendorIdentifierPrefix);
    if(p!= tstring::npos)
      vendorIdentifier_=
        toUInt(
          hardwareIds_.substr(p+ pciVendorIdentifierPrefix.size(),
                              vendorIdentifierSize));
  }

  // PID/DEV
  p= hardwareIds_.find(usbProductIdentifierPrefix);
  if(p!= tstring::npos)
  {
    productIdentifier_=
      toUInt(
        hardwareIds_.substr(p+ usbProductIdentifierPrefix.size(),
                            productIdentifierSize));
  }
  else
  {
    p= hardwareIds_.find(pciDeviceIdentifierPrefix);
    if(p!= tstring::npos)
      productIdentifier_=
        toUInt(hardwareIds_.substr(p+ pciDeviceIdentifierPrefix.size(),
                                   productIdentifierSize));
  }
}
// ---------------------------------------------------------------------------
tstring SerialPortInfo::portName() const
{
  return portName_;
}
// ---------------------------------------------------------------------------
tstring SerialPortInfo::description() const
{
  return description_;
}
// ---------------------------------------------------------------------------
tstring SerialPortInfo::manufacturer() const
{
  return manufacturer_;
}
// ---------------------------------------------------------------------------
uint SerialPortInfo::vendorIdentifier() const
{
  return vendorIdentifier_;
}
// ---------------------------------------------------------------------------
uint SerialPortInfo::productIdentifier() const
{
  return productIdentifier_;
}
// ---------------------------------------------------------------------------
tstring SerialPortInfo::systemLocation() const
{
  return device_;
}
// ---------------------------------------------------------------------------
tstring SerialPortInfo::hardwareIds()const
{
  return hardwareIds_;
}
// ---------------------------------------------------------------------------
tstring SerialPortInfo::portNameToSystemLocation(const tstring& location)
{
  static const tstring defaultPathPrefix= TEXT("\\\\.\\");
  if(location.find(defaultPathPrefix)==tstring::npos)
    return defaultPathPrefix+location;

  return location;
}
// ---------------------------------------------------------------------------
