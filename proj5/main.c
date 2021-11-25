#include "proj5.h"
#include <unistd.h>
int main(){

	char ferro;
	printf("Ferro? or antiFerro? Anser 0(ferro) or 1(antiferro) : ");
ferro =0;//	scanf("%hhd",&ferro);
	printf("\n");
	
	if( ferro == 0)
		ferro = 1;
	else if (ferro == 1)
		ferro = -1;
	else{
		printf("Error, only 0 or 1 can be an input!\n");
		exit(1);
	}

	double h;
	printf("Give values for h : ");
h=1;//	scanf("%lf", &h);
	printf("\n");

    unsigned int loop;
    printf("How many times loop? : ");
loop=1000000;//    scanf("%u", &loop);
    printf("\n");

    double t = TMAX;
    double dt = 0.1;
	struct lat *lat1 =  (struct lat *)malloc(sizeof(struct lat));
	struct lat *lat2 = (struct lat *)malloc(sizeof(struct lat));

	printf("Type length of the n*n lattice, n : ");
	unsigned int n;
n = 6;//	scanf("%u",&n);
	printf("\n");

	lat1->size=n;
	lat2->size=n;

	char *lattice1 = (char *)malloc(n*n*sizeof(char));
	char *lattice2 = (char *)malloc(n*n*sizeof(char));	

	//Starting with all
	init_lattice(lattice1, n);
    cpy_lattice(lattice1, lattice2, n);
    p_lattice(lattice2,n);
	lat1->lattice = lattice1;
	lat2->lattice = lattice2;
	
	while(t >= TMIN){

        for(unsigned int i = 0; i< loop; i++){
            unsigned int x;
            unsigned int y;
            srand(time(NULL));
            unsigned int pos = rand()%(n*n);
            x = pos/n;
            y = pos%n;
            //lattice 1 for before flip, 2 for flip.
            lat2->lattice[pos] *= -1;

            lat1->hamiltonian = etot(lat1, n, ferro, h);
            lat2->hamiltonian = etot(lat2, n, ferro, h);
            //printf("%lf, %lf\n", lat1->t_energy, lat2->t_energy);

            double e_diff = lat2->hamiltonian - lat1->hamiltonian;
            
            //flip success
            if(matro(e_diff,t) == 1){
                cpy_lattice(lat2->lattice, lat1->lattice, n);
                }
            else{
                cpy_lattice(lat1->lattice, lat2->lattice, n);
            }
        }
        t -= dt;
        printf("-----------------Temp = %lf----------------\n", t);
        p_lattice(lat2->lattice, lat2->size);
        printf("Energy now : %lf\n", lat2->energy);
        printf("Magnetisation now : %lf\n", lat2->magnet);
        printf("\n");
	}
	return 0;
		
	

	
}


