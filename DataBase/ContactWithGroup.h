#ifndef SDD_EASYCONTACT_DATABASE_CONTACTWITHGROUP
#define SDD_EASYCONTACT_DATABASE_CONTACTWITHGROUP
#include<vector>
#include<memory>
#include"ContactNOGroup.h"
using namespace std;
class ContactWithGroup{
    vector<unique_ptr<ContactNOGroup>> _Rep;
    public:
        ContactWithGroup() { _Rep=vector<unique_ptr<ContactNOGroup>>(); }
        void addGroup(const string& name) { _Rep.push_back(unique_ptr<ContactNOGroup>(new ContactNOGroup(name))); }
        void addContact(const string& groupName,const Contact& contact){
          for(int i=0;i<(int)_Rep.size();i++){
              if(_Rep[i]->getName()==groupName){
                  _Rep[i]->addContact(contact);
              }
          }
        }
        list<Contact>::iterator getContact(const string& groupName){
          for(int i=0;i<(int)_Rep.size();i++){
            if(_Rep[i]->getName()==groupName){
              return _Rep[i]->getList();
            }
          }
        }
        void setContact(const Contact& contact){
          for(int i=0;i<(int)_Rep.size();i++){
              if(_Rep[i]->contains(contact)){
                  _Rep[i]->setContact(contact);
              }
          }
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
};
#endif
