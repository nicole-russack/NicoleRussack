CXX := g++
CXXFLAGS := -g -Wall --std=c++11

VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: internal-range-test bst-test avl-test

internal-range-test: internal-range-test.cpp internal-range.o 
	$(CXX) $(CXXFLAGS) $^ -o internal-range-test

internal-range.o: internal-range.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@



bst-test: bst-test.o
	$(CXX) $(CXXFLAGS) $^ -o bst-test

bst-test.o: bst-test.cpp bst.h
	$(CXX) $(CXXFLAGS) -c $< -o $@



avl-test: bst-test.o
	$(CXX) $(CXXFLAGS) $^ -o bst-test

bst-test.o: bst-test.cpp bst.h avlbst.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

	

clean:
	rm -f *~ *.o bst-test internal-range-test
