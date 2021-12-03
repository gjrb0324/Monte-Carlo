CC=gcc
CFLAGS=-g -Wall -std=c99 -fopenmp -pthread
LDFLAGS=-fopenmp -lm

proj6: proj6.o main.o stat.o
	rm -f proj6
	$(CC) $(CFLAGS) main.o stat.o proj6.o -o proj6 $(LDFLAGS)

main.o: main.c proj6.h
	$(CC) -g -c -o $@ main.c

proj6.o: proj6.c proj6.h
	$(CC) -g -c -o $@ $< -lm -fopenmp -pthread
stat.o: stat.c proj6.h
	$(CC) -g -c -o $@ $< -mavx -mfma

clear:
	rm -f *.o
	rm -f proj6
