#include <dataio.h>
#include <sqlite3.h>
#include <stdlib.h>

static int callback(void *, int argc, char **argv, char **col_name) {
    return 0;
}

void DataIO::create_table() {
    sqlite3 *db;
    char *err_msg;
    int rc;
    rc = sqlite3_open("data.db", &db);
    char sql[] = 
        "CREATE TABLE IF NOT EXISTS \"Admins\" ("
	        "\"id\"	INTEGER,"
	        "\"username\"	TEXT NOT NULL UNIQUE,"
	        "\"password\"	TEXT NOT NULL,"
	        "PRIMARY KEY(\"id\" AUTOINCREMENT)"
        ");"
    ;
    rc = sqlite3_exec(db, sql, callback, NULL, &err_msg);
    sqlite3_close(db);
}
