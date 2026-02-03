#include <exam.h>


const Question &Exam::question(unsigned i) {
    return questions[i];
}

Exam::Result Exam::check_answer(const std::vector<unsigned> &answer) {
    Exam::Result res(size());
    for (std::size_t i = 0; i < size(); i++) {
        res[i] = (answer[i] == questions[i].correct);
    }
    return res;
}
