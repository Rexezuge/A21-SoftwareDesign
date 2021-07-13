#ifndef SDD_EASYCONTACT_DATABASE_DBEXPORT
#define SDD_EASYCONTACT_DATABASE_DBEXPORT

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Contact.h"

class DbExport{

  public:

    /**
     * @brief Construct a new task of exporting database
     *
     * @param _fileName The destination of CSV
     * @param _contacts A list of contact objects
     */
    DbExport(std::string _fileName, std::vector<Contact> _contacts)
      : fileName(_fileName), contacts(_contacts) {};

    int  start();

  private:

    int  parse();
    int  write();

    // file name to the database file, preferably ending with .csv
    std::string                fileName;
    // the vector of contact objects
    std::vector<Contact>       contacts;
    // the vector of name of  contacts, used at parse()
    std::vector<std::string>   names;
    // the vector of emails of contacts, used at parse()
    std::vector<std::string>   emails;
    // the vector of phones of contacts, used at parse()
    std::vector<unsigned long> phones;

};

#endif
