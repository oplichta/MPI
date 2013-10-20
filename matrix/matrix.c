#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MLD 1000000000.0
double timedif(struct timespec *timeA_p, struct timespec *timeB_p)
{
        double dif = (((timeA_p->tv_sec * MLD) + timeA_p->tv_nsec) -
                                         ((timeB_p->tv_sec * MLD) + timeB_p->tv_nsec));
        return dif / MLD;
}
int main(int argc, char **argv)
{
    int np, rank;
    long int dimmension = atoi(argv[1]);
    long int numberOfElements = dimmension*dimmension;
    MPI_Init(&argc, &argv);
    struct timespec timestart, timeend;
    double sp;
	long int sum1, sum2=0;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	
	int *matrix;
	if (rank == 0)
		matrix = (int *)malloc(sizeof(int)*numberOfElements);
	int *vector = (int *)malloc(sizeof(int)*dimmension);
	int i;
	long int start = rank*(numberOfElements/np);
	long int stop = (rank+1)*(numberOfElements/np);
	long int pa = numberOfElements/np;
	printf("rank %d pa %lu\n",rank,pa);
	clock_gettime(CLOCK_MONOTONIC,&timestart);
	if (rank == 0){
		srand(time(0));
		for (i=0;i<dimmension;i++)
			vector[i]=rand()%5;
		for (i=0;i<numberOfElements;i++)
			matrix[i]=rand()%5;
	}
	int *part = (int *)malloc(sizeof(int)*pa);
	MPI_Scatter(matrix,pa,MPI_INT,part,pa,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(vector,dimmension,MPI_INT,0,MPI_COMM_WORLD);
	srand(vector[rank%dimmension]);
	for (i=0;i<pa;i++) {
		part[i] =  part[i]* vector[(i+start)%dimmension];
		sum2 = sum2 + part[i];
	}
	MPI_Reduce(&sum2,&sum1,1,MPI_LONG,MPI_SUM,0,MPI_COMM_WORLD);
	sum2=0;
	free(vector);
	MPI_Gather(part,pa,MPI_INT,matrix,pa,MPI_INT,0,MPI_COMM_WORLD);
	free(part);
	if (rank == 0){
		for (i=0;i<numberOfElements;i++){
			sum2 = sum2 + matrix[i];
		}
		free(matrix);
	}
	clock_gettime(CLOCK_MONOTONIC,&timeend);
	sp=timedif(&timeend, &timestart);
	double tt;
	MPI_Reduce(&sp,&tt,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if (rank == 0){
		sp = tt/np;
		printf("Wymiar macierzy %ld na %ld \n",dimmension,dimmension );
		printf("Lacznie elementow: %ld \n", numberOfElements );
		printf("Suma przed: %ld i po %ld \n",sum1,sum2);
		printf("Czas dla wszystkich watkow %3.5lf\n",sp);
	}
	MPI_Finalize();
	return 0;
}
