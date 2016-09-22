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

    explicit AtomicCounter(ValueType initialValue=0);

    ValueType increment();
    ValueType decrement();

    ValueType exchange(ValueType newValue);

    ValueType load() const;
    ValueType store(ValueType newValue);

    operator ValueType()const;
    ValueType operator=(ValueType value);

	 private:
			volatile ValueType value_;
};
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
#endif
