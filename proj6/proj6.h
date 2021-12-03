#ifndef _PROJ3_H
#define _RROJ3_H

#include <math.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#ifndef min
#define min(a,b) (( (a) < (b) )? (a) : (b))
#endif

#ifndef TMAX
#define TMAX 5
#endif

#ifndef TMIN
#define TMIN 0.1
#endif

struct lat {
	unsigned int size;
	char *lattice;
	double hamiltonian;
    double energy;
    double magnet;
};

extern double etot(struct lat * lat_struct,unsigned int n, char ferro, double h);
extern char matro(double e_diff, double T);
extern void cpy_lattice(char *lattice1, char*lattice2, unsigned int n);
extern void p_lattice(char *lattice, unsigned int n);
extern void transpose(char *lattice, unsigned int n);
extern void resize_arr(unsigned int *arr, size_t arr_size,unsigned int elem, unsigned int total_size);
extern void init_lattice(char *lattice, unsigned int n);
extern double magnet(char * lattice, unsigned int n);
extern double energy(char * lattice, unsigned int n);
#endif
