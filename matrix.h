///////////////////////
// matrix.h
///////////////////////
// Author:     ROBERT DUNN
// Instructor: Clayton Price
// Course:     CS 5201
// Purpose:    class declaration for the abstract base matrix class
///////////////////////

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <cmath>

////////////////////////
// Matrix class
// desc: An abstract base interface for all the specialized child matrix classes
////////////////////////
template <class T>
class Matrix
{
  private:
    // Desc: The private matrix builder function for use by constructors
    virtual void constructMatrix(const unsigned int rows, const unsigned int cols)=0;

  public:
    // Desc: get the numbers of rows and columns
    virtual int size() const=0;

    // Desc: get the number of rows
    virtual int rows() const=0;

    // Desc: get the number of columns
    virtual int cols() const=0;

    // Desc: matrix accessor operator overload
    virtual T& operator()(const unsigned int i, const unsigned int j)=0;

    // Desc: const matrix accessor operator overload
    virtual const T operator()(const unsigned int i, const unsigned int j) const=0;

    //Desc: to solve the system of Ax=b
    virtual Vector<T> solve(const Vector<T>& vec) const=0;

};

#endif