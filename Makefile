CXX=g++
CXXFLAGS=-g
LIBS=-lm
TREESIM_OBJECTS=main.o Plot.o Tree.o Branch.o
MATRIX_OBJECTS=matrix.o

all: TreeSim matrix

TreeSim: $(TREESIM_OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(TREESIM_OBJECTS) -o TreeSim

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Plot.o: Plot.cpp Plot.h
	$(CXX) $(CXXFLAGS) -c Plot.cpp -o Plot.o

Tree.o: Tree.cpp Tree.h
	$(CXX) $(CXXFLAGS) -c Tree.cpp -o Tree.o

Branch.o: Branch.cpp Branch.h
	$(CXX) $(CXXFLAGS) -c Branch.cpp -o Branch.o

matrix: $(MATRIX_OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(MATRIX_OBJECTS) -o matrix

matrix.o: matrix.cpp
	$(CXX) $(CXXFLAGS) -c matrix.cpp -o matrix.o

clean:
	rm *.o TreeSim matrix
