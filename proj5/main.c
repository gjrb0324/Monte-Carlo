#include "proj5.h"

int main(){

	char ferro;
	printf("Ferro? or antiFerro? Anser 0(ferro) or 1(antiferro) : ");
	scanf("%hhd",&ferro);
	printf("\n");
	
	if( ferro == 0)
		ferro = 1;
	else if (ferro == 1)
		ferro = -1;
	else{
		printf("Error, only 0 or 1 can be an input!\n");
		exit(1);
	}

	double T, h;
	printf("Give values for T and h : ");
	scanf("%lf %lf", &T, &h);
	printf("\n");

	struct lat *lat1 =  (struct lat *)malloc(sizeof(int)+sizeof(char *)+sizeof(double));
	struct lat *lat2 = (struct lat *)malloc(sizeof(int) + sizeof(char *) + sizeof(double));

	printf("Type length of the n*n lattice, n : ");
	unsigned int n;
	scanf("%u",&n);
	printf("\n");

	lat1->size=n;
	lat2->size=n;

	char *lattice1 = (char *)malloc(n*n*sizeof(char));
	char *lattice2 = (char *)malloc(n*n*sizeof(char));	

	unsigned int pos=0;
	//Starting with all
	char init;
	if(ferro== 1){
		printf("Type initial spin 1 or -1 : ");
		scanf("%hhd",&init);
		printf("\n");
	}

	for(unsigned int i=0;i<n;i++){
		for(unsigned int j=0;j<n;j++){
			pos=n*i+j;
			if(ferro == 1){
				lattice1[pos] = init;
				lattice2[pos] = init;
			}
			else if(ferro == -1){
				lattice1[pos] = pow((-1),pos);
				lattice2[pos] = pow((-1),pos);	
			}	
		}
	}
	p_lattice(lattice2,n);
	lat1->lattice = lattice1;
	lat2->lattice = lattice2;
	
	unsigned int index_arr[n*n];
	for(unsigned int i =0; i<(n*n); i++)
		index_arr[i] = i;
	unsigned int size = n*n;
	while(size >0){

		unsigned int x;
		unsigned int y;

		srand(time(NULL));
		pos = index_arr[rand()%size];
		x = pos/n;
		y = pos%n;
		resize_arr(index_arr, size, pos, n*n);
		size = size -1;
		//lattice 1 for before flip, 2 for flip.
		lattice2[pos] = (-1) * lattice2[pos];

		lat1->t_energy = etot(lattice1, n, ferro, h);
		lat2->t_energy = etot(lattice2, n, ferro, h);
		//printf("%lf, %lf\n", lat1->t_energy, lat2->t_energy);

		double e_diff = lat2->t_energy - lat1->t_energy;
		
		//flip success
		if(matro(e_diff,T) == 1){

			printf("--------------------------------------\n");
			printf("Flip Success : x = %d, y= %d\n", x, y);
			printf("Energy changed : %lf\n", e_diff);
			p_lattice(lat2->lattice, lat2->size);
			printf("\n");
			cpy_lattice(lat2->lattice, lat1->lattice, n);
			}
		else{
			printf("Flip Failed : e_diff = %lf, x = %d, y = %d\n ", e_diff,x,y);
		}
	}
	return 0;
		
	

	
}


