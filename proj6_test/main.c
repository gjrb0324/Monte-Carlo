#include "proj5.h"
#include <unistd.h>
int main(int argc, char** argv){
    //open file to write output
	FILE *fp;
    fp = fopen(argv[1], "w");
    fprintf(fp, "E,M,ln(g(M,E))\n");

    //get this is ferro or antiferro
	char ferro;
	printf("Ferro? or antiFerro? Anser 0(ferro) or 1(antiferro) : ");
	ferro=1;//scanf("%hhd",&ferro);
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
    h=1;//scanf("%lf", &h);
	printf("\n");

    //Decleare Monte Carlo steps each time
    unsigned int loop;
    printf("How many times loop? : ");
    loop=10000;//scanf("%u", &loop);
    printf("\n");

    //information about energy, magnet, size, lattice itself
    //lattice 1 for previous lattice
    //lattice 2 for spin flipped lattice
	struct lat *lat1 =  (struct lat *)malloc(sizeof(struct lat));
	struct lat *lat2 = (struct lat *)malloc(sizeof(struct lat));

    //declare the size of lattice
	printf("Type length of the n*n lattice, n : ");
	unsigned int n;
    n=8;//scanf("%u",&n);
	printf("\n");

	lat1->size=n;
	lat2->size=n;

    //Allocating memory to lattice
	char *lattice1 = (char *)malloc(n*n*sizeof(char));
	char *lattice2 = (char *)malloc(n*n*sizeof(char));	
    for(int i =0 ; i<n; i++){
        for(int j = 0 ; j <n; j++){
            lattice1[i*n+j] = 1;
        }
    }
    lat1->lattice =lattice1;
    double e_max = abs(etot(lat1,n,ferro,h));
    //start MonteCarlo
    for(h=-5; h<6;h++){
	//Make initial lattice randomly
	init_lattice(lattice1, n);
    //and copy to lattice 2
    cpy_lattice(lattice1, lattice2, n);
    p_lattice(lattice2,n);
	lat1->lattice = lattice1;
	lat2->lattice = lattice2;

    double g[2*(int)e_max];
    for(int  i = 0; i < (2*(int)e_max) ; i++)
        g[i] = 0;

    double f = exp(1);

    printf("[                h =%lf                          ]\n",h);
	
    while(f >= 1.00000001){
        for(unsigned int i = 0; i< loop; i++){

            srand(time(NULL));
            unsigned int pos = rand()%(n*n);
            //lattice 1 for before flip, 2 for flip.
            lat2->lattice[pos] *= -1;

            //calculate hamiltonian of those lattices 
            //and calculate energy difference to do metropolis
            lat1->hamiltonian = etot(lat1, n, ferro, h);
            lat2->hamiltonian = etot(lat2, n, ferro, h);
            int pos1 = (int)e_max - (int)lat1->hamiltonian;
            int pos2 = (int)e_max - (int)lat2->hamiltonian;
            if(g[pos1] >= g[pos2]){
      //          printf("pos2 :%d\n", pos2);
                g[pos2] += log(f);
                cpy_lattice(lat2->lattice, lat1->lattice,n);
            }
            else{
                double r = (double)(rand()%10000 )/10000;
                if(exp(g[pos1] - g[pos2] ) > r){
        //            printf("pos2: %d\n",pos2);
                    g[pos2] += log(f);
                    cpy_lattice(lat2->lattice, lat1->lattice,n);
                }
                else{
          //          printf("pos1 : %d\n", pos1);
                    g[pos1] += log(f);
                    cpy_lattice(lat1->lattice, lat2->lattice, n);
                }
            }
        }

        printf("-----------------f = %lf----------------\n", f);
	    printf("%lf,%lf,%lf\n",lat1->energy, lat1->magnet,log( g[(int)e_max - (int)lat1->hamiltonian]));
	    fprintf(fp,"%lf,%lf,%lf\n",lat1->energy, lat1->magnet,log( g[(int)e_max - (int)lat1->hamiltonian]));
        sleep(1.5);
        f = sqrt(f);
    }
    }
    free(lattice1);
    free(lattice2);
    free(lat1);
    free(lat2);
    fclose(fp);
	return 0;
		
	

	
}


