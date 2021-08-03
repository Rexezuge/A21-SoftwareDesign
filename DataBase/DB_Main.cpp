#include"DATABASE_INCLUDE.h"

int main(int numArgs,char** Argv){
  if(numArgs!=1) { return EXIT_FAILURE; }
  setvbuf(stdout,NULL,_IONBF,0);
  InputFile FPRep=InputFile("ECDB.txt");
  return EXIT_SUCCESS;
}
