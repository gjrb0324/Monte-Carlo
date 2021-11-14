CC=gcc
CFLAGS=-g -Wall -std=c99 -fopenmp -pthread
LDFLAGS=-fopenmp -lm

proj5: main.o stat.o proj5.o
	rm -f proj5.out
	$(CC) $(CFLAGS) main.o stat.o proj5.o -o proj5 $(LDFLAGS)

main.o: main.c proj5.h
	$(CC) -g -c -o $@ $<

proj5.o: proj5.c proj5.h
	$(CC) -g -c -o $@ $< -lm -fopenmp -pthread
stat.o: stat.c proj5.h
	$(CC) -g -c -o $@ $< -mavx -mfma

clear:
	rm -f *.o
	rm -f proj5
