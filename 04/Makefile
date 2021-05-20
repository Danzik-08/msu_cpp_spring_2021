CC=g++
FLAGS=-std=c++17

all: main

main: main.o bigint.o
	$(CC) main.o bigint.o $(FLAGS) -o main

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

bigint.o: bigint.cpp bigint.hpp
	$(CC) $(FLAGS) -c bigint.cpp

test:
	./main

clean:
	rm -rf *.o main
