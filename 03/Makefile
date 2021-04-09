CC=g++
FLAGS=-std=c++17 -Wall -Werror -fsanitize=address -Wextra

all: main.o matrix.o
	$(CC) $(FLAGS) main.o matrix.o -o main

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c

matrix.o: matrix.hpp matrix.cpp
	$(CC) $(FLAGS) matrix.cpp -c

test: main.o matrix.o
	$(CC) $(FLAGS) main.o matrix.o -o test
	./test

clean:
	rm -f *.o main
