#ifndef _DATAIO_H_
#define _DATAIO_H_

class DataIO {
<<<<<<< HEAD
    private:
    sqlite3 *dbcon;
    public:
    DataIO(const std::string &path);
    ~DataIO();

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

    // Dummy function to be removed later
    void create_table();
=======
public:
    void init();
    
>>>>>>> 8f23868 (final database task)
};

#endif /* _DATAIO_H_ */
