#include <iostream>
#include <cassert>

using namespace std;

#include "Other/Matrix.h"
#include "Other/Rational.h"


template<typename M>
void print(M& m,M& b)
{
  for(std::size_t r=0;r< m.rowSize(); ++r)
  {
    for(std::size_t c=0;c< m.colSize(); ++c)
    {
      if(c==0)
       std::cout<< m[r][c];
      else
       std::cout<<"\t"<< m[r][c];
    }

    std::cout<<"\t"<< b[r][0];
    std::cout<<std::endl;
  }
}

// https://www.youtube.com/watch?v=QAMyicklakA&index=4&list=PLwwk4BHih4fg6dz8m2K3R3uvDPC2bwUIR
void luDecomposition(const Matrix<Rational>& a,
                     const Matrix<Rational>& b,
          Matrix<Rational>& l,
          Matrix<Rational>& u,
          Matrix<Rational>& b_)
{
  assert(a.rowSize()==a.colSize());
  assert(a.rowSize()==b.rowSize());

  const std::size_t size= a.rowSize();

  u =  a;
  b_ = b;
  l= Matrix<Rational>(size,size);
  for(std::size_t i=0; i<size; ++i)
    l[i][i]= Rational(1);

  for(std::size_t c=0; c<size-1; ++c)
  {
    for(std::size_t r=c+1; r<size; ++r)
    {
      l[r][c] = u[r][c]/u[c][c];

      for(std::size_t i=c; i<size; ++i)
         u[r][i] -= l[r][c]*u[c][i];

      b_[r][0] -= l[r][c]*b_[c][0];
    }
  }
}

Matrix<Rational> findX(const Matrix<Rational>& u,
                       const Matrix<Rational>& b_)
{
  assert(u.rowSize()==u.colSize());
  assert(u.rowSize()==b_.rowSize());

  const std::size_t size= u.rowSize();

  Matrix<Rational> x(size);
  x.fill(Rational(1));

  for(int i= size-1; i>=0; --i)
  {
    Rational sum(0);
    for(std::size_t c= 0; c<size; ++c)
      if(c!=i)
        sum += u[i][c]*x[c][0];

    x[i][0] = (b_[i][0]-sum)/u[i][i];
  }
  return x;
}


int main()
{
  Matrix<Rational> a=
  {
    { Rational(2),Rational(1),Rational(1) },
    { Rational(4),Rational(-6),Rational(0) },
    { Rational(-2),Rational(7),Rational(2) }
  };

  Matrix<Rational>
      b({ Rational(5),
          Rational(-2),
          Rational(9) });

  print(a,b);
  std::cout <<  std::endl;

  Matrix<Rational> l,u,b_;
  luDecomposition(a,b, l,u, b_);
  std::cout << l <<  std::endl <<  std::endl;
  print(u,b_);
  std::cout <<  std::endl;

  Matrix<Rational> x = findX(u,b_);
  std::cout << x <<  std::endl <<  std::endl;

  assert(a*x==b);

  // Test 2

  Matrix<Rational> a2=
  {
    { Rational(2),Rational(1),Rational(-1) },
    { Rational(-3),Rational(-1),Rational(2) },
    { Rational(-2),Rational(1),Rational(2) }
  };

  Matrix<Rational>
      b2({ Rational(8),
          Rational(-11),
          Rational(-3) });

  print(a2,b2);
  std::cout <<  std::endl;

  Matrix<Rational> l2,u2,b2_;
  luDecomposition(a2,b2, l2,u2, b2_);
  std::cout << l2 <<  std::endl <<  std::endl;
  print(u2,b2_);
  std::cout <<  std::endl;

  Matrix<Rational> x2 = findX(u2,b2_);
  std::cout << x2 <<  std::endl <<  std::endl;

  assert(a2*x2==b2);


  getchar();
  return 0;
}

