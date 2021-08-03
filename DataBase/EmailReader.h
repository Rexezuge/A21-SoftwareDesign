#include"DATABASE_INCLUDE.h"
#define _MINUTE 1

int NoNewEmail(FILE* FP){
  fseek(FP,0,SEEK_END);
  if(!ftell(FP)) { return 1; }
  fseek(FP,0,SEEK_SET);
  return 0;
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
  fgets(_RECEIVER,128,EM);
  fgets(_CONTEXT,2048,EM);
  printf("==EMRD %d== _TIME\n%s\n",getpid(),_TIME);
  printf("==EMRD %d== _RECEIVER\n%s\n",getpid(),_RECEIVER);
  printf("==EMRD %d== _CONTEXT\n%s\n",getpid(),_CONTEXT);
  fclose(EM);
  return EXIT_SUCCESS;
}

int StartEmailReader(){
  printf("==EMRD %d==\n",getpid());
  while(1){
    ReadLocalEmail();
    sleep(_MINUTE*15);
  }
  return EXIT_SUCCESS;
}
