CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable
all: my_prog
test: my_prog
	./my_prog

my_prog: test.o
	$(CXX) $(CXXFLAGS) -o my_prog test.o

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -rf *.o my_prog
