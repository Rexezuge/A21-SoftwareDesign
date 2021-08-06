#include"DATABASE_INCLUDE.h"
#define _SLEEPTIMER 10

void PR_SignalMain(){
  kill(getppid(),SIGUSR2);
}

void UpdateDatabase(ContactWithGroup* DB){
  #ifdef DEBUG
    printf("==PRST %d== Now Sorting the DataBase\n",getpid());
  #endif
  DB->PrioritySort();
  PR_SignalMain();
}

int StartPrioritySort(ContactWithGroup* DB){
  #ifdef DEBUG
    printf("==PRST %d== PS<PrioritySort> Running In [DEBUG] Mode\n",getpid());
  #endif
  while(1){
    UpdateDatabase(DB);
    sleep(_SLEEPTIMER*60);
  }
  return EXIT_SUCCESS;
}
