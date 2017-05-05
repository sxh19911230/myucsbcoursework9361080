// grading2.cpp
// Xianghong Sun, 10/25/2014

#include <iostream>
#include "Record.h"
using namespace std;

Record getScores();


int main() {
    Record rec = getScores();
    cout << "Grade is " << rec.overallGrade() << endl;
    return 0;
}

Record getScores() {
    Record result;
    double quiz1, quiz2, midterm, final;
    cout << "Enter scores in this order: 2 quizzes, midterm, final: ";
    cin >> quiz1 >> quiz2 >> midterm >> final;
    result.setGrades(quiz1, quiz2, midterm, final);
    return result;
}


