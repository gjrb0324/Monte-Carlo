#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include "needle.h"
#define PI 3.1415926535
int main(int argc, char *argv[]){
    if(argc != 2){
	fprintf(stderr, "Error: Usage - ./buffon [output_file_name]\n");
	return(1);
    }

    FILE* fp = fopen(argv[1],"w");
    if(fp == NULL){
        fprintf(stderr, "Error: The file pointer is NULL\n");
	return(1);
    }
    double l =0;
    double d =0;
    unsigned int n = 0;
    
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
    srand(time(NULL));
    double pi_list[100];
    for(int k = 0; k < 100; k++){
    unsigned int hit =0;
    #pragma omp parallel for reduction(+: hit)
    for(int i = 0; i < n ; i++){
	struct needle *nd= (struct needle *)malloc(sizeof(struct needle));
	nd->length = l;
	nd->angle = (rand()%1800)%180+ (double)(rand()%10000)/10000;
	nd->y=  fmod(rand()%10000,d) + (double)(rand()%10000)/10000;
	int sya = (int)nd->y/d;
	int syb = (int)(nd->y + l * sin((double)nd->angle * PI / (double)180) ) /d;
	if( sya != syb )
		hit++;
	free(nd);
	nd = NULL;
    }
    //expected pi
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
