#ifndef CSCI4400_DBEXPORT
#define CSCI4440_DBEXPORT

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Contact.h"

class DbExport{

  public:

    DbExport(std::string _fileName, std::vector<Contact> _contacts)
      : fileName(_fileName), contacts(_contacts) {};

    int  start();

  private:

    int  parse();
    int  write();

    std::string               fileName;
    std::vector<Contact>      contacts;
    std::vector<std::string>  names;
    std::vector<std::string>  emails;
    std::vector<int>          phones;

};

#endif
