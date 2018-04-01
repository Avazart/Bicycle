#include "Any.h"

#include <algorithm>
#include <stdexcept>
#include <typeinfo>

using namespace Bicycle;
//---------------------------------------------------------
Any::Any()
	:ptr_(0),
	 holder_(0)
{
}
//---------------------------------------------------------
Any::Any(const Any &other)
{
	if (other.empty())
		clear();
	else
	{
		ptr_ = other.holder_->clone(other.ptr_);
		holder_ = other.holder_;
	}
}
//----------------------------------------------------------
Any &Any::operator=(const Any &other)
{
	if (other.empty())
		clear();
	else
	{
		void* ptr = other.holder_->clone(other.ptr_);
		std::swap(ptr_, ptr);
		holder_->destroy(ptr);
		holder_ = other.holder_;
	}
	return *this;
}
//----------------------------------------------------------
#ifdef USE_CPP_11
//----------------------------------------------------------
Any::Any(Any&& other)
	:Any()
{
	this->swap(other);
}
//----------------------------------------------------------
Any& Any::operator=(Any&& other)
{
	this->swap(other);
	return *this;
}
//----------------------------------------------------------
#endif
//----------------------------------------------------------
Any::~Any()
{
	if(!empty())
	{
		holder_->destroy(ptr_);
	}
}
//----------------------------------------------------------
bool Any::empty() const
{
	return ptr_ == 0;
}
//----------------------------------------------------------
void Any::clear()
{
	if(!empty())
	{
		holder_->destroy(ptr_);
		holder_ = 0;
		ptr_ = 0;
	}
}
//----------------------------------------------------------
void Any::swap(Any &other)
{
	std::swap(ptr_, other.ptr_);
	std::swap(holder_, other.holder_);
}
//---------------------------------------------------------
bool Any::isType(const Any& other)const
{
	return holder_ == other.holder_;
}
//---------------------------------------------------------
void Bicycle::swap(Any &a1, Any &a2)
{
	a1.swap(a2);
}
//---------------------------------------------------------
