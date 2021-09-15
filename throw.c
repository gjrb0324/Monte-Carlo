#include "needle.h"
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#define PI 3.1415926535

double nd_throw(double d, double l, unsigned int n){
    double pi_list[100];
    srand(time(NULL));
    //We will get 10 computed pi values
    for(int k = 0; k < 100; k++){
    unsigned int hit =0; //how many needles hit the line
    
    // omp parallel for to use multi-threading
    // reduction phrase to avoid race condition
    #pragma omp parallel for reduction(+: hit)
    for(int i = 0; i < n ; i++){
	struct needle *nd= (struct needle *)malloc(sizeof(struct needle)); //memory allcation to avoid SEGFAULT error
	nd->length = l;
	
	//Random number Generating
	//We should use modular arithmetic for generating fair random number
	//Specific explanation is in the report
	//angle between the needle and the line
	nd->angle = (rand()%1800)%180+ (double)(rand()%10000)/10000;
	//y position of the center of needle
	nd->y=  fmod(rand()%10000,d) + (double)(rand()%10000)/10000;
	
	//qya - quotient of ya (center of the needle's y position) divided by d
	//qyb - quotient of yb (heighest y position of the needle) divided by d
	int qya = (int)nd->y/d; 
	int qyb = (int)(nd->y + l * sin((double)nd->angle * PI / (double)180) ) /d;
	
	//Difference of qya and qyb means that needle hit the line
	if( qya != qyb )
		hit++;
	free(nd);
	nd = NULL;
    }
    //expected pii
    double epi = (double)hit/(double)n;
    epi = 2*l/(epi * d);
    pi_list[k] = epi;

    }
    double pi_avg = mean(pi_list,100);
    return pi_avg;
}
