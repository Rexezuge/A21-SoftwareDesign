#include<stdio.h>
#include<stdlib.h>
#include"Contact.h"
#include"ContactNOGroup.h"
#include"ContactWithGroup.h"
#include"DB_Export.h"
#include"InputFile.h"
#include"Merge.h"
using namespace std;
int main(int numArgs,char** Argv){
  if(numArgs!=1) { return EXIT_FAILURE; }
  setvbuf(stdout,NULL,_IONBF,0);
  InputFile FPRep=InputFile("ECDB.txt");
  return EXIT_SUCCESS;
}
