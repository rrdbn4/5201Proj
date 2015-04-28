///////////////////////
// vector.h
///////////////////////
// Author:     ROBERT DUNN
// Instructor: Clayton Price
// Course:     CS 5201
// Purpose:    class declaration for the vector class
///////////////////////

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

////////////////////////
// Vector class
// desc: A dynamically sized, but not resizeable, vector with certain overloaded math operators
////////////////////////
template <class T>
class Vector
{
  private:
    int m_size;
    T* m_data;

  public:
    // Pre:  size is the length of the array
    // Post: the calling object is initialized and all elements are set to zero
    // Desc: Parameterized constructor
    Vector(const unsigned int size);

    // Pre:  none
    // Post: A completely empty and pretty much unusable vector is created
    // Desc: default constructor. This only exists because some things require a default constructor
    Vector();

    // Pre:  none
    // Post: A deep copy is made from source to the calling object which constructs the calling object
    // Desc: copy constructor
    Vector(const Vector<T>& source);

    // Pre:  none
    // Post: the calling object is deconstructed and memory is freed
    // Desc: deconstructor
    ~Vector();

    // Pre:  none
    // Post: returns m_size
    // Desc: getter for m_size
    int size() const { return m_size; }

    // Pre:  T has the unary - operator overloaded
    // Post: returns a vector with all of its elements negated
    // Desc: overloaded unary - operator
    Vector<T> operator-() const;

    // Pre:  the calling object and rhs must have the same m_size
    //       T must have the binary - operator defined
    // Post: returns a vector with the result of element-wise subtraction of rhs fromt he calling object
    // Desc: overloaded binary - operator
    Vector<T> operator-(const Vector<T>& rhs) const;

    // Pre:  the calling object and rhs must have the same m_size
    //       T must be a type with the binary + operator defined
    // Post: returns a vector with the result of element-wise addition between the calling opbject and rhs
    // Desc: overloaded + operator
    Vector<T> operator+(const Vector<T>& rhs) const;

    // Pre:  the calling object and rhs must have the same m_size
    //       T must be a type with the binary * operator defined
    // Post: returns the dot product of the calling object and rhs
    // Desc: overloaded * operator
    T operator*(const Vector<T>& rhs) const;

    // Pre:  the calling object and rhs must have the same m_size
    // Post: deep copies input into the calling object and returns the result
    // Desc: overloaded assignment operator
    Vector<T>& operator=(const Vector<T>& input);

    // Pre:  i must be less than m_size
    //       the vector can't be empty
    // Post: returns the ith element in the vector
    //       returns the 0th element if i is >= m_size
    // Desc: overloaded bracket operator acting as getter and setter
    T& operator[](const unsigned int i);

    // Pre:  i must be less than m_size
    //       the vector can't be empty
    // Post: returns the ith element in the vector
    //       returns the 0th element if i is >= m_size
    // Desc: overloaded bracket operator acting as getter
    const T& operator[](const unsigned int i) const;

    ////////////////////
    // Friend Functions
    ////////////////////

    // Pre:  N must be a type with the binary * operator defined
    // Post: returns a vector that is the scalar times rhs
    // Desc: overloaded * operator for scalar multiplication
    template <class N>
    friend Vector<N> operator*(const N& scalar, const Vector<N>& rhs);

    // Pre:  N must have << defined
    // Post: outputs the elements of the vector in a readable format to the stream
    // Desc: overloaded << operator
    template <class N>
    friend std::ostream& operator<<(std::ostream& stream, const Vector<N>& input);

    // Pre:  N must have >> defined
    //       m_size must correspond with the number of things there are to read in
    // Post: reads in the elements of the vector from the stream
    // Desc: overloaded >> operator
    template <class N>
    friend std::istream& operator>>(std::istream& stream, Vector<N>& input);
};

#include "vector.hpp"

#endif