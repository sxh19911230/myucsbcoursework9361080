#include "Record.h"

void Record::setGrades(double quiz1, double quiz2, double midterm, double final) {
	this->quiz1 = quiz1;
	this->quiz2 = quiz2;
	this->midterm = midterm;
	this->final = final;
}

char Record::letterEquiv(const double grade) const {      // FIX SIGNATURE
	if (grade >= 90) return 'A';
	if (grade >= 80) return 'B';
	if (grade >= 70) return 'C';
	if (grade >= 60) return 'D';
	return 'F';
}

char Record::overallGrade() const {   // FIX SIGNATURE
	// ALSO CHANGE HOW THE OBJECT'S DATA ARE ACCESSED (WHO IS r NOW?  ;-)
	double quizPct = (quiz1 / 10 + quiz2 / 10) / 2;
	double overall = 25 * quizPct + 0.25 * midterm + 0.5 * final;
	return letterEquiv(overall);
}
