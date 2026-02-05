#include <dataio.h>
using std::string;


static const char select_admin[] =
    "SELECT id, username, password FROM Admins "
    "WHERE username = ?;"
;
Admin DataIO::getAdminByUser(const string &username) {
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(
        dbcon,
        select_admin,
        sizeof (select_admin),
        &stmt,
        nullptr
    );
    if (rc != SQLITE_OK) throw std::runtime_error("sqlite3_prepare: " + std::to_string(rc));

    rc = sqlite3_bind_text(stmt, 1, username.c_str(), username.size(), SQLITE_STATIC);
    if (rc != SQLITE_OK) throw std::runtime_error("sqlite3_bind: " + std::to_string(rc));

    Admin admin;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        admin.setID(0);
        admin.setUsername("");
        admin.setPassword("");
    }
    else if (rc == SQLITE_ROW) {
        admin.setID(sqlite3_column_int(stmt, 0));
        admin.setUsername((const char *)sqlite3_column_text(stmt, 1));
        admin.setPassword((const char *)sqlite3_column_text(stmt, 2));
    }
    sqlite3_finalize(stmt);
    return admin;
}


static const char select_student[] =
    "SELECT id, username, password FROM Students "
    "WHERE username=?;"
;
Student DataIO::getStudentByUser(const string &username) {
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(
        dbcon,
        select_student,
        sizeof (select_student),
        &stmt,
        nullptr
    );

    sqlite3_bind_text(stmt, 1, username.c_str(), username.size(), SQLITE_STATIC);

    Student student;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        student.setID(0);
        student.setUsername("");
        student.setPassword("");
    }
    else {
        student.setID(sqlite3_column_int(stmt, 0));
        student.setUsername((const char *)sqlite3_column_text(stmt, 1));
        student.setPassword((const char *)sqlite3_column_text(stmt, 2));
    }
    sqlite3_finalize(stmt);
    return student;
}


static const char select_result_student[] =
    "SELECT exam_id, grade FROM Results "
    "WHERE student_id=?;"
;
std::vector<Result> DataIO::getResultByStudentID(unsigned student_id) {
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(
        dbcon,
        select_result_student,
        sizeof (select_result_student),
        &stmt,
        nullptr
    );

    rc = sqlite3_bind_int(stmt, 1, student_id);

    std::vector<Result> results;
    unsigned exam_id;
    double grade;
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        exam_id = sqlite3_column_int(stmt, 0);
        grade = sqlite3_column_double(stmt, 1);
        results.push_back(Result(exam_id, student_id, grade));
    }

    sqlite3_finalize(stmt);
    return results;
}


static const char select_result_exam[] =
    "SELECT student_id, grade FROM Results "
    "WHERE exam_id=?;"
;
std::vector<Result> DataIO::getResultByExamID(unsigned exam_id) {
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(
        dbcon,
        select_result_exam,
        sizeof (select_result_exam),
        &stmt,
        nullptr
    );

    rc = sqlite3_bind_int(stmt, 1, exam_id);

    std::vector<Result> results;
    unsigned student_id;
    double grade;
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        student_id = sqlite3_column_int(stmt, 0);
        grade = sqlite3_column_double(stmt, 1);
        results.push_back(Result(exam_id, student_id, grade));
    }

    sqlite3_finalize(stmt);
    return results;
}

