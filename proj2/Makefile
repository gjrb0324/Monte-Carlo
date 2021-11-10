CC=gcc
CFLAGS=-g -Wall -std=c99 -fopenmp -pthread
LDFLAGS=-fopenmp

proj2: src/main.o src/stat.o src/throw.o
	rm -f proj2.out
	$(CC) $(CFLAGS) src/main.o src/stat.o src/throw.o -o proj2.out $(LDFLAGS) -lm

main.o: src/throw.h src/main.c
	gcc -g -c -o src/main.o src/main.c
throw.o : src/throw.h src/throw.c
	gcc -g -c -o src/throw.o src/throw.c -fopenmp -pthread
stat.o : src/throw.h src/stat.c
	gcc -g -c -o src/stat.o src/stat.c -mavx -mfma

clear:
	rm -f *.o 
	rm -f proj2.out


