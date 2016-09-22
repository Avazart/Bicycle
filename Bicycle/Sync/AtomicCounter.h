#ifdef _MSC_VER
  #pragma once
#endif
//---------------------------------------------------------------------------
#ifndef AtomicCounterH
#define AtomicCounterH
//---------------------------------------------------------------------------
#include <windows.h>
#include "NonCopyable.h"
//---------------------------------------------------------------------------
namespace Bicycle
{
//---------------------------------------------------------------------------
class AtomicCounter: private NonCopyable
{
	 public:
		typedef LONG ValueType;

		explicit AtomicCounter(ValueType initialValue=0)
      :value_(initialValue){}

		ValueType increment()
			{ return InterlockedIncrement(&value_); }
		ValueType decrement()
			{ return InterlockedDecrement(&value_); }
		ValueType exchange(ValueType newValue)
			{ return InterlockedExchange(&value_,newValue); }

		ValueType load() const
			{ return value_; }
		ValueType store(ValueType newValue)
			{ return exchange(newValue); }

		operator ValueType()const{ return load(); }
		ValueType operator=(ValueType value)
			{ store(value); return value; }

	 private:
			volatile ValueType value_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
