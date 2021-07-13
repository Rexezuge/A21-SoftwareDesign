#include<stdio.h>
#include<iostream>
#include"TierDB.h"
#include"FileIO.h"
#define BYPASSUNUSED(X)(void)(X)
int main(int numArgs,char** Argv){
  if(numArgs!=1) { return EXIT_FAILURE; }
  setvbuf(stdout,NULL,_IONBF,0);
  BYPASSUNUSED(Argv);
  FileIO FPRep=FileIO("data.txt");
  BYPASSUNUSED(FPRep);
  return EXIT_SUCCESS;
}
