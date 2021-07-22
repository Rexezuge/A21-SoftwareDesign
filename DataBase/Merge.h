#ifndef SDD_EASYCONTACT_DATABASE_MERGE
#define SDD_EASYCONTACT_DATABASE_MERGE
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<list>
#include"Contact.h"

class Merge{
  std::vector<Contact> _ContactVector;
  std::list<Contact> _ContactList;
  public:
    //Take a list iterator and convert it to vector
    Merge(std::list<Contact>::iterator ptr, std::list<Contact>::iterator ptrend){
      while(ptr!=ptrend){
        _ContactVector.push_back(*ptr);
      }
    }
    //Take a vector iterator and convert it to list
    Merge(std::vector<std::string>::iterator ptr, std::vector<std::string>::iterator ptrend){
      while(ptr!=ptrend){
        Contact temp = Contact(*ptr, strtol((*(ptr+2)).c_str(), NULL,10), *(ptr+1));
        _ContactList.push_back(temp);
        ptr = ptr+3;
      }
    }
    std::list<Contact>::iterator mergeForRead(){
      return _ContactList.begin();
    }
    std::vector<Contact> mergeForWrite(){
      return _ContactVector;
    }
};
#endif
