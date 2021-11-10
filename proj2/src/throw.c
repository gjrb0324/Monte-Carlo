#include "throw.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>


double p_throw(double l, unsigned int n){
    double x0 = l/2;
    double y0 = l/2;
    double pi_list[100];
    srand(time(NULL));
    for(int k = 0 ; k <100; k++){
        unsigned int hit = 0;

//#pragma omp parallel for reduction (+: hit)
	for(int i = 0; i< n; i++){
	    double x = fmod(rand()%10000,l) + (double)(rand()%10000)/10000;
	    double y = fmod(rand()%10000,l) + (double)(rand()%10000)/10000;
            double d = sqrt(pow(x-x0,2) + pow(y-y0,2));
	    if(d < l/2)
		    hit++;
	}
	double epi = ((double)hit/n)*4;
	pi_list[k] = epi;
    }
    double pi_avg = mean(pi_list,100);
    return pi_avg;
}
