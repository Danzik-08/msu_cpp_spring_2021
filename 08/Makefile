CC = g++

FLAGS = -std=c++17 -Wall


all: Thread_Pool.tpp Thread_Pool.hpp
	$(CC) $(FLAGS) test_for_Thread_Pool.cpp -o test.exe -pthread
test: test.exe
	./test.exe
clean:
	rm test.exe
