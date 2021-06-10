#include<string.h>

struct Contact{
  char* Name;
  int Phone;
  char* Address;
};

void newContact(struct Contact* Input,char* ContactName,int theirPhones,char* theirAddress){
  Input->Name=malloc(strlen(ContactName)+1);
  strcpy(Input->Name,ContactName);
  Input->Phone=theirPhones;
  Input->Address=malloc(strlen(theirAddress)+1);
  strcpy(Input->Address,theirAddress);
}

void deleteContact(struct Contact* Input){
  free(Input->Name);
  free(Input->Address);
}

unsigned int Hash(struct Contact* Input,int numBlocks){
  int StringSum=0;
  for(int i=0;i<(int)strlen(Input->Name);i++)
    StringSum+=(int)*(Input->Name+i);
  for(int i=0;i<(int)strlen(Input->Address);i++)
    StringSum+=(int)*(Input->Address+i);
  return (unsigned int)StringSum%numBlocks;
}
