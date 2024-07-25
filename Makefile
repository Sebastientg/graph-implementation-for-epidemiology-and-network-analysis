# Use g++ with C++11 support
# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -pedantic -g -O0 -std=c++11
OUTFILES = GraphTest

# Default target
all: $(OUTFILES)

# Build the main executable
$(OUTFILES): GraphTest.cpp Graph.cpp DisjointSet.cpp
	$(CXX) $(CXXFLAGS) -o $(OUTFILES) GraphTest.cpp Graph.cpp DisjointSet.cpp

# Build with profiling support
gprof: GraphTest.cpp Graph.cpp DisjointSet.cpp
	make clean
	$(CXX) $(CXXFLAGS) -pg -o $(OUTFILES) GraphTest.cpp Graph.cpp DisjointSet.cpp

# Clean up build files
clean:
	$(RM) $(OUTFILES) *.o
