#ifndef _DATAIO_H_
#define _DATAIO_H_

#include <sqlite3.h>
#include <string>
#include <vector>
#include <user.h>
#include <exam.h>

class DataIO {
    private:
    sqlite3 *dbcon;
    public:
    DataIO(const std::string &path);
    ~DataIO();

    int addAdmin(const Admin &admin);
    int addStudent(const Student &student);
    int addResult(const Result &res);
    Admin getAdminByUser(const std::string &username);
    Student getStudentByUser(const std::string &username);
    std::vector<Result> getResultByStudentID(unsigned student_id);
    std::vector<Result> getResultByExamID(unsigned exam_id);

    // Dummy function to be removed later
    void create_table();
};

#endif /* _DATAIO_H_ */
