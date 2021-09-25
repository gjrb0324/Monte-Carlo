CC = gcc
CFLAGS = -g -Wall -std=c99 -fopenmp -pthread
LDFLAGS = -fopenmp

buffon: main.o stat.o throw.o
	rm -f buffon
	$(CC) $(CFLAGS) main.o stat.o throw.o -o buffon $(LDFLAGS) -lm

main.o: needle.h main.c
	gcc -c -o main.o main.c

throw.o: needle.h throw.c
	gcc -c -o throw.o throw.c -fopenmp -pthread

stat.o: needle.h stat.c
	gcc -c -o stat.o stat.c -mavx -mfma

clear:
	rm -f *.o
	rm -f buffon

clear_output:
	rm -f output*.txt
