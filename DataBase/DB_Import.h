#ifndef SDD_EASYCONTACT_DATABASE_DB_IMPORT
#define SDD_EASYCONTACT_DATABASE_DB_IMPORT
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include"Contact.h"
#include"ContactNOGroup.h"
#include"ContactWithGroup.h"
using namespace std;

class DB_Import{
  string fileName;
  vector <unique_ptr<ContactNOGroup>> contactBook;

  public:
    //Constructor
    DB_Import(string name) { 
      fileName = name; 
    }

    //Read the input file and return a ContactWithGroup object
    vector <unique_ptr<ContactNOGroup>> extract() {
        ifstream file;
        file.open(fileName);

        //read file
        while (file) {
          //read each line
          getline(file, line);
          
          //Store contact info
          string groupName, contactName, mailAddress, phoneNumber;
          //Store info position
          int start, end;
          //Verify which info
          int check = 0;

          //Run through each character
          for(int i=0; i< line.length()-1; i++){
            //get current character
            char tmp1 = line.at(i);
            char tmp2 = line.at(i+1);


            //If Contact info start
            if(tmp1=="\"" && tmp2!="," && tmp2!="\n" && start==0){
              start = i+1;
            //If Contact info end
            } else if (tmp1!="\"" && tmp1!="," && tmp2=="\"" && end==0){
              end = i;
            }
            //Locate info
            if (start!=0 && end!=0){
              string info = line.substr(start, end);
              start = 0;
              end = 0;

              //set contact info
              if(check==0){
                groupName = info;
              } else if(check==1){
                contactName = info;
              } else if(check==2){
                mailAddress = info;
              } else {
                phoneNumber = info;
                check = 0;
              }
            }
          }

          //compose Contact object
          Contact newContact = Contact(contactName, phoneNumber, mailAddress);

          //If new Contact list
          if(!contactBook.contain(groupName)){
            contactBook.addGroup(groupName);
            contactBook.addContact(groupName, newContact);
          } else {
            contactBook.addContact(groupName, newContact);
          }
        }

        file.close();
        return contactBook;
    }

};
#endif