#include"DATABASE_INCLUDE.h"

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

		//Constructor that only take in _GName
		ContactNOGroup(string name = ""): _GName(name) {}

		/**
     	 * @param name : The name for the contact group.
     	 * @param gList : The list of Contact object.
     	 * @effects Constructs a new ContactNOGroup with _GName value = name, _Group = gList.
     	 */
		ContactNOGroup(string name, list<Contact> gList){
			_GName = name;
			_Group.assign(gList.begin(), gList.end());
			BYPASSUNUSED(gList);
		}

		/**
     	 * @effects returns the name for the contact group.
     	 */
		string getName() {
			return _GName;
		}

		/**
     	 * @effects returns the first Contact object of the contact list.
     	 */
		list<Contact> getList() {
			return std::list<Contact>(_Group);
		}

		/**
		 * @param input : The Contact object to be add in.
		 * @effects append a Contact object to the end of the contact list if no duplicate.
		 */
		void addContact(Contact input){
			if(!this->contains(input)){
				#ifdef DEBUG
					printf("==DATA== Added New Contact [%s]\n",input.getName().c_str());
				#endif
				_Group.push_back(input);
			}
		}

		/**
		 * @param input : The Contact object to be set prior.
		 * @param rank : The new rank of the contact.
		 * @effects insert the Contact object to desired position
		 */
		void setPriority(Contact input, int rank){
			int size = _Group.size();

			//check if position valid
			if(size >= rank){
				return;
			} else {
				//remove object from list
				for(list<Contact>::iterator it=_Group.begin(); it!=_Group.end(); it++){
					if(*it==input){
						_Group.erase(it);
						break;
					}
				}
			}

			//re-add object to new position
			list<Contact>::iterator it = _Group.begin();
			advance(it, rank);
			_Group.insert(it, input);
		}

		/**
		 * @param input : The Contact object to be reset.
		 * @effects reset the Contact object and append it to the end of the contact list.
		 */
		void setContact(Contact input){
			//remove the target contact
			for(list<Contact>::iterator it=_Group.begin(); it!=_Group.end(); it++){
				if(it->getName()==input.getName()){
					_Group.erase(it);
					break;
				}
			}

			//append the new one
			_Group.push_back(input);
		}

		bool removeContact(const std::string& name){
			for(list<Contact>::iterator i=_Group.begin();i!=_Group.end();i++){
				if(i->getName()==name){
					_Group.erase(i);
					return true;
				}
			}
			return false;
		}

		/**
		 * @param input : The Contact object to be check.
		 * @effects check if the contact list contains the Contact object.
		 */
		bool contains(Contact input){
			for(list<Contact>::iterator it=_Group.begin(); it!=_Group.end(); it++){
				if(*it==input){
					return true;
				}
			}
			return false;
		}

		bool contains(const std::string& Input){
			for(list<Contact>::iterator it=_Group.begin(); it!=_Group.end(); it++){
				if(it->getName()==Input){
					return true;
				}
			}
			return false;
		}

		void updateEmail(const string& contact,int time,const string& email){
			for(list<Contact>::iterator it=_Group.begin(); it!=_Group.end(); it++){
				if(it->getName()==contact){
					it->_Weight.newMail(email,time);
					return;
				}
			}
		}

		int getGroupPreferedTime(){
			int _RESULT=0;
			for(list<Contact>::iterator i=_Group.begin();i!=_Group.end();i++){
				printf("======================GET TIME\n");
				_RESULT+=i->_Weight.getPreferedTime();
			}
			printf("RETURN PREFERED TIME\n");
			return _RESULT/_Group.size();
		}
		bool restoreWeight(const std::string& contact,int numMails,const std::string& lastMail,const std::string& times){
			std::list<int> T;
			for(int i=0;i<numMails;i++){
				T.push_back(stoi(times.substr(i*4,4)));
			}
			for(std::list<Contact>::iterator i=_Group.begin();i!=_Group.end();i++){
				if(i->getName()==contact){
					return i->_Weight.restoreWeight(lastMail,T);
				}
			}
			return false;
		}
};
