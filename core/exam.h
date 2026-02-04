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

class Exam {
    public:
    typedef std::vector<bool> Result;

    private:
    unsigned id;
    std::vector<Question> questions;
    unsigned duration;

    public:
    Exam();
    inline std::size_t size() { return questions.size(); }
    const Question &question(unsigned i);
    Result check_answer(const std::vector<unsigned> &answer);
};


#endif
