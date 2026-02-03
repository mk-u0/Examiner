#include <user.h>
#include <util.h>


User::User(const string &user, const string &pass) {
    username = user;
    password = pass_hash(pass);
}

bool User::verify_pass(const string &pass) {
    return password == pass_hash(pass);
}
