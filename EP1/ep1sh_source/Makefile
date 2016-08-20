CC=gcc
CFLAGS=-static -g  -ansi -pedantic -Wall
OBJ = ep1sh.o

default: ep1sh

ep1sh.o: ep1sh.c

ep1sh: $(OBJ)
	gcc -g -o $@ *.o -pedantic -Wall -lreadline

clean:
	rm ep1sh.o ep1sh
