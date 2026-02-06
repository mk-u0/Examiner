#include <dataio.h>
#include <iostream>
#include <cstdio>
#include <string>
using std::cerr;
using std::string;

static int test_admin();
static int test_student();

#define TEST_DB "test.db"

int main(int argc, char *args[]) {
    if (argc < 2) {
        cerr << "Too few arguments\n";
        return -1;
    }

    string test(args[1]);

    int rc;
    if (test == "admin") {
        rc = test_admin();
    }
    else if (test == "student") {
        rc = test_student();
    }
    else {
        cerr << "Not a valid argument\n";
        rc = -1;
    }

    std::remove(TEST_DB);
    return rc;
}


static int test_admin() {
    DataIO db(TEST_DB);
    db.init();
    Admin admin("admin", "admin");
    db.addAdmin(admin);
    Admin r_admin = db.getAdminByUser(admin.getUsername());

    int rc = 0;
    rc = rc || admin.getUsername() != r_admin.getUsername();
    rc = rc || admin.getPassword() != r_admin.getPassword();
    return rc;
}


static int test_student() {
    DataIO db(TEST_DB);
    db.init();
    Student student("mk", "1234");
    db.addStudent(student);
    Student r_student = db.getStudentByUser("mk");

    int rc = 0;
    rc = rc || student.getUsername() != r_student.getUsername();
    rc = rc || student.getPassword() != r_student.getPassword();
    return rc;
}
