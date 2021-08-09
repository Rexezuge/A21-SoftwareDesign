#include"DATABASE_INCLUDE.h"
#include"APIAccess.h"
#include"APIRouter.h"
#include"APIHandler.h"
pthread_mutex_t REP_INUSE;
ContactWithGroup* _Rep;
pthread_t PID_ER;
pthread_t PID_PR;

void SIGupdateEmail(){
  FILE* EM=fopen("newMail.txt","r");
  char _TIME[32];
  char _RECEIVER[128];
  char _CONTEXT[2048];
  fgets(_TIME,32,EM);
  fgets(_RECEIVER,128,EM);
  fgets(_CONTEXT,2048,EM);
  fclose(EM);
  _Rep->updateEmail(_RECEIVER,atoi(_TIME),_CONTEXT);
}

void Signal_Handler(int SIG){
  if(SIG==SIGINT){
    #ifdef DEBUG
      printf("==MAIN %d== Received Signal [SIGINT], Terminating ALL PS\n",getpid());
    #endif
    kill(PID_ER,SIGTERM);
    kill(PID_PR,SIGTERM);
    exit(EXIT_FAILURE);
  }
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

int main(int numArgs,char** Argv){
  BYPASSUNUSED(Argv);
  if(numArgs!=1) { return EXIT_FAILURE; }
  signal(SIGINT,SIG_IGN);
  REP_INUSE=PTHREAD_MUTEX_INITIALIZER;
  #ifdef DEBUG
    setvbuf(stdout,NULL,_IONBF,0);
    printf("==MAIN %d== PS<DB_MAIN> Running In [DEBUG] Mode\n",getpid());
  #endif
  _Rep=(ContactWithGroup*)malloc(sizeof(ContactWithGroup));
  pthread_create(&PID_ER,0,StartEmailReader,_Rep);
  pthread_create(&PID_PR,0,StartPrioritySort,_Rep);
  signal(SIGUSR1,Signal_Handler);
  signal(SIGUSR2,Signal_Handler);
  signal(SIGINT,Signal_Handler);
  // *_Rep=DB_Import("ECDB.txt").extract();
  while(1){ sleep(10); }
  return EXIT_SUCCESS;
}
