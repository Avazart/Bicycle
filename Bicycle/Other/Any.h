#ifdef _MSC_VER
  #pragma once
#endif
//----------------------------------------------------------
#ifndef AnyH
#define AnyH

#include "Value.h"
//----------------------------------------------------------
namespace Bicycle
{
//----------------------------------------------------------
class IHolder
{
public:
  virtual void* clone(void* ptr)=0;
  virtual void destroy(void* ptr)=0;
};
//----------------------------------------------------------
template<typename T>
class Holder: public IHolder
{
public:
  void* clone(void* ptr)
  {
    return new T(*static_cast<T*>(ptr));
  }

  virtual void destroy(void* ptr)
  {
    if(ptr)
      delete static_cast<T*>(ptr);
  }
};
//----------------------------------------------------------
template<typename T>
Holder<T>* makeHolder()
{
  static Holder<T> holder;
  return &holder;
}
//======================== Any =============================
class Any
{
public:
  Any();

  template<typename T>
  Any(const T& value);

  Any(const Any& any);
  Any& operator=(const Any& any);

  ~Any();

  void clear();
  bool empty()const;

  template<typename T>
  bool isType()const;

  template<typename T>
  Any& operator=(const T& value);

  template<typename T>
  const T& cast() const;
  
  template<typename T>
  bool tryCast(T& value) const;

  template<typename T>
  Value<T> value()const;

  void swap(Any& any);

private: 
  void* ptr_;
  IHolder* holder_;
};
//================== not member ============================
template<typename T>
const T& any_cast(const Any& any)
{
  return any.cast<T>();
}
//----------------------------------------------------------
void swap(Any &a1, Any &a2)
{
  a1.swap(a2);
}
//================== member ================================
Any::Any()
  :ptr_(0),
    holder_(0)
{
}
//----------------------------------------------------------
template<typename T>
Any::Any(const T &value)
  : ptr_(new T(value)),
    holder_(makeHolder<T>())
{
}
//----------------------------------------------------------
Any::~Any()
{
   holder_->destroy(ptr_);
}
//----------------------------------------------------------
Any::Any(const Any &any)
{
  if(any.empty())
    clear();
  else
  {
    ptr_= any.holder_->clone(any.ptr_);
    holder_= any.holder_;
  }
}
//----------------------------------------------------------
Any &Any::operator=(const Any &any)
{
  if(any.empty())
    clear();
  else
  {
    void* ptr= any.holder_->clone(any.ptr_);
    std::swap(ptr_,ptr);
    holder_->destroy(ptr);
    holder_= any.holder_;
  }
  return *this;
}
//----------------------------------------------------------
template<typename T>
Any &Any::operator=(const T& value)
{
  void* ptr= new T(value);
  std::swap(ptr_,ptr);
  holder_->destroy(ptr);
  holder_ = makeHolder<T>();
  return *this;
}
//----------------------------------------------------------
template<typename T>
bool Any::isType()const
{
  return holder_==makeHolder<T>();
}
//----------------------------------------------------------
template<typename T>
const T& Any::cast() const
{
  if(isType<T>())
    return *(static_cast<T*>(ptr_));
  else
    throw std::bad_cast("bad any cast");
}
//----------------------------------------------------------
template<typename T>
bool Any::tryCast(T& value) const
{
  if(isType<T>())
  {
    value = *(static_cast<T*>(ptr_));
    return true;
  }
  return false;
}
//----------------------------------------------------------
template<typename T>
Value<T> Any::value()const
{
  if(isType<T>())
    return Value<T>(*(static_cast<T*>(ptr_)));
  return Value<T>();
}
//----------------------------------------------------------
bool Any::empty() const
{
  return ptr_==0;
}
//----------------------------------------------------------
void Any::clear()
{
  holder_->destroy(ptr_);
  ptr_ = 0;
  holder_ = 0;
}
//----------------------------------------------------------
void Any::swap(Any &any)
{
  std::swap(ptr_,any.ptr_);
  std::swap(holder_,any.holder_);
}
//----------------------------------------------------------
}
//----------------------------------------------------------
#endif
