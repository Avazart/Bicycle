//---------------------------------------------------------------------------
#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef CriticalSectionH
#define CriticalSectionH
//---------------------------------------------------------------------------
#include <windows.h>
#include "../NonCopyable.h"
#include "LockGuard.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
class CriticalSection: private NonCopyable
{
	public:
		CriticalSection();
		~CriticalSection();

		void enter();
		bool tryEnter();
		void leave();

		// Lockable
		void lock();
		void unlock();
		bool try_lock();

	private:
		CRITICAL_SECTION cs_;
};
//---------------------------------------------------------------------------
typedef LockGuard<CriticalSection> CSGuard;
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
