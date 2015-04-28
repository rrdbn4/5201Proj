///////////////////////
// uppertrimatrix.hpp
///////////////////////
// Author:     ROBERT DUNN
// Instructor: Clayton Price
// Course:     CS 5201
// Purpose:    function implementation for the uppertrimatrix class
///////////////////////
template <class T>
void UpperTriMatrix<T>::constructMatrix(const unsigned int rows, const unsigned int cols)
{
  m_rows = rows;
  m_cols = cols;
  m_data = new T*[m_rows];
  for(int i = 0; i < m_rows; i++)
    m_data[i] = new T[m_cols - i];
}

template <class T>
UpperTriMatrix<T>::UpperTriMatrix(const unsigned int size)
{
  constructMatrix(size, size);
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; j < m_cols - i; j++)
      m_data[i][j] = 0;
}

template <class T>
UpperTriMatrix<T>::UpperTriMatrix(const UpperTriMatrix<T>& source)
{
  constructMatrix(source.m_rows, source.m_cols);
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; j < m_cols - i; j++)
      m_data[i][j] = source.m_data[i][j];
}

template <class T>
UpperTriMatrix<T>::~UpperTriMatrix()
{
  for(int i = 0; i < m_rows; i++)
    delete [] m_data[i];
  delete [] m_data;
}

template <class T>
int UpperTriMatrix<T>::size() const
{
  return m_rows;
}

template <class T>
int UpperTriMatrix<T>::rows() const
{
  return m_rows;
}

template <class T>
int UpperTriMatrix<T>::cols() const
{
  return m_cols;
}

template <class T>
Vector<T> UpperTriMatrix<T>::solve(const Vector<T>& vec) const
{
  UpperTriMatrix<T> A(*this);   //copy the values over as to avoid tampering with the calling object
  Vector<T> b(vec);

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
T& UpperTriMatrix<T>::operator()(const unsigned int i, const unsigned int j)
{
  if(i >= rows() || i < 0 || j >= cols() || j < 0)
    throw std::out_of_range(std::string("Tried to access out of bounds"));

  if(j < i)
  {
    T ret;
    ret = 0;  //return a reference to something that will be destroyed immediately affectively blocking access to the lower triangular
    return ret;
  }
  return m_data[i][j - i];
}

template <class T>
const T UpperTriMatrix<T>::operator()(const unsigned int i, const unsigned int j) const
{
  if(i >= rows() || i < 0 || j >= cols() || j < 0)
    throw std::out_of_range(std::string("Tried to access out of bounds"));

  if(j < i)
    return 0;
  return m_data[i][j - i];
}

template <class T>
UpperTriMatrix<T> UpperTriMatrix<T>::operator+(const UpperTriMatrix<T>& rhs) const
{
  if(size() != rhs.size())
    throw std::length_error(std::string("Size mismatch error"));

  UpperTriMatrix<T> temp(rhs.size());
  for(int i = 0; i < m_rows; i++)
    for(int j = i; j < m_cols; j++)
      temp(i, j) = (*this)(i, j) + rhs(i, j);
  return temp;
}

template <class T>
UpperTriMatrix<T> UpperTriMatrix<T>::operator-(const UpperTriMatrix<T>& rhs) const
{
  if(size() != rhs.size())
    throw std::length_error(std::string("Size mismatch error"));

  UpperTriMatrix<T> temp(rhs.size());
  for(int i = 0; i < m_rows; i++)
    for(int j = i; j < m_cols; j++)
      temp(i, j) = (*this)(i, j) - rhs(i, j);
  return temp;
}

template <class T>
UpperTriMatrix<T> UpperTriMatrix<T>::operator*(const UpperTriMatrix<T>& rhs) const
{
  if(size() != rhs.size())
    throw std::length_error(std::string("Size mismatch error"));

  UpperTriMatrix<T> temp(rhs.size());
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
UpperTriMatrix<T>& UpperTriMatrix<T>::operator=(const UpperTriMatrix<T>& input)
{
  if(m_data != NULL)
  {
    for(int i = 0; i < m_rows; i++)
      delete [] m_data[i];
    delete [] m_data;
  }
  constructMatrix(input.size(), input.size());
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; j < m_cols - i; j++)
      m_data[i][j] = input.m_data[i][j];
  return (*this);  
}

////////////////////////
// FRIEND FUNCTIONS
////////////////////////

template <class N>
UpperTriMatrix<N> operator*(const N& scalar, const UpperTriMatrix<N>& mat)
{
  UpperTriMatrix<N> temp(mat);
  for(int i = 0; i < mat.m_rows; i++)
    for(int j = i; j < mat.m_cols; j++)
      temp(i, j) = scalar * temp(i, j);
  return temp;
}

template <class N>
Vector<N> operator*(const Vector<N>& vec, const UpperTriMatrix<N>& mat)
{
  if(vec.size() != mat.size())
    throw std::length_error(std::string("Size mismatch error"));

  Vector<N> temp(vec.size());

  for(int i = 0; i < vec.size(); i++)
  {
    N sum = 0;
    for(int k = i; k < vec.size(); k++)
      sum += (vec[k] * mat(k, i));
    temp[i] = sum;
  }
      
  return temp;
}

template <class N>
Vector<N> operator*(const UpperTriMatrix<N>& mat, const Vector<N>& vec)
{
  if(vec.size() != mat.size())
    throw std::length_error(std::string("Size mismatch error"));

  Vector<N> temp(vec.size());

  for(int i = 0; i < vec.size(); i++)
  {
    N sum = 0;
    for(int k = i; k < vec.size(); k++)
      sum += (mat(i, k) * vec[k]);
    temp[i] = sum;
  }
      
  return temp;
}

template <class N>
std::ostream& operator<<(std::ostream& stream, const UpperTriMatrix<N>& input)
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
std::istream& operator>>(std::istream& stream, UpperTriMatrix<N>& input)
{
  for(int i = 0; i < input.m_rows; i++)
    for(int j = 0; j < input.m_cols; j++)
      stream >> input(i, j);
  return stream;
}