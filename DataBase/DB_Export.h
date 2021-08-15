#include "DATABASE_INCLUDE.h"

class DbExport {
 public:
  /**
   * @brief Construct a new task of exporting database
   *
   * @param _fileName The destination of CSV
   * @param _contacts A list of contact objects
   */
  DbExport(std::string _fileName, std::vector<Contact> _contacts)
      : fileName(_fileName), contacts(_contacts){};

  /**
   * @brief Start the exporting process
   * It checks the size of contacts and the size of file name. If they are
   * unset, return with 1. This will also call parse() and write(), if any
   * methods exit with 1, it will return with 1.
   *
   * @modifies names, emails, phones
   * @return int 0 if the method runs successfully, otherwise 1
   */
  int start() {
    if (this->contacts.size() == 0 || this->fileName.size() == 0)
      return EXIT_FAILURE;

    this->names.clear();
    this->emails.clear();
    this->phones.clear();

    if (parse()) return EXIT_FAILURE;
    if (write()) return EXIT_FAILURE;

    return EXIT_SUCCESS;
  };

 private:
  /**
   * @brief Parse the existing contacts
   * It firstly parse the contacts iteratively, read and write to the cor-
   * responding vectors.  It gives warning in STDERR when any of columns
   * are empty.
   *
   * @modifies names, emails, phones
   * @return int 0 if the method runs successfully, otherwise 1
   */
  int parse() {
    for (unsigned int i = 0; i < this->contacts.size(); i++) {
      if (this->contacts[i].getName().empty())
        std::cerr << "[WARNING] Empty contact name at " << i << ".\n";
      this->names.push_back(this->contacts[i].getName());

      if (this->contacts[i].getAddress().empty())
        std::cerr << "[WARNING] Empty contact address at " << i << ".\n";
      this->emails.push_back(this->contacts[i].getAddress());

      if (this->contacts[i].getPhone() == 0)
        std::cerr << "[WARNING] Empty contact phone at " << i << ".\n";
      this->phones.push_back(this->contacts[i].getPhone());
    }

    if (this->names.size() != this->emails.size() ||
        this->names.size() != this->phones.size() ||
        this->emails.size() != this->phones.size()) {
      std::cerr << "[FAILURE] Mismatched contact size.\n";
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  };

  /**
   * @brief Write data to file
   * It opens a stream with fileName, and insert first row as title, then
   * the contacts.  The format is Comma-Seperated Values.
   *
   * @return int 0 if the method runs successfully, otherwise 1
   */
  int write() {
    std::ofstream csvFile(fileName);
    if (!csvFile) {
      std::cerr << "[FAILURE] Could not create " << fileName << ".\n";
      return EXIT_FAILURE;
    }

    csvFile << "\"Name\",\"Email\",\"Phone\"" << std::endl;

    for (unsigned int i = 0; i < this->contacts.size(); i++) {
      csvFile << "\"" << this->names[i] << "\""
              << ",";
      csvFile << "\"" << this->emails[i] << "\""
              << ",";
      csvFile << "\"" << this->phones[i] << "\"";
      csvFile << std::endl;
    }

    return EXIT_SUCCESS;
  };

  // file name to the database file, preferably ending with .csv
  std::string fileName;
  // the vector of contact objects
  std::vector<Contact> contacts;
  // the vector of name of  contacts, used at parse()
  std::vector<std::string> names;
  // the vector of emails of contacts, used at parse()
  std::vector<std::string> emails;
  // the vector of phones of contacts, used at parse()
  std::vector<unsigned long> phones;
};
