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


void DataIO::init() {
    char* err_msg = 0;

    // 1. Read Schema File
    std::ifstream sqlFile("schema.sql");
    if (!sqlFile.is_open()) {
        std::cerr << "File Error: schema.sql missing!" << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << sqlFile.rdbuf();
    std::string sql = buffer.str();

    // 2. Execute SQL
    if (sqlite3_exec(dbcon, sql.c_str(), nullptr, 0, &err_msg) != SQLITE_OK) {
        std::cerr << "SQL Error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Database initialized successfully." << std::endl;
    }
}
