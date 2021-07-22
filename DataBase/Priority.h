#include<vector>
#include<string>
#include<utility>
#include"Contact.h"
#include"EasyContactDataBase.h"
using namespace std;
class Priority{
  int SleepTime;
  vector<pair<string,Contact>> AlwaysTop;
  void* TimeTrigger(void* Time);
  void UpdateDatabase(ECDB* DB);
};
