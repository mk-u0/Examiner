#ifndef _DATAIO_H_
#define _DATAIO_H_

#include <vector>
#include <string>
#include <sqlite3.h>
#include <user.h>
#include <exam.h>

class DataIO {
    private:
    sqlite3 *dbcon;
    public:
    DataIO(const std::string &path);
    ~DataIO();

    /* Define the database tables */
    void init();

    /* Data insertion functions */
    int addAdmin(const Admin &admin);
    int addStudent(const Student &student);
    int addResult(const Result &result);
    int addExam(const Exam &exam);

    /* Data selection functions */
    Admin getAdminByUser(const std::string &username);
    Student getStudentByUser(const std::string &username);
    std::vector<Result> getResultByStudentID(unsigned student_id);
    std::vector<Result> getResultByExamID(unsigned exam_id);

    /* Data deletion functions */
    int deleteAdmin(int id);
    int deleteStudent(int id);
    int deleteExam(int id);

};

#endif /* _DATAIO_H_ */
