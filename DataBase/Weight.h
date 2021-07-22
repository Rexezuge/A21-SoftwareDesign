#ifndef SDD_EASYCONTACT_DATABASE_WEIGHT
#define SDD_EASYCONTACT_DATABASE_WEIGHT
#include<list>
#include<string>
class Weight{
  std::string _Mail;
  std::list<int> _Times;
  public:
    void newMail(const std::string& newMail,const int MailTime) { _Mail=newMail; _Times.push_front(MailTime); }
    const std::string& getMail() { return _Mail; }
    int getPreferedTime();
};
#endif