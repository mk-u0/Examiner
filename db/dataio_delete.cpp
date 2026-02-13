#include <dataio.h>

using std::string;

static const char delete_admin[] = "DELETE FROM Admins WHERE id = ?;";
int DataIO::deleteAdmin(int id) {
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(dbcon, delete_admin, sizeof(delete_admin), &stmt, nullptr);
    if (rc != SQLITE_OK) return rc;
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc;
}

static const char delete_student[] = "DELETE FROM Students WHERE id = ?;";
int DataIO::deleteStudent(int id) {
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(dbcon, delete_student, sizeof(delete_student), &stmt, nullptr);
    if (rc != SQLITE_OK) return rc;
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc;
}

static const char delete_exam[] = "DELETE FROM Exams WHERE id = ?;";
int DataIO::deleteExam(int id) {
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(dbcon, delete_exam, sizeof(delete_exam), &stmt, nullptr);
    if (rc != SQLITE_OK) return rc;
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc;
}
