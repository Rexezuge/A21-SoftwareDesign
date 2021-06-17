#ifndef GONGZ3_CSCI4440_FILEIO
#define GONGZ3_CSCI4440_FILEIO
#include<stdio.h>
#include<stdlib.h>
#include<string>
class FileIO{
  FILE* FPRep;
  public:
    FileIO(std::string FileName) { FPRep=fopen(FileName.c_str(),"r"); }
};
#endif
