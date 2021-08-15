#include "DATABASE_INCLUDE.h"

bool Import_Email_From_Local(const char* FileName, ContactWithGroup* DB) {
    BYPASSUNUSED(DB);

    ifstream file;
    file.open(FileName);

    // read file
    if (file.is_open()) {
        string line;
        int check=0;
        while (getline(file, line)) {
            // Store contact info
            string input1, input2, input3, input4;
            // Store info position
            int start = 0;
            int end = 0;

            // Run through each character
            for (unsigned int i = 0; i < line.length()-1; i++) {
                // get current character
                char tmp1 = line[i];
                char tmp2 = line[i + 1];

                if (tmp1 == '\"' && tmp2 != ',' && tmp2 != '\n' && start == 0) {
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

                    if (check == 0) {
                        input1 = info;
                        check++;
                    } else if (check == 1) {
                        input2 = info;
                        check++;
                    } else if (check == 2) {
                        input3 = info;
                        check++;
                    } else if (check == 3) {
                        input4 = info;
                        check = 0;
                        DB->restoreWeight(input1, input2, input3, input4);
                    }
                }
            }
        }
    }

    file.close();
    return true;
}
