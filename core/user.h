#ifndef _USER_H_
#define _USER_H_

#include <string>


class User {
    protected:
    int id;
    std::string username;
    std::string password;

    public:
    User() {};
    User(const std::string &user, const std::string &pass, int id = -1);

    /* Getters */
    inline int getID() const { return id; }
    inline const std::string &getUsername() const { return username; }
    inline const std::string &getPassword() const { return password; }

    /* Setters */
    inline void setID(int id) { this->id = id; }
    inline void setUsername(const std::string &user) { username = user; }
    inline void setPassword(const std::string &pass) { password = pass; }

    bool verifyPassword(const std::string &pass) const;
};

class Admin: public User {
    public:
    Admin() {}
    Admin(const std::string &user, const std::string &pass, int id = 0):
    User(user, pass, id) {}
};

class Student: public User {
    public:
    Student() {}
    Student(const std::string &user, const std::string &pass, int id = 0):
    User(user, pass, id) {}
};


#endif /* _USER_H_ */
