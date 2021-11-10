#include "proj3.h"
#include <math.h>
#include <stdio.h>
#define PI 3.1415926535

double* strange_func(double x, double y){
	//Allocating memory to result pointer at heap memory
	//to store result values even if we exit this function
	double *result = (double *)malloc(ARR_SIZE * sizeof(double));
	srand(time(NULL));

	//Using multi-threads
#pragma omp parallel for
	for (int n = 0; n<ARR_SIZE; n++){
	//Random vairable theta and r	
		double theta = (double) (rand()%10000)/10000;
		double r = (double)(rand()%10000)/10000;
	
		//multiply 2*PI to set range of integration to 0 to 1
		theta = 2*PI*theta;
		
		//Compute function using random theta and r values
		double exp = (1+ ( pow( (x-r*cos(theta)), 2 ) +
				pow( (y-r*sin(theta)), 2 ) )/(1-r*r) );
		exp = pow(exp,-0.5);

		//multiply 2*PI to set range of integration to 0 to 1
		result[n] = 2*PI*exp;
		}
	return result; 
}
