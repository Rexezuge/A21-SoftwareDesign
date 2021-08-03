#ifndef SDD_EASYCONTACT_DATABASE_PRIORITY
#define SDD_EASYCONTACT_DATABASE_PRIORITY
#include<vector>
#include<string>
#include<utility>
#include"ContactWithGroup.h"
using namespace std;
class Priority{
  int SleepTime;
  vector<pair<string,string>> AlwaysTop;
  public:
    void* TimeTrigger(void* Time);
    void UpdateDatabase(ContactWithGroup* DB);
    void setAlwaysTop(string GroupName,string Contact Name);
};
#endif
