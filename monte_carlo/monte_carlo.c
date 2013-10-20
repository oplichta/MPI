#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

double timedif(struct timespec *timeA_p, struct timespec *timeB_p)
{
        double dif = (((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
                                         ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec));
        return dif / 1000000000;
}

main(int argc, char **argv)
{
	struct timespec start, end, start2, end2;
	int np, rank, all=0;
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	int size = atoi(argv[1]);
	
		
	double *x = (double *) malloc( size * sizeof(double));
	double *y = (double *) malloc( size * sizeof(double));
	int i;
	srand(time(0));
	if(rank == 0){
		for(i=0; i<size; i++){
			x[i] = (double) rand() / (double) RAND_MAX;
			y[i] = (double) rand() / (double) RAND_MAX;
		} 
	clock_gettime(CLOCK_MONOTONIC, &start2);
	}

	MPI_Bcast(x, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(y, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int count = 0;
	clock_gettime(CLOCK_MONOTONIC, &start);
    for(i=(rank*size)/np; i<((rank+1)*size)/np;i++){
    	if((x[i]*x[i])+(y[i]*y[i])<=1){
    		count++;
    	}
    }

	clock_gettime(CLOCK_MONOTONIC, &end);
        printf("time%d: %.16f\n\n", rank, timedif(&end, &start));
	
    MPI_Reduce(&count,&all,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank==0){
	clock_gettime(CLOCK_MONOTONIC, &end2);
    	double pi4 = (double) all / size;
    	printf("pi = %f\n", pi4*4);
	printf("time : %.16f\n\n", timedif(&end2, &start2));
    }

	MPI_Finalize();
}
