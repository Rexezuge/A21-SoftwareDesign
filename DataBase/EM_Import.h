#include"DATABASE_INCLUDE.h"

bool Import_Email_From_Local(const char* FileName,ContactWithGroup* DB){
  BYPASSUNUSED(DB);
  FILE* FD=fopen(FileName,"r");
  char _CONTEXT[4096];
  while(!strncmp(fgets(_CONTEXT,4096,FD),"s",1)){
    BYPASSUNUSED(_CONTEXT);
  }
  fclose(FD);
  return EXIT_SUCCESS;
}
