#include <user.h>
#include <util.h>


User::User(const string &user, const string &pass) {
    username = user;
    password = hashPassword(pass);
}

bool User::verifyPassword(const string &pass) const {
    return password == hashPassword(pass);
}
