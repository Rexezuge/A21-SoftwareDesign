#include "DATABASE_INCLUDE.h"

bool Import_Email_From_Local(const char* FileName, ContactWithGroup* DB) {
  BYPASSUNUSED(DB);
  FILE* FD = fopen(FileName, "r");
  char _CONTEXT[4096];
  while (fgets(_CONTEXT, 4096, FD)) {
    _CONTEXT[strlen(_CONTEXT) - 1] = '\0';
    // DB->restoreWeight();
  }
  fclose(FD);
  return EXIT_SUCCESS;
}
