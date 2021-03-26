CC=g++
FLAGS=-std=c++17 -Wall -Werror -fsanitize=address -Wextra

all: main.o allocator.o
	$(CC) $(FLAGS) main.o allocator.o -o main

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c

allocator.o: allocator.hpp allocator.cpp
	$(CC) $(FLAGS) allocator.cpp -c

test: main.o allocator.o
	$(CC) $(FLAGS) main.o allocator.o -o test
	./test

clean:
	rm -f *.o main
