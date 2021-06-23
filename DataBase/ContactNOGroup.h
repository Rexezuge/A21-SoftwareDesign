#ifndef SDD_EASYCONTACT_DATABASE_CONTACTNOGROUP
#define SDD_EASYCONTACT_DATABASE_CONTACTNOGROUP
#include<string>
#include <list>
#include <iterator>
#include"Contact.h"
using namespace std;

/**
 * @author Henry Hongbin Liu
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
     	 * @effects returns the first Contact object of the contact list.
     	 */
		list<Contact>::iterator getList() {
			return _Group.begin();
		}

		/**
		 * @param input : The Contact object to be add in.
		 * @effects append a Contact object to the end of the contact list if no duplicate.
		 */
		void addContact(Contact input){
			if(!_Group.Contains(input)){
				_Group.push_back(input);
			}
		}

		/**
		 * @param input : The Contact object to be set prior.
		 * @param rank : The new rank of the contact.
		 * @effects insert the Contact object to desired position
		 */
		void setPriority(Contact input, int rank){

		}

		/**
		 * @param input : The Contact object to be reset.
		 * @effects reset the Contact object and append it to the end of the contact list.
		 */
		void setContact(Contact input){
			Contact tmp = input;
			
			
			//remove the target contact
			for(list<Contact>::iterator it=_Group.begin(); it!=_Group.end(); it++){

			}
		}

		/**
		 * @param input : The Contact object to be check.
		 * @effects check if the contact list contains the Contact object.
		 */
		bool Contains(Contact input){
			for(list<Contact>::iterator it=_Group.begin(); it!=_Group.end(); it++){
				if(it==input){
					return true;
				}
			}
			return false;
		}		
};
#endif
