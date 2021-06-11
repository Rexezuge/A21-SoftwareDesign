#include<string>

class Contact{
  long unsigned int _Phone;
  std::string _Name;
  std::string _Address;
  public:
    Contact(std::string Name,long unsigned int Phone,std::string Address){
      _Name=Name;
      _Address=Address;
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
    std::string toString(){ return std::string(_Name+"%%%"+std::to_string(_Phone)+"%%%"+_Address); }
};
