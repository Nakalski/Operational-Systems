#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int bandeja=4, rank, tag;
MPI_Status status;
char msg[100];
sem_t mutex;

void initSemaphore()
{
	sem_init(&mutex,0,1);
}



int main()
{
	initSemaphore();
	MPI_Init(NULL, NULL);
 	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank == 0)
  	{
     		while(1)
     		{
				sleep(1);
				for(int i=0;i<4;i++){
        			MPI_Send(msg, sizeof(msg), MPI_CHAR, 1, tag, MPI_COMM_WORLD);
      			}
				printf("Gaules fez %d javalis \n", bandeja);
				MPI_Recv(msg, sizeof(msg), MPI_CHAR, 1, tag, MPI_COMM_WORLD, &status);
     		}
  	}
  	if(rank == 1)
	{	
  		while(1)
		{
			sem_wait(&mutex);
		  	MPI_Recv(msg, sizeof(msg), MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
		  	bandeja--;
		 	printf("Um Gaules Consumiu um Javali %d\n", bandeja);
		  	sleep(1);
		  	if(bandeja==0)
		  	{
		  		bandeja=4;
				MPI_Send(msg, sizeof(msg), MPI_CHAR, 0, tag, MPI_COMM_WORLD);
			}
			sem_post(&mutex);	
		}
  	}
}
