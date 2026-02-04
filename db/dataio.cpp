#include "dataio.h"
#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <sstream>

static int callback(void*, int argc, char** argv, char** col_name) { return 0; }

void DataIO::init() {
    sqlite3* db;
    char* err_msg = 0;

    // 1. Open Connection
    if (sqlite3_open("data.db", &db) != SQLITE_OK) {
        std::cerr << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // 2. Read Schema File
    std::ifstream sqlFile("schema.sql");
    if (!sqlFile.is_open()) {
        std::cerr << "File Error: schema.sql missing!" << std::endl;
        sqlite3_close(db);
        return;
    }

    std::stringstream buffer;
    buffer << sqlFile.rdbuf();
    std::string sql = buffer.str();

<<<<<<< HEAD
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
=======
    // 3. Execute SQL
    if (sqlite3_exec(db, sql.c_str(), callback, 0, &err_msg) != SQLITE_OK) {
        std::cerr << "SQL Error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Database initialized successfully." << std::endl;
    }

    sqlite3_close(db);
}
>>>>>>> 8f23868 (final database task)
