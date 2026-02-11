#include <dataio.h>
#include <exam.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

#define TEMP_DB "logic_test_temp.db"

int main() {
    int rc = 0;

    {
        try {
            std::cout << "Opening database...\n";
            DataIO db(TEMP_DB);
            db.init();

//Prepare Test Data
            Exam originalExam;
            originalExam.setID(101);
            originalExam.setTitle("C++ Logic Test");
            originalExam.setDuration(30);

            Question q1;
            q1.setID(1);
            q1.setText("What is the base class of Admin?");
            q1.setChoice({"Student", "User", "DataIO", "Exam"});
            q1.setCorrect(1);

            originalExam.addQuestion(q1);

//Insert Into Database
            std::cout << "Saving exam to database...\n";
            int insertCode = db.addExam(originalExam);

            if (insertCode != SQLITE_OK) {
                std::cerr << "Insert failed. SQLite Code: " << insertCode << "\n";
                return 1;
            }

//Retrieve From Database
            std::cout << "Retrieving exam from database...\n";
            Exam retrievedExam = db.getExamById(101);

//Validate Data Integrity
            if (retrievedExam.getID() == -1) {
                std::cerr << "Exam not found.\n";
                rc = 1;
            }
            else if (retrievedExam.getTitle() != originalExam.getTitle()) {
                std::cerr << "Title mismatch.\n";
                rc = 1;
            }
            else if (retrievedExam.getDuration() != originalExam.getDuration()) {
                std::cerr << "Duration mismatch.\n";
                rc = 1;
            }
            else if (retrievedExam.size() != 1) {
                std::cerr << "Question count mismatch.\n";
                rc = 1;
            }
            else {
                Question fetchedQ = retrievedExam.getQuestion(0);

                if (fetchedQ.getText() != q1.getText()) {
                    std::cerr << "Question text mismatch.\n";
                    rc = 1;
                }
                else if (fetchedQ.getCorrect() != q1.getCorrect()) {
                    std::cerr << "Correct answer mismatch.\n";
                    rc = 1;
                }
                else {
                    std::cout << "Test passed successfully.\n";
                }
            }

        }
        catch (const std::exception& e) {
            std::cerr << "Critical exception: " << e.what() << "\n";
            rc = 1;
        }

        std::cout << "Closing database connection...\n";
    }



    if (std::remove(TEMP_DB) == 0) {
        std::cout << "Temporary database removed.\n";
    } else {
        std::cerr << "Failed to remove temporary database file.\n";
    }

    return rc;
}
