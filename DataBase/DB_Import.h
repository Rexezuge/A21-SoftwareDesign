#include "DATABASE_INCLUDE.h"

class DB_Import {
    string fileName;

   public:
    // Constructor
    DB_Import(string name) { fileName = name; }

    // Read the input file and return a ContactWithGroup object
    ContactWithGroup* extract() {
        ContactWithGroup* contactBook =
            (ContactWithGroup*)malloc(sizeof(ContactWithGroup));
        ifstream file;
        file.open(fileName);

        // read file
        if (file.is_open()) {
            string line;
            int check = 0;
            while (getline(file, line)) {
                // Store contact info
                string groupName, contactName, mailAddress, phoneNumber;
                // Store info position
                int start = 0;
                int end = 0;

                // Run through each character
                for (unsigned int i = 0; i < line.length()-1; i++) {
                    // get current character
                    char tmp1 = line[i];
                    char tmp2 = line[i + 1];

                    // If Contact info start
                    if (tmp1 == '\"' && tmp2 != ',' && tmp2 != '\n' &&
                        start == 0) {
                        start = i + 1;
                        // If Contact info end
                    } else if (tmp1!='\"' && tmp1!=',' && tmp2=='\"' && end==0) {
                        end = i - start+1;
                    }
                    // Locate info
                    if (start != 0 && end != 0) {
                        string info = line.substr(start, end);
                        start = 0;
                        end = 0;

                        // set contact info
                        if (check == 0) {
                            groupName = info;
                            check++;
                            cout<<groupName<<endl;
                        } else if (check == 1) {
                            contactName = info;
                            check++;
                            cout<<contactName<<endl;
                        } else if (check == 2) {
                            mailAddress = info;
                            check++;
                            cout<<mailAddress<<endl;
                        } else if (check == 3) {
                            phoneNumber = info;
                            cout<<phoneNumber<<endl;
                            check=0;

                            cout<<groupName<<", "<<contactName<<", "<<mailAddress<<", "<<phoneNumber<<"\n";

                            // compose Contact object
                            Contact newContact =
                                Contact(contactName, atoi(phoneNumber.c_str()),
                                        mailAddress);

                            // If new Contact list
                            if (!contactBook->containBook(groupName)) {
                                contactBook->addGroup(groupName);
                                contactBook->addContact(groupName, newContact);
                            } else {
                                contactBook->addContact(groupName, newContact);
                            }
                        }
                    }
                }
            }
        }

        file.close();
        return contactBook;
    }
};