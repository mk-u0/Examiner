#ifndef _USER_H_
#define _USER_H_

#include <string>
using std::string;


class User {
    protected:
    string username;
    string password;
    string name;

    public:
    User(const string &user, const string &pass);
    bool verify_pass(const string &pass);
};


#endif /* _USER_H_ */
