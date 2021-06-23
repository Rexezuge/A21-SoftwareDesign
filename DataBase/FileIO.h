#ifndef GONGZ3_CSCI4440_FILEIO
#define GONGZ3_CSCI4440_FILEIO
#include<stdio.h>
#include<stdlib.h>
#include<string>
class FileIO{
  FILE* FPRep;
  vector<string> InputInfo;
  vector<string> primaryInfo;
  public:
    FileIO(string FileName) { FPRep=fopen(FileName.c_str(),"r"); }
    std::vector<string> GatherInfoFromFile(){
      if(FPRep==NULL) perror ("Error opening file");
      else{
        int c;
        do{
          string InputChar;
          c=getc(FPRep);
          InputChar=putchar(c);
          InputInfo.push_back(InputChar);
        }while(c!=EOF);
        fclose(FPRep);
        int start_index=0;
        int end_index=0;
        for(int i=0;i<InputInfo.size();i++)
        {
          if(InputInfo[i].compare("\"")&&start_index==0)
            start_index=i;
          else if(InputInfo[i].compare("\"")&&start_index!=0)
            end_index=i;
          if(start_index!=0&&end_index!=0)
          {
            string temp_element=InputInfo[start_index+1];
            for(int i=start_index+2;i<end_index;i++)
            {
              temp_element=temp_element+InputInfo[start_index];
            }
            primaryInfo.push_back(temp_element);
            start_index=0;
            end_index=0;
          }
        }
      }
    }
};
#endif
