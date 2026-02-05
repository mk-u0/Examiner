#include <dataio.h>
#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;

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

/* Define the database tables */
#include <schema.h>
void DataIO::init() {
    char* err_msg = 0;

    if (sqlite3_exec(dbcon, tables, nullptr, nullptr, &err_msg) != SQLITE_OK) {
        std::cerr << "SQL Error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Database initialized successfully." << std::endl;
    }
}

