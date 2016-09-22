//---------------------------------------------------------------------------
#include "CriticalSection.h"

using namespace Bicycle;
//---------------------------------------------------------------------------
CriticalSection::CriticalSection()
{
	InitializeCriticalSection(&cs_);
}
//---------------------------------------------------------------------------
CriticalSection::~CriticalSection()
{
	 DeleteCriticalSection(&cs_);
};
//---------------------------------------------------------------------------
void CriticalSection::enter()
{
	 EnterCriticalSection(&cs_);
}
//---------------------------------------------------------------------------
bool CriticalSection::tryEnter()
{
  return TryEnterCriticalSection(&cs_)==1;
}
//---------------------------------------------------------------------------
void CriticalSection::leave()
{
	LeaveCriticalSection(&cs_);
};
//---------------------------------------------------------------------------
// Lockable
//---------------------------------------------------------------------------
void CriticalSection::lock()
{
	 enter();
}
//---------------------------------------------------------------------------
void CriticalSection::unlock()
{
	 leave();
}
//---------------------------------------------------------------------------
bool CriticalSection::try_lock()
{
	return tryEnter();
}
//---------------------------------------------------------------------------
