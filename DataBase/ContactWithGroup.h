#ifndef SDD_EASYCONTACT_DATABASE_CONTACTWITHGROUP
#define SDD_EASYCONTACT_DATABASE_CONTACTWITHGROUP
#include<memory>
#include"ContactNoGroup.h"
using namespace std;
class ContactWithGroup{
vector<unique_ptr<ContactNoGroup>> Rep;
    public:
    ContactWithGroup();
    void addGroup(const string* name);
    void addContact(const string* groupName,const Contact* contact);
    void setContact(const Contact* contact);
    void setPriority(const Contact* contact,int priority);
    void setPriority(const string* groupName,int priority);
};

Contact::ContactWithGroup(){
    Rep=vector<ContactNoGroup*>();
}

void Contact::addGroup(const string* name){
    Rep.push_back(unique_ptr<ContactNoGroup>(new ContactNoGroup));
}

void Contact::addContact(const string* groupName,const Contact* contact){
    for(int i=0;i<Rep.size();i++){
        if(!Rep[i].getName().compare(groupName)){
            Rep[i].addContact(contact);
        }
    }
}

void Contact::setContact(const Contact* contact){
    for(int i=0;i<Rep.size();i++){
        if(Rep[i].contains(contact)){
            Rep[i].setContact(contact);
        }
    }
}

void setPriority(const Contact* contact,int priority){
    for(int i=0;i<Rep.size();i++){
        if(Rep[i].contains(contact)){
            Rep[i].setPriority(priority);
        }
    }
}

void setPriority(const string* groupName,int priority){
    for(int i=0;i<Rep.size();i++){
        if(!Rep[i].getName().compare(groupName)){
            auto tmpBuffer=Rep[i+priority];
            Rep[i+priority]=Rep[i];
            Rep[i]=tmpBuffer;
        }
    }
}

#endif