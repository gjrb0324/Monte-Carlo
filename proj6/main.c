#include "proj6.h"
#include <unistd.h>
int main(int argc, char **argv){
    FILE *fp = fopen(argv[1],"w");
    fprintf(fp, "E,M,g\n");
	char ferro;
	printf("Ferro? or antiFerro? Anser 0(ferro) or 1(antiferro) : ");
ferro =1;//	scanf("%hhd",&ferro);
	printf("\n");
	
	if( ferro == 0)
		ferro = 1;
	else if (ferro == 1)
		ferro = -1;
	else{
		printf("Error, only 0 or 1 can be an input!\n");
		exit(1);
	}

    unsigned int loop;
    printf("How many times loop? : ");
loop=10000000;//    scanf("%u", &loop);
    printf("\n");


    //h
    double h = 1;
    double t = TMAX;
    double dt = 0.1;
	struct lat *lat1 =  (struct lat *)malloc(sizeof(struct lat));
	struct lat *lat2 = (struct lat *)malloc(sizeof(struct lat));

	printf("Type length of the n*n lattice, n : ");
	unsigned int n;
n = 8;//	scanf("%u",&n);
	printf("\n");

	lat1->size=n;
	lat2->size=n;

	char *lattice1 = (char *)malloc(n*n*sizeof(char));
	char *lattice2 = (char *)malloc(n*n*sizeof(char));	
    //Before initialize lattice Calculate energy_max
    for(unsigned int i=0; i < n; i++){
        for(unsigned int j = 0; j < n ; j++){
            lattice1[i*n+j] =1;
        }
    }
    //Density of State g: Initialize with 0,  log(g(E) = 1)=0
    //Initialize f = e;
    int e_max =(int)abs(energy(lattice1,n)+ abs(h) * magnet(lattice1,n));
    double g[2*e_max];
    for(unsigned int i=0; i <2*e_max ; i++)
	    g[i]=0;
    double f = exp(1);
    //Initialize historgram
   // int histogram[2*e_max];
	lat1->lattice = lattice1;
	lat2->lattice = lattice2;
    //if f<fmin, stop
    while( f >= 1.00000001){
        double f_log = log(f);
        int cont =1;
        //histogram initialize.
     //   for ( int i = 0; i< 2*e_max; i++)
       //     histogram[i] = 0;
       // while(cont){
            for (unsigned int j = 0; j < loop; j++){
                //for(unsigned int i = 0; i< (n*n); i++){
                    init_lattice(lat1->lattice, n);
                    cpy_lattice(lat1->lattice, lat2->lattice, n);
                    srand(time(NULL));
                    unsigned int pos = rand()%(n*n);
                    //lattice 1 for before flip, 2 for flip.
                    lat2->lattice[pos] *= -1;
                    lat1->hamiltonian = etot(lat1, n, ferro, h);
                    lat2->hamiltonian = etot(lat2, n, ferro, h);
                    //Wang-Landau Start
                    //if g(E2) <= g(E1), success flip
                    //g [ e_max - ~~] for handling energy less than 0;
                    int pos1 = e_max - (int)lat1->hamiltonian;
                    int pos2 = e_max - (int)lat2->hamiltonian;
                    if(g[ pos2 ] <= g[ pos1]){
                        //histogram[pos2]+=1;
                        g[ pos2 ] += f_log;
                        cpy_lattice(lat2->lattice, lat1->lattice,n);
                    }
                    //g(E2) > g(E1)
                    else{
                        double r = (double)(rand()%10000)/10000;
                        //success
                        if( exp(g[pos1]-g[pos2]) > r){
                            g[pos2] += log(f);
                            cpy_lattice(lat2->lattice, lat1->lattice,n);
                            //histogram[pos2] +=1;
                        }
                        else{
                            g[pos1] += log(f);
                            //histogram[pos1]+=1;
                            cpy_lattice(lat1->lattice, lat2->lattice,n);
                        }

                    }       
                    
                //}
            }
            //int h_max = 0;
            //int h_min = 10000000;
            //for (int i = 0 ; i <2 *e_max; i++){
              //  if((histogram[i] > h_max) && (histogram[i] != 0)){
               //         h_max = histogram[i];
                //    }
                //if((histogram[i] < h_min) && (histogram[i] != 0))
                 //       h_min = histogram[i];
            //}
            //double flat = ((double) h_max - (double)h_min)/ ((double)h_max + (double)h_min);
            //if(flat < 0.05)
             //   cont = 0;
           // printf("flat : %lf, cont : %d\n", flat, cont);
        //}
        printf("f : %lf\n",log(f));
        fprintf(stdout, "%lf,%lf,%lf\n",lat1->energy, lat1->magnet, g[(int)lat1->hamiltonian]);
        fprintf(fp, "%lf,%lf,%lf\n",lat1->energy, lat1->magnet, g[(int)lat1->hamiltonian]);
        f = sqrt(f);
    }
    free(lattice1);
    free(lattice2);
    free(lat1);
    free(lat2);
    fclose(fp);
    return 0;
		
	

	
}


