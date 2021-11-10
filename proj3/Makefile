CC=gcc
CFLAGS=-g -Wall -std=c99 -fopenmp -pthread
LDFLAGS=-fopenmp -lm

proj3: main.o stat.o proj3.o
	rm -f proj3.out
	$(CC) $(CFLAGS) main.o stat.o proj3.o -o proj3.out $(LDFLAGS)

main.o: proj3.h main.c
	$(CC) -g -c -o main.o main.c

proj3.o: proj3.h proj3.c
	$(CC) -g -c -o proj3.o proj3.c -lm -fopenmp -pthread
stat.o: proj3.h stat.c
	$(CC) -g -c -o stat.o stat.c -mavx -mfma

clear:
	rm -f *.o
	rm -f proj3.out
