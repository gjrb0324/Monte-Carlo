#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include "throw.h"

int main(int argc, char *argv[]){
    FILE *fp = NULL;
    if(argc != 2)
	fp = fopen("output.csv", "w");
    else{
        fp = fopen(argv[1],"w");
    }
    if (fp == NULL){
	    fprintf(stderr, "Error : The file pointer is NULL\n");
	    return(1);
    }
    double avg_pi_list[1000001];
    double l; //l is a surrouunding length of the square, and it is also the 2*radius of the circle
    double x0 ; //x0 and y0 is the center of square and circle
    double y0 ;
    unsigned int n = 0;
    unsigned int stride = 10;
    
    printf("The surrounding length of the square? : ");
    scanf("%lf",&l);
    unsigned int i = 0;
   for(n=10; n<1000001; n = n + stride){
       avg_pi_list[i] = p_throw(l,n);
       fprintf(fp, "%u,%lf\n",n,avg_pi_list[n]);
       if(n==10 || n==100 || n==1000 || n== 10000 || n == 100000){
	       fprintf(stdout, "When %u times throw, the expected pi value is %lf\n", n, avg_pi_list[i]);
	       stride = n;
       }
       i++;
   } 
    

}

