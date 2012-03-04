CXX=g++
CXXFLAGS=-g
LIBS=-lm
OBJECTS=main.o Plot.o Tree.o Branch.o
PROJECT=TreeSim

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJECTS) -o $(PROJECT)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Plot.o: Plot.cpp Plot.h
	$(CXX) $(CXXFLAGS) -c Plot.cpp -o Plot.o

Tree.o: Tree.cpp Tree.h
	$(CXX) $(CXXFLAGS) -c Tree.cpp -o Tree.o

Branch.o: Branch.cpp Branch.h
	$(CXX) $(CXXFLAGS) -c Branch.cpp -o Branch.o

clean:
	rm *.o $(PROJECT)
