#include"DATABASE_INCLUDE.h"

class InputFile{
  FILE* FPRep;
  vector<string> InputInfo;
  vector<string> primaryInfo;
  public:
    InputFile(string FileName) { FPRep=fopen(FileName.c_str(),"r"); }
    vector<string> GatherInfoFromFile(){
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
        for(int i=0;i<(int)InputInfo.size();i++)
        {
          if(InputInfo[i].compare("\"")&&start_index==0)
            start_index=i;
          else if(InputInfo[i].compare("\"")&&start_index!=0)
            end_index=i;
          if(start_index!=0&&end_index!=0)
          {
            string temp_element=InputInfo[start_index+1];
            for(int i=start_index+2;i<end_index;i++)
              temp_element=temp_element+InputInfo[start_index];
            primaryInfo.push_back(temp_element);
            start_index=0;
            end_index=0;
          }
        }
      }
      return primaryInfo;
    }
};
