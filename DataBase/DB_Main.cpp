#include"DATABASE_INCLUDE.h"

void SIGupdateEmail(){
  FILE* EM=fopen("newMail.txt","r");
  char _TIME[32];
  char _RECEIVER[128];
  char _CONTEXT[2048];
  fgets(_TIME,32,EM);
  fgets(_RECEIVER,128,EM);
  fgets(_CONTEXT,2048,EM);
  fclose(EM);
  _Rep.updateEmail(_RECEIVER,_TIME,_CONTEXT);
}

void Signal_Handler(int SIG){
  if(SIG==SIGUSR1){
    SIGupdateEmail();
  }
}

pid_t SplitChildPS(){
  pid_t PID=fork();
  if(!PID) { StartEmailReader(); exit(EXIT_SUCCESS); }
  return PID;
}

int main(int numArgs,char** Argv){
  if(numArgs!=1) { return EXIT_FAILURE; }
  setvbuf(stdout,NULL,_IONBF,0);
  pit_t PID_ER=SplitChildPS();
  signal(SIGUSR1,Signal_Handler);
  InputFile FPRep=InputFile("ECDB.txt");
  kill(PID_ER,SIGTERM);
  return EXIT_SUCCESS;
}
