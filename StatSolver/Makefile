CXX := g++
CXXFLAGS := -g -Wall --std=c++11

VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: gridpaths sat_solver

gridpaths: gridpaths.cpp 
	$(CXX) $(CXXFLAGS) $^ -o gridpaths


sat_solver: sat_solver.cpp 
	$(CXX) $(CXXFLAGS) $^ -o sat_solver


	

clean:
	rm -f *~ *.o gridpaths sat_solver