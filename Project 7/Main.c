#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>

#define READ 0
#define WRITE 1
#define M 16
#define N 8

int tubo[2];

int main(){

  pipe(tubo);
  pid_t pid;
  int i = 0;
  if((pid = fork()) == 0){
      close(tubo[READ]);
      char channel[2];
      sprintf(channel,"%d",tubo[WRITE]);
      execl("./Cozinha","cozinha",channel,NULL);
    }
  for(i = 0; i < N; i++){
    if((pid = fork()) == 0){
        close(tubo[WRITE]);
        char channel[2], id[4];
        sprintf(id,"%d",i);
        sprintf(channel,"%d",tubo[READ]);
        execl("./Gaules","gaules",channel,id,NULL);
    }
  }

  pid_t child;
  for(;;){
    child = wait(NULL);
    if((child == -1) && (errno != EINTR))
      break;
  }

  return 0;
}
