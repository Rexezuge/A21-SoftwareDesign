#include"DATABASE_INCLUDE.h"
/*
 * @author Zhenyuan Gong
 * ContactWithGroup represents an mutable database
 *   to store all of the Contact objects
 * This class contains: Rep
 */
class ContactWithGroup{
    vector<unique_ptr<ContactNOGroup>> _Rep;
    string _AlwaysTopGroup;
    deque<pair<string,string>> _AlwaysTopContact;
    public:
        ContactWithGroup() { _AlwaysTopGroup=""; }
        bool addGroup(const string& name) {
          for(int i=0;i<(int)_Rep.size();i++){
            if(_Rep[i]->getName()==name){
              return false;
            }
          }
          _Rep.push_back(unique_ptr<ContactNOGroup>(new ContactNOGroup(name)));
          return true;
        }
        bool addContact(const string& groupName,const Contact& contact){
          for(int i=0;i<(int)_Rep.size();i++){
            if(_Rep[i]->contains(contact)){
              return false;
            }
          }
          for(int i=0;i<(int)_Rep.size();i++){
              if(_Rep[i]->getName()==groupName){
                  _Rep[i]->addContact(contact);
                  return true;
              }
          }
          return false;
        }
        list<Contact> getGroup(const string& groupName){
          for(int i=0;i<(int)_Rep.size();i++){
            if(_Rep[i]->getName()==groupName){
              return _Rep[i]->getList();
            }
          }
          return std::list<Contact>();
        }
        vector<string> getGroups(){
          std::vector<std::string> _RESULT;
          for(int i=0;i<(int)_Rep.size();i++){
            _RESULT.push_back(_Rep[i]->getName());
          }
          return _RESULT;
        }
        bool setContact(const Contact& contact){
          for(int i=0;i<(int)_Rep.size();i++){
              if(_Rep[i]->contains(contact)){
                  _Rep[i]->setContact(contact);
              }
          }
          return true;
        }
        bool removeContact(const std::string& name){
          for(int i=0;i<(int)_Rep.size();i++){
            if(_Rep[i]->contains(name)){
              return _Rep[i]->removeContact(name);
            }
          }
          return false;
        }
        bool setGroup(const std::string& groupName,const std::string& name){
          for(int i=0;i<(int)_Rep.size();i++){
            std::list<Contact> LC=_Rep[i]->getList();
            for(std::list<Contact>::iterator iR=LC.begin();iR!=LC.end();iR++){
              if(iR->getName()==name){
                for(int iL=0;iL<(int)_Rep.size();iL++){
                  if(_Rep[iL]->getName()==groupName){
                    _Rep[iL]->addContact(*iR);
                    _Rep[i]->removeContact(iR->getName());
                    return true;
                  }
                }
              }
            }
          }
          return false;
        }
        bool AlwaysTop(const std::string& groupName){
          _AlwaysTopGroup=groupName;
          return true;
        }
        bool CancelTop(){
          _AlwaysTopGroup="";
          return true;
        }
        bool AlwaysTop(const std::string& groupName,const std::string& contactName){
          for(int i=0;i<(int)_AlwaysTopContact.size();i++){
            if(_AlwaysTopContact[i].first==groupName){
              _AlwaysTopContact[i].second=contactName;
              return true;
            }
          }
          _AlwaysTopContact.push_back(pair<string,string>(groupName,contactName));
          return true;
        }
        bool CancelTop(const std::string& groupName){
          for(std::deque<std::pair<std::string,std::string>>::iterator i=_AlwaysTopContact.begin();i!=_AlwaysTopContact.end();i++){
            if(i->first==groupName){
              _AlwaysTopContact.erase(i);
              return true;
            }
          }
          return false;
        }
        void setPriority(const Contact& contact,int priority){
          for(int i=0;i<(int)_Rep.size();i++){
              if(_Rep[i]->contains(contact)){
                  _Rep[i]->setPriority(contact,priority);
              }
          }
        }
        void setPriority(const string& groupName,int priority){
          for(int i=0;i<(int)_Rep.size();i++){
              if(_Rep[i]->getName()==groupName){
                  auto tmpBuffer=move(_Rep[i+priority]);
                  _Rep[i+priority]=move(_Rep[i]);
                  _Rep[i]=move(tmpBuffer);
              }
          }
        }
        void updateEmail(const string& contact,int time,const string& email){
          for(int i=0;i<(int)_Rep.size();i++){
            if(_Rep[i]->contains(contact)){
              _Rep[i]->updateEmail(contact,time,email);
              return;
            }
          }
        }
        void PrioritySort(){
          for(int i=0;i<(int)_Rep.size();i++){
            for(int iR=i;iR<(int)_Rep.size();iR++){
              if(_Rep[i]->getGroupPreferedTime()>_Rep[iR]->getGroupPreferedTime()){
                swap(_Rep[i],_Rep[iR]);
              }
            }
          }
        }
        bool containBook(const string& groupName){
          for(int i=0;i<(int)_Rep.size();i++){
            if(_Rep[i]->getName()==groupName){
              return true;
            }
          }
          return false;
        }
};
