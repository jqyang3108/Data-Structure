
CFLAGS = -Werror -Wshadow -Wall -O3 -g
GCC = gcc $(CFLAGS)

all: exam.o main.o
	$(GCC) exam.c main.c -o exam

%.o: %.c exam.h
	$(GCC) -c $<

test: all
	./exam

mem0: all
	valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes ./exam

mem1: all
	valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes ./exam


clean:
	/bin/rm -f *.o
	/bin/rm -f exam
	/bin/rm -f output
