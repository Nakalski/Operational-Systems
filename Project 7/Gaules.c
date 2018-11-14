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

int channel;
int id;

int main(int argc, char *args[]){
  id = atoi(args[2]);
  channel = atoi(args[1]);
  char bandeja[M];
  char nome[9] = {'V','I','N','I','C','I','U','S'};
  srand(time(NULL));
  sleep(1);
  while(1){
    read(channel,bandeja,M);
    printf("O Gaules %c[%d] comeu. \n",nome[id], id);
    sleep(0);
  }

  return 0;
}
