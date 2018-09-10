# ECE368 PA2 Makefile

CFLAGS = -Werror -Wall -Wshadow -O3 -g
GCC = gcc $(CFLAGS)

all: sorting.o main.o
	$(GCC) sorting.c main.c -o proj2

%.o: %.c sorting.h
	$(GCC) -c $<

test: all	
	./proj2 given_files/1000.b output

memory: all
	valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes proj2 given_files/15.b output 

clean:
	/bin/rm -f *.o
	/bin/rm -f proj2
	/bin/rm -f output
