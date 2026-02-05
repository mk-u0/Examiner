#include <exam.h>



Result::Result(unsigned exam_id, unsigned student_id, double grade) {
    this->exam_id = exam_id;
    this->student_id = student_id;
    this->grade = grade;
}


int Exam::findIndexByID(unsigned id) const {
    for (unsigned i = 0; i < size(); i++) {
        if (questions[i].getID() == id) {
            return i;
        }
    }
    return -1;
}

const Question &Exam::getQuestion(unsigned i) const {
    return questions[i];
}

const Question &Exam::getQuestionByID(unsigned id) const {
    return questions[findIndexByID(id)];
}

void Exam::addQuestion(const Question &q) {
    questions.push_back(q);
}

void Exam::removeQuestion(unsigned i) {
    questions.erase(questions.begin() + i);
}

void Exam::removeQuestionByID(unsigned id) {
    questions.erase(questions.begin() + findIndexByID(id));
}

void Exam::modifyQuestion(unsigned i, const Question &q) {
    questions[i] = q;
}

void Exam::modifyQuestionByID(unsigned id, const Question &q) {
    questions[findIndexByID(id)] = q;
}


std::vector<bool> Exam::checkAnswer(const std::vector<unsigned> &answer)
{
    std::vector<bool> res(size());
    for (std::size_t i = 0; i < size(); i++)
    {
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


std::string Exam::serialize() const {
    nlohmann::json j;
    j["exam_id"] = this->id;
    j["duration_minutes"] = this->duration;

    nlohmann::json questions_array = nlohmann::json::array();
    for (const auto &q : this->questions)
    {
        nlohmann::json temp_j;
        to_json(temp_j, q);
        questions_array.push_back(temp_j);
    }
    j["questions"] = questions_array;

    return j.dump(4);
}

void Exam::deserialize(const std::string &text) {
    try
    {
        nlohmann::json j = nlohmann::json::parse(text);

        j.at("exam_id").get_to(this->id);
        j.at("duration_minutes").get_to(this->duration);

        this->questions.clear();
        for (const auto &item : j.at("questions"))
        {
            Question q;
            from_json(item, q);
            this->questions.push_back(q);
        }

        std::cout << "Success: Loaded " << questions.size() << " questions." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "JSON Error: " << e.what() << std::endl;
    }
}

