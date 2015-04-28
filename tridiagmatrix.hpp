///////////////////////
// tridiagmatrix.hpp
///////////////////////
// Author:     ROBERT DUNN
// Instructor: Clayton Price
// Course:     CS 5201
// Purpose:    function implementation for the TriDiagmatrix class
///////////////////////
template <class T>
void TriDiagMatrix<T>::constructMatrix(const unsigned int rows, const unsigned int cols)
{
  m_rows = rows;
  m_cols = cols;
  m_data = new T*[m_rows];
  for(int i = 0; i < m_rows; i++)
  {
    if(i == 0 || i == m_rows - 1)
      m_data[i] = new T[2];
    else
      m_data[i] = new T[3];
  }
}

template <class T>
TriDiagMatrix<T>::TriDiagMatrix(const unsigned int size)
{
  constructMatrix(size, size);
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; (i == 0 || i == m_rows - 1 ? j < 2 : j < 3); j++)
      m_data[i][j] = 0;
}

template <class T>
TriDiagMatrix<T>::TriDiagMatrix(const TriDiagMatrix<T>& source)
{
  constructMatrix(source.m_rows, source.m_cols);
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; (i == 0 || i == m_rows - 1 ? j < 2 : j < 3); j++)
      m_data[i][j] = source.m_data[i][j];
}

template <class T>
TriDiagMatrix<T>::~TriDiagMatrix()
{
  for(int i = 0; i < m_rows; i++)
    delete [] m_data[i];
  delete [] m_data;
}

template <class T>
int TriDiagMatrix<T>::size() const
{
  return m_rows;
}

template <class T>
int TriDiagMatrix<T>::rows() const
{
  return m_rows;
}

template <class T>
int TriDiagMatrix<T>::cols() const
{
  return m_cols;
}

template <class T>
Vector<T> TriDiagMatrix<T>::solve(const Vector<T>& vec) const
{
  Vector<T> result(vec.size());
  TriDiagMatrix<T> L(size());
  TriDiagMatrix<T> U(size());

  //LU decomposition
  U(0, 0) = (*this)(0, 0);
  U(0, 1) = (*this)(0, 1);
  L(0, 0) = 1;

  for(int i = 1; i < size() - 1; i++)
  {
    L(i, i) = 1;
    L(i, i-1) = (*this)(i, i-1) / U(i-1, i-1);
    U(i, i) = (*this)(i, i) - (L(i, i-1) * U(i-1, i));
    U(i, i+1) = (*this)(i, i+1);
  }
  int N = size() - 1;
  L(N, N) = 1;
  L(N, N-1) = (*this)(N, N-1) / U(N-1, N-1);
  U(N, N) = (*this)(N, N) - (L(N, N-1) * U(N-1, N));

  //forward subsitution
  Vector<T> y(size());  //temporary result vector
  y[1] = vec[1];
  for(int i = 1; i < size(); i++)
  {
    y[i] = vec[i] - (L(i, i-1) * y[i-1]);
  }

  //back subsitution
  result[N] = y[N] / U(N, N);
  for(int i = N-1; i >= 0; i--)
  {
    result[i] = (y[i] - (U(i, i+1) * result[i+1])) / U(i, i);
  }

  return result;
}

////////////////////////
// Operator Overloads
////////////////////////

template <class T>
T& TriDiagMatrix<T>::operator()(const unsigned int i, const unsigned int j)
{
  if(i >= rows() || i < 0 || j >= cols() || j < 0)
    throw std::out_of_range(std::string("Tried to access out of bounds"));

  if(i == 0 && j <= i + 1)
    return m_data[i][j];
  if(j > i + 1 || j < i - 1)
  {
    T ret;
    ret = 0;  //return a reference to something that will be destroyed immediately affectively blocking access to the lower triangular
    return ret;
  }
  return m_data[i][j - (i - 1)];
}

template <class T>
const T TriDiagMatrix<T>::operator()(const unsigned int i, const unsigned int j) const
{
  if(i >= rows() || i < 0 || j >= cols() || j < 0)
    throw std::out_of_range(std::string("Tried to access out of bounds"));

  if(i == 0 && j <= i + 1)
    return m_data[i][j];
  if(j > i + 1 || j < i - 1)
    return 0;
  return m_data[i][j - (i - 1)];
}

template <class T>
TriDiagMatrix<T> TriDiagMatrix<T>::operator+(const TriDiagMatrix<T>& rhs) const
{
  if(size() != rhs.size())
    throw std::length_error(std::string("Size mismatch error"));

  TriDiagMatrix<T> temp(rhs.size());
  for(int i = 0; i < m_rows; i++)
    for(int j = std::max(i - 1, 0); (j < i + 1 || j < cols()); j++)
      temp(i, j) = (*this)(i, j) + rhs(i, j);
  return temp;
}

template <class T>
TriDiagMatrix<T> TriDiagMatrix<T>::operator-(const TriDiagMatrix<T>& rhs) const
{
  if(size() != rhs.size())
    throw std::length_error(std::string("Size mismatch error"));

  TriDiagMatrix<T> temp(rhs.size());
  for(int i = 0; i < m_rows; i++)
    for(int j = std::max(i - 1, 0); (j < i + 1 || j < cols()); j++)
      temp(i, j) = (*this)(i, j) - rhs(i, j);
  return temp;
}

template <class T>
TriDiagMatrix<T> TriDiagMatrix<T>::operator*(const TriDiagMatrix<T>& rhs) const
{
  if(size() != rhs.size())
    throw std::length_error(std::string("Size mismatch error"));

  TriDiagMatrix<T> temp(rhs.size());
  for(int i = 0; i < m_rows; i++)
  {
    for(int j = 0; j < m_cols; j++)
    {
      T sum = 0;
      for(int k = 0; k < m_rows; k++)
        sum += ((*this)(i, k) * rhs(k, j));
      temp(i, j) = sum;
    }
  }
      
  return temp;
}

template <class T>
TriDiagMatrix<T>& TriDiagMatrix<T>::operator=(const TriDiagMatrix<T>& input)
{
  if(m_data != NULL)
  {
    for(int i = 0; i < m_rows; i++)
      delete [] m_data[i];
    delete [] m_data;
  }
  constructMatrix(input.size(), input.size());
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; (i == 0 || i == m_rows - 1 ? j < 2 : j < 3); j++)
      m_data[i][j] = input.m_data[i][j];
  return (*this);  
}

////////////////////////
// FRIEND FUNCTIONS
////////////////////////

template <class N>
TriDiagMatrix<N> operator*(const N& scalar, const TriDiagMatrix<N>& mat)
{
  TriDiagMatrix<N> temp(mat);
  for(int i = 0; i < mat.m_rows; i++)
    for(int j = std::max(i - 1, 0); (j < i + 1 || j < mat.cols()); j++)
      temp(i, j) = scalar * temp(i, j);
  return temp;
}

template <class N>
Vector<N> operator*(const Vector<N>& vec, const TriDiagMatrix<N>& mat)
{
  if(vec.size() != mat.size())
    throw std::length_error(std::string("Size mismatch error"));

  Vector<N> temp(vec.size());

  for(int i = 0; i < vec.size(); i++)
  {
    N sum = 0;
    for(int j = std::max(i - 1, 0); (j < i + 1 || j < mat.cols()); j++)
      sum += (vec[j] * mat(j, i));
    temp[i] = sum;
  }
      
  return temp;
}

template <class N>
Vector<N> operator*(const TriDiagMatrix<N>& mat, const Vector<N>& vec)
{
  if(vec.size() != mat.size())
    throw std::length_error(std::string("Size mismatch error"));

  Vector<N> temp(vec.size());

  for(int i = 0; i < vec.size(); i++)
  {
    N sum = 0;
    for(int j = std::max(i - 1, 0); (j < i + 1 || j < mat.cols()); j++)
      sum += (mat(i, j) * vec[j]);
    temp[i] = sum;
  }
      
  return temp;
}

template <class N>
std::ostream& operator<<(std::ostream& stream, const TriDiagMatrix<N>& input)
{
  for(int i = 0; i < input.rows(); i++)
  {
    for(int j = 0; j < input.cols(); j++)
    { 
      stream << input(i, j) << (j == input.cols()-1 ? "" : " ");
    }
    if(i != input.rows() - 1)
      stream << std::endl;
  }
  return stream;
}

template <class N>
std::istream& operator>>(std::istream& stream, TriDiagMatrix<N>& input)
{
  for(int i = 0; i < input.m_rows; i++)
    for(int j = 0; j < input.m_cols; j++)
      stream >> input(i, j);
  return stream;
}