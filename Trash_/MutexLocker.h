//---------------------------------------------------------------------------

#ifndef MutexLockerH
#define MutexLockerH
// ---------------------------------------------------------------------------
#include <windows.h>
#include <stdexcept>
// ---------------------------------------------------------------------------
class MutexLoker
{
	private: // not copyable
		MutexLoker(const MutexLoker&);
		MutexLoker& operator= (const MutexLoker&);
	public:
		MutexLoker(const HANDLE& mutex,DWORD ms);
		virtual ~MutexLoker();
		bool loked()const;
	private:
		HANDLE mutex_;
		bool locked_;
};
//---------------------------------------------------------------------------
#endif
