#include<stdio.h>
#include<stdlib.h>
#include"Contact.h"
#include"ContactNOGroup.h"
#include"ContactWithGroup.h"
#include"DB_Export.h"
#include"DB_Import.h"
#include"Merge.h"
using namespace std;

int main(int numArgs,char** Argv){
  if(numArgs!=1) { return EXIT_FAILURE; }
  setvbuf(stdout,NULL,_IONBF,0);
  
  DB_Import fp = DB_Import("ECDB.txt");
  vector<unique_ptr<ContactNOGroup>> _Rep = fp.extract();


  return EXIT_SUCCESS;
}