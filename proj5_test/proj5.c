#include "proj5.h"

double etot(char* lattice, unsigned int n, char ferro, double h){
	int magnet = 0;
	int energy = 0;
	int pos = 0;
	double result;

	//Find M
	for (unsigned int  i=0; i<n; i++){
		for(unsigned int j=0;j<n ; j++){
			pos = (i*n+j); 
			magnet+=lattice[pos];

		}
	}
	//Find E
	//Horizontal part energy
	for (unsigned int i=0; i<n; i++){
		for(unsigned int j=0; j<n ; j++){
			
			pos = (i*n +j);
			
			//if  i ==1 or i== (m-1) expand lattice
			if(j == 0){
				energy+=( lattice[pos] * (*(lattice+i*n+n-1)) );
				energy+=( lattice[pos] * lattice[pos+1] );
			}
			else if( j == (n-1))
				energy+=( lattice[pos] * (*(lattice+i*n)) );
			else
				energy+=( lattice[pos] * lattice[pos+1]);
		}
	}
	//transpose to decrease stride and increase hit rate
	transpose(lattice, n);

	//Vertical part energy
	for (unsigned int i=0; i<n; i++){
		for(unsigned int j=0; j<n ; j++){
			
			pos = (i*n +j);
			
			//if  i ==1 or i== (m-1) expand lattice
			if(j == 0){
				energy+=( lattice[pos] * (*(lattice+i*n+n-1)) );
				energy+=( lattice[pos] * lattice[pos+1]);
			}
			else if( j == (n-1))
				energy+=( lattice[pos] * (*(lattice+i*n)) );
			else
				energy+=( lattice[pos] * lattice[pos+1]);
		}
	}
	transpose(lattice, n);

	result=  (-1) * ferro * energy - h * magnet ;
	return result;
}

char matro(double e_diff,double T){
	//1 for true(flip)
	//0 for don't flip
	if(e_diff <= 0){
		return 1;
	}

    double val = exp( (-1) * e_diff/T);
    unsigned char fcount=0;
    double r=0; //random number
    do{
        srand(time(NULL));
        r = (double)(rand()%10000)/10000;
        fcount++;
	}while( val <r  && fcount <11);
    if (val >r){
		return 1;
	}
	else
		return 0;
}

//copy lattice 1's data to lattice 2
void cpy_lattice(char *lattice1, char *lattice2, unsigned int n){
	unsigned int pos;
	for(unsigned int i=0; i<n;i++){
		for(unsigned int j=0; j<n; j++){
			pos = i*n+j;
			lattice2[pos] = lattice1[pos];
		}
	}
}


void p_lattice(char *lattice, unsigned int n){
	printf("\n<white circles are for spin 1, blacks are for spin -1>\n");
	for(unsigned int i = 0; i<n ;i++){
		for(unsigned int j=0;j<n;j++){
			unsigned int pos=n*i+j;
			if(j == (n-1)){
				if(lattice[pos] == 1)
					printf("\u25cf\n");
				else
					printf("\u25cb\n");
			}
			else{ 
				if(lattice[pos] == 1)
					printf("\u25cf - ");
				else
					printf("\u25cb - ");
			}
		}
	}
	fflush(stdin);
}

void transpose(char *lattice, unsigned int n){
	
	unsigned int l_min= 0;
	for(unsigned int i=0;i<n; i++){
		for(unsigned int j=0;j<n;j++){
			if( (i !=0) && ((i==j) || (min(i,j) <= l_min)) )
				continue;
			else{
				char temp= lattice[i*n+j];
				lattice[i*n+j] = lattice[j*n+i];
				lattice[j*n+i] = temp;
			}
		}
		
		l_min = i;
	}
}


void resize_arr(unsigned int *arr, size_t arr_size, unsigned int elem, unsigned int total_size){
	unsigned int pos  =0 ;
	for(unsigned int i=0; i<arr_size; i++){
		if(arr[i] == elem)
			pos =i;
	}
	for (unsigned int i=pos; i<arr_size; i++){
		if(i != (arr_size -1))
			arr[i]= arr[i+1];	
		else arr[arr_size-1] = 0;
	}
}
