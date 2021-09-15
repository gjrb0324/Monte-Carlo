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
    unsigned int n = 1; //Number of times needles will be thrown
    double avg_pi_list[1000001]; //Array that contains the values of computed pi at each thrown.
    unsigned int stride = 10; 
    printf("Type the distance between two lines: ");
    scanf("%lf",&d);
    printf("Type the length of a needle: ");
    scanf("%lf",&l);
    
    if(l>d){
        fprintf(stderr, "Error : the lengthe of a needle can't be longer than the distance between two lines");
	exit(1);
    }

    for( n=10; n<1000001;n= n + stride){
        avg_pi_list[n] = nd_throw(d,l,n);
	fprintf(fp, "%u,%lf\n",n,avg_pi_list[n]);
	if(n ==10 || n == 100 || n==1000 || n==10000|| n == 100000 || n== 1000000){
	    fprintf(stdout,"When %u times needle throwing, the expected pi vlaue is %lf\n",n,avg_pi_list[n]);
    	    stride = n;
	}
    }
    return 0;

}
