#ifndef MATRIX
#define MATRIX
//------------------------------------------------
#include <iostream>
#include <algorithm>
//------------------------------------------------
#define USE_CPP11
//------------------------------------------------
template<typename T>
class Matrix;
//--------------- friends forward define --------------------------
template<typename T>
std::ostream& operator<<(std::ostream& stream,const Matrix<T>& m);

template<typename T>
std::istream& operator>>(std::istream& stream,Matrix<T>& m);

template<typename T>
Matrix<T> operator*(const Matrix<T>& m,const T& value);

template<typename T>
Matrix<T> operator/(const Matrix<T>& m,const T& value);

template<typename T>
Matrix<T> operator*(const T& value,const Matrix<T>& m);

template<typename T>
Matrix<T> operator/(const T& value,const Matrix<T>& m);
//---------------- Proxy class row --------------------------------
template<typename T>
class Row
{
  friend class Matrix<T>;

public:
  Row(std::size_t size=0);
  ~Row();

  T& operator[](std::size_t c);
  const T& operator[](std::size_t c)const;  

  Row operator+(const Row& other)const;
  Row operator-(const Row& other)const;

private:
  // hidden member function, used only Matrix<T>

  Row(const Row& row);
//  Row& operator=(const Row& row);

  void swap(Row& row);

#ifdef USE_CPP11
  Row(Row&& row);
  Row& operator=(Row&& row);
#endif

  void clear();
  void recreate(std::size_t size);

private:
  T* data_;
};
//-----------------------------------------
//   public
//-----------------------------------------
template<typename T>
T& Row<T>::operator[](std::size_t c)
{
  return data_[c];
}

template<typename T>
const T& Row<T>::operator[](std::size_t c)const
{
  return data_[c];
}
//-----------------------------------------
//  private
//-----------------------------------------
template<typename T>
Row<T>::Row(std::size_t size)
  :data_(0)
{
  if(size)
    data_= new T[size];
}

//template<typename T>
//Row<T>& Row<T>::operator=(const Row<T>& row)
//{
//  if(data!=row.data_)
//  {
//    clear();
//    ???
//  }
//  return *this;
//}
//-------------------------------------------
template<typename T>
void Row<T>::swap(Row<T>& row)
{
  std::swap(data_,row.data_);
}
//-------------------------------------------
#ifdef USE_CPP11
//-------------------------------------------
template<typename T>
Row<T>::Row(Row<T>&& row)
   :Row<T>()
{
  this->swap(row);
}

template<typename T>
Row<T>& Row<T>::operator=(Row<T>&& row)
{
   this->swap(row);
   return *this;
}
//-------------------------------------------
#endif
//-------------------------------------------
template<typename T>
Row<T>::~Row()
{
  clear();
}

template<typename T>
void Row<T>::clear()
{
  delete[] data_;
  data_ = 0;
}

template<typename T>
void Row<T>::recreate(std::size_t size)
{
  clear();
  data_= new T[size];
}
//-------------------------------------------
//              Matrix
//-------------------------------------------
template<typename T>
class Matrix
{
public:
  Matrix();
  Matrix(std::size_t rowSize,std::size_t colSize=1);
  ~Matrix();

  Matrix(const Matrix& m);
  Matrix& operator=(const Matrix& m);

  void clear();
  void resize(std::size_t rowSize,std::size_t colSize);

  bool empty()const;
  void swap(Matrix& m);

#ifdef USE_CPP11
  Matrix(Matrix&& m);
  Matrix& operator=(Matrix&& m);

  Matrix(const std::initializer_list<T>& list, bool horizontal=false);
  Matrix(const std::initializer_list<std::initializer_list<T> >& list);
#endif

  Row<T>& operator[](std::size_t r);
  const Row<T>& operator[](std::size_t r)const;

  bool operator==(const Matrix& m)const;

  std::size_t rowSize()const;
  std::size_t colSize()const;

  bool isSquare() const;

  void fill(const T& value);

  Matrix operator+(const Matrix& m)const;
  Matrix operator-(const Matrix& m)const;

  Matrix operator!() const;   // Inverse
  Matrix operator~() const;   // Transpose

  // friends
  friend Matrix operator*<T>(const Matrix& m,const T& value);
  friend Matrix operator/<T>(const Matrix& m,const T& value);

  friend Matrix operator*<T>(const T& value,const Matrix& m);
  friend Matrix operator/<T>(const T& value,const Matrix& m);

  friend std::ostream& operator<< <T>(std::ostream& stream,const Matrix& m);
  friend std::istream& operator>> <T>(std::istream& stream,Matrix& m);
  //
  bool canMultiply(const Matrix& m)const;
  Matrix operator*(const Matrix& m)const;


  T det()const;

  void inverse();
  Matrix inversed()const;

  T& item(int row, int col); // note slice ??
  const T& item(int row, int col)const;

  //   Matrix operator/(const Matrix& m)const;

  //   Matrix& operator+=(const Matrix& m);

  //   Matrix& operator-=(const Matrix& m);
  //   Matrix& operator*=(const Matrix& m);
  //   Matrix& operator/=(const Matrix& m);
  //   Matrix& operator*=(const T& value);
  //   Matrix& operator/=(const T& value);

  void transponde();
  Matrix transponded()const;

  Matrix minor(std::size_t r,std::size_t c)const;
  T minor_det(std::size_t row,std::size_t col)const;

  T addition(std::size_t r,std::size_t c) const;

private:
  Row<T>* data_;
  std::size_t rowSize_;
  std::size_t colSize_;
};
//------------------------------------------------
template<typename T, std::size_t size,std::size_t colSize>
Matrix<T> fromArray(const T (&a)[size][colSize])
{
  Matrix<T> rm(colSize,size);
  for(std::size_t r=0; r<size; ++r)
    for(std::size_t c=0; c<colSize; ++c)
      rm[c][r]= a[c][r];
  return rm;
}
//------------------------------------------------
template<typename T, std::size_t size>
Matrix<T> fromArray(const T (&a)[size],bool horizontal=true)
{
  Matrix<T> rm(horizontal?size:1,
               horizontal?1:size);

  for(std::size_t i=0; i<size; ++i)
    if(horizontal)
       rm[i][0]= a[i];
    else
       rm[0][i]= a[i];
  return rm;
}
//------------------------------------------------
template<typename T>
Matrix<T>::Matrix()
  :data_(0),
   rowSize_(0),
   colSize_(0)
{
}
//------------------------------------------------
template<typename T>
Matrix<T>::Matrix(std::size_t rowSize,
                  std::size_t colSize)
  :rowSize_(rowSize),
   colSize_(colSize)
{
  data_= new Row<T>[rowSize_];
  for(std::size_t r=0; r<rowSize_; ++r)
    data_[r].recreate(colSize_);
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& m)
{
  rowSize_= m.rowSize_;
  colSize_= m.colSize_;

  data_= new Row<T>[rowSize_];
  for(std::size_t r=0; r<rowSize_; ++r)
    data_[r].recreate(colSize_);

  for(std::size_t r=0; r<rowSize_; ++r)
    for(std::size_t c=0; c<colSize_; ++c)
      data_[r][c]= m.data_[r][c];
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
  if(data_==m.data_)
    return *this;

  resize(m.rowSize_,m.colSize_);

  for(std::size_t r=0; r<rowSize_; ++r)
    for(std::size_t c=0; c<colSize_; ++c)
      data_[r][c]= m.data_[r][c];

  return *this;
}


template<typename T>
void Matrix<T>::swap(Matrix<T>& m)
{
  std::swap(data_,m.data_);
  std::swap(rowSize_,m.rowSize_);
  std::swap(colSize_,m.colSize_);
}
//----------------------------------------------------
#ifdef USE_CPP11
//----------------------------------------------------
// move semantic
//----------------------------------------------------
template<typename T>
Matrix<T>::Matrix(Matrix<T>&& m)
  :Matrix<T>()
{
  this->swap(m);
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& m)
{
  this->swap(m);
  return *this;
}
//----------------------------------------------------
//  initializer_list
//----------------------------------------------------
template<typename T>
Matrix<T>::Matrix(const std::initializer_list<T>& list, bool horizontal)
  :Matrix<T>()
{
    resize( horizontal ? 1           : list.size(), // row = 1
            horizontal ? list.size() : 1 ); // col = 1

    for(std::size_t i=0; i<list.size(); ++i)
      if(horizontal)
        data_[0][i]= *(list.begin()+i);
      else
        data_[i][0]= *(list.begin()+i);
}

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& list)
  :Matrix<T>()
{
  resize(list.size(),list.begin()->size());

  for(std::size_t r=0; r<rowSize_; ++r)
    for(std::size_t c=0; c<colSize_; ++c)
       data_[r][c]=  *((list.begin()+r)->begin()+c);
}
//----------------------------------------------------
#endif
//----------------------------------------------------
template<typename T>
Matrix<T>::~Matrix()
{
  clear();
}

template<typename T>
void Matrix<T>::clear()
{
  delete[] data_;
  data_= 0;
  rowSize_ = 0;
  colSize_ = 0;
}

template<typename T>
void Matrix<T>::resize(std::size_t newRowSize,std::size_t newColSize)
{
  if(newRowSize==rowSize_ && newColSize==colSize_)
    return;

  if(newRowSize==0)
  {
    clear();
    return;
  }
  Matrix<T> m(newRowSize,newColSize);

  // copy old data
  std::size_t minRowSize = std::min(newRowSize,rowSize_);
  std::size_t minColSize = std::min(newColSize,colSize_);
  for(std::size_t r=0; r<minRowSize; ++r)
    for(std::size_t c=0; c<minColSize; ++c)
      m[r][c] = data_[r][c];

  this->swap(m);
}
//------------------------------------------------
template<typename T>
bool Matrix<T>::empty()const
{
  return !data_ && !rowSize_ && !colSize_;
}

template<typename T>
std::size_t Matrix<T>::rowSize()const
{
  return rowSize_;
}

template<typename T>
std::size_t Matrix<T>::colSize()const
{
  return colSize_;
}

template<typename T>
bool Matrix<T>::isSquare() const
{
  return rowSize_==colSize_;
}

template<typename T>
Row<T>& Matrix<T>::operator[](std::size_t r)
{
  return data_[r];
}

template<typename T>
const Row<T>& Matrix<T>::operator[](std::size_t r)const
{
  return data_[r];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix &m) const
{
  if(rowSize_==m.rowSize_ && colSize_==m.colSize_)
  {
    for(std::size_t r=0; r<rowSize_; ++r)
       for(std::size_t c=0; c<colSize_; ++c)
         if(data_[r][c]!=m.data_[r][c])
            return false;
    return true;
  }
  return false;
}
//------------------------------------------------
template<typename T>
void Matrix<T>::fill(const T& value)
{
  for(std::size_t r=0; r<rowSize_; ++r)
    for(std::size_t c=0; c<colSize_; ++c)
      data_[r][c]= value;
}
//------------------------------------------------
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m)const
{
  assert(rowSize_== m.rowSize_ && colSize_== m.colSize_);

  Matrix<T> rm(rowSize_,colSize_);
  for(std::size_t r=0; r<rowSize_; ++r)
    for(std::size_t c=0; c<colSize_; ++c)
      rm.data_[r][c]= data_[r][c]+m.data_[r][c];
  return rm;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& m)const
{
  assert(rowSize_== m.rowSize_ && colSize_== m.colSize_);

  Matrix<T> rm(rowSize_,colSize_);
  for(std::size_t r=0; r<rowSize_; ++r)
    for(std::size_t c=0; c<colSize_; ++c)
      rm.data_[r][c]= data_[r][c]-m.data_[r][c];
  return rm;
}

template<typename T>
Matrix<T> Matrix<T>::operator!() const
{
  return inversed();
}

template<typename T>
Matrix<T> Matrix<T>::operator~() const
{
  return transponded();
}
//------------------------------------------------
template<typename T>
std::ostream& operator<<(std::ostream& stream,const Matrix<T>& m)
{
  for(std::size_t r=0;r< m.rowSize_; ++r)
  {
    if(r)
      stream<<std::endl;
    for(std::size_t c=0;c< m.colSize_; ++c)
    {
      if(c==0) stream<< m[r][c];
      else     stream<<"\t"<< m[r][c];
    }
  }
  return stream;
}

template<typename T>
std::istream& operator>>(std::istream& stream,Matrix<T>& m)
{
  std::vector<std::vector<T> > rows;
  std::string line;

  std::size_t colSize= 0;

  while(getline(stream,line))
  {
    std::stringstream ss(line);
    std::vector<T> row;
    T value;
    while(ss>>value)
      row.push_back(value);

    if(colSize==0)
      colSize= row.size();
    else if(colSize!=row.size())
    {
      stream.setstate(std::ios::failbit);
      return stream;
    }
    rows.push_back(row);
  }

  m.resize(rows.size(),colSize);
  for(std::size_t r=0; r<rows.size(); ++r)
    for(std::size_t c=0;c<rows[r].size(); ++c)
      m.data_[r][c]= rows[r][c];

  return stream;
}
//------------------------------------------------
template<typename T>
Matrix<T> operator*(const Matrix<T>& m,const T& value)
{
  Matrix<T> rm(rowSize_,colSize_);
  for(std::size_t r=0; r<rowSize_; ++r)
    for(std::size_t c=0; c<colSize_; ++c)
      rm.data_[r][c]= m.data_[r][c]*value;
  return rm;
}

template<typename T>
Matrix<T> operator/(const Matrix<T>& m,const T& value)
{
  Matrix<T> rm(rowSize_,colSize_);
  for(std::size_t r=0; r<rowSize_; ++r)
    for(std::size_t c=0; c<colSize_; ++c)
      rm.data_[r][c]= m.data_[r][c]/value;
  return rm;
}

template<typename T>
Matrix<T> operator*(const T& value,const Matrix<T>& m)
{
  Matrix<T> rm(m.rowSize_,m.colSize_);
  for(std::size_t r=0; r<m.rowSize_; ++r)
    for(std::size_t c=0; c<m.colSize_; ++c)
      rm.data_[r][c]= value*m.data_[r][c];
  return rm;
}

template<typename T>
Matrix<T> operator/(const T& value,const Matrix<T>& m)
{
  Matrix<T> rm(m.rowSize_,m.colSize_);
  for(std::size_t r=0; r<m.rowSize_; ++r)
    for(std::size_t c=0; c<m.colSize_; ++c)
      rm.data_[r][c]= value/m.data_[r][c];
  return rm;
}
//------------------------------------------------
template<typename T>
bool Matrix<T>::canMultiply(const Matrix<T>& m)const
{
  return colSize_== m.rowSize_;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m)const
{
  Matrix<T> rm;
  if(!canMultiply(m))
    throw std::runtime_error("Can not multiply this matrix");

  rm.resize(rowSize_,m.colSize_);
  rm.fill(T(0));

  for(std::size_t r=0; r<rm.rowSize();  ++r)
    for(std::size_t c=0; c<rm.colSize();  ++c)
    {
      for(std::size_t i=0; i<colSize_; ++i)
        rm[r][c]+= data_[r][i]*m.data_[i][c];
    }
  return rm;
}
//------------------------------------------------
template<typename T>
T& Matrix<T>::item(int row,int col)
{
  row%= (int)rowSize_;
  col%= (int)colSize_;

  row= (row>=0)?row:(row+rowSize_);
  col= (col>=0)?col:(col+colSize_);

  return data_[row][col];
}

template<typename T>
const T& Matrix<T>::item(int row, int col)const
{
  row%= (int)rowSize_;
  col%= (int)colSize_;

  row= (row>=0)?row:(row+rowSize_);
  col= (col>=0)?col:(col+colSize_);

  return data_[row][col];
}
//------------------------------------------------
template<typename T>
T Matrix<T>::det()const
{
  if(!isSquare())
    throw std::runtime_error("Matrix is not square!");

  if(colSize_==2)
    return data_[0][0]*data_[1][1]-data_[1][0]*data_[0][1];

  T d(0);
  for(std::size_t c=0; c<colSize_;  ++c)
  {
    T p(1),n(1);
    for(std::size_t i=0; i<rowSize_;  ++i)
    {
      p*= item(c+i,i);
      n*= item(int(rowSize_)-1-c-i,i);
    }
    d+= p-n;
  }
  return d;
}
//------------------------------------------------
template<typename T>
Matrix<T> Matrix<T>::minor(std::size_t row,std::size_t col)const
{
  if(empty())
    throw std::runtime_error("Matrix is empty!");

  Matrix<T> rm(rowSize_-1,colSize_-1);
  for(std::size_t r1=0,r2=0; r1<rowSize_;  ++r1)
  {
    if(r1!=row)
    {
      for(std::size_t c1=0,c2=0; c1<colSize_;  ++c1)
        if(c1!=col)
        {
          rm.data_[r2][c2]= data_[r1][c1];
          ++c2;
        }
      ++r2;
    }
  }
  return rm;
}

template<typename T>
T Matrix<T>::minor_det(std::size_t row,std::size_t col) const
{
  return minor(row,col).det();
}

template<typename T>
T Matrix<T>::addition(std::size_t row,std::size_t col)const
{
  int k= (row+col)%2?-1:+1;
  return k*minor_det(row,col);
}

//------------------------------------------------
template<typename T>
Matrix<T> Matrix<T>::inversed()const
{
  if(!isSquare())
    throw std::runtime_error("Matrix is not square!");

  Matrix<T> rm(rowSize_,colSize_);
  T d= det();
  if(d==0)
    throw std::runtime_error("det Matrix is zero!");

  for(std::size_t r=0; r<rowSize_;  ++r)
    for(std::size_t c=0; c<colSize_;  ++c)
    {
      rm.data_[c][r]= addition(r,c)/d;
    }
  return rm;
}

template<typename T>
void Matrix<T>::inverse()
{
  if(!isSquare())
    throw std::runtime_error("Matrix is not square!");

  Matrix<T> rm(rowSize_,colSize_);
  T d= det();
  if(d==0)
    throw std::runtime_error("det Matrix is zero!");

  for(std::size_t r=0; r<rowSize_;  ++r)
    for(std::size_t c=0; c<colSize_;  ++c)
    {
      rm.data_[c][r]= addition(r,c)/d;
    }

  rm.swap(rm);
}


template<typename T>
Matrix<T> Matrix<T>::transponded()const
{
  Matrix<T> rm(colSize_,rowSize_);
  for(std::size_t r=0; r<rowSize_; ++r)
    for(std::size_t c=0; c<colSize_; ++c)
      rm.data_[c][r]= data_[r][c];
  return rm;
}

template<typename T>
void Matrix<T>::transponde()
{
  if(!isSquare())
  {
    swap(transponded());
    return;
  }

  for(std::size_t i=0; i<rowSize_;  ++i)
  {
    for(std::size_t c=i+1; c<colSize_; ++c)
      std::swap(data_[c][i],data_[i][c]);
  }
}
//------------------------------------------------



#endif // MATRIX

