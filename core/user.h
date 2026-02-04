#ifndef _USER_H_
#define _USER_H_

#include <string>
using std::string;


class User {
    protected:
    unsigned id;
    string username;
    string password;

    public:
    User(const string &user, const string &pass);

    inline unsigned getID() const { return id; }
    inline const string &getUsername() const { return username; }
    inline const string &getPassword() const { return password; }

    bool verifyPassword(const string &pass) const;
};

class Admin: public User {
    public:
    Admin(const string &user, const string &pass): User(user, pass) {}
};

class Student: public User {
    public:
    Student(const string &user, const string &pass): User(user, pass) {}
};


#endif /* _USER_H_ */
