CC=g++
FLAGS=-std=c++17 -Wall -Werror -fsanitize=address -Wextra

all: main.o 
	$(CC) $(FLAGS) main.o  -o main

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c

test: main.o 
	$(CC) $(FLAGS) main.o -o test
	./test

clean:
	rm -f *.o main
