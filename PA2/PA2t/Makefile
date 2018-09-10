# ECE368 PA2 Makefile

CFLAGS = -Werror -Wall -Wshadow -O3 -g
GCC = gcc $(CFLAGS)

all: sorting.o main.o
	$(GCC) sorting.c main.c -o proj2

%.o: %.c sorting.h
	$(GCC) -c $<

test: all
	./proj2 15.b out15.b

memory: all
	valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes proj2 15.b test_output

clean:
	/bin/rm -f *.o
	/bin/rm -f proj2
	/bin/rm -f test_output test_seq
