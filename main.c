#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include "needle.h"
#define PI 3.1415926535
int main(int argc, char *argv[]){
    FILE* fp = NULL;
   //Controlling the error cases
   //When no outputfile is defined,
   //open arbitrary output.txt 
    if(argc != 2){
	fp = fopen("output.txt", "w");
    }
    //else, open second argument
    else{
        fp = fopen(argv[1],"w");
    }
    //When the file pointer is still NULL;
    if(fp == NULL){
        fprintf(stderr, "Error: The file pointer is NULL\n");
	return(1);
    }
    
    //values that will be used in this program
    double l =0; // Length of the needle
    double d =0; // Distance between two lines
    unsigned int n = 0; //Number of times needles will be thrown
    double pi_list[100]; //Array that contains the values of computed pi at each thrown.
    
    printf("Type the distance between two lines: ");
    scanf("%lf",&d);
    printf("Type the length of a needle: ");
    scanf("%lf",&l);
    
    if(l>d){
        fprintf(stderr, "Error : the lengthe of a needle can't be longer than the distance between two lines");
	exit(1);
    }

    printf("How many times will you throw? ");
    scanf("%u",&n);

    srand(time(NULL)); //srand to get better pseudo-random number than from just using random() function
    
    //We will get 100 computed pi values
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

    fprintf(fp,"%d - expected PI: %lf\n",k, epi);
    printf("%d - Expected PI: %lf\n",k, epi);
    }
    double pi_avg = mean(pi_list,100);
    double pi_sd = sd(pi_list, pi_avg, 100);
    fprintf(fp, "Mean of 100 times : %lf, SD of 100 times: %lf \n", pi_avg, pi_sd);
    printf("Mean of 100 times : %lf, SD of 100 times : %lf \n",pi_avg, pi_sd);
    

    return 0;



}
