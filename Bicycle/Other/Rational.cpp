#include "Rational.h"

#include <utility> // std::swap
#include <cmath>

Rational::Rational(int numerator/*=0*/,
                       int denominator/*=1*/)
  :numerator_(numerator),
    denominator_(denominator)
{
  reduction();
}

int Rational::greatestCommonDivisor(int a,int b)
{
  if(a<b)
    std::swap(a,b);
  while(b!=0)
  {
    int t = b;
    b = a%b;
    a = t;
  }
  return a;
}

void Rational::reduction()
{
  int gcd =  greatestCommonDivisor(numerator_, denominator_);
  if(gcd!=1)
  {
    numerator_   /= gcd;
    denominator_ /= gcd;
  }
}

int Rational::numerator()const
{
  return numerator_;
}

int Rational::denominator()const
{
  return denominator_;
}

bool Rational::isInt()const
{
  return std::abs(denominator_)==1;
}

double Rational::toDouble()const
{
  return double(numerator_)/denominator_;
}

int Rational::toInt()const
{
  return numerator_/denominator_;
}

int Rational::remainder() const
{
  return numerator_%denominator_;
}

bool Rational::operator==(const Rational& other)const
{
  return numerator_== other.numerator_ && denominator_== other.denominator_;
}

bool Rational::operator!=(const Rational &other) const
{
  return !(*this==other);
}

bool Rational::operator<(const Rational& other)const
{
  return toDouble() < other.toDouble();
}

bool Rational::operator>(const Rational &other) const
{
  return toDouble() > other.toDouble();
}

bool Rational::operator==(int value)const
{
  return isInt() && numerator_==value;
}

bool Rational::operator!=(int value) const
{
  return !(*this==value);
}

bool Rational::operator<(double value)const
{
  return toDouble()<value;
}

bool Rational::operator>(double value) const
{
  return toDouble()>value;
}

Rational Rational::operator+(const Rational& other)const
{
  return Rational(numerator_*other.denominator_ + denominator_*other.numerator_,
                    denominator_*other.denominator_);
}

Rational Rational::operator-(const Rational& other)const
{
  return Rational(numerator_*other.denominator_ - denominator_*other.numerator_,
                    denominator_*other.denominator_);
}

Rational Rational::operator*(const Rational& other)const
{
  return Rational(numerator_*other.numerator_,
                    denominator_*other.denominator_);
}

Rational Rational::operator/(const Rational& other)const
{
  return Rational(numerator_*other.denominator_,
                    denominator_*other.numerator_);
}


Rational& Rational::operator+=(const Rational &other)
{
  numerator_ =  numerator_*other.denominator_ + denominator_*other.numerator_,
  denominator_ *= other.denominator_;
  reduction();
  return *this;
}

Rational& Rational::operator-=(const Rational &other)
{
 numerator_ = numerator_*other.denominator_ - denominator_*other.numerator_;
 denominator_ *= other.denominator_;
 reduction();
 return *this;
}

Rational &Rational::operator*=(const Rational &other)
{
  numerator_ *= other.numerator_;
  denominator_ *= other.denominator_;
  reduction();
  return *this;
}

Rational &Rational::operator/=(const Rational &other)
{
  numerator_ *= other.denominator_;
  denominator_ *= other.numerator_;
  reduction();
  return *this;
}

Rational &Rational::operator+=(int value)
{
  numerator_ +=  denominator_*value;
  reduction();
  return *this;
}

Rational &Rational::operator-=(int value)
{
  numerator_ -=  denominator_*value;
  reduction();
  return *this;
}

Rational &Rational::operator*=(int value)
{
  numerator_ *=  denominator_*value;
  reduction();
  return *this;
}

Rational &Rational::operator/=(int value)
{
  denominator_ *= value;
  reduction();
  return *this;
}

Rational operator+(const Rational& f,int value)
{
  return f + Rational(value);
}

Rational operator+(int value,const Rational& f)
{
  return Rational(value)+f;
}

Rational operator-(const Rational& f,int value)
{
  return f - Rational(value);
}

Rational operator-(int value,const Rational& f)
{
  return Rational(value) - f;
}

Rational operator*(const Rational& f,int value)
{
  return f * Rational(value);
}

Rational operator*(int value,const Rational& f)
{
  return Rational(value)*f;
}

Rational operator/(const Rational& f,int value)
{
  return f/Rational(value);
}

Rational operator/(int value,const Rational& f)
{
  return Rational(value)/f;
}

std::ostream& operator<<(std::ostream& stream,const Rational& fractional)
{
  int k = fractional.denominator_<0?-1:1; // минус в числителе
  if(!fractional.isInt())
    stream << k*fractional.numerator_ << '/' << k*fractional.denominator_;
  else
    stream << fractional.toInt();
  return stream;
}
