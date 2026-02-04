#ifndef _DATAIO_H_
#define _DATAIO_H_

#include <sqlite3.h>
#include <string>
#include <user.h>

class DataIO {
    private:
    sqlite3 *dbcon;
    public:
    DataIO(const std::string &path);
    ~DataIO();

    int addAdmin(const Admin &a);
    int addResult();
    Admin getAdminByUser(const std::string &username);
    int getResultByStudentID(unsigned);
    int getResultByExamID(unsigned);

    // Dummy function to be removed later
    void create_table();
};

#endif /* _DATAIO_H_ */
