///////////////////////
// vector.hpp
///////////////////////
// Author:     ROBERT DUNN
// Instructor: Clayton Price
// Course:     CS 5201
// Purpose:    function implementation for the vector class
///////////////////////

////////////////////////
// CONSTRUCTORS
////////////////////////

template <class T>
Vector<T>::Vector()
{
  m_size = 0;
  m_data = NULL;
}

template <class T>
Vector<T>::Vector(const unsigned int size)
{
  m_size = size;
  m_data = new T[m_size];
  for(int i = 0; i < m_size; i++)
    m_data[i] = 0;
}

template <class T>
Vector<T>::Vector(const Vector<T>& source)
{
  m_size = source.m_size;
  m_data = new T[m_size];
  for(int i = 0; i < m_size; i++)
    m_data[i] = source.m_data[i];
}

template <class T>
Vector<T>::~Vector()
{
  delete [] m_data;
}

////////////////////////
// OPERATOR OVERLOADS
////////////////////////

template <class T>
Vector<T> Vector<T>::operator-() const
{
  Vector<T> temp(*this);
  for(int i = 0; i < m_size; i++)
    temp.m_data[i] = -temp.m_data[i];
  return temp;
}

template <class T>
Vector<T> Vector<T>::operator-(const Vector<T>& rhs) const
{
  Vector<T> temp(m_size);
  for(int i = 0; i < m_size; i++)
    temp.m_data[i]  = m_data[i] - rhs.m_data[i];
  return temp;
}

template <class T>
Vector<T> Vector<T>::operator+(const Vector<T>& rhs) const
{
  Vector<T> temp(m_size);
  for(int i = 0; i < m_size; i++)
    temp.m_data[i]  = m_data[i] + rhs.m_data[i];
  return temp;
}

template <class T>
T Vector<T>::operator*(const Vector<T>& rhs) const
{
  T result = 0;
  for(int i = 0; i < m_size; i++)
    result += (m_data[i] * rhs.m_data[i]);
  return result;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& input)
{
  m_size = input.m_size;
  if(m_data != NULL)
    delete [] m_data;
  m_data = new T[m_size];
  for(int i = 0; i < m_size; i++)
    m_data[i] = input.m_data[i];
  return (*this);
}

template <class T>
T& Vector<T>::operator[](const unsigned int i)
{
  if(i >= m_size)
    return m_data[0];
  return m_data[i];
}

template <class T>
const T& Vector<T>::operator[](const unsigned int i) const
{
  if(i >= m_size)
    return m_data[0];
  return m_data[i];
}

////////////////////////
// FRIEND FUNCTIONS
////////////////////////

template <class N>
Vector<N> operator*(const N& scalar, const Vector<N>& rhs)
{
  Vector<N> temp(rhs);
  for(int i = 0; i < temp.m_size; i++)
    temp.m_data[i] = scalar * temp.m_data[i];
  return temp;
}

template <class N>
std::ostream& operator<<(std::ostream& stream, const Vector<N>& input)
{
  stream << "(";
  for(int i = 0; i < input.m_size; i++)
    stream << input.m_data[i] << (i == input.m_size - 1 ? ")" : ", ");
  return stream;
}

template <class N>
std::istream& operator>>(std::istream& stream, Vector<N>& input)
{
  for(int i = 0; i < input.m_size; i++)
    stream >> input.m_data[i];
  return stream;
}