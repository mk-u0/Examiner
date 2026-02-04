#include <dataio.h>
#include <sqlite3.h>
#include <string>
#include <sstream>
//#include <fmt/core.h>

using std::string, std::stringstream;


/* Constructor and Destructor */

DataIO::DataIO(const string &path) {
    int rc;
    rc = sqlite3_open(path.c_str(), &dbcon);
    if (rc != SQLITE_OK) {
        throw sqlite3_errmsg(dbcon);
    }
}

DataIO::~DataIO() {
    sqlite3_close(dbcon);
    dbcon = nullptr;
}


int DataIO::addAdmin(const Admin &a) { /* TODO */ }
int DataIO::addStudent(const Student &student) { /* TODO */ }
int DataIO::addResult(const Result &res) { /* TODO */ }
Admin DataIO::getAdminByUser(const std::string &username) { /* TODO */ }
Student getStudentByUser(const std::string &username) { /* TODO */ }
std::vector<Result> DataIO::getResultByStudentID(unsigned student_id) { /* TODO */ }
std::vector<Result> DataIO::getResultByExamID(unsigned exam_id) { /* TODO */ }


// Garbage to be deleted
static int callback(void *, int argc, char **argv, char **col_name) {
    return 0;
}

// Dummy function to be removed later
void DataIO::create_table() {
    char *err_msg;
    int rc;
    char sql[] = 
        "CREATE TABLE IF NOT EXISTS \"Admins\" ("
	        "\"id\"	INTEGER,"
	        "\"username\"	TEXT NOT NULL UNIQUE,"
	        "\"password\"	TEXT NOT NULL,"
	        "PRIMARY KEY(\"id\" AUTOINCREMENT)"
        ");"
    ;
    rc = sqlite3_exec(dbcon, sql, callback, NULL, &err_msg);
}
