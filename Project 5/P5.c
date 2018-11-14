#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

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

void *Gaules(void *n)
{
	long numgaules = (long) n;
	char nome[N] = {'V','I','N','I','C','I','U','S'};
	while(1)
	{
		sem_wait(&mutex);
		if(count == 0)
		{
			printf("Gaules %c(%d) acordou cozinheiro\n",nome[numgaules],numgaules);
			sem_post(&cozinha);
			sem_wait(&cheia);
		}
		count--;
		sem_post(&mutex);
		printf("Gaules %c(%d) comendo, sobram %d javalis na travessa\n",nome[numgaules],numgaules,count);
		sleep(3);
	}
}

void *Cozinheiro(void *n)v
{
	int i;
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
	pthread_t gaules[N], cozinheiro;
	long i=0;
	pthread_create(&cozinheiro, NULL, Cozinheiro, (void*)(0));
	while(i<N)
	{
		pthread_create(&gaules[i], NULL, Gaules, (void*)(i));
		i++;
	}
	while(1)
	{}
}
