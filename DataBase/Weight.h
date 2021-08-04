#include"DATABASE_INCLUDE.h"

class Weight{
  std::string _Mail;
  std::list<int> _Times;
  public:
    void newMail(const std::string& newMail,const int MailTime){
      _Mail=newMail;
      if(_Times.size()>100) { _Times.pop_back(); }
      _Times.push_front(MailTime);
    }
    const std::string& getMail() { return _Mail; }
    int getPreferedTime(){
      int _INDEX=0;
      int _WEIGHT_1=0;
      int _WEIGHT_2=0;
      int _WEIGHT_3=0;
      for(std::list<int>::iterator i=_Times.begin();i!=_Times.end();i++){
        if(_INDEX<=_Times.size()*0.2) { _WEIGHT_1+=*i; }
        if(_INDEX>_Times.size()*0.2&&_INDEX<=_Times.size()*0.5) { _WEIGHT_2+=*i; }
        if(_INDEX>_Times.size()*0.5) { _WEIGHT_3+=*i; }
        _INDEX++;
      }
      return _WEIGHT_1*0.4+_WEIGHT_2*0.3+_WEIGHT_3*0.3;
    }
};
