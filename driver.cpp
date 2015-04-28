///////////////////////
// driver.cpp
///////////////////////
// Author:     ROBERT DUNN
// Instructor: Clayton Price
// Course:     CS 5201
// Purpose:    the main driver with int main and such for assignment 5
///////////////////////

#include <iostream>
#include <iomanip>
#include <fstream>
#include "vector.h"
#include "uppertrimatrix.h"
#include "lowertrimatrix.h"
#include "densematrix.h"
#include "diagmatrix.h"
#include "symmetricmatrix.h"
#include "tridiagmatrix.h"

int main(int argv, char** argc)
{
  if(argv < 2)
  {
    std::cout << "No file name specified. Exiting..." << std::endl;
    return 0;
  }

  std::cout << "Opening \"" << argc[1] << "\"" << std::endl;

  std::ifstream fin;                              // open the file stream
  fin.open(argc[1]);                              // open the file 
  int size;

  if(fin >> size)                                 // read in the number of lines in the file
  {
    DenseMatrix<double> mat(size);
    fin >> mat;
    Vector<double> vec(size);
    fin >> vec;

    std::cout << "Input matrix: " << std::endl;
    std::cout << mat << std::endl << std::endl;
    std::cout << "Input vector: " << std::endl;
    std::cout << vec << std::endl << std::endl;
    std::cout << "test: " << std::endl;
    std::cout << (mat + mat) << std::endl << std::endl;

    std::cout << std::endl << "The solution to Ax=b:" << std::endl;
    std::cout << mat.solve(vec) << std::endl;
  }
  else
    std::cout << "File read error. Exiting..." << std::endl;

  fin.close();                                    // close the file stream

  return 0;                                       // all good things must come to an end
}