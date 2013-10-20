#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "mpi.h"
double timeDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
        double diff = (((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
                                         ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec));
        return diff / 1000000000;
}
double fun(double x){
        return pow(M_E, (-1) * pow(x,2) );
}

int main(int argc, char **argv){

	struct timespec start, end;

        int rank, np;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &np);

        double a = -2, b = 2;
        double size = (double) atoi( argv[1] );
	clock_gettime(CLOCK_MONOTONIC, &start);
        double h = ( b - a ) / size;
        
        double x = a;
        double wynik = 0, all=0;

        int i;
        
        x += (double) (rank * size / np) * h;
       

        for(i = rank * size / np; i < (rank + 1) * size / np; i++){
                wynik += ( ( fun(x) + fun(x+h) ) / 2 ) * h;                
                x += h;
        }

        MPI_Reduce(&wynik,&all,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	clock_gettime(CLOCK_MONOTONIC, &end);
        if(rank == 0){
                printf("Calka(e^(-x^2)) = %.16f\n", all);
		printf("Czas : %.16f\n\n", timeDiff(&end, &start));
        }

        MPI_Finalize();

        return 0;
}
