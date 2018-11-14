#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define NT 5

sem_t s[3];
void initSemaphore()
{
	sem_init(&s[0],0,0);
	sem_init(&s[1],0,0);
	sem_init(&s[2],0,0);
}

void *threadGrafo(void *n)
{
	long tnumber = (long)n;
	srand(time(NULL)*tnumber);
	int tempo = (rand()%6);
	if(tnumber==0)
	{
		printf("i'm process A and i will live for %d seconds\n",tempo);
		sleep(tempo);
		printf("i'm process A and i will die\n");
		sem_post(&s[0]);
	}
	if(tnumber==1)
	{
		printf("i'm process B and i will live for %d seconds\n",tempo);
		sleep(tempo);
		printf("i'm process B and i will die\n");
		sem_post(&s[1]);
	}
	if(tnumber==2)
	{
		sem_wait(&s[0]);
		sem_wait(&s[1]);
		printf("i'm process C and i will live for %d seconds\n",tempo);
		sleep(tempo);
		printf("i'm process C and i will die\n");
		sem_post(&s[2]);
		sem_post(&s[2]);
	}
	if(tnumber==3)
	{
		sem_wait(&s[2]);
		printf("i'm process D and i will live for %d seconds\n",tempo);
		sleep(tempo);
		printf("i'm process D and i will die\n");
	}
	if(tnumber==4)
	{
		sem_wait(&s[2]);
		printf("i'm process E and i will live for %d seconds\n",tempo);
		sleep(tempo);
		printf("i'm process E and i will die\n");
	}
}

int main(void)
{
	initSemaphore();
	pthread_t threads[NT];
	long i=0;
	while (i<NT)
	{
		pthread_create(&threads[i],NULL,threadGrafo, (void*)(i));
		i++;
	}
	for (i=0; i<NT; i++)
    {
    	pthread_join(threads[i],NULL);
    }
}
