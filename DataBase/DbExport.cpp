#include "DbExport.h"

int DbExport::start() {

  if (this->contacts.size() == 0 || this->fileName.size() == 0)
    return EXIT_FAILURE;

  this->names.clear();
  this->emails.clear();
  this->phones.clear();

  if (parse())  return EXIT_FAILURE;
  if (write())  return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

int DbExport::parse() {

  for (unsigned int i = 0; i < this->contacts.size(); i++) {
    if (this->contacts[i].getName().empty())
      std::cerr << "[WARNING] Empty contact name at " << i << ".\n";
    this->names.push_back(this->contacts[i].getName());

    if (this->contacts[i].getAddress().empty())
      std::cerr << "[WARNING] Empty contact address at " << i << ".\n";
    this->emails.push_back(this->contacts[i].getAddress());

    if (this->contacts[i].getPhone() == NULL)
      std::cerr << "[WARNING] Empty contact phone at " << i << ".\n";
    this->phones.push_back(this->contacts[i].getPhone());
  }

  if (this->names.size()  != this->emails.size() ||
      this->names.size()  != this->phones.size() ||
      this->emails.size() != this->phones.size()) {
    std::cerr << "[FAILURE] Mismatched contact size.\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int DbExport::write() {

  std::ofstream csvFile(fileName);
  if (!csvFile) {
    std::cerr << "[FAILURE] Could not create " << fileName << ".\n";
    return EXIT_FAILURE;
  }

  csvFile << "Name,Email,Phone" << std::endl;

  for (unsigned int i = 0; i < this->contacts.size(); i++) {
    csvFile << "\"" << this->names[i] << "\"" << ",";
    csvFile << "\"" << this->emails[i] << "\"" << ",";
    csvFile << "\"" << this->phones[i] << "\"";
    csvFile << std::endl;
  }

  return EXIT_SUCCESS;
}
