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
    fprintf(fp,"======================================================================\n");
    unsigned int hit =0;
    #pragma omp parallel for reduction(+: hit)
    for(int i = 0; i < n ; i++){
	struct needle *nd= (struct needle *)malloc(sizeof(struct needle));
	fprintf(fp,"===============trial %d===============\n",i+1);
	nd->length = l;
	nd->angle = (rand()%1800)%180+ (double)(rand()%10000)/10000;
	fprintf(fp,"needle's angle: ");
	fprintf(fp,"%lf\n",nd->angle);
	nd->y=  fmod(rand()%10000,d) + (double)(rand()%10000)/10000;
	int sya = (int)nd->y/d;
	int syb = (int)(nd->y + l * sin((double)nd->angle * PI / (double)180) ) /d;
	fprintf(fp,"needle's ya: ");
	fprintf(fp,"%d\n",sya);
	fprintf(fp,"needle's yb: ");
	fprintf(fp,"%d\n",syb);
	if( sya != syb )
		hit++;
	fprintf(fp,"hit count so far : %u \n",hit);
	free(nd);
	nd = NULL;
	fprintf(fp,"=====================================\n");
    }
    //expected pi
    double epi = (double)hit/(double)n;
    epi = 2*l/(epi * d);
    fprintf(fp,"Hit : %d times, expected PI: %lf\n",hit, epi);
    fprintf(fp,"======================================================================\n");
    printf("Expected PI: %lf\n",epi);
    
    return 0;



}
