#include"DATABASE_INCLUDE.h"
extern ContactWithGroup* _Rep;

bool addGroup(const std::string& GROUPNAME){
  return _Rep->addGroup(GROUPNAME);
}

std::vector<std::string> getContact(const std::string& NAME) {
  Contact tmp = _Rep->getContact(NAME);
  std::vector<std::string> ret;
  ret.push_back(tmp.getName());
  ret.push_back(std::to_string(tmp.getPhone()));
  ret.push_back(tmp.getAddress());
  return ret;
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

std::vector<Contact> getGroup(const std::string& GROUPNAME){
  std::list<Contact> tmp = _Rep->getGroup(GROUPNAME);
  std::vector<Contact> ret;
  for (std::list<Contact>::iterator i = tmp.begin(); i != tmp.end(); i++) {
    ret.push_back(*i);
  }
  return ret;
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

bool CancelTop(){
  return _Rep->CancelTop();
}

bool AlwaysTop(const std::string& GROUP,const std::string& CONTACT){
  return _Rep->AlwaysTop(GROUP,CONTACT);
}

bool CancelTop(const std::string& GROUP){
  return _Rep->AlwaysTop(GROUP);
}
