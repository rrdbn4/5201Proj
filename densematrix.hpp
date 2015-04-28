///////////////////////
// matrix.hpp
///////////////////////
// Author:     ROBERT DUNN
// Instructor: Clayton Price
// Course:     CS 5201
// Purpose:    function implementation for the matrix class
///////////////////////
template <class T>
void DenseMatrix<T>::constructMatrix(const unsigned int rows, const unsigned int cols)
{
  m_rows = rows;
  m_cols = cols;
  m_data = new T*[m_rows];
  for(int i = 0; i < m_rows; i++)
    m_data[i] = new T[m_cols];
}

template <class T>
DenseMatrix<T>::DenseMatrix(const unsigned int size)
{
  constructMatrix(size, size);
}

template <class T>
DenseMatrix<T>::DenseMatrix(const DenseMatrix<T>& source)
{
  constructMatrix(source.m_rows, source.m_cols);
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; j < m_cols; j++)
      m_data[i][j] = source.m_data[i][j];
}

template <class T>
DenseMatrix<T>::~DenseMatrix()
{
  for(int i = 0; i < m_rows; i++)
    delete [] m_data[i];
  delete [] m_data;
}

template <class T>
int DenseMatrix<T>::size() const
{
  return m_rows;
}

template <class T>
int DenseMatrix<T>::rows() const
{
  return m_rows;
}

template <class T>
int DenseMatrix<T>::cols() const
{
  return m_cols;
}

template <class T>
Vector<T> DenseMatrix<T>::solve(const Vector<T>& vec) const
{
  DenseMatrix<T> A(*this);   //copy the values over as to avoid tampering with the parameters
  Vector<T> b(vec);

  // forward elimination step
  for(int p = 0; p < b.size() - 1; p++)
  {
    // find max for pivoting
    int max = 0, maxIndex = 0;
    for(int i = p; i < A.size(); i++)
    {
      if(std::abs(A(i, p)) >= max)
      {
        max = std::abs(A(i, p));
        maxIndex = i;
      }
    }

    // perform row swap with max
    for(int j = 0; j < A.size(); j++)
    {
      T temp = A(maxIndex, j);
      A(maxIndex, j) = A(p, j);
      A(p, j) = temp;
    } 
    T temp = b[maxIndex];
    b[maxIndex] = b[p];
    b[p] = temp;

    // do forward elimination
    for(int i = p+1; i < A.size(); i++)
    {
      T mult = A(i, p) / A(p, p);
      for(int j = p; j < b.size(); j++)
        A(i, j) = A(i, j) - (A(p, j) * mult);
      b[i] = b[i] - (b[p] * mult);
    }
  }

  // backward substitution
  Vector<T> result(b.size());
  // first result at the end of the matrix
  result[b.size() - 1] = b[b.size() - 1] / A(A.size() - 1, A.size() - 1);
  for(int p = A.size() - 2; p >= 0; p--)
  {
    T sum = 0;
    for(int j = b.size() - 1; j > p; j--)
      sum += (-(A(p, j) * result[j]));
    result[p] = (b[p] + sum) / A(p, p); 
  }

  return result;
}

////////////////////////
// Operator Overloads
////////////////////////

template <class T>
T& DenseMatrix<T>::operator()(const unsigned int i, const unsigned int j)
{
  return m_data[i][j];
}

template <class T>
const T DenseMatrix<T>::operator()(const unsigned int i, const unsigned int j) const
{
  return m_data[i][j];
}

template <class T>
DenseMatrix<T> DenseMatrix<T>::operator+(const DenseMatrix<T>& rhs) const
{
  DenseMatrix<T> temp(rhs.size());
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; j < m_cols; j++)
      temp(i, j) = m_data[i][j] + rhs(i, j);
  return temp;
}

template <class T>
DenseMatrix<T> DenseMatrix<T>::operator-(const DenseMatrix<T>& rhs) const
{
  DenseMatrix<T> temp(rhs.size());
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; j < m_cols; j++)
      temp(i, j) = m_data[i][j] - rhs(i, j);
  return temp;
}

template <class T>
DenseMatrix<T> DenseMatrix<T>::operator~() const
{
  DenseMatrix<T> temp(size());
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; j < m_cols; j++)
      temp(j, i) = m_data(i, j);
  return temp;
}

template <class T>
DenseMatrix<T> DenseMatrix<T>::operator*(const DenseMatrix<T>& rhs) const
{
  if(size() != rhs.size())  //sizes don't match. panic. return calling object
    return (*this);
  DenseMatrix<T> temp(rhs.size());
  for(int i = 0; i < m_rows; i++)
  {
    for(int j = 0; j < m_cols; j++)
    {
      T sum = 0;
      for(int k = 0; k < m_rows; k++)
        sum += (m_data[i][k] * rhs(k, j));
      temp(i, j) = sum;
    }
  }
      
  return temp;
}

template <class T>
DenseMatrix<T>& DenseMatrix<T>::operator=(const DenseMatrix<T>& input)
{
  if(m_data != NULL)
  {
    for(int i = 0; i < m_rows; i++)
      delete [] m_data[i];
    delete [] m_data;
  }
  constructMatrix(input.size(), input.size());
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; j < m_cols; j++)
      m_data[i][j] = input.m_data[i][j];
  return (*this);  
}

////////////////////////
// FRIEND FUNCTIONS
////////////////////////

template <class N>
DenseMatrix<N> operator*(const N& scalar, const DenseMatrix<N>& mat)
{
  DenseMatrix<N> temp(mat);
  for(int i = 0; i < mat.m_rows; i++)
    for(int j = 0; j < mat.m_cols; j++)
      temp(i, j) = scalar * temp(i, j);
  return temp;
}

template <class N>
Vector<N> operator*(const Vector<N>& vec, const DenseMatrix<N>& mat)
{
  Vector<N> temp(vec.size());

  for(int i = 0; i < vec.size(); i++)
  {
    N sum = 0;
    for(int k = 0; k < vec.size(); k++)
      sum += (vec[k] * mat(k, i));
    temp[i] = sum;
  }
      
  return temp;
}

template <class N>
Vector<N> operator*(const DenseMatrix<N>& mat, const Vector<N>& vec)
{
  Vector<N> temp(vec.size());

  for(int i = 0; i < vec.size(); i++)
  {
    N sum = 0;
    for(int k = 0; k < vec.size(); k++)
      sum += (mat(i, k) * vec[k]);
    temp[i] = sum;
  }
      
  return temp;
}

template <class N>
std::ostream& operator<<(std::ostream& stream, const DenseMatrix<N>& input)
{
  for(int i = 0; i < input.m_rows; i++)
  {
    for(int j = 0; j < input.m_cols; j++)
    {
      stream << input.m_data[i][j] << (j == input.m_cols-1 ? "" : " ");
    }
    if(i != input.m_rows - 1)
      stream << std::endl;
  }
  return stream;
}

template <class N>
std::istream& operator>>(std::istream& stream, DenseMatrix<N>& input)
{
  for(int i = 0; i < input.m_rows; i++)
    for(int j = 0; j < input.m_cols; j++)
      stream >> input.m_data[i][j];
  return stream;
}