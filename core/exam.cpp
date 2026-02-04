#include <exam.h>


const Question &Exam::question(unsigned i) {
    return questions[i];
}

Result::Result(unsigned exam_id, unsigned student_id, double grade) {
    this->exam_id = exam_id;
    this->student_id = student_id;
    this->grade = grade;
}

std::vector<bool> Exam::checkAnswer(const std::vector<unsigned> &answer) {
    std::vector<bool> res(size());
    for (std::size_t i = 0; i < size(); i++) {
        res[i] = (answer[i] == questions[i].correct);
    }
    return res;
}

Result Exam::getResult(const std::vector<unsigned> &answer, unsigned student_id) {
    std::vector<bool> res = checkAnswer(answer);
    unsigned correct_num = 0;
    for (unsigned i = 0; i < size(); i++) {
        correct_num += static_cast<unsigned>(res[i]);
    }
    double grade = static_cast<double>(correct_num) / size();
    return Result(id, student_id, grade);
}

