#include "DATABASE_INCLUDE.h"

class Weight {
    std::string _Mail;
    std::list<int> _Times;

   public:
    /**
     * Create entry for the new email
     *
     * @param newMail
     * @param MailTime
     */
    void newMail(const std::string& newMail, const int MailTime) {
        _Mail = newMail;
        if (_Times.size() > 100) {
            _Times.pop_back();
        }
        _Times.push_front(MailTime);
    }
    /**
     * Get the Mail
     *
     * @return const std::string&
     */
    const std::string& getMail() { return _Mail; }
    /**
     * Get the Preferred Time
     *
     * @return int
     */
    int getPreferedTime() {
        if (!_Times.size()) {
            return 0;
        } else if (_Times.size() < 20) {
            int _INDEX = 0;
            int _WEIGHT_1 = 0, _WEIGHT_1_SIZE = _Times.size();
            for (std::list<int>::iterator i = _Times.begin(); i != _Times.end();
                 i++) {
                if (_INDEX <= _WEIGHT_1_SIZE) {
                    _WEIGHT_1 += *i;
                }
            }
            return _WEIGHT_1 / _WEIGHT_1_SIZE;
        } else if (_Times.size() < 50) {
            int _INDEX = 0;
            int _WEIGHT_1 = 0, _WEIGHT_1_SIZE = 20;
            int _WEIGHT_2 = 0, _WEIGHT_2_SIZE = _Times.size() - 20;
            for (std::list<int>::iterator i = _Times.begin(); i != _Times.end();
                 i++) {
                if (_INDEX <= _WEIGHT_1_SIZE) {
                    _WEIGHT_1 += *i;
                }
                if (_INDEX > _WEIGHT_1_SIZE) {
                    _WEIGHT_2 += *i;
                }
            }
            return _WEIGHT_1 / _WEIGHT_1_SIZE * 0.6 +
                   _WEIGHT_2 / _WEIGHT_2_SIZE * 0.4;
        }
        int _INDEX = 0;
        int _WEIGHT_1 = 0, _WEIGHT_1_SIZE = _Times.size() * 0.2;
        int _WEIGHT_2 = 0, _WEIGHT_2_SIZE = _Times.size() * 0.5;
        int _WEIGHT_3 = 0;
        for (std::list<int>::iterator i = _Times.begin(); i != _Times.end();
             i++) {
            if (_INDEX <= _WEIGHT_1_SIZE) {
                _WEIGHT_1 += *i;
            }
            if (_INDEX > _WEIGHT_1_SIZE && _INDEX <= _WEIGHT_2_SIZE) {
                _WEIGHT_2 += *i;
            }
            if (_INDEX > _WEIGHT_2_SIZE) {
                _WEIGHT_3 += *i;
            }
            _INDEX++;
        }
        return _WEIGHT_1 / _WEIGHT_1_SIZE * 0.4 +
               _WEIGHT_2 / _WEIGHT_2_SIZE * 0.3 +
               _WEIGHT_3 / _WEIGHT_2_SIZE * 0.3;
    }
    /**
     * Get the Latest email received Time
     *
     * @return int
     */
    int getLatestTime() { return _Times.front(); }
    /**
     * Reset the weight of the email
     *
     * @param mail
     * @param T
     * @return true
     */
    bool restoreWeight(const std::string& mail, const std::list<int>& T) {
        _Mail = mail;
        _Times = T;
        return true;
    }
    /**
     * Get the Total number of emails
     *
     * @return int
     */
    int getTotalMails() { return (int)_Times.size(); }
    void cpyWeight(const Weight& W) {
        this->_Mail = W._Mail;
        this->_Times = W._Times;
    }
};
