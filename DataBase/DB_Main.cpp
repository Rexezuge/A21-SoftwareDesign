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
  // _Rep.updateEmail(_RECEIVER,_TIME,_CONTEXT);
}

void Signal_Handler(int SIG){
  if(SIG==SIGUSR1){
    #ifdef DEBUG
      printf("==MAIN %d== Received Signal [SIGUSR1], Just Received New Email\n",getpid());
    #endif
    SIGupdateEmail();
  }
  if(SIG==SIGUSR2){
    #ifdef DEBUG
      printf("==MAIN %d== Received Signal [SIGUSR2], DataBase Just Sorted\n",getpid());
    #endif
  }
}

pid_t SplitChildPS(int _W,ContactWithGroup* _DB){
  pid_t PID=fork();
  if(!PID&&_W==1) { StartEmailReader(); exit(EXIT_SUCCESS); }
  if(!PID&&_W==2) { StartPrioritySort(_DB); exit(EXIT_SUCCESS); }
  return PID;
}

int main(int numArgs,char** Argv){
  BYPASSUNUSED(Argv);
  if(numArgs!=1) { return EXIT_FAILURE; }
  setvbuf(stdout,NULL,_IONBF,0);
  #ifdef DEBUG
    printf("==MAIN %d== PS<DB_MAIN> Running In [DEBUG] Mode\n",getpid());
  #endif
  pid_t PID_ER=SplitChildPS(1,_Rep);
  pid_t PID_PR=SplitChildPS(2,_Rep);
  signal(SIGUSR1,Signal_Handler);
  InputFile FPRep=InputFile("ECDB.txt");
  kill(PID_ER,SIGTERM);
  kill(PID_PR,SIGTERM);
  return EXIT_SUCCESS;
}
