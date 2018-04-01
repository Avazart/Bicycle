#ifdef _MSC_VER
#pragma once
#endif
//----------------------------------------------------------
#ifndef AnyH
#define AnyH
//----------------------------------------------------------
#define USE_COMPARE_OPERATORS
#define USE_CPP_11

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

#ifdef USE_COMPARE_OPERATORS
	virtual bool equal(void* ptr1, void* ptr2) = 0;
	virtual bool less(void* ptr1, void* ptr2) = 0;
	virtual bool greater(void* ptr1, void* ptr2) = 0;
#endif
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

#ifdef USE_COMPARE_OPERATORS
	virtual bool equal(void* ptr1, void* ptr2) // ==
	{
		if (ptr1 && ptr2)
			return  (*static_cast<T*>(ptr1)) == (*static_cast<T*>(ptr2));

		return (ptr1==0) && (ptr2==0);
	}

	virtual bool less(void* ptr1, void* ptr2) // <
	{
		if(ptr1 && ptr2)
			return  (*static_cast<T*>(ptr1)) < (*static_cast<T*>(ptr2));

		return false;
	}

	virtual bool greater(void* ptr1, void* ptr2) // >
	{
		if (ptr1 && ptr2)
			return  (*static_cast<T*>(ptr1)) > (*static_cast<T*>(ptr2));

		return false;
	}
#endif
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

	template<typename T>
	Any(const T& value);

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
	Any& operator=(const T& value);

	template<typename T>
	const T& cast() const;

	template<typename T>
	T& cast();

	template<typename T>
	bool tryCast(T& value) const;

	void swap(Any& other);

	bool isType(const Any& other)const;

#ifdef USE_COMPARE_OPERATORS
	bool operator==(const Any& other)const;
	bool operator!=(const Any& other)const;

	bool operator<(const Any& other)const;
	bool operator>(const Any& other)const;

	bool operator<=(const Any& other)const;
	bool operator>=(const Any& other)const;
#endif

#ifdef ValueH
  template<typename T>
  Value<T> value()const;
#endif
  
private:
	void checkType(const Any& other)const;

	void* ptr_;
	AbstractHolder* holder_;
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
	: ptr_(new T(value)),
	  holder_(makeHolder<T>())
{
}
//----------------------------------------------------------
template<typename T>
Any &Any::operator=(const T& value)
{
	void* ptr = new T(value);
	std::swap(ptr_, ptr);
	if (!empty())
	{
		holder_->destroy(ptr);
		holder_ = makeHolder<T>();
	}
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
