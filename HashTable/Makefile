CXX=g++
CXXFLAGS=-g -Wall -std=c++11 
# Uncomment for parser DEBUG
#DEFS=-DDEBUG


all: ht-test ht-perf str-hash-test

ht-test: ht-test.cpp ht.h
	$(CXX) $(CXXFLAGS) $(DEFS) $< -o $@

# enable optimizations for performance tests with -O3
ht-perf: ht-perf.cpp ht.h
	$(CXX) -Wall -std=c++11 -O3 $(DEFS) $< -o $@

str-hash-test: str-hash-test.cpp hash.h
	$(CXX) $(CXXFLAGS) $(DEFS) $< -o $@





clean:
	rm -f *~ *.o *.sol *.out ht-test ht-perf str-hash-test 
