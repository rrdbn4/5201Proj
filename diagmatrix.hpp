///////////////////////
// diagmatrix.hpp
///////////////////////
// Author:     ROBERT DUNN
// Instructor: Clayton Price
// Course:     CS 5201
// Purpose:    function implementation for the Diagmatrix class
///////////////////////
template <class T>
void DiagMatrix<T>::constructMatrix(const unsigned int rows, const unsigned int cols)
{
  m_rows = rows;
  m_cols = cols;
  m_data = new T[m_rows];
}

template <class T>
DiagMatrix<T>::DiagMatrix(const unsigned int size)
{
  constructMatrix(size, size);
}

template <class T>
DiagMatrix<T>::DiagMatrix(const DiagMatrix<T>& source)
{
  constructMatrix(source.m_rows, source.m_cols);
  for(int i = 0; i < m_rows; i++)
    m_data[i] = source.m_data[i];
}

template <class T>
DiagMatrix<T>::~DiagMatrix()
{
  delete [] m_data;
}

template <class T>
int DiagMatrix<T>::size() const
{
  return m_rows;
}

template <class T>
int DiagMatrix<T>::rows() const
{
  return m_rows;
}

template <class T>
int DiagMatrix<T>::cols() const
{
  return m_cols;
}

template <class T>
Vector<T> DiagMatrix<T>::solve(const Vector<T>& vec) const
{
  DiagMatrix<T> A(*this);   //copy the values over as to avoid tampering with the calling object
  Vector<T> b(vec);
  Vector<T> result(b.size());

  for(int i = 0; i < A.size(); i++)
  {
    result[i] = b[i] / A(i, i);
  }

  return result;
}

////////////////////////
// Operator Overloads
////////////////////////

template <class T>
T& DiagMatrix<T>::operator()(const unsigned int i, const unsigned int j)
{
  if(i >= rows() || i < 0 || j >= cols() || j < 0)
    throw std::out_of_range(std::string("Tried to access out of bounds"));

  if(i != j)
  {
    T ret;
    ret = 0;  //return a reference to something that will be destroyed immediately affectively blocking access to the lower triangular
    return ret;
  }
  return m_data[i];
}

template <class T>
const T DiagMatrix<T>::operator()(const unsigned int i, const unsigned int j) const
{
  if(i >= rows() || i < 0 || j >= cols() || j < 0)
    throw std::out_of_range(std::string("Tried to access out of bounds"));

  if(i != j)
    return 0;
  return m_data[i];
}

template <class T>
DiagMatrix<T> DiagMatrix<T>::operator+(const DiagMatrix<T>& rhs) const
{
  if(size() != rhs.size())
    throw std::length_error(std::string("Size mismatch error"));

  DiagMatrix<T> temp(rhs.size());
  for(int i = 0; i < m_rows; i++)
    temp(i, i) = (*this)(i, i) + rhs(i, i);
  return temp;
}

template <class T>
DiagMatrix<T> DiagMatrix<T>::operator-(const DiagMatrix<T>& rhs) const
{
  if(size() != rhs.size())
    throw std::length_error(std::string("Size mismatch error"));

  DiagMatrix<T> temp(rhs.size());
  for(int i = 0; i < m_rows; i++)
    temp(i, i) = (*this)(i, i) - rhs(i, i);
  return temp;
}

template <class T>
DiagMatrix<T> DiagMatrix<T>::operator*(const DiagMatrix<T>& rhs) const
{
  if(size() != rhs.size())
    throw std::length_error(std::string("Size mismatch error"));

  DiagMatrix<T> temp(rhs.size());
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
DiagMatrix<T>& DiagMatrix<T>::operator=(const DiagMatrix<T>& input)
{
  if(m_data != NULL)
  {
    delete [] m_data;
  }
  constructMatrix(input.size(), input.size());
  for(int i = 0; i < m_rows; i++)
    m_data[i] = input.m_data[i];
  return (*this);  
}

////////////////////////
// FRIEND FUNCTIONS
////////////////////////

template <class N>
DiagMatrix<N> operator*(const N& scalar, const DiagMatrix<N>& mat)
{
  DiagMatrix<N> temp(mat);
  for(int i = 0; i < mat.m_rows; i++)
    temp(i, i) = scalar * temp(i, i);
  return temp;
}

template <class N>
Vector<N> operator*(const Vector<N>& vec, const DiagMatrix<N>& mat)
{
  if(vec.size() != mat.size())
    throw std::length_error(std::string("Size mismatch error"));

  Vector<N> temp(vec.size());

  for(int i = 0; i < vec.size(); i++)
  {
    temp[i] = (vec[i] * mat(i, i));
  }
      
  return temp;
}

template <class N>
Vector<N> operator*(const DiagMatrix<N>& mat, const Vector<N>& vec)
{
  if(vec.size() != mat.size())
    throw std::length_error(std::string("Size mismatch error"));

  Vector<N> temp(vec.size());

  for(int i = 0; i < vec.size(); i++)
  {
    temp[i] = (mat(i, i) * vec[i]);
  }
      
  return temp;
}

template <class N>
std::ostream& operator<<(std::ostream& stream, const DiagMatrix<N>& input)
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
std::istream& operator>>(std::istream& stream, DiagMatrix<N>& input)
{
  for(int i = 0; i < input.m_rows; i++)
    for(int j = 0; j < input.m_cols; j++)
      stream >> input(i, j);
  return stream;
}