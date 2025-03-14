CC = gcc

CFLAGS = -Wall -Wextra -std=c11

all: reverse tests

reverse: reverse.c
	$(CC) $(CFLAGS) reverse.c -o reverse

tests: tests.c
	$(CC) $(CFLAGS) tests.c -o tests

test: reverse tests
	./tests

clean:
	rm -f reverse tests *.o output*.txt test*.txt temp*.txt empty.txt single.txt
