#include <dataio.h>
#include <iostream>
#include <cstdio>
#include <string>

using std::string;

#define TEST_DB "test_update.db"

int main() {
    DataIO db(TEST_DB);
    db.init();

   
    Admin admin("sara_test", "old_pass");
    db.addAdmin(admin);
    Admin r_admin = db.getAdminByUser("sara_test");

   
    string newPass = "SARA_SECRET";
    db.updateAdminPassword(r_admin.getID(), newPass);

    
    Admin updated_admin = db.getAdminByUser("sara_test");

    int rc = 0;
    
    rc = rc || (updated_admin.getPassword() != newPass);

    if (rc == 0) std::cout << "Update Admin Test: PASSED\n";
    
    std::remove(TEST_DB); 
    return rc;
}