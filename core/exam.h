#ifndef _EXAM_H_
#define _EXAM_H_

#include <vector>
#include <string>

class Question {
    public:
    typedef std::vector<std::string> Choice;

    private:
    unsigned id;
    std::string text;
    Choice choice;
    unsigned correct;

    public:
    inline unsigned get_correct() { return correct; }

    friend class Exam;
};

class Result {
    private:
    unsigned exam_id;
    unsigned student_id;
    double grade;

    public:
    Result(unsigned exam_id, unsigned student_id, double grade_id);

    inline unsigned getExamID() const { return exam_id; }
    inline unsigned getStudentID() const { return student_id; }
    inline double getGrade() const { return grade; }

    friend class Exam;
};

class Exam {
    private:
    unsigned id;
    std::vector<Question> questions;
    unsigned duration;

    public:
    Exam();
    inline std::size_t size() const { return questions.size(); }
    const Question &question(unsigned i);
    std::vector<bool> checkAnswer(const std::vector<unsigned> &answer);
    Result getResult(const std::vector<unsigned> &answer, unsigned student_id);
};


#endif
