#include "proj5.h"
#include <unistd.h>
int main(int argc, char** argv){
    //open file to write output
	FILE *fp;
    fp = fopen(argv[1], "w");
    fprintf(fp, "T,E,M\n");

    //get this is ferro or antiferro
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
    //To get h value
	double h;
	printf("Give values for h : ");
    scanf("%lf", &h);
	printf("\n");

    //Decleare Monte Carlo steps each time
    unsigned int loop;
    printf("How many times loop? : ");
    scanf("%u", &loop);
    printf("\n");

    //simulated annealing; temperature T starts with 5 and decreases to 0 with 0.1 stride
    double t = TMAX;
    double dt = 0.1;

    //Allocating memory to store structure lat: which containts
    //information about energy, magnet, size, lattice itself
    //lattice 1 for previous lattice
    //lattice 2 for spin flipped lattice
	struct lat *lat1 =  (struct lat *)malloc(sizeof(struct lat));
	struct lat *lat2 = (struct lat *)malloc(sizeof(struct lat));

    //declare the size of lattice
	printf("Type length of the n*n lattice, n : ");
	unsigned int n;
    scanf("%u",&n);
	printf("\n");

	lat1->size=n;
	lat2->size=n;

    //Allocating memory to lattice
	char *lattice1 = (char *)malloc(n*n*sizeof(char));
	char *lattice2 = (char *)malloc(n*n*sizeof(char));	

	//Make initial lattice randomly
	init_lattice(lattice1, n);
    //and copy to lattice 2
    cpy_lattice(lattice1, lattice2, n);
    p_lattice(lattice2,n);
	lat1->lattice = lattice1;
	lat2->lattice = lattice2;
	
    //start MonteCarlo
	while(t >= TMIN){

        for(unsigned int i = 0; i< loop; i++){

            //x,y position
            unsigned int x;
            unsigned int y;
            srand(time(NULL));
            unsigned int pos = rand()%(n*n);
            x = pos/n;
            y = pos%n;
            //lattice 1 for before flip, 2 for flip.
            lat2->lattice[pos] *= -1;

            //calculate hamiltonian of those lattices 
            //and calculate energy difference to do metropolis
            lat1->hamiltonian = etot(lat1, n, ferro, h);
            lat2->hamiltonian = etot(lat2, n, ferro, h);
            
            double e_diff = lat2->hamiltonian - lat1->hamiltonian;
            
            //flip success
            //accept flipped state
            if(matro(e_diff,t) == 1){
                cpy_lattice(lat2->lattice, lat1->lattice, n);
                }
            //flip failed
            //denied flipped state, make lat2 to previous lattice state
            //with copy lattice function
            else{
                cpy_lattice(lat1->lattice, lat2->lattice, n);
            }
        }
        t -= dt;
        printf("-----------------Temp = %lf----------------\n", t);
        p_lattice(lat2->lattice, lat2->size);
        printf("Energy now : %lf\n", lat2->energy);
        printf("Magnetisation now : %lf\n", lat2->magnet);
        fprintf(fp, "%lf,%lf,%lf\n",t,lat2->energy,lat2->magnet);
        printf("\n");
	}
    fclose(fp);
	return 0;
		
	

	
}


