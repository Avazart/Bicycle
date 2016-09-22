//---------------------------------------------------------------------------
#include "AtomicCounter.h"

using namespace Bicycle;
//---------------------------------------------------------------------------
AtomicCounter::AtomicCounter(AtomicCounter::ValueType initialValue)
  :value_(initialValue)
{

}
//---------------------------------------------------------------------------
AtomicCounter::ValueType AtomicCounter::increment()
{
  return InterlockedIncrement(&value_);
}
//---------------------------------------------------------------------------
AtomicCounter::ValueType AtomicCounter::decrement()
{
  return InterlockedDecrement(&value_);
}
//---------------------------------------------------------------------------
AtomicCounter::ValueType
  AtomicCounter::exchange(AtomicCounter::ValueType newValue)
{
  return InterlockedExchange(&value_,newValue);
}
//---------------------------------------------------------------------------
AtomicCounter::ValueType AtomicCounter::load() const
{
  return value_;
}
//---------------------------------------------------------------------------
AtomicCounter::ValueType
  AtomicCounter::store(AtomicCounter::ValueType newValue)
{
  return exchange(newValue);
}
//---------------------------------------------------------------------------
AtomicCounter::operator AtomicCounter::ValueType() const
{
  return load();
}
//---------------------------------------------------------------------------
AtomicCounter::ValueType
  AtomicCounter::operator=(AtomicCounter::ValueType value)
{
  store(value);
  return value;
}
//---------------------------------------------------------------------------
