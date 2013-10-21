#include <stdio.h>
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
    int dimmension = atoi(argv[1]);
    long int numberOfElements = dimmension*dimmension;
    struct timespec  start, end;
    	int  sum=0;
	int *matrix = (int *)malloc(sizeof(int)*numberOfElements);
	int *vector = (int *)malloc(sizeof(int)*dimmension);
	int i;

	clock_gettime(CLOCK_MONOTONIC,&start);
	srand(time(0));
	
	for (i=0;i<dimmension;i++)
		vector[i]=rand()%5;
	srand(time(0));
	
	for (i=0;i<numberOfElements;i++){
		matrix[i]=rand()%5 * vector[i%dimmension];
		sum = sum + matrix[i];
	}
	
	free(vector);
	free(matrix);
	
	clock_gettime(CLOCK_MONOTONIC,&end);
	printf("Wymiar macierzy: %i \n",dimmension);
	printf("Suma %d \n",sum);
	printf("Czas  %3.5lf\n",timedif(&end, &start));
	
	return 0;
}
