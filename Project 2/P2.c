#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
int qnt_C = 0;

void (*OldHandler_CTRLC) (int);
void (*OldHandler_CTRLZ) (int);
void (*OldHandler_ALARM) (int);

void trata_CTRLC()
{
	qnt_C++;
	if (qnt_C >= 10)
	{
		char op;
		printf("\nQuer sair? (Y/n): ");
		alarm(5);
		scanf(" %c",&op);
		alarm(0);
		
		if(op == 'n')
		{
			printf("Contagens resetadas.\n");
			qnt_C=0;
		}
		if(op == 'Y')
		{	
			printf("Saindo em 1s\n");
			sleep(1);
			exit(0);
		}
	}
}

void trata_CTRLZ()
{
	printf("\nNº de CTRL+C -> %d\n",qnt_C);
}

void trata_ALARM()
{
	printf("Saindo em 1s\n");
	sleep(1);
	exit(0);
}

int main(void)
{
	OldHandler_CTRLC = signal (SIGINT, trata_CTRLC);
	OldHandler_CTRLZ = signal (SIGTSTP, trata_CTRLZ);
	OldHandler_ALARM = signal (SIGALRM, trata_ALARM);
	for(;;) 
	{
        	pause();
	} 
}
