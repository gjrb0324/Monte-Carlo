#include <stdio.h>
#include "proj3.h"

int main(int argc, char** argv){
	FILE *fp;
	if (argc != 2)
		fp=fopen("output.data","w");
	else{

		if ( (fp =fopen(argv[1],"w")) == NULL)
			fprintf(stderr, "Error: Can't open %s",argv[1]);
	}
	srand(time(NULL));
	double result;
	double x=-10;
	double y=-10;

	//Computing result of function(x,y) (x,y are in range -10 to 10, increasing 0.5 each time)
	for(x; x<=10; x=x+0.5){
		for(y;y<=10;y=y+0.5){
			//result pointer to get computed value, which is heap allocated pointer
			double* result_ptr;

			//I divided two steps 1. run function, 2. computing mean = result of function(x,y)
			//becasue if we are trying to compute mean value in strange_func function,
			//Stack overflowed and the function returns SEGFAULT.

	       		result_ptr=strange_func(x,y);
			result=mean(result_ptr, ARR_SIZE);

			//print values
			printf("%lf %f %lf\n",x,y,result);
			fprintf(fp,"%lf ",result);
			//free heap allocated pointer, result_ptr
			free(result_ptr);
			result_ptr=NULL;
		}
		fprintf(fp,"\n");
		y=-10;
	}
	
	return 0;
}


