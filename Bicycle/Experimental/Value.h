#ifdef _MSC_VER
  #pragma once
#endif
//----------------------------------------------------------
#ifndef ValueH
#define ValueH
//----------------------------------------------------------
namespace Bicycle
{
//----------------------------------------------------------
template <typename T>
class Value
{
   public:
     Value():value_(T()),valid_(false){}

     Value(const T& value,bool valid= true)
     {
       this->value_= value;
       valid_= valid;
     }

     Value<T>& operator=(const T& value)
     {
       this->value_= value;
       valid_= true;
       return *this;
     }

     const T& value()const{ return value_; }
     bool isValid()const{ return valid_; }
     operator T()const { return value_; }
   private:
     T value_;
     bool valid_;
};
//----------------------------------------------------------
} //  Bicycle
//----------------------------------------------------------
#endif // VALUE

