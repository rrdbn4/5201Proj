########################
#--MAKEFILE--
########################
## Author:     ROBERT DUNN
## Instructor: Clayton Price
## Course:     CS 5201
## Purpose:    makefile for assignment 5
########################

####
# A makefile for assignment 5
####

CXX = /usr/bin/g++

# Generic g++ compiler flags
CXXFLAGS = -W -Wall -g -pedantic-errors -std=c++11

OBJECTS =  driver.o

.SUFFIXES: .cpp

.cpp.o: $<
	$(CXX) -c $(CXXFLAGS) $< -o $@

default: all

all: driver

driver: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

clean:
	-@rm -f  core > /dev/null 2>&1
	-@rm -f driver > /dev/null 2>&1
	-@rm -f $(OBJECTS) > /dev/null 2>&1

# Dependency lists
driver.o:    driver.cpp vector.h vector.hpp matrix.h uppertrimatrix.h uppertrimatrix.hpp \
	           lowertrimatrix.h lowertrimatrix.hpp densematrix.h densematrix.hpp \
	           diagmatrix.h diagmatrix.hpp tridiagmatrix.h tridiagmatrix.hpp symmetricmatrix.h symmetricmatrix.hpp


########################
# END OF FILE
########################
