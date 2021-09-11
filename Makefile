CC = gcc
CFLAGS = -g -Wall -std=c99 -mavx -mfma -fopenmp -pthread
LDFLAGS = -fopenmp

buffon:
	rm -f buffon
	$(CC) $(CFLAGS) main.c stat.c -o buffon $(LDFLAGS) -lm

clear:
	rm -f *.o
	rm -f buffon

clear_output:
	rm -f output*.txt
