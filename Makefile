############################################################################
# mazer2016 - an implementation of the assignment 1 specification for
# CPT323 - Object Oriented Programming Using C++.
#
# Developed by Paul Miller. This solution can be used as a starting point for
# Assignment 2.
############################################################################

#object files created as part of compilation
OBJECTS= data/Maze.o generators/Generator.o generators/ABGenerator.o \
	generators/EllerGenerator.o main.o args/action.o args/arg_processor.o \
	solvers/solver.o solvers/DFSSolver.o solvers/BFSSolver.o\
	solvers/DijkstraSolver.o
#header files included in various files.
HEADERS=data/Maze.h generators/Generator.h args/action.h \
	args/arg_processor.h constants/constants.h solvers/BFSSolver.h \
	data/Edge.h data/Cell.h solvers/solver.h generators/ABGenerator.h \
	generators/EllerGenerator.h solvers/DFSSolver.h \
	solvers/DijkstraSolver.h
CXXFLAGS=-Wall -pedantic -std=c++14
LFLAGS=
#how do we create the binary for execution
all: $(OBJECTS)
	g++ $(LFLAGS) $(OBJECTS) -o mazer

#how do we make each individual object file? 
%.o: %.cpp $(HEADERS)
	g++ $(CXXFLAGS) -c $< -o $@

#how do we do cleanup so that we only have the source files?
.PHONY:clean
clean:
	rm -f $(OBJECTS) mazer TAGS

#run program in debug mode
debug:CXXFLAGS+=-DDEBUG -g
debug:clean all

#clean all files needed for compilation as well as svg files
.PHONY:svgclean
svgclean : clean
	rm -f *.svg
