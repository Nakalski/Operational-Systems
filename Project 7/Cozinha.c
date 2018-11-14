#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>

#define M 16

int id;
int channel;

int main(int argc, char *args[]){
  channel = atoi(args[1]);
  char bandeja[M];
  srand(time(NULL));

  while(1){
    for(int k=0;k<16;k++)
    	write(channel,bandeja,M);
    printf("Cozinheiro acabou de produzir 16 javalis em 8 segundos. \n");

  }

  return 0;
}
