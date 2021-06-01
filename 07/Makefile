CC = g++

FLAGS = -std=c++17 -Wall


all: Vector.tpp
	$(CC) $(FLAGS) test_for_Vector.cpp -o test.exe
test: test.exe
	./test.exe
clean:
	rm test.exe
	rm task.o
