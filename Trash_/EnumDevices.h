// ---------------------------------------------------------------------------
#ifndef EnumDevicesH
#define EnumDevicesH
// ---------------------------------------------------------------------------
#include "Global.h"
#include "SystemException.h"

#include <vector>

#include <setupapi.h>
#include <cfgmgr32.h>
#include <devguid.h>
// ---------------------------------------------------------------------------
namespace My
{
// ---------------------------------------------------------------------------
 class Device
 {
	public:
			typedef std::vector<Device> DeviceVector;

			Device(const SP_DEVINFO_DATA& data, const tstring& instId);

			tstring instId() const ;
			unsigned long instHandle() const ;
			GUID classGuid() const ;

			static void enumerate(DeviceVector& devices,
														const GUID& guid,
														const tstring& enumerator= tstring());

			static void enumerate2(DeviceVector& devices,
														 const GUID& guid,
														 const tstring& enumerator= tstring());

			std::string test;

		protected:
			// SP_DEVINFO_DATA& data();
			// void setInstId(const tstring& instId);

		private :
			SP_DEVINFO_DATA data_;
			tstring instId_;
 };
	// ---------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------
#endif
