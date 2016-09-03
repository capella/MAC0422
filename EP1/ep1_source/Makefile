CC=gcc
CFLAGS= -g -Wall -Wno-unused-result -O0 -pedantic
OBJ = ep1.o

default: time2.o fcfs.o srtf.o load-process.o ep1.o 
	$(CC) $(CFLAGS) *.o -o ep1

ep1.o: ep1.c
	$(CC) $(CFLAGS) -ansi -c  *.c 

load-process.o: load-process/load-process.c load-process/load-process.h
	$(CC) $(CFLAGS) -ansi -c $^

fcfs.o: fcfs/fcfs.c fcfs/fcfs.h
	$(CC) $(CFLAGS) -ansi -c $^

srtf.o: srtf/srtf.c srtf/srtf.h
	$(CC) $(CFLAGS) -ansi -c $^

time2.o: time2/time2.c time2/time2.h
	$(CC) $(CFLAGS) -ansi -c $^

clean:
	$(RM) ep1
	$(RM) *.o
	find . -name "*.gch" -type f -delete
