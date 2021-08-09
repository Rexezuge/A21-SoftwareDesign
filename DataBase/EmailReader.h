#include"DATABASE_INCLUDE.h"
#define _EMAILTIMER 1

int NoNewEmail(FILE* FP){
  fseek(FP,0,SEEK_END);
  if(!ftell(FP)) { return 1; }
  fseek(FP,0,SEEK_SET);
  return 0;
}

void ER_SignalMain(){
  kill(getppid(),SIGUSR1);
}

int ReadLocalEmail(){
  FILE* EM=fopen("newMail.txt","r");
  if(NoNewEmail(EM)){
    fclose(EM);
    return EXIT_SUCCESS;
  }
  char _TIME[32];
  char _RECEIVER[128];
  char _CONTEXT[2048];
  fgets(_TIME,32,EM);
  _TIME[strlen(_TIME)-1]=0;
  fgets(_RECEIVER,128,EM);
  _RECEIVER[strlen(_RECEIVER)-1]=0;
  fgets(_CONTEXT,2048,EM);
  _CONTEXT[strlen(_CONTEXT)-1]=0;
  #ifdef DEBUG
    printf("==EMRD %d== Received New Email\n",getpid());
    printf("==EMRD %d== _TIME\n%s\n",getpid(),_TIME);
    printf("==EMRD %d== _RECEIVER\n%s\n",getpid(),_RECEIVER);
    printf("==EMRD %d== _CONTEXT\n%s\n",getpid(),_CONTEXT);
  #endif
  fclose(EM);
  ER_SignalMain();
  return EXIT_SUCCESS;
}

void* StartEmailReader(void* ARGV){
  BYPASSUNUSED(ARGV);
  #ifdef DEBUG
    printf("==EMRD %d== PS<EmailReader> Running In [DEBUG] Mode\n",getpid());
  #endif
  while(1){
    ReadLocalEmail();
    sleep(_EMAILTIMER*60);
  }
  return EXIT_SUCCESS;
}
