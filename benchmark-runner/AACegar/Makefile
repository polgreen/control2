CC=g++

#list of source files
SOURCE= src/RowSort.cpp src/Scalar.cpp src/Set.cpp src/MatrixToString.cpp\
      src/Tableau.cpp src/DualSimplex.cpp src/VertexEnumerator.cpp \
      src/Polyhedra.cpp src/AbstractPolyhedra.cpp src/EigenPolyhedra.cpp \
      src/JordanSolver.cpp src/JordanMatrix.cpp src/AccelMatrix.cpp \
      src/AbstractMatrix.cpp src/DynamicalSystem.cpp src/ProgramOptions.cpp \
      src/RefinedDynamicalSystem.cpp src/Synthesiser.cpp main.cpp

#include directories
INCLUDE= -I./include -I./mpreal \
         -I../Eigen -I../Eigen/unsupported/Eigen/ \
         -I../boost -I../boost/boost \
         -I /usr/include/eigen3 \
         -I/opt/local/include

#object files directly derived from source files
OBJECTS=$(SOURCE:.cpp=.o)

#name of executable
EXEC = axelerator

#compile options. Optimised for speed. 
CFLAGS= -o3 $(INCLUDE) -std=c++98

#full compilation
all: $(OBJECTS) $(EXEC)

#build each object file
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

#link object files
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ -lmpfr 

#clean object files and executable
clean:
	rm -f $(OBJECTS) $(EXEC)
