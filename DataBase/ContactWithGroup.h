#include "DATABASE_INCLUDE.h"
/*
 * @author Zhenyuan Gong
 * ContactWithGroup represents an mutable database
 *   to store all of the Contact objects
 * This class contains: Rep
 */
class ContactWithGroup {
    vector<unique_ptr<ContactNOGroup>> _REP;
    string _AlwaysTopGroup;
    vector<pair<string, string>> _AlwaysTopContact;
    bool CheckRep() {
        PrioritySort();
        return true;
    }

   public:
    ContactWithGroup() { _AlwaysTopGroup = string(""); }
    bool addGroup(const string& name) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->getName() == name) {
                return false;
            }
        }
        _REP.push_back(unique_ptr<ContactNOGroup>(new ContactNOGroup(name)));
        return CheckRep();
    }
    bool addContact(const string& groupName, const Contact& contact) {
#ifdef DEBUG
        printf("==DATA== Request Add New Contact to Group [%s]\n",
               groupName.c_str());
#endif
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->contains(contact)) {
#ifdef DEBUG
                printf("==DATA== Contact Already Exist\n");
#endif
                return false;
            }
        }
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->getName() == groupName) {
                _REP[i]->addContact(contact);
                return CheckRep();
            }
        }
        return false;
    }
    Contact* getContact(const string& name) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            list<Contact> lst = _REP[i]->getList();
            for (list<Contact>::iterator j = lst.begin(); j != lst.end(); j++) {
                if (j->getName() == name) return &*j;
            }
        }
        return NULL;
    }
    list<Contact> getGroup(const string& groupName) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->getName() == groupName) {
                return _REP[i]->getList();
            }
        }
        return std::list<Contact>();
    }
    vector<string> getGroups() {
        std::vector<std::string> _RESULT;
        for (int i = 0; i < (int)_REP.size(); i++) {
            _RESULT.push_back(_REP[i]->getName());
        }
        return _RESULT;
    }
    bool setContact(const Contact& contact) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->contains(contact)) {
                _REP[i]->setContact(contact);
            }
        }
        return true;
    }
    bool removeContact(const std::string& name) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->contains(name)) {
                return _REP[i]->removeContact(name);
            }
        }
        return false;
    }
    bool setGroup(const std::string& groupName, const std::string& name) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            std::list<Contact> LC = _REP[i]->getList();
            for (std::list<Contact>::iterator iR = LC.begin(); iR != LC.end();
                 iR++) {
                if (iR->getName() == name) {
                    for (int iL = 0; iL < (int)_REP.size(); iL++) {
                        if (_REP[iL]->getName() == groupName) {
                            _REP[iL]->addContact(*iR);
                            _REP[i]->removeContact(iR->getName());
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
    bool hasAlwaysTop() { return _AlwaysTopGroup != ""; }
    bool AlwaysTop(const std::string& groupName) {
        _AlwaysTopGroup = groupName;
        return CheckRep();
    }
    bool CancelTop() {
        if (!hasAlwaysTop())  return false;
        _AlwaysTopGroup = string("");
        return true;
    }
    bool hasAlwaysTop(const std::string& groupName) {
        for (int i = 0; i < (int)_AlwaysTopContact.size(); i++) {
            if (_AlwaysTopContact[i].first == groupName) {
                return true;
            }
        }
        return false;
    }
    bool AlwaysTop(const std::string& groupName,
                   const std::string& contactName) {
        for (int i = 0; i < (int)_AlwaysTopContact.size(); i++) {
            if (_AlwaysTopContact[i].first == groupName) {
                _AlwaysTopContact[i].second = contactName;
                return CheckRep();
            }
        }
        pair<string, string> top;
        top.first  = groupName;
        top.second = contactName;
        _AlwaysTopContact.push_back(top);
        return CheckRep();
    }
    bool CancelTop(const string& groupName) {
        for (vector<pair<string, string>>::iterator i =
                 _AlwaysTopContact.begin();
             i != _AlwaysTopContact.end(); i++) {
            if (i->first == groupName) {
                _AlwaysTopContact.erase(i);
                return true;
            }
        }
        return false;
    }
    void setPriority(const Contact& contact, int priority) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->contains(contact)) {
                _REP[i]->setPriority(contact, priority);
            }
        }
    }
    void setPriority(const string& groupName, int priority) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->getName() == groupName) {
                auto tmpBuffer = move(_REP[i + priority]);
                _REP[i + priority] = move(_REP[i]);
                _REP[i] = move(tmpBuffer);
            }
        }
    }
    void updateEmail(const string& address, int time, const string& email) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->containsAddress(address)) {
                _REP[i]->updateEmail(address, time, email);
                return;
            }
        }
    }
    void PrioritySort() {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->getName() == _AlwaysTopGroup) {
                swap(_REP[0], _REP[i]);
            }
        }
        for (int i = 1; i < (int)_REP.size(); i++) {
            for (int iR = i; iR < (int)_REP.size(); iR++) {
                if (_REP[i]->getGroupPreferedTime() >
                    _REP[iR]->getGroupPreferedTime()) {
                    swap(_REP[i], _REP[iR]);
                }
            }
        }
    }
    bool containBook(const string& groupName) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->getName() == groupName) {
                return true;
            }
        }
        return false;
    }
    bool restoreWeight(const std::string& contact, const std::string& numMails,
                       const std::string& lastMail, const std::string& times) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->contains(contact)) {
                return _REP[i]->restoreWeight(contact, stoi(numMails), lastMail,
                                              times);
            }
        }
        return false;
    }
};
