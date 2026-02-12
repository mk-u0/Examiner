#include <dataio.h>

using std::string;


static const char update_admin_pass[] = "UPDATE Admins SET password = ? WHERE id = ?;";
int DataIO::updateAdminPassword(int id, const string &newPassword) {
    int rc;
    sqlite3_stmt *stmt;
    
    rc = sqlite3_prepare_v2(dbcon, update_admin_pass, sizeof(update_admin_pass), &stmt, nullptr);
    if (rc != SQLITE_OK) return rc;

    sqlite3_bind_text(stmt, 1, newPassword.c_str(), (int)newPassword.size(), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return (rc == SQLITE_DONE) ? SQLITE_OK : rc;
}


static const char update_student_pass[] = "UPDATE Students SET password = ? WHERE id = ?;";
int DataIO::updateStudentPassword(int id, const string &newPassword) {
    int rc;
    sqlite3_stmt *stmt;
    
    rc = sqlite3_prepare_v2(dbcon, update_student_pass, sizeof(update_student_pass), &stmt, nullptr);
    if (rc != SQLITE_OK) return rc;

    sqlite3_bind_text(stmt, 1, newPassword.c_str(), (int)newPassword.size(), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return (rc == SQLITE_DONE) ? SQLITE_OK : rc;
}


static const char update_exam[] =
    "UPDATE Exams SET title = ?, duration = ?, questions = ? "
    "WHERE id = ?;"
;
int DataIO::updateExamByID(int id, const Exam &exam) {
    int rc;
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(dbcon, update_exam, sizeof (update_exam), &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, exam.getTitle().c_str(), exam.getTitle().size(), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, exam.getDuration());
    sqlite3_bind_text(stmt, 3, exam.serialize().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, exam.getID());

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (rc == SQLITE_DONE)? 0 : rc;
}
