#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int bandeja=16;

int main()
{
  MPI_Init(NULL, NULL);
  int rank, tag;
  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  char msg[100];
  if(rank == 0)
  {
     while(1)
     {
		sleep(1);
		for(int i=0;i<16;i++)
        	MPI_Send(msg, sizeof(msg), MPI_CHAR, 1, tag, MPI_COMM_WORLD);	
		printf("Gaules fez 16 javalis\n");
		MPI_Recv(msg, sizeof(msg), MPI_CHAR, 1, tag, MPI_COMM_WORLD, &status);
     }
  }
  else
  {
      #pragma omp parallel num_threads(8)
      {
      	printf("aqui");
        while(1)
		{
        	MPI_Recv(msg, sizeof(msg), MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
	 		printf("Um Gaules Consumiu um Javali \n");
	 	 	bandeja--;
	  		sleep(1);
          	if(bandeja==0)
          	{
				MPI_Send(msg, sizeof(msg), MPI_CHAR, 0, tag, MPI_COMM_WORLD);
				bandeja=16;
      	    }
        }
      }
    }
}
