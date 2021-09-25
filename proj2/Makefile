CC=gcc
CFLAGS=-g -Wall -std=c99 -fopenmp -pthread
LDFLAGS = -fopenmp

proj2: main.o stat.o throw.o
	rm -f proj2
	$(CC) $(CFLAGS) main.o stat.o throw.o -o proj2 $(LDFLAGS) -lm

main.o: throw.h main.c
	gcc -c -o main.o main.c
throw.o : throw.h throw.c
	gcc -c -o throw.o throw.c -fopenmp -pthread
stat.o : throw.h stat.c
	gcc -c -o stat.o stat.c -mavx -mfma

clear:
	rm -f *.o 
	rm -f proj2


