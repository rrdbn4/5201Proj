///////////////////////
// symmetricmatrix.h
///////////////////////
// Author:     ROBERT DUNN
// Instructor: Clayton Price
// Course:     CS 5201
// Purpose:    class declaration for the Symmetricmatrix class
///////////////////////

#ifndef SYM_MATRIX_H
#define SYM_MATRIX_H

#include <iostream>
#include "matrix.h"

////////////////////////
// Symmetrical Matrix class
// desc: A dynamically sized, but not resizeable, matrix with certain overloaded math operators
//       It is always a sqaure matrix
////////////////////////
template <class T>
class SymmetricMatrix : public Matrix<T>
{
  private:
    // the data of the matrix
    T** m_data;
    // the dimensions of the matrix
    int m_rows, m_cols;

    // Pre:  Since the matrix is assumed to be square, rows should equal cols  
    // Post: m_data is initialized to all zeros and the object is constructed
    // Desc: privatized constructor helper function
    void constructMatrix(const unsigned int rows, const unsigned int cols);

  public:

    // Pre:  none
    // Post: initializes the matrix as completely empty and m_data set to NULL
    // Desc: default constructor
    SymmetricMatrix(): m_data(NULL), m_rows(0), m_cols(0) {}

    // Pre:  size is greater than 0
    // Post: a triangular matrix is initialized
    // Desc: parameterized constructor
    SymmetricMatrix(const unsigned int size);

    // Pre:  source is a non-empty matrix
    // Post: a deep copy is made from source to the calling object
    // Desc: copy constructor
    SymmetricMatrix(const SymmetricMatrix<T>& source);

    // Pre:  none
    // Post: calling object is properly disposed of
    // Desc: deconstructor
    ~SymmetricMatrix();

    // Pre:  the matrix is square
    // Post: the dimension of the square matrix is returned
    // Desc: m_rows getter
    int size() const;

    // Pre:  none
    // Post: the number of rows is returned
    // Desc: get the number of rows
    int rows() const;

    // Pre:  none
    // Post: the number of rows is returned
    // Desc: get the number of rows
    int cols() const;

    //Pre:  T must have a zero and have such mathematical operators like +, -, *, and /
    //      mat must be square and vec.size() and size() must be equivalent 
    //Post: returns the vector containing the result to the sytem of equations
    //Desc: perform cholesky decomposition to solve the system of equations
    Vector<T> solve(const Vector<T>& vec) const;

    ////////////////////
    // Operator Overloads
    ////////////////////

    // Pre:  i and j must be within matrix bounds
    // Post: returns a pointer to the row and col of m_data specified with i and j
    //       if i and j point to a right of the triangular containing zeroes, a static local variable is returned
    // Desc: overloaded parenthetical operator for accessing
    T& operator()(const unsigned int i, const unsigned int j);

    // Pre:  i and j must be with matrix bounds
    // Post: returns a pointer to the row and col of m_data specified with i and j
    //       if i and j point to a right of the triangular containing zeroes, 0 is returned
    // Desc: overloaded const bracket operator
    const T operator()(const unsigned int i, const unsigned int j) const;

    // Pre:  the calling object and rhs must have the same dimensions
    //       T must work with + and =0
    // Post: a matrix is returned that is the result of element-wise addition between 
    //          rhs and the calling object
    // Desc: overloaded + operator
    SymmetricMatrix<T> operator+(const SymmetricMatrix<T>& rhs) const;

    // Pre:  the calling object and rhs must have the same dimensions
    //       T must work with - and =0  
    // Post: a matrix is returned that is the result of element-wise addition between 
    //          rhs and the calling object
    // Desc: overloaded - operator
    SymmetricMatrix<T> operator-(const SymmetricMatrix<T>& rhs) const;

    // Pre:  the calling object and rhs must have the same dimensions or the function will return the calling object
    //       T must work with *, +, +=, and =0  
    // Post: a matrix is returned that is the result of the dot product between 
    //          rhs and the calling object
    // Desc: overloaded * operator
    SymmetricMatrix<T> operator*(const SymmetricMatrix<T>& rhs) const;

    // Pre:  input must be initialized
    // Post: deep copies input into the calling object and returns the result
    // Desc: overloaded assignment operator
    SymmetricMatrix<T>& operator=(const SymmetricMatrix<T>& input);

    ////////////////////
    // Friend Functions
    ////////////////////

    // Pre:  N must work with * and =0
    //       mat must be non-empty
    // Post: returns a matrix which is the result of scalar * mat
    // Desc: overloaded * operator for scalar multiplication
    template <class N>
    friend SymmetricMatrix<N> operator*(const N& scalar, const SymmetricMatrix<N>& mat);

    // Pre:  vec.size() == mat.size() and both must be non-empty
    //       N must work with * and =0
    // Post: returns the dot product of vec * mat
    // Desc: overloaded * operator for vector - matrix multiplication
    template <class N>
    friend Vector<N> operator*(const Vector<N>& vec, const SymmetricMatrix<N>& mat);

    // Pre:  vec.size() == mat.size() and both must be non-empty
    //       N must work with * and =0
    // Post: returns the dot product of mat * vec
    // Desc: overloaded * operator for vector - matrix multiplication
    template <class N>
    friend Vector<N> operator*(const SymmetricMatrix<N>& mat, const Vector<N>& vec);

    // Pre:  input must be non-empty
    //       N must work with <<
    // Post: outputs the matrix to the stream
    // Desc:overloaded << operator
    template <class N>
    friend std::ostream& operator<<(std::ostream& stream, const SymmetricMatrix<N>& input);

    // Pre:  input must be non-empty
    //       N must work with >>
    // Post: inputs the matrix from the stream
    // Desc:overloaded >> operator
    template <class N>
    friend std::istream& operator>>(std::istream& stream, SymmetricMatrix<N>& input);
};

#include "symmetricmatrix.hpp"

#endif