CC=gcc
CFLAGS=-ansi -pedantic -Wall
OBJ = ep1sh.o

default: ep1sh

ep1sh.o: ep1sh.c

ep1sh: $(OBJ)
	gcc -o $@ *.o -pedantic -Wall -lreadline