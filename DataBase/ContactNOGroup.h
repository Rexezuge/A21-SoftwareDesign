#ifndef SDD_EASYCONTACT_DATABASE_CONTACT
#define SDD_EASYCONTACT_DATABASE_CONTACT
#include<string>
#include <list>
#include <iterator>
#include"Contact.h"
using namespace std;

/**
 * @author henry
 * <b>ContactNOGroup</b> represents a <b>mutable</b> ContactNOGroup object for contact List.
 * It includes the group name for the group using a string and a list of Contact objects.
 */

class ContactNOGroup{
	string _GName;
	list<Contact> _Group;

	public:
		// Default constructor of ContactNOGroup
		ContactNOGroup() = default;

		/**
     	 * @param name : The name for the contact group.
     	 * @param gList : The list of Contact object.
     	 * @effects Constructs a new ContactNOGroup with _GName value = name, _Group = gList.
     	 */
		ContactNOGroup(string name, list<Contact> gList){
			_GName = name;
			_Group.assign.assign(gList.begin(), gList.end());
		}

		/**
     	 * @effects returns the name for the contact group.
     	 */
		string getName() {
			return name;
		}

		/**
     	 * @effects returns the label for the Edge.
     	 */
		list<Contact>::iterator getList() {
			return _Group.begin();
		}

		/**
		 * @param input : The name for the contact group.
		void addContact(Contact input)
};
#endif
