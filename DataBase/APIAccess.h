#ifndef SDD_EASYCONTACT_APIACCESS
#define SDD_EASYCONTACT_APIACCESS

#include "DATABASE_INCLUDE.h"
extern ContactWithGroup* _REP;

bool addGroup(const std::string& GROUPNAME) {
    return _REP->addGroup(GROUPNAME);
}

Contact* getContact(const std::string& NAME) { return _REP->getContact(NAME); }

bool addContact(const std::string& GROUPNAME, const Contact& CONTACT) {
    return _REP->addContact(GROUPNAME, CONTACT);
}

bool setGroup(const std::string& GROUPNAME, const std::string& CONTACTNAME) {
    return _REP->setGroup(GROUPNAME, CONTACTNAME);
}

bool removeContact(const std::string& CONTACTNAME) {
    return _REP->removeContact(CONTACTNAME);
}

std::vector<Contact> getGroup(const std::string& GROUPNAME) {
    std::list<Contact> tmp = _REP->getGroup(GROUPNAME);
    std::vector<Contact> ret;
    for (std::list<Contact>::iterator i = tmp.begin(); i != tmp.end(); i++)
        ret.push_back(*i);
    return ret;
}

bool editContact(const std::string& OLDCONTACT, const std::string& GROUPNAME,
                 const Contact& CONTACT) {
    _REP->removeContact(OLDCONTACT);
    return _REP->addContact(GROUPNAME, CONTACT);
}

std::vector<std::string> getGroups() { return _REP->getGroups(); }

bool AlwaysTop(const std::string& GROUP) { return _REP->AlwaysTop(GROUP); }

bool hasAlwaysTop() { return _REP->hasAlwaysTop(); }

bool CancelTop() { return _REP->CancelTop(); }

bool AlwaysTop(const std::string& GROUP, const std::string& CONTACT) {
    return _REP->AlwaysTop(GROUP, CONTACT);
}

bool hasAlwaysTop(const std::string& GROUP) {
    return _REP->hasAlwaysTop(GROUP);
}

bool CancelTop(const std::string& GROUP) { return _REP->CancelTop(GROUP); }

#endif
