///////////////////////
// symmetricmatrix.hpp
///////////////////////
// Author:     ROBERT DUNN
// Instructor: Clayton Price
// Course:     CS 5201
// Purpose:    function implementation for the Symmetricmatrix class
///////////////////////
template <class T>
void SymmetricMatrix<T>::constructMatrix(const unsigned int rows, const unsigned int cols)
{
  m_rows = rows;
  m_cols = cols;
  m_data = new T*[m_rows];
  for(int i = 0; i < m_rows; i++)
    m_data[i] = new T[i + 1];
}

template <class T>
SymmetricMatrix<T>::SymmetricMatrix(const unsigned int size)
{
  constructMatrix(size, size);
}

template <class T>
SymmetricMatrix<T>::SymmetricMatrix(const SymmetricMatrix<T>& source)
{
  constructMatrix(source.m_rows, source.m_cols);
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; j < i + 1; j++)
      m_data[i][j] = source.m_data[i][j];
}

template <class T>
SymmetricMatrix<T>::~SymmetricMatrix()
{
  for(int i = 0; i < m_rows; i++)
    delete [] m_data[i];
  delete [] m_data;
}

template <class T>
int SymmetricMatrix<T>::size() const
{
  return m_rows;
}

template <class T>
int SymmetricMatrix<T>::rows() const
{
  return m_rows;
}

template <class T>
int SymmetricMatrix<T>::cols() const
{
  return m_cols;
}

template <class T>
Vector<T> SymmetricMatrix<T>::solve(const Vector<T>& vec) const
{
  Vector<T> result(size());
  SymmetricMatrix<T> L(size());

  //cholesky decomposition
  for(int i = 0; i < size(); i++)
  {
    for(int j = 0; j <= i; j++)
    {
      if(i == j)
      {
        T summation = 0;
        for(int k = 0; k < i; k++)
          summation += pow(L(i, k), 2);
        L(i, j) = sqrt((*this)(i, j) - summation);
      }
      else
      {
        T summation = 0;
        for(int k = 0; k < j; k++)
          summation += (L(j, k) * L(i, k));
        L(i, j) = ((*this)(i, j) - summation) / L(j, j);
      }
    }
  }

  //forward substitution L*z = vec
  Vector<T> z(size());
  z[0] = vec[0] / L(0, 0);
  for(int p = 1; p < size(); p++)
  {
    T sum = 0;
    for(int j = p; j >= 0; j--)
      sum += (-(L(p, j) * z[j]));
    z[p] = (vec[p] + sum) / L(p, p); 
  }

  //back substitution Lt*result = z
  result[vec.size() - 1] = z[z.size() - 1] / L(size() - 1, size() - 1);
  for(int p = size() - 2; p >= 0; p--)
  {
    T sum = 0;
    for(int j = z.size() - 1; j > p; j--)
      sum += (-(L(p, j) * result[j]));
    result[p] = (z[p] + sum) / L(p, p); 
  }

  return result;
}

////////////////////////
// Operator Overloads
////////////////////////

template <class T>
T& SymmetricMatrix<T>::operator()(const unsigned int i, const unsigned int j)
{
  if(i >= rows() || i < 0 || j >= cols() || j < 0)
    throw std::out_of_range(std::string("Tried to access out of bounds"));

  if(i < j)
  {
    return m_data[j][i];  //return the mirror of the inputs
  }
  return m_data[i][j];
}

template <class T>
const T SymmetricMatrix<T>::operator()(const unsigned int i, const unsigned int j) const
{
  if(i >= rows() || i < 0 || j >= cols() || j < 0)
    throw std::out_of_range(std::string("Tried to access out of bounds"));

  if(i < j)
    return m_data[j][i];  //return the mirror of the inputs
  return m_data[i][j];
}

template <class T>
SymmetricMatrix<T> SymmetricMatrix<T>::operator+(const SymmetricMatrix<T>& rhs) const
{
  if(size() != rhs.size())
    throw std::length_error(std::string("Size mismatch error"));

  SymmetricMatrix<T> temp(rhs.size());
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; j < i + 1; j++)
      temp(i, j) = (*this)(i, j) + rhs(i, j);
  return temp;
}

template <class T>
SymmetricMatrix<T> SymmetricMatrix<T>::operator-(const SymmetricMatrix<T>& rhs) const
{
  if(size() != rhs.size())
    throw std::length_error(std::string("Size mismatch error"));

  SymmetricMatrix<T> temp(rhs.size());
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; j < i + 1; j++)
      temp(i, j) = (*this)(i, j) - rhs(i, j);
  return temp;
}

template <class T>
SymmetricMatrix<T> SymmetricMatrix<T>::operator*(const SymmetricMatrix<T>& rhs) const
{
  if(size() != rhs.size())
    throw std::length_error(std::string("Size mismatch error"));

  SymmetricMatrix<T> temp(rhs.size());
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
SymmetricMatrix<T>& SymmetricMatrix<T>::operator=(const SymmetricMatrix<T>& input)
{
  if(m_data != NULL)
  {
    for(int i = 0; i < m_rows; i++)
      delete [] m_data[i];
    delete [] m_data;
  }
  constructMatrix(input.size(), input.size());
  for(int i = 0; i < m_rows; i++)
    for(int j = 0; j < i + 1; j++)
      m_data[i][j] = input.m_data[i][j];
  return (*this);  
}

////////////////////////
// FRIEND FUNCTIONS
////////////////////////

template <class N>
SymmetricMatrix<N> operator*(const N& scalar, const SymmetricMatrix<N>& mat)
{
  SymmetricMatrix<N> temp(mat);
  for(int i = 0; i < mat.m_rows; i++)
    for(int j = 0; j < i + 1; j++)
      temp(i, j) = scalar * temp(i, j);
  return temp;
}

template <class N>
Vector<N> operator*(const Vector<N>& vec, const SymmetricMatrix<N>& mat)
{
  if(vec.size() != mat.size())
    throw std::length_error(std::string("Size mismatch error"));

  Vector<N> temp(vec.size());

  for(int i = 0; i < vec.size(); i++)
  {
    N sum = 0;
    for(int k = 0; k < i + 1; k++)
      sum += (vec[k] * mat(k, i));
    temp[i] = sum;
  }
      
  return temp;
}

template <class N>
Vector<N> operator*(const SymmetricMatrix<N>& mat, const Vector<N>& vec)
{
  if(vec.size() != mat.size())
    throw std::length_error(std::string("Size mismatch error"));

  Vector<N> temp(vec.size());

  for(int i = 0; i < vec.size(); i++)
  {
    N sum = 0;
    for(int k = 0; k < i + 1; k++)
      sum += (mat(i, k) * vec[k]);
    temp[i] = sum;
  }
      
  return temp;
}

template <class N>
std::ostream& operator<<(std::ostream& stream, const SymmetricMatrix<N>& input)
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
std::istream& operator>>(std::istream& stream, SymmetricMatrix<N>& input)
{
  for(int i = 0; i < input.m_rows; i++)
    for(int j = 0; j < input.m_cols; j++)
      stream >> input(i, j);
  return stream;
}