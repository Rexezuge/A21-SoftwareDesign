#include"DATABASE_INCLUDE.h"

bool Import_Email_From_Local(const char* FileName,ContactWithGroup* DB){
  BYPASSUNUSED(DB);
  FILE* FD=fopen(FileName,"r");
  fclose(FD);
  return EXIT_SUCCESS;
}
