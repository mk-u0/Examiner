#include <user.h>
#include <util.h>


User::User(const std::string &user, const std::string &pass, int id) {
    username = user;
    password = hashPassword(pass);
    this->id = id;
}

bool User::verifyPassword(const std::string &pass) const {
    return password == hashPassword(pass);
}
