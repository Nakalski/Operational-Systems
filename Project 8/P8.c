#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <omp.h>

#define M 16
#define N 8
sem_t cozinha, mutex, cheia;
int count=0;
void initSemaphore()
{
	sem_init(&cozinha,0,0);
	sem_init(&mutex,0,1);
	sem_init(&cheia,0,0);
}

void Gaules(void)
{
	while(1)
	{
		sem_wait(&mutex);
		if(count == 0)
		{
			printf("Um Gaules acordou o cozinheiro\n");
			sem_post(&cozinha);
			sem_wait(&cheia);
		}
		count--;
		sem_post(&mutex);
		printf("Gaules comendo, sobram %d javalis na travessa\n",count);
		sleep(1);
	}
}

void Cozinheiro(void)
{
	while(1)
	{
		sem_wait(&cozinha);
		printf("Cozinhando 16 javalis em 8 segundos\n");
		sleep(8);
		count=16;
		sem_post(&cheia);
	}
}


int main(void)
{
	initSemaphore();
	#pragma omp parallel 
	{
		#pragma omp sections
		{
			#pragma omp section
				Cozinheiro();
			#pragma omp section
				Gaules();
		}
	}
	while(1)
	{}
}
