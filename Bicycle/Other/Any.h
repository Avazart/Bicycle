#ifdef _MSC_VER
  #pragma once
#endif
//----------------------------------------------------------
#ifndef AnyH
#define AnyH
//----------------------------------------------------------
#define USE_CPP_11

#include <algorithm>
#include "Value.h"
//----------------------------------------------------------
namespace Bicycle
{
//----------------------------------------------------------
class AbstractHolder
{
public:
  virtual void* clone(void* ptr) = 0;
  virtual void destroy(void* ptr) = 0;
};
//----------------------------------------------------------
template<typename T>
class Holder : public AbstractHolder
{
public:
  void* clone(void* ptr)
  {
    return new T(*static_cast<T*>(ptr));
  }

  virtual void destroy(void* ptr)
  {
    if (ptr)
      delete static_cast<T*>(ptr);
  }
};
//----------------------------------------------------------
// Array specilization
template<typename T,int N>
class Holder<T[N]> : public AbstractHolder
{
public:
  void* clone(void* ptr)
  {
    T* originalArray= static_cast<T*>(ptr);
    T* copyOfArray = new T[N];
    std::copy(originalArray,originalArray+N,copyOfArray);
    return copyOfArray;
  }

  virtual void destroy(void* ptr)
  {
    if (ptr)
      delete[] static_cast<T*>(ptr);
  }
};
//----------------------------------------------------------
template<typename T>
Holder<T>* makeHolder()
{
  static Holder<T> Holder;
  return &Holder;
}
//======================== Any =============================
class Any
{
public:
  Any();

  // Simple types
  template<typename T>
  Any(const T& value);

  template<typename T>
  Any& operator=(const T& value);

  // Array and C-string
  template<typename A,int N>
  Any(const A(& array)[N]);

  template<typename T,int N>
  Any& operator=(const T(& array)[N]);

  //

  Any(const Any& other);
  Any& operator=(const Any& other);

#ifdef USE_CPP_11
  Any(Any&& other);
  Any& operator=(Any&& other);
#endif

  ~Any();

  void clear();
  bool empty()const;

  template<typename T>
  bool isType()const;

  template<typename T>
  const T& cast() const;

  template<typename T>
  T& cast();

  template<typename T>
  bool tryCast(T& value) const;

  void swap(Any& other);

  bool isType(const Any& other)const;

#ifdef ValueH
  template<typename T>
  Value<T> value()const;
#endif
  
private:
  AbstractHolder* holder_;
  void* ptr_;
};
//================== not member ============================
template<typename T>
const T& anyCast(const Any& other)
{
  return other.cast<T>();
}
//----------------------------------------------------------
void swap(Any &a1, Any &a2);
//================== member ================================
template<typename T>
Any::Any(const T &value)
  : holder_(makeHolder<T>()),
    ptr_(new T(value))
{
}
//----------------------------------------------------------
template<typename T,int N>
Any::Any(const T(& array)[N])
  : holder_(makeHolder<T[N]>())
{
   ptr_ = static_cast<void*>(new T[N]);
   std::copy(array,array+N,static_cast<T*>(ptr_));
}
//----------------------------------------------------------
template<typename T>
Any &Any::operator=(const T& value)
{
  void* ptr = new T(value);
  std::swap(ptr_, ptr);

  if (ptr)
     holder_->destroy(ptr);

  holder_ = makeHolder<T>();
  return *this;
}
//----------------------------------------------------------
template<typename T, int N>
Any &Any::operator=(const T(& array)[N])
{
  void* ptr = static_cast<void*>(new T[N]);
  std::copy(array,array+N, static_cast<T*>(ptr));

  std::swap(ptr_, ptr);

  if(ptr)
     holder_->destroy(ptr);

  holder_ = makeHolder<T[N]>();
  return *this;
}
//----------------------------------------------------------
template<typename T>
bool Any::isType()const
{
  return holder_ == makeHolder<T>();
}
//----------------------------------------------------------
template<typename T>
const T& Any::cast() const
{
  if (isType<T>())
    return *(static_cast<T*>(ptr_));
  else
    throw std::bad_cast();
}
//----------------------------------------------------------
template<typename T>
T& Any::cast()
{
  if (isType<T>())
    return *(static_cast<T*>(ptr_));
  else
    throw std::bad_cast();
}
//----------------------------------------------------------
template<typename T>
bool Any::tryCast(T& value) const
{
  if (isType<T>())
  {
    value = *(static_cast<T*>(ptr_));
    return true;
  }
  return false;
}

//----------------------------------------------------------
}
//----------------------------------------------------------
#endif
