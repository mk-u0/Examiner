#ifndef _EXAM_H_
#define _EXAM_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

class Question {
public:
    typedef std::vector<std::string> Choice;

private:
    unsigned id;
    std::string text;
    Choice choice;
    unsigned correct;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Question, id, text, choice, correct)

    /* Getters */
    inline unsigned getID() const { return id; }
    inline const std::string &getText() const { return text; }
    inline const Choice &getChoice() const { return choice; }
    inline unsigned getCorrect() const { return correct; }

    /* Setters */
    inline void setID(unsigned id) { this->id = id; }
    inline void setText(const std::string &text) { this->text = text; }
    inline void setChoice(const Choice &choice) { this->choice = choice; }
    inline void setCorrect(unsigned correct) { this->correct = correct; }

    friend class Exam;
};

class Result {
private:
    unsigned exam_id;
    unsigned student_id;
    double grade;

public:
    Result(unsigned exam_id, unsigned student_id, double grade);

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
    Exam() {}

    inline std::size_t size() const { return questions.size(); }
    inline unsigned getID() const { return id; }
    inline unsigned getDuration() const { return duration; }

    unsigned findIndexByID(unsigned id) const;
    const Question &getQuestion(unsigned i) const;
    const Question &getQuestionByID(unsigned id) const;
    void addQuestion(const Question &q);
    void removeQuestion(unsigned i);
    void removeQuestionByID(unsigned id);
    void modifyQuestion(unsigned i, const Question &q);
    void modifyQuestionByID(unsigned id, const Question &q);

    std::vector<bool> checkAnswer(const std::vector<unsigned> &answer);
    Result getResult(const std::vector<unsigned> &answer, unsigned student_id);

    std::string serialize() const;
    void deserialize(const std::string &text);
};

#endif
