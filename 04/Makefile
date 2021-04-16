CC=g++
FLAGS=-std=c++17 -Wall -Werror -fsanitize=address -Wextra

all: main.o bigint.o
	$(CC) $(FLAGS) main.o bigint.o -o main

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c

bigint.o: bigint.hpp bigint.cpp
	$(CC) $(FLAGS) bigint.cpp -c

test: main.o bigint.o
	$(CC) $(FLAGS) main.o bigint.o -o test
	./test

clean:
	rm -f *.o main
