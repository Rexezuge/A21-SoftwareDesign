#ifndef SDD_EASYCONTACT_DATABASE_CONTACTWITHGROUP
#define SDD_EASYCONTACT_DATABASE_CONTACTWITHGROUP
#include<memory>
#include"ContactNOGroup.h"
using namespace std;
class ContactWithGroup{
vector<unique_ptr<ContactNOGroup>> _Rep;
    public:
    ContactWithGroup() { _Rep=vector<unique_ptr<ContactNOGroup>>(); }
    void addGroup(const string* name) { _Rep.push_back(unique_ptr<ContactNOGroup>(new ContactNOGroup(name))); }
    void addContact(const string* groupName,const Contact* contact){
      for(int i=0;i<_Rep.size();i++){
          if(!_Rep[i].getName().compare(groupName)){
              _Rep[i].addContact(contact);
          }
      }
    }
    auto getContact(const string* groupName){
      for(int i=0;i<_Rep.size();i++){
        if(!_Rep[i].getName().equals(groupName)){
          return _Rep[i].getList();
        }
      }
    }
    void setContact(const Contact* contact){
      for(int i=0;i<_Rep.size();i++){
          if(_Rep[i].contains(contact)){
              _Rep[i].setContact(contact);
          }
      }
    }
    void setPriority(const Contact* contact,int priority){
      for(int i=0;i<_Rep.size();i++){
          if(_Rep[i].contains(contact)){
              _Rep[i].setPriority(contact,priority);
          }
      }
    }
    void setPriority(const string* groupName,int priority){
      for(int i=0;i<_Rep.size();i++){
          if(!_Rep[i].getName().compare(groupName)){
              auto tmpBuffer=_Rep[i+priority];
              _Rep[i+priority]=_Rep[i];
              _Rep[i]=tmpBuffer;
          }
      }
    }
};
#endif
