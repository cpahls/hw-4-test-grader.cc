/**
 *   @file: test-grader.cc
 * @author: Christian Pahls
 *   @date: 03/07/2024
 *  @brief: This Program is used to show us how to access (read from and write to) a txt file.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
using namespace std;



int letter_grade(double score){
    char grade;

    // letter grade assigned based on score
    if (score >= 90){
        grade = 'A';
    } else if (score >= 80 && score < 90){
        grade = 'B';
    } else if (score >= 70 && score < 80){
        grade = 'C';
    } else if (score >= 60 && score < 70){
        grade = 'D';
    } else {
        grade = 'F';
    }

    return grade;
} // end letter_grade()



int grade_exam_one(string key, string answers){
    double score = 0;
    double correct = 0;
    double max = answers.size();

    // determines number correct
    for (int i = 0; i <= max -1; ++i){
        if (key.at(i) == answers.at(i)){
            correct++;
        }
    }

    // score = total correct divided by maximum possible correct
    score = (correct / max) * 100;
    return score;
} //end int_grade_exam_one



int output_report(string outputFile, string first, string last, string key, string answers, double score, char grade) {

    // open file (to append) for output
    fstream fOut;
    fOut.open(outputFile, fstream::app);

    if (fOut.is_open()) {
        // Write data to the file
        fOut << last << ", " << first << '\n';
        fOut << "------------------------------------------------------------" << '\n';
        fOut << "Answers, correct answer in parenthesis" << endl << endl;

        // section for writing out answers 1 - 5
        fOut << "    " << "1: " << answers.at(0) << "(" << key.at(0) << ")" << '\t';
        fOut << '\t' << "2: " << answers.at(1) << "(" << key.at(1) << ")" << '\t';
        fOut << '\t' << "3: " << answers.at(2) << "(" << key.at(2) << ")" << '\t';
        fOut << '\t' << "4: " << answers.at(3) << "(" << key.at(3) << ")" << '\t';
        fOut << '\t' << "5: " << answers.at(4) << "(" << key.at(4) << ")" << '\n';

        // section for writing out answers 6 - 10
        fOut << "    " << "6: " << answers.at(5) << "(" << key.at(5) << ")" << '\t';
        fOut << '\t' << "7: " << answers.at(6) << "(" << key.at(6) << ")" << '\t';
        fOut << '\t' << "8: " << answers.at(7) << "(" << key.at(7) << ")" << '\t';
        fOut << '\t' << "9: " << answers.at(8) << "(" << key.at(8) << ")";
        fOut << "    " << "10: " << answers.at(9) << "(" << key.at(9) << ")" << '\n';

        // section for writing out answers 11 - 15
        fOut << "   " << "11: " << answers.at(10) << "(" << key.at(10) << ")";
        fOut << "    " << "12: " << answers.at(11) << "(" << key.at(11) << ")";
        fOut << "    " << "13: " << answers.at(12) << "(" << key.at(12) << ")";
        fOut << "    " << "14: " << answers.at(13) << "(" << key.at(13) << ")";
        fOut << "    " << "15: " << answers.at(14) << "(" << key.at(14) << ")" << endl << endl;
    
        fOut << "Score: " << score << "% " << grade << '\n';
        fOut << "------------------------------------------------------------" << endl << endl;
    } else {
        cout << "Unable to open " << outputFile << " for writing.\n";
    }
    fOut.close();

    return 0;
} // end output_report



int main(int argc, char const *argv[]) {

// define variables
    string inputFile, line, key, first, last, answers, answersU;
    double score, clsCorrect, clsMax, clsScore;
    char grade;

// program steps
    // sets inputFile variable equal to argument in position 1 (exam.txt)
    inputFile = argv[1];

    // open exam.txt
    fstream fIn;
    fIn.open(inputFile, fstream::in);

    // first line is the key
    getline(fIn, key);

    // remaining lines are the students/answers
    while (getline(fIn, line)) {
        // isolate first name
        size_t spc1 = line.find(' ');
        first = line.substr(0,spc1);
        // isolate last name
        size_t spc2 = line.find(' ', spc1 + 1);
        last = line.substr(spc1 + 1, spc2 - spc1 -1);
        // isolate answers
        answers = line.substr(spc2 + 1, key.size());
        answersU = "";

        // convert answers to upper case
        for (char c : answers){
            answersU += std::toupper(c);
        }

        // score each exam
        score = grade_exam_one(key, answersU);

        // keep running total for class average
        clsCorrect = clsCorrect + (score / 100 * key.size());
        clsMax = clsMax + key.size();
        
        // assign letter grade
        grade = letter_grade(score);
    
        // output to report
        output_report(argv[2], first, last, key, answersU, score, grade);

        } // end while loop through file
        fIn.close();    // close exam.txt file

        // calc class average
        clsScore = clsCorrect / clsMax * 100;
        grade = letter_grade(clsScore);

        // write out class average
        fstream fOut;
        fOut.open(argv[2], fstream::app);

        if (fOut.is_open()) {
            fOut << "------------------------------------------------------------" << '\n';
            fOut << "Class average: " << clsScore << "% " << grade << '\n';
            fOut << "------------------------------------------------------------" << '\n';
        }
    fOut.close();   // close report.txt file

    return 0;

} // end main()