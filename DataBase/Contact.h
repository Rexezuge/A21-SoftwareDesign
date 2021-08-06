#include"DATABASE_INCLUDE.h"
/*
 * @author Zhenyuan Gong
 * Contact represents an immutable Contact object for contact address
 * This class contains: Name, Phone, Address
 */
class Contact{
  long unsigned int _Phone=0;
  std::string _Name;
  std::string _Address;
  public:
    Weight _Weight;
    /*
     * @pram Name : name to be stored
     * @pram Phone : phone number to be stored
     * @pram Address : email address to be stored
     * This is the constructor for Contact class
     */
    Contact(const std::string& Name,const long unsigned int Phone,const std::string& Address){
      _Name=Name;
      _Address=Address;
      _Phone=Phone;
      _Weight=Weight();
    }
    /*
     * @return Name : stored name
     * Returns the stored name
     */
    const std::string& getName() { return _Name; }
    /*
     * @return Address : stored email address
     * Returns the stored email address
     */
    const std::string& getAddress() { return _Address; }
    int getPhone() { return _Phone; }
    int Hash(int StackSize){
      long StringSum=0;
      for(int i=0;i<(int)_Name.size();i++)
        StringSum+=(int)_Name[i];
      for(int i=0;i<(int)_Address.size();i++)
        StringSum+=(int)_Address[i];
      return (int)StringSum%StackSize;
    }
    /*
     * @return bool : true if equal, false if not  equal
     * Compares if the current Contact equal to the reference Contact
     */
    bool operator==(const Contact& Input) { return this->_Name==Input._Name&&this->_Phone==Input._Phone&&this->_Address==Input._Address; }
};
