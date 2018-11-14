#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
	pid_t childpid;
	printf ("I'M PROCESS A, WITH: PID=%d ; PPID=%d\n", getpid(), getppid()) ;
	if (fork()==0)
	{
		printf ("I'M PROCESS B, WITH: PID=%d ; PPID=%d\n", getpid(), getppid());
		if (fork()==0)
		{
			printf ("I'M PROCESS C, WITH: PID=%d ; PPID=%d\n", getpid(), getppid());
			printf("I'M PROCESS C AND I WILL DIE IN ONE SEC!\n");
			sleep(1);
			exit(0);
		}
		else if (fork() > 0)
		{
			wait(NULL);
			printf("I'M PROCESS B AND I WILL DIE IN ONE SEC!\n");
			sleep(1);
			exit(0);
		}
	}
	else 
	{
		wait(NULL);
		if (fork() == 0)
		{
			printf ("I'M PROCESS D, WITH: PID=%d ; PPID=%d\n", getpid(), getppid());
			printf("I'M PROCESS D AND I WILL DIE IN ONE SEC!\n");
			sleep(1);
			exit(0);
		}
		else
		{
			wait(NULL);
			if (fork() == 0)
			{
				printf ("I'M PROCESS E, WITH: PID=%d ; PPID=%d\n", getpid(), getppid());
				if (fork() == 0)
				{

					printf ("I'M PROCESS F, WITH: PID=%d ; PPID=%d\n", getpid(), getppid());
					if (fork() == 0)
					{
						printf ("I'M PROCESS G, WITH: PID=%d ; PPID=%d\n", getpid(), getppid());
						printf("I'M PROCESS G AND I WILL DIE IN ONE SEC!\n");
						sleep(1);
						exit(0);
					}
					else if (fork() > 0)
					{
						wait(NULL);
						printf("I'M PROCESS F AND I WILL DIE IN ONE SEC!\n");
						sleep(1);
						exit(0);
					}
				}
				else if (fork() > 0)
				{
					for (;;) 
					{
						childpid = wait(NULL);
						if ((childpid ==-1) && (errno != EINTR))	
						    break;
				    }	
					printf("I'M PROCESS E AND I WILL DIE IN ONE SEC!\n");
					sleep(1);
					exit(0);
				}
			}
			else if (fork() > 0)
			{
				for (;;)
				{
					childpid = wait(NULL);
					if ((childpid ==-1) && (errno != EINTR))	
						break;
				}
				printf("I'M PROCESS A AND I WILL DIE IN ONE SEC!\n");
				sleep(1);
				exit(0);
			}
		}	
	}
	return 0;
}
