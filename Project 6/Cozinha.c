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
	printf("Cozinha: Coz=%d  Mutex=%d  Cheia=%d Bandeja=%d\n",sem_coz, sem_mut, sem_cheia, dat->count);
}

void *Cozinheiro(void *n)
{	
	while(1)
	{
		sem_wait(&dat->cozinha);
		printf("Cozinhando 16 javalis em 8 segundos\n");
		sleep(8);
		dat->count=16;
		sem_post(&dat->cheia);
	}
}

int main()
{
	ShareData();
	sleep(3);
	pthread_t cozinha;
	pthread_create(&cozinha, NULL, Cozinheiro,(void*)0);
	while(1)
	{}
}
