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
    vector<string> _AlwaysTopContact;
    public:
        ContactWithGroup() { _Rep=vector<unique_ptr<ContactNOGroup>>(); }
        void addGroup(const string& name) { _Rep.push_back(unique_ptr<ContactNOGroup>(new ContactNOGroup(name))); }
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
        }
#if 0
>>> THIS FUNCTION IS NOT USED <<<
        list<Contact>::iterator getContact(const string& groupName){
          for(int i=0;i<(int)_Rep.size();i++){
            if(_Rep[i]->getName()==groupName){
              return _Rep[i]->getList();
            }
          }
        }
#endif
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
              if(_Rep[i]>_Rep[iR]){
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
