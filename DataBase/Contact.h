#ifndef SDD_EASYCONTACT_DATABASE_CONTACT
#define SDD_EASYCONTACT_DATABASE_CONTACT
#include<string>
class Contact{
  long unsigned int _Phone;
  std::string _Name;
  std::string _Address;
  public:
    Contact(const std::string* Name,const long unsigned int Phone,const std::string* Address){
      _Name=std::string(*Name);
      _Address=std::string(*Address);
      _Phone=Phone;
    }
    std::string getName() { return _Name; }
    std::string getAddress() { return _Address; }
    int getPhone() { return _Phone; }
    int Hash(int StackSize){
      long StringSum=0;
      for(int i=0;i<(int)_Name.size();i++)
        StringSum+=(int)_Name[i];
      for(int i=0;i<(int)_Address.size();i++)
        StringSum+=(int)_Address[i];
      return (int)StringSum%StackSize;
    }
    bool operator==(const Contact* Input) { return this->_Name==Input->_Name&&this->_Phone==Input->_Phone&&this->_Address==Input->_Address; }
};
#endif