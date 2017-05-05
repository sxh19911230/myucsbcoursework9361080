// grading2.cpp - uses C++ style object-handling (AFTER CHANGES BELOW)
// Xianghong Sun, 10/18/2014

#include <iostream>
using namespace std;

class Record {                      // CHANGE TO class
    
// DECLARE A public SECTION, AND DEFINE A NEW METHOD NAMED setGrades,
// THAT TAKES FOUR double ARGUMENTS

public:
        void setGrades(double, double, double, double);
	char letterEquiv(const double grade) const;  	// MOVE TO private SECTION OF THE CLASS
                                        	// AND FIX SIGNATURE TO SUPPORT CONSTANT OBJECTS
	char overallGrade() const;		// MOVE TO public SECTION OF THE CLASS
                            			// AND MAKE SIGNATURE BE 'char overallGrade() const'


// DECLARE A private SECTION AND MAKE ALL DATA PART OF IT
private:
	double quiz1, quiz2; 
	double midterm, final;
};

Record getScores();


int main() {
    Record rec = getScores();
    cout << "Grade is " << rec.overallGrade() << endl;    // FIX USAGE OF rec
    return 0;
}

// getScores IS AN external FUNCTION, SO IT MUST USE setGrades TO SET THE VALUES
// OF THE OBJECT'S private DATA (Hint: You'll need some local variables.)
Record getScores() {
    Record result;
    double quiz1, quiz2, midterm, final;
    cout << "Enter scores in this order: 2 quizzes, midterm, final: ";
    cin >> quiz1 >> quiz2 >> midterm >> final;
    result.setGrades(quiz1, quiz2, midterm, final);
    return result;
}

// THE NEXT TWO FUNCTIONS ARE METHODS OF THE CLASS, SO THEY MUST PROPERLY
// BE IDENTIFIED AS SUCH WITH THE SCOPE RESOLUTION OPERATOR '::'
// REMEMBER TO IMPLEMENT THE NEW setGrades METHOD TOO.

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

// ASK A TA TO HELP IF YOU GET STUCK, BUT FIRST TRY YOUR BEST TO FIGURE IT OUT!
