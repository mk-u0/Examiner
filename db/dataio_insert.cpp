#include <dataio.h>
using std::string;


static  const char insert_admin[] =
    "INSERT INTO Admins (id, username, password)"
    "VALUES (?, ?, ?);"
;
int DataIO::addAdmin(const Admin &admin) {
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(
        dbcon,
        insert_admin,
        sizeof (insert_admin),
        &stmt,
        nullptr
    );

    sqlite3_bind_int(stmt, 1, admin.getID());
    const string &username = admin.getUsername();
    sqlite3_bind_text(stmt, 2, username.c_str(), username.size(), SQLITE_STATIC);
    const string &password = admin.getPassword();
    sqlite3_bind_text(stmt, 3, password.c_str(), password.size(), SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    rc = sqlite3_finalize(stmt);
    return rc;
}


static const char insert_student[] = 
    "INSERT INTO Students (id, username, password)"
    "VALUES (?, ?, ?);"
;
int DataIO::addStudent(const Student &student) {
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(
        dbcon,
        insert_student,
        sizeof (insert_student),
        &stmt,
        nullptr
    );

    sqlite3_bind_int(stmt, 1, student.getID());
    const string &username = student.getUsername();
    sqlite3_bind_text(stmt, 2, username.c_str(), username.size(), SQLITE_STATIC);
    const string &password = student.getPassword();
    sqlite3_bind_text(stmt, 3, password.c_str(), password.size(), SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    rc = sqlite3_finalize(stmt);
    return rc;
}


static const char insert_result[] = 
    "INSERT INTO Results (exam_id, student_id, grade)"
    "VALUES (?, ?, ?);"
;
int DataIO::addResult(const Result &result) {
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(
        dbcon,
        insert_result,
        sizeof (insert_result),
        &stmt,
        nullptr
    );

    sqlite3_bind_int(stmt, 1, result.getExamID());
    sqlite3_bind_int(stmt, 2, result.getStudentID());
    sqlite3_bind_double(stmt, 3, result.getGrade());

    rc = sqlite3_step(stmt);
    rc = sqlite3_finalize(stmt);
    return rc;
}


static const char insert_exam[] = 
    "INSERT INTO Exams (exam_id, duration, body)"
    "VALUES (?, ?, ?);"
;
int DataIO::addExam(const Exam &exam) {
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(
        dbcon,
        insert_exam,
        sizeof (insert_exam),
        &stmt,
        nullptr
    );

    sqlite3_bind_int(stmt, 1, exam.getID());
    sqlite3_bind_int(stmt, 2, exam.getDuration());
    string body = exam.serialize();
    sqlite3_bind_text(stmt, 3, body.c_str(), body.size(), SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    rc = sqlite3_finalize(stmt);
    return rc;
}

