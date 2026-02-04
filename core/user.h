#ifndef _USER_H_
#define _USER_H_

#include <string>
using std::string;


class User {
    protected:
    unsigned id;
    string username;
    string password;
    string name;

    public:
    User(const string &user, const string &pass);
    bool verify_pass(const string &pass);
};

class Admin: public User {
};


#endif /* _USER_H_ */
