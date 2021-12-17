#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//function, bounary : circle with radius 1
double distance(double x1, double y1, double x2, double y2);
int main(int argc, char **argv){
    int vert = 1;
    int hori = 1;
    srand(time(NULL));
    double x1=0.5;
    double y1 =0;
    double r1 = 1;
    double epsilon = 0.001;
    //first set
    int n=1;

    char *fname;
    sprintf(fname, "result.csv");
    FILE*fp = fopen(fname,"w");
    fprintf(fp,"Degree,count\n");
    int count[180];
    for(int i =0; i<180; i++)
        count[i] = 0;
    for(int i =0 ; i<18000; i++){
        double x=x1;
        double y=y1;
        double r=0;
        double theta = 0;
        while(  (r1 - distance(0,0,x,y)) > epsilon){
            r = r1 - distance(0,0,x,y);
            theta = fmod(rand(),3.141592);
            x = x + r*cos(theta);
            y = y + r*sin(theta);
        }
        count[(int)((theta)*180/3.141592)] +=1;
    
    }

    for(int i = 1; i<180;i++){
        fprintf(fp,"%lf,%lf\n",(double) i/180*3.141592,count[i]*pow(sin(i*3.141592/180),2)/1000);
    }
    fclose(fp);
}


double distance(double x1, double y1, double x2, double y2){
    double result = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    return result;
}

