CC=g++
FLAGS=-std=c++17 -Wall -Werror -fsanitize=address -Wextra
#FLAGS=
all: main.o allocator.o
	$(CC) $(FLAGS) main.o allocator.o -o main

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c

allocator.o: allocator.hpp allocator.cpp
	$(CC) $(FLAGS) allocator.cpp -c

clean:
	rm -f *.o main
