#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#define M 	16
#define N	8

typedef struct SharedData
{
	sem_t cozinha, cheia, mutex;	
	int count;
}Data;

int shmid;

key_t KEY;
Data *dat;
int DataSize = sizeof(Data);

void ShareData()
{
	KEY = ftok("/home/vinicius/Documents/Op. Sys./Trabalhos/Trab6/key.txt",1);
	shmid = shmget(KEY, DataSize, IPC_CREAT|SHM_R|SHM_W);
	dat = shmat(shmid, 0 ,0);
}

void InitializeData()
{
	dat->count=16;
	sem_init(&dat->mutex,1,1);
	sem_init(&dat->cheia,1,0);
	sem_init(&dat->cozinha,1,0);
}

int main()
{
	int i;
	pid_t PidC;
	pid_t PidP;
	ShareData();
   	printf("The shared memory is %d \n",shmid);
	printf("Unique key: %d \n",KEY);
	InitializeData();
	if((PidC = fork())==0)
	{
		printf ("Criando Gaules \n");
		execl("Gaules", NULL);
	}
	if((PidP = fork())==0)
	{
		printf ("Criando Cozinha \n");
		execl("Cozinha", NULL);
	}
	pid_t child;
 	for(;;){
    		child = wait(NULL);
    		if((child == -1) && (errno != EINTR))
      	break;
  	}
	exit(0);
	
}
