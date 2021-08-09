#include"DATABASE_INCLUDE.h"
#define _SLEEPTIMER 10
extern pthread_mutex_t REP_INUSE;

void PR_SignalMain(){
  kill(getpid(),SIGUSR2);
}

int UpdateDatabase(ContactWithGroup* DB){
  #ifdef DEBUG
    printf("==PRST %d== Now Sorting the DataBase\n",getpid());
  #endif
  DB->PrioritySort();
  PR_SignalMain();
  return EXIT_SUCCESS;
}

void* StartPrioritySort(void* ARGV){
  ContactWithGroup* DB=(ContactWithGroup*)ARGV;
  pthread_detach(pthread_self());
  #ifdef DEBUG
    printf("==PRST %d== PS<PrioritySort> Running In [DEBUG] Mode\n",getpid());
  #endif
  while(1){
    pthread_mutex_lock(&REP_INUSE);
    {
      UpdateDatabase(DB);
    }
    pthread_mutex_unlock(&REP_INUSE);
    sleep(_SLEEPTIMER*60);
  }
  return EXIT_SUCCESS;
}
