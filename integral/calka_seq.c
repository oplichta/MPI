#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double timedif(struct timespec *timeA_p, struct timespec *timeB_p)
{
        double dif = (((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
                                         ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec));
        return dif / 1000000000;
}


double fun(double x){
        return pow(M_E, (-1) * pow(x,2) );
}

int main(int argc, char **argv){

	struct timespec start, end;

        int rank, np;

        double a = -2, b = 2;
        double size = (double) atoi( argv[1] );

        double h = ( b - a ) / size;
        
        double x = a;
        double wynik = 0, all=0;

        int i;
        
     	clock_gettime(CLOCK_MONOTONIC, &start);       

        for(i = 0; i < size; i++){
                wynik += ( ( fun(x) + fun(x+h) ) / 2 ) * h;
                
                x += h;
        }

	   clock_gettime(CLOCK_MONOTONIC, &end);
	
        if(rank == 0){
                printf("Calka(e^(-x^2)) = %.16f\n", wynik);
		printf("time : %.16f\n\n", timedif(&end, &start));
        }
        return 0;
}
