//---------------------------------------------------------------------------
#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef LockGuardH
#define LockGuardH
//---------------------------------------------------------------------------
#include "../NonCopyable.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
template<typename Lockable>
class LockGuard: private NonCopyable
{
 public:
	typedef Lockable LockableType;

	explicit LockGuard(LockableType& obj,bool locked=true)
		:obj_(obj)
	{
		if(locked)
			obj_.lock();
	};

	~LockGuard()
	{
		obj_.unlock();
	}	
private:
	 LockableType& obj_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
