#include"DATABASE_INCLUDE.h"

bool addGroup(const std::string& GROUPNAME){
  return _Rep->addGroup(GROUPNAME);
}

bool addContact(const std::string& GROUPNAME,const Contact& CONTACT){
  return _Rep->addContact(GROUPNAME,CONTACT);
}

bool setGroup(const std::string& GROUPNAME,const std::string& CONTACTNAME){
  return _Rep->setGroup(GROUPNAME,CONTACTNAME);
}

bool removeContact(const std::string& CONTACTNAME){
  return _Rep->removeContact(CONTACTNAME);
}

std::list<Contact> getGroup(const std::string& GROUPNAME){
  return _Rep->getGroup(GROUPNAME);
}

bool editContact(const std::string& OLDCONTACT,const std::string& GROUPNAME,const Contact& CONTACT){
  _Rep->removeContact(OLDCONTACT);
  return _Rep->addContact(GROUPNAME,CONTACT);
}

std::vector<std::string> getGroups(){
  return _Rep->getGroups();
}

bool AlwaysTop(const std::string& GROUP){
  return _Rep->AlwaysTop(GROUP);
}

bool AlwaysTop(const std::string& GROUP,const std::string& CONTACT){
  return _Rep->AlwaysTop(GROUP,CONTACT);
}
