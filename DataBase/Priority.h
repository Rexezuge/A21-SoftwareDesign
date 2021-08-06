#include"DATABASE_INCLUDE.h"

class Priority{
  int SleepTime;
  vector<pair<string,string>> AlwaysTop;
  public:
    void* TimeTrigger(void* Time);
    void UpdateDatabase(ContactWithGroup* DB);
    void setAlwaysTop(string GroupName,string Contact Name);
};
