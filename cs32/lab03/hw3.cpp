// grading2.cpp - uses C++ style object-handling (AFTER CHANGES BELOW)
// Xianghong Sun, 10/21/2014

#include <iostream>
using namespace std;

class Record {                      // CHANGE TO class
    
// DECLARE A public SECTION, AND DEFINE A NEW METHOD NAMED setGrades,
// THAT TAKES FOUR double ARGUMENTS

public:
	Record();
	Record(double, double, double, double);

	void setGrades(double, double, double, double);
	void setQuiz1Grade(double);
	void setQuiz2Grade(double);
	void setMidtermGrade(double);
	void setFinalGrade(double);
	char letterEquiv(const double grade) const;  	

	char overallGrade() const;
	char overallGrade(double, double, double) const;

	double getQuiz1Grade() const;
	double getQuiz2Grade() const;
	double getAveQuizGrade() const;
	double getMidtermGrade() const;
	double getFinalGrade() const;

	void display() const;

// DECLARE A private SECTION AND MAKE ALL DATA PART OF IT
private:
	double quiz1, quiz2; 
	double midterm, final;
};

Record getScores();
bool quizIsInRange(double);
bool examIsInRange(double);


int main() {
	Record rec = getScores();
	rec.display();

	cout << "Function testing:" << endl;
	cout << "Record testRec(8,8,90,100)" << endl;
	Record testRec(8,8,90,100);
	testRec.display();
	cout << "setQuiz1Grade(11);" << endl;
	testRec.setQuiz1Grade(11);
	cout << "getQuiz1Grade() : " << testRec.getQuiz1Grade() << endl;
        cout << "setQuiz2Grade(6);" << endl;
        testRec.setQuiz2Grade(6);
	cout << "getQuiz2Grade() : " << testRec.getQuiz2Grade() << endl;
	cout << "getAveQuizGrade() : " << testRec.getAveQuizGrade() << endl;
        cout << "setMidtermGrade(101);" << endl;
        testRec.setMidtermGrade(101);
	cout << "getMidtermGrade() : " << testRec.getMidtermGrade() << endl;
        cout << "setFinalGrade(80);" << endl;
        testRec.setFinalGrade(80);
	cout << "getFinalGrade() : " << testRec.getFinalGrade() << endl;
	cout << "overallGrade() : " << testRec.overallGrade() << endl;
	cout << "overallGrade(1,5,2) : " << testRec.overallGrade(1,5,2) << endl;
	cout << "testing finished. 感觉萌萌哒." << endl;
	return 0;
}

//External Functions

// getScores IS AN external FUNCTION, SO IT MUST USE setGrades TO SET THE VALUES
// OF THE OBJECT'S private DATA (Hint: You'll need some local variables.)
Record getScores() {
	Record result;
	bool isSet = false;
	char tmp;
	double quiz1 = -1, quiz2 = -1, midterm = -1, final = -1;
	while (!isSet) {
		cout << "Enter scores in this order: 2 quizzes, midterm, final: ";
		cin >> quiz1 >> quiz2 >> midterm >> final;

		//cin fails
		if (cin.fail()){
			cin.clear();
			cin.ignore(200, '\n');
			cout << "Your input fails, please enter again." << endl;
			quiz1 = quiz2 = midterm = final = -1;
			continue;
		}
		

		//more than 4 arguments
		while (cin.peek() == 32) {
			cin.get(tmp);
		}
		
		if (cin.peek() != 10) {
			cout << "Your input has more than 4 arguments, please enter again." << endl;
			cin.ignore(200, '\n');
			continue;
		}

		//no input error
		isSet = true;

		//Score in range 0-100
		if (!quizIsInRange(quiz1) || !quizIsInRange(quiz2)) {
			cout << "Quiz score must between 0 and 10." << endl;
			isSet = false;
		}
		if (!examIsInRange(midterm) || !examIsInRange(final)) {
			cout << "Midterm and Final score must between 0 and 100." << endl;
			isSet = false;
		}
		
		
	}
	result.setGrades(quiz1, quiz2, midterm, final);
	return result;
}

bool quizIsInRange(double score) {
	return score <= 10.0 && score >= 0.0;
}

bool examIsInRange(double score) {
	return score <= 100.0 && score >= 0.0;
}



//Record functions

//Construction
Record::Record() {
	setGrades(0, 0, 0, 0);
}

Record::Record(double quiz1, double quiz2, double midterm, double final) {
	setGrades(quiz1, quiz2, midterm, final);
}



// THE NEXT TWO FUNCTIONS ARE METHODS OF THE CLASS, SO THEY MUST PROPERLY
// BE IDENTIFIED AS SUCH WITH THE SCOPE RESOLUTION OPERATOR '::'
// REMEMBER TO IMPLEMENT THE NEW setGrades METHOD TOO.

void Record::setGrades(double quiz1, double quiz2, double midterm, double final) {
	if (quiz1 < 0.0)
		this->quiz1 = 0.0;
	else if (quiz2 > 10.0)
		this->quiz1 = 10.0;
	else
		this->quiz1 = quiz1;

	if (quiz2 < 0.0)
		this->quiz2 = 0.0;
	else if (quiz2 > 10.0)
		this->quiz2 = 10.0;
	else
		this->quiz2 = quiz2;

	if (midterm < 0.0)
		this->midterm = 0.0;
	else if (midterm > 100.0)
		this->midterm = 100.0;
	else
		this->midterm = midterm;

	if (final < 0.0)
		this->final = 0.0;
	else if (final > 100.0)
		this->final = 100.0;
	else
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

char Record::overallGrade(double quizWt, double midtermWt, double finalWt) const {

	double overall;
	double overallPercent = quizWt + midtermWt + finalWt;
	quizWt = quizWt / overallPercent;
	midtermWt = midtermWt / overallPercent;
	finalWt = finalWt / overallPercent;
	
	overall =  getAveQuizGrade() * quizWt + getMidtermGrade() * midtermWt
		+getFinalGrade() * finalWt;
	return letterEquiv(overall);
}

double Record::getAveQuizGrade() const {
	return (quiz1 + quiz2) / 0.2;
}

double Record::getMidtermGrade() const {
	return midterm;
}

double Record::getFinalGrade() const {
	return final;
}

void Record::setQuiz1Grade(double score) {
	if (score > 10)
		quiz1 = 10;
	else if (score < 0)
		quiz1 = 0;
	else
		quiz1 = score;
}
void Record::setQuiz2Grade(double score) {
	if (score > 10)
		quiz2 = 10;
        else if (score < 0)
                quiz2 = 0;
        else
                quiz2 = score;

}
void Record::setMidtermGrade(double score) {
	if (score > 100)
                midterm = 100;
        else if (score < 0)
                midterm = 0;
        else
                midterm = score;

}
void Record::setFinalGrade(double score) {
	if (score > 100)
                final = 100;
        else if (score < 0)
                final = 0;
        else
                final = score;
}

double Record::getQuiz1Grade() const {	
	return quiz1;
}
double Record::getQuiz2Grade() const {
	return quiz2;
}

void Record::display() const {
	cout << "Quizs: " << getAveQuizGrade() << " percent" << endl
        << "Midterm: " << getMidtermGrade() << " percent" << endl
        << "Final: " << getFinalGrade() << " percent" << endl
        << "Grade is " << overallGrade() << endl;    // FIX USAGE OF rec
}

// ASK A TA TO HELP IF YOU GET STUCK, BUT FIRST TRY YOUR BEST TO FIGURE IT OUT!

