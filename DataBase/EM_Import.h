#include"DATABASE_INCLUDE.h"

bool Import_Email_From_Local(const char* FileName,ContactWithGroup* DB){
  BYPASSUNUSED(DB);

  ifstream file;
  file.open(FileName);

  //read file
  if(file.is_open()){
    string line;
    while (getline(file, line)) {
      string input1, input2, input3, input4;

      int start=0;
      int end=0;
      //Verify which info
      int check = 0;

      //Run through each character
      for(unsigned int i=0; i<line.length()-1; i++){
        //get current character
        char tmp1 = line[i];
        char tmp2 = line[i+1];

        //If Contact info start
        if(tmp1=='\"' && tmp2!=',' && tmp2!='\n' && start==0){
          start = i+1;
        //If Contact info end
        } else if (tmp1!='\"' && tmp1!=',' && tmp2=='\"' && end==0){
          end = i;
        }
        //Locate info
        if (start!=0 && end!=0){
          string info = line.substr(start, end);
          start = 0;
          end = 0;

          //set contact info
          if(check==0){
            input1 = info;
          } else if(check==1){
            input2 = info;
          } else if(check==2){
            input3 = info;
          } else {
            input4 = info;
            check = 0;
          }
        }
      }

      DB->restoreWeight(input1, input2, input3, input4);
    }
  }



  file.close();

  return EXIT_SUCCESS;
}