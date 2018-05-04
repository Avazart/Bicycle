#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

// #define USE_IMPLICIT

class Rational
{
  public:
     #ifndef USE_IMPLICIT
        explicit
     #endif
        Rational(int numerator=0, int denominator=1);

     int numerator()const;
     int denominator()const;

     double toDouble()const;
     bool isInt()const;
     int  toInt()const;
     int  remainder()const;

     bool operator==(const Rational& other)const;
     bool operator!=(const Rational& other)const;
     bool operator<(const Rational& other)const;
     bool operator>(const Rational& other)const;

     bool operator==(int value)const;
     bool operator!=(int value)const;
     bool operator<(double value)const;
     bool operator>(double value)const;

     Rational operator+(const Rational& other)const;
     Rational operator-(const Rational& other)const;
     Rational operator*(const Rational& other)const;
     Rational operator/(const Rational& other)const;

     Rational& operator+=(const Rational& other);
     Rational& operator-=(const Rational& other);
     Rational& operator*=(const Rational& other);
     Rational& operator/=(const Rational& other);

     Rational& operator+=(int value);
     Rational& operator-=(int value);
     Rational& operator*=(int value);
     Rational& operator/=(int value);

     friend Rational operator+(const Rational& f,int value);
     friend Rational operator+(int value,const Rational& f);

     friend Rational operator-(const Rational& f,int value);
     friend Rational operator-(int value,const Rational& f);

     friend Rational operator*(const Rational& f,int value);
     friend Rational operator*(int value,const Rational& f);

     friend Rational operator/(const Rational& f,int value);
     friend Rational operator/(int value,const Rational& f);

     friend std::ostream& operator<<(std::ostream& stream,
                                     const Rational& fractional);

  private:
     void reduction();
     static int greatestCommonDivisor(int a,int b);

  private:
     int numerator_;
     int denominator_;
};

#endif // RATIONAL_H
