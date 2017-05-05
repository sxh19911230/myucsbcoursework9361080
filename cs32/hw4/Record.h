// Record.h - uses C++ style object-handling
// Xianghong Sun, 10/25/2014

#ifndef RECORD_H
#define RECORD_H

class Record {

public:
	void setGrades(double, double, double, double);
	char letterEquiv(const double grade) const;
	char overallGrade() const;

private:
	double quiz1, quiz2;
	double midterm, final;
};
#endif