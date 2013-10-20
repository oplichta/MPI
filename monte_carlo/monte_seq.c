#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MLD 1000000000.0

double timedif(struct timespec *timeA_p, struct timespec *timeB_p)
{
        double dif = (((timeA_p->tv_sec * MLD) + timeA_p->tv_nsec) -
                                         ((timeB_p->tv_sec * MLD) + timeB_p->tv_nsec));
        return dif / MLD;
}

main(int argc, char **argv)
{
	struct timespec start, end;

	int np, rank, all=0;
	int size = atoi(argv[1]);
	
		
	double *x = (double *) malloc( size * sizeof(double));
	double *y = (double *) malloc( size * sizeof(double));
	
	int i;
	srand(time(0));
	
	for(i=0; i<size; i++){
			x[i] = (double) rand() / (double) RAND_MAX;
			y[i] = (double) rand() / (double) RAND_MAX;
		}
	
	clock_gettime(CLOCK_MONOTONIC, &start);
	int count = 0;
	for(i=0; i<size;i++){
    	if((x[i]*x[i])+(y[i]*y[i])<=1){
    		count++;
    	}
    }
	clock_gettime(CLOCK_MONOTONIC, &end);
    
    	double pi4 = (double) count/size;
    	printf("pi = %f\n", pi4*4);
	printf("time : %.16f\n\n", timedif(&end, &start));
}
