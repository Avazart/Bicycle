// ---------------------------------------------------------------------------
#pragma hdrstop
#include "MutexLocker.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
// ---------------------------------------------------------------------------
MutexLoker::MutexLoker(const HANDLE& mutex, DWORD ms):mutex_(mutex)
{
	const DWORD rc= WaitForSingleObject(mutex_, ms);
	switch (rc)
	{
	case WAIT_OBJECT_0:
		locked_= true;
		break;
		// case WAIT_TIMEOUT:  locked_= false; break;
	case WAIT_FAILED:
		locked_= false;
		throw std::runtime_error("Lock Error!");
		break;
		// case WAIT_ABANDONED:locked_= false; break;
	default:
		locked_= false;
		break;
	}
};
// ---------------------------------------------------------------------------
/*virtual*/ MutexLoker::~MutexLoker()
{
	if (locked_)
		ReleaseMutex(mutex_);
}
// ---------------------------------------------------------------------------
bool MutexLoker::loked() const
{
	return locked_;
};
// ---------------------------------------------------------------------------
