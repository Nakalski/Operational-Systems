#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>

#define M 	16
#define N	8

typedef struct SharedData
{
	sem_t cozinha, cheia, mutex;		
	int count;
}Data;

int shmid;
Data *dat;

void ShareData()
{
	key_t KEY = ftok("/home/vinicius/Documents/Op. Sys./Trabalhos/Trab6/key.txt",1);
	int DataSize = sizeof(Data);
	shmid = shmget(KEY, DataSize, IPC_CREAT|SHM_R|SHM_W);
	dat = shmat(shmid, 0 ,0);
}

void valueSem()
{
	int sem_coz, sem_mut, sem_cheia;
	sem_getvalue(&dat->cozinha, &sem_coz);
	sem_getvalue(&dat->mutex, &sem_mut);
	sem_getvalue(&dat->cheia, &sem_cheia);
	printf("Gaules: Coz=%d  Mutex=%d  Cheia=%d Bandeja=%d\n",sem_coz, sem_mut, sem_cheia, dat->count);
}

void *Gaules(void *n)
{
	long numgaules = (long) n;
	char nome[N] = {'V','I','N','I','C','I','U','S'};
	while(1)
	{
		sem_wait(&dat->mutex);
		if(dat->count == 0)
		{
			printf("Gaules %c(%d) acordou cozinheiro\n",nome[numgaules],numgaules);
			sem_post(&dat->cozinha);
			sem_wait(&dat->cheia);
		}
		dat->count--;
		printf("Gaules %c(%d) comendo, sobram %d javalis na travessa\n",nome[numgaules],numgaules,dat->count);
		sem_post(&dat->mutex);
		sleep(3);
	}
}

int main()
{
	ShareData();
	sleep(3);
	pthread_t gaules[N];
	long i=0;
	while(i<N)
	{
		pthread_create(&gaules[i], NULL, Gaules, (void*)(i));
		i++;
	}
	while(1)
	{}
}
