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
    int id;
    std::string text;
    Choice choice;
    int correct;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Question, id, text, choice, correct)

    /* Getters */
    inline int getID() const { return id; }
    inline const std::string &getText() const { return text; }
    inline const Choice &getChoice() const { return choice; }
    inline int getCorrect() const { return correct; }

    /* Setters */
    inline void setID(int id) { this->id = id; }
    inline void setText(const std::string &text) { this->text = text; }
    inline void setChoice(const Choice &choice) { this->choice = choice; }
    inline void setCorrect(int correct) { this->correct = correct; }

    friend class Exam;
};

class Result {
private:
    int exam_id;
    int student_id;
    double grade;

public:
    Result(int exam_id, int student_id, double grade);

    inline int getExamID() const { return exam_id; }
    inline int getStudentID() const { return student_id; }
    inline double getGrade() const { return grade; }

    friend class Exam;
};

class Exam {
private:
    int id;
    std::vector<Question> questions;
    int duration;
    std::string title;

public:
    Exam() {}

    inline std::size_t size() const { return questions.size(); }

    /* Getters */
    inline int getID() const { return id; }
    inline int getDuration() const { return duration; }
    inline const std::string &getTitle() const { return title; }
    inline const std::vector<Question> &getQuestions() const { return questions; }

    /* Setters */
    inline void setID(int id) { this->id = id; }
    inline void setDuration(int duration) { this->duration = duration; }
    inline void setTitle(const std::string &title) { this->title = title; }

    /* Questions Functions */
    int findIndexByID(int id) const;
    const Question &getQuestion(int i) const;
    const Question &getQuestionByID(int id) const;
    void addQuestion(const Question &q);
    void removeQuestion(int i);
    void removeQuestionByID(int id);
    void modifyQuestion(int i, const Question &q);
    void modifyQuestionByID(int id, const Question &q);

    std::vector<bool> checkAnswer(const std::vector<int> &answer);
    Result getResult(const std::vector<int> &answer, int student_id);

    std::string serialize() const;
    void deserialize(const std::string &text);
};

#endif
