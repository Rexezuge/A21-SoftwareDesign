#include<map>
#include<vector>
#include<string>
#include<utility>
#include"Contact.h"

using namespace std;

class TierDB{
  vector<pair<string,vector<Contact>>> Rep;
  public:
    void addGroup(string GroupName) { Rep.push_back(pair<string,vector<Contact>>(GroupName,vector<Contact>())); }
    void addContact(string Index,Contact Input){
      for(int i=0;i<(int)Rep.size();i++)
        if(Rep[i].first==Index)
          Rep[i].second.push_back(Input);
    }
    void removeContact(Contact Input){
      for(int R=0;R<(int)Rep.size();R++)
        for(int i=0;i<(int)Rep[R].second.size();i++)
          if(Rep[R].second[i]==Input)
            Rep[R].second.erase(Rep[R].second.begin()+i);
    }
    void reOrderX();
};
