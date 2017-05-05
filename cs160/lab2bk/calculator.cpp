
#include "calculator.hpp"
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

// Scanner implementation

// You may have to modify this constructor, although it might not be neccessary.
Scanner::Scanner() : line(1), 
                     value(0) {
    // WRITEME
}

// You need to fill this method with the appropriate code for it to work as described in the project description.
Token Scanner::nextToken() {
	int i;
	char *digits;
	char t = cin.peek();
	while (t == ' ' || t == '\n')  {
		cin.get();
		if (t == '\n') ++this->line;
		t = cin.peek();
	}

	switch (t) {
		case ('+'): return T_PLUS;
		case ('-'): return T_MINUS;
		case ('*'): cin.get(); if (cin.peek() == '*') {cin.putback('*'); return T_EXP;}
					cin.putback('*'); return T_MULTIPLY;
		case ('/'): return T_DIVIDE;
		case ('%'): return T_MODULO;
		case ('('): return T_OPENPAREN;
		case (')'): return T_CLOSEPAREN;
		case (';'): return T_SEMICOLON;
		case ('\n'): return T_NEWLN;
		case (EOF): return T_EOF;
		default:
			
			if (t >= '0' && t <= '9') {
				i = 0;
				digits = new char[30];
				
				this->value = 0;
				do {
					cin.get();
					this->value = (this->value) * 10 + t - 48;
					digits[i++] = t;
					if (this->value < 0) outOfBoundsError(this->line, this->value);
					t = cin.peek();
				} while (t >= '0' && t <= '9');
				
				while (i > 0) {
					cin.putback(digits[--i]);
				}
				
				delete [] digits;
				return T_NUMBER;
			}
		}
	scanError(this->line, t);
    return T_EOF;
}

// You need to fill this method with the appropriate code for it to work as described in the project description.
void Scanner::eatToken(Token toConsume) {
	char t;
	Token find = nextToken();
    if (find != toConsume) mismatchError(this->line, toConsume, find);
	if (toConsume == T_NUMBER) {
		t = cin.peek();
		while (t >= '0' && t <= '9') {
			cin.get();
			t = cin.peek();
		}
	} else if (toConsume == T_EXP){
		cin.get();cin.get();
	}  else {
		cin.get();
	}

}

int Scanner::lineNumber() {
    return this->line;
}

int Scanner::getNumberValue() {
    return this->value;
}

// Parser implementation

// You may need to modify this constructor and make it do stuff, although it might not be neccessary.
Parser::Parser(bool eval) : evaluate(eval) {
    // WRITEME
}

void Parser::parse() {
    start();
}

void Parser::start() {
	count = 0;
    exprList();
	if (evaluate)
		for(int i = 0; i < count; ++i)
			cout << result[i] << endl;
	
}

// You will need to add more methods for this to work. Don't forget to also define them in calculator.hpp!
// WRITEME

void Parser::exprList() {
	result[count++] = expr(0, '+');
	exprListP();
}

void Parser::exprListP() {
	switch(scanner.nextToken()) {
		case(T_SEMICOLON):
		scanner.eatToken(T_SEMICOLON);
		exprList();
		break;

		case(T_EOF):
		break;
		default:
		parseError(scanner.lineNumber(), scanner.nextToken());
	}
}

int Parser::numOrExpr() {
	int rtn = 0;
	switch(scanner.nextToken()) {
		case(T_OPENPAREN):
		scanner.eatToken(T_OPENPAREN);
		rtn = expr(0, '+');
		scanner.eatToken(T_CLOSEPAREN);
		break;
		case(T_NUMBER):
		scanner.eatToken(T_NUMBER);
		rtn = scanner.getNumberValue();
		break;
		default:
		parseError(scanner.lineNumber(), scanner.nextToken());
	}
	return rtn;
}

int Parser::expr(int n, char c) {
	
	int i = termP(expoP(numOrExpr()));
	
	if (c == '+') n+=i;
	else if (c == '-') n-=i;

	return exprP(n);	
}

int Parser::term(int n, char c) {
	int i = expoP(numOrExpr());
	if (c == '*') n*=i;
	else if (c == '/') {
		if (i == 0) divideByZeroError(scanner.lineNumber(), n);
		n/=i;
	}
	else if (c == '%') n = n % i;
	return termP(n);
}

int Parser::expo(){
	return expoP(numOrExpr());
}

int Parser::exprP(int n) {

	switch(scanner.nextToken()) {
		case(T_PLUS):
		scanner.eatToken(T_PLUS);
		return expr(n, '+');
		break;
		case(T_MINUS):
		scanner.eatToken(T_MINUS);
		return expr(n, '-');
		break;
		case(T_CLOSEPAREN):
		case(T_NEWLN):
		case(T_EOF):
		case(T_SEMICOLON):
		break;
		default:
		parseError(scanner.lineNumber(), scanner.nextToken());
	}
	return n;
}


int Parser::termP(int n) {


	switch(scanner.nextToken()) {
		case(T_MULTIPLY):
		scanner.eatToken(T_MULTIPLY);
		return term(n, '*');
		break;
		case(T_DIVIDE):
		scanner.eatToken(T_DIVIDE);
		return term(n, '/');
		break;
		case(T_MODULO):
		scanner.eatToken(T_MODULO);
		return term(n, '%');
		break;
		case(T_PLUS):
		case(T_MINUS):
		case(T_CLOSEPAREN):
		case(T_NEWLN):
		case(T_EOF):
		case(T_SEMICOLON):
		break;
		default:
		parseError(scanner.lineNumber(), scanner.nextToken());
	}
	return n;
}


int Parser::expoP(int n) {
	int rtn = n;
	switch(scanner.nextToken()) {
		case(T_EXP):
		scanner.eatToken(T_EXP);
		for(int i = expo(); i > 1 ; --i){
			if (INT_MAX / n < rtn) outOfBoundsError(scanner.lineNumber(), rtn);
			rtn = n * rtn;
		}
		
		break;
		case(T_PLUS):
		case(T_MINUS):
		case(T_MULTIPLY):
		case(T_DIVIDE):
		case(T_MODULO):
		case(T_CLOSEPAREN):
		case(T_NEWLN):
		case(T_EOF):
		case(T_SEMICOLON):
		break;
		default:
		parseError(scanner.lineNumber(), scanner.nextToken());
	}
	return rtn;
}
