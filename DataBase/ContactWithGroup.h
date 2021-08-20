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
    /**
     * Add a contact at initialization (without sorting)
     */
    bool addContact_init(const string& groupName, const Contact& contact) {
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
                return true;
            }
        }
        return false;
    }
    /**
     * Add a contact
     */
    bool addContact(const string& groupName, const Contact& contact) {
        if (this->addContact_init(groupName, contact)) {
            return CheckRep();
        }
        return false;
    }
    /**
     * Get the Contact object
     * It will return NULL if the Contact is not presented
     * @param name Contact Name
     * @return Contact*
     */
    Contact* getContact(const string& name) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            list<Contact> lst = _REP[i]->getList();
            for (list<Contact>::iterator j = lst.begin(); j != lst.end(); j++) {
                if (j->getName() == name) return &*j;
            }
        }
        return NULL;
    }
    /**
     * @brief Get the contacts from a group
     * If the specific group is not presented, an empty list is returned
     * @param groupName
     * @return list<Contact>
     */
    list<Contact> getGroup(const string& groupName) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->getName() == groupName) {
                return _REP[i]->getList();
            }
        }
        return std::list<Contact>();
    }
    /**
     * Get the group names
     *
     * @return vector<string> Group names
     */
    vector<string> getGroups() {
        std::vector<std::string> _RESULT;
        for (int i = 0; i < (int)_REP.size(); i++) {
            _RESULT.push_back(_REP[i]->getName());
        }
        return _RESULT;
    }
    /**
     * Set the Contact object
     */
    bool setContact(const Contact& contact) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->contains(contact)) {
                _REP[i]->setContact(contact);
            }
        }
        return true;
    }
    /**
     * Remove the specific contact
     */
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
    /**
     * has always topped group
     *
     * @return true
     * @return false
     */
    bool hasAlwaysTop() { return _AlwaysTopGroup != ""; }
    /**
     * Set the always top group and trigger the sorting
     */
    bool AlwaysTop(const std::string& groupName) {
        _AlwaysTopGroup = groupName;
        return CheckRep();
    }
    /**
     * Cancel the current top of a group
     */
    bool CancelTop() {
        if (!hasAlwaysTop()) return false;
        _AlwaysTopGroup = string("");
        return true;
    }
    /**
     * has always top contact in a group
     *
     * @return true
     * @return false
     */
    bool hasAlwaysTop(const std::string& groupName) {
        for (int i = 0; i < (int)_AlwaysTopContact.size(); i++) {
            if (_AlwaysTopContact[i].first == groupName) {
                return true;
            }
        }
        return false;
    }
    /**
     * Set the always top contact in a group and trigger sorting
     */
    bool AlwaysTop(const std::string& groupName,
                   const std::string& contactName) {
        for (int i = 0; i < (int)_AlwaysTopContact.size(); i++) {
            if (_AlwaysTopContact[i].first == groupName) {
                _AlwaysTopContact[i].second = contactName;
                return CheckRep();
            }
        }
        pair<string, string> top;
        top.first = groupName;
        top.second = contactName;
        _AlwaysTopContact.push_back(top);
        return CheckRep();
    }
    /**
     * Cancel the current top of a contact in a specific group
     */
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
    /**
     * @brief Set the Priority of a contact
     *
     * @param contact
     * @param priority
     */
    void setPriority(const Contact& contact, int priority) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->contains(contact)) {
                _REP[i]->setPriority(contact, priority);
            }
        }
    }
    /**
     * @brief Set the Priority of a group
     *
     * @param groupName
     * @param priority
     */
    void setPriority(const string& groupName, int priority) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->getName() == groupName) {
                auto tmpBuffer = move(_REP[i + priority]);
                _REP[i + priority] = move(_REP[i]);
                _REP[i] = move(tmpBuffer);
            }
        }
    }
    /**
     * Add the new email
     *
     * @param address
     * @param time
     * @param email
     */
    void updateEmail(const string& address, int time, const string& email) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->containsAddress(address)) {
                _REP[i]->updateEmail(address, time, email);
                return;
            }
        }
    }
    /**
     * Call the priority sorts
     */
    bool PrioritySort() {
        this->PrioritySort_Groups();
        this->PrioritySort_Contacts();
        return true;
    }
    /**
     * Call the priority sort for groups
     */
    bool PrioritySort_Groups() {
        if (_REP.size() < 2) {
            return true;
        }
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->getName() == _AlwaysTopGroup) {
                if (i == 0) break;
                swap(_REP[i], _REP[0]);
                for (int iR = 1; iR < i; iR++) {
                    swap(_REP[iR], _REP[iR + 1]);
                }
            }
        }
#if 0
        >>> TIME BASED SORTING IS DISABLED <<<
        for (int i = 1; i < (int)_REP.size(); i++) {
            for (int iR = i; iR < (int)_REP.size(); iR++) {
                if (_REP[i]->getGroupPreferedTime() >
                    _REP[iR]->getGroupPreferedTime()) {
                    swap(_REP[i], _REP[iR]);
                }
            }
        }
#endif
        return true;
    }
    /**
     * Call the priority sort for contacts
     */
    bool PrioritySort_Contacts() {
        for (int i = 0; i < (int)_REP.size(); i++) {
            int PR = 0;
            for (int iR = 0; iR < (int)_AlwaysTopContact.size(); iR++) {
                if (_AlwaysTopContact[iR].first == _REP[i]->getName()) {
                    _REP[i]->PrioritySort_Top(_AlwaysTopContact[iR].second);
                    PR = 1;
                    break;
                }
            }
            if (!PR) _REP[i]->PrioritySort();
        }
        return true;
    }
    /**
     * Show the group name contains in the contact book
     *
     * @return true
     * @return false
     */
    bool containBook(const string& groupName) {
        for (int i = 0; i < (int)_REP.size(); i++) {
            if (_REP[i]->getName() == groupName) {
                return true;
            }
        }
        return false;
    }
    /**
     * Reset all weights for a contact
     */
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
