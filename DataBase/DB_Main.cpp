#include"DATABASE_INCLUDE.h"

void Signal_Handler(int SIG){
  if(SIG==SIGUSR1){
    _REP.
  }
}

int main(int numArgs,char** Argv){
  if(numArgs!=1) { return EXIT_FAILURE; }
  setvbuf(stdout,NULL,_IONBF,0);
  signal(SIGUSR1,Signal_Handler);
  InputFile FPRep=InputFile("ECDB.txt");
  return EXIT_SUCCESS;
}
