// bigint.cpp
// Xianghong Sun, 11/15/2014

#include <iosfwd>
#include <string>
#include <iostream>
#include "bigint.h"
using std::ostream;
using std::istream;
using std::string;

string toString(const DigitNode*);
void getRidOfZero(DigitNode*);
DigitNode* absSubtract(const DigitNode *, const DigitNode *);
int absCompare(const DigitNode *, const DigitNode *);
DigitNode* sameSignAdd(const DigitNode *, const DigitNode *);
int compare(char, const DigitNode *, char, const DigitNode *);

struct DigitNode {
	int int_node;
	DigitNode* nextnode;
};

// two friends for output and input of BigInt objects
ostream &operator<<(ostream &out, const BigInt &o) {
	if (o.sign_ == '-')
		out << o.sign_;
	out << toString(o.first_node_);
	return out;
}
istream &operator>>(istream &in, BigInt &o) {
	string str;
	in >> str;
	o = BigInt(str);
	return in;
}



	// four constructors and a destructor
BigInt::BigInt(const string &str) throw(BigException) {
	DigitNode *now;
	int i, hasSign;

	
	//Check
	
	if (!isdigit(str[0]) && str[0] != '+' && str[0] != '-') {
		throw BigException();
	}
	for (unsigned int i = 1; i < str.size(); i++)
		if (!isdigit(str[i]))
			throw BigException();


	if (str[0] == '+') {
		sign_ = '+';
		hasSign = 1;
	}
	else if (str[0] == '-') {
		sign_ = '-';
		hasSign = 1;
	}
	else if (!str.compare("0")){
		sign_ = 'Z';
		first_node_ = NULL;
		return;
	}
	else {
		hasSign = 0;
		sign_ = '+';
	}


	first_node_ = new DigitNode;
	now = first_node_;
	for (i = str.size(); i > 9 + hasSign; i -= 9) {
		now->int_node = atoi(str.substr(i - 9, 9).c_str());
		
		now->nextnode = new DigitNode;
		now = now->nextnode;
	}

	now->int_node = atoi(str.substr(hasSign, i - hasSign).c_str());
	now->nextnode = NULL;
	
	getRidOfZero(this->first_node_);
	if (first_node_ == NULL) sign_ = 'Z';
	
}

BigInt::BigInt(int n) {

	if (n == 0) {
		sign_ = 'Z';
		first_node_ = NULL;
		return;
	}
	else if (n > 0)
		sign_ = '+';
	else {
		sign_ = '-';
		n = -n;
	}
	first_node_ = new DigitNode;
	if (n > 1000000000) {
		first_node_->int_node = n % 10000000000;
		first_node_->nextnode = new DigitNode;
		first_node_->nextnode->int_node = n / 1000000000;
		first_node_->nextnode->nextnode = NULL;
	}
	else {
		first_node_->int_node = n;
		first_node_->nextnode = NULL;
	}
	
}

BigInt::BigInt(const BigInt &o) {
	DigitNode *t1, *t2;
	sign_ = o.sign_;
	if (o.first_node_ == NULL){
		first_node_ = NULL;
		return;
	}

	t1 = o.first_node_;
	t2 = first_node_ = new DigitNode;
	t2->int_node = t1->int_node;
	t1 = t1->nextnode;
	while (t1 != NULL) {
		
		t2->nextnode = new DigitNode;
		t2 = t2->nextnode;
		t2->int_node = t1->int_node;
		t1 = t1->nextnode;
	}
	t2->nextnode = NULL;
}

BigInt::~BigInt() {
	DigitNode *t1 = first_node_, *t2;
	while (t1 != NULL) {
		t2 = t1;
		t1 = t1->nextnode;
		delete t2;
	}
}

	// assignment operator
BigInt& BigInt::operator=(const BigInt &o) {
	DigitNode *t1, *t2;
	if (this != &o){
		t1 = first_node_;
		while (t1 != NULL) {
			t2 = t1;
			t1 = t1->nextnode;
			delete t2;
		}
		sign_ = o.sign_;
		if (o.first_node_ == NULL){
			first_node_ = NULL;
			return *this;
		}
		t1 = o.first_node_;
		t2 = first_node_ = new DigitNode;
		t2->int_node = t1->int_node;
		t1 = t1->nextnode;

		while (t1 != NULL) {
			t2->nextnode = new DigitNode;
			t2 = t2->nextnode;
			t2->int_node = t1->int_node;
			t1 = t1->nextnode;
		}
		t2->nextnode = NULL;
	}
	return *this;
}

	// three binary arithmetic operators (this always on the left)
BigInt BigInt::operator+(const BigInt &o) const {

	BigInt t1;
	if (sign_ == 'Z')
		return o;
	else if (o.sign_ == 'Z')
		return *this;
	else if (sign_ == o.sign_) {
		
		t1.sign_ = sign_;
		t1.first_node_=sameSignAdd(first_node_, o.first_node_);
	}
	else if (absCompare(first_node_, o.first_node_) == 0) {
		return t1;
	}
	else if (absCompare(first_node_,o.first_node_) > 0){
		t1.sign_ = sign_;
		t1.first_node_ = absSubtract(first_node_, o.first_node_);
	}
	else{
		t1.sign_ = o.sign_;
		t1.first_node_ = absSubtract(o.first_node_, first_node_);
	}
	return t1;
}


BigInt BigInt::operator-(const BigInt &o) const {
	BigInt t1;
	if (sign_ == 'Z') {
		t1 = o;
		if (o.sign_ == '+') t1.sign_ = '-';
		else t1.sign_ = '+';
	}
	else if (o.sign_ == 'Z')
		return *this;
	else if (sign_ != o.sign_) {
		t1.sign_ = sign_;
		t1.first_node_ = sameSignAdd(this->first_node_, o.first_node_);
	}
	else if (absCompare(this->first_node_, o.first_node_) == 0) {
		t1.sign_ = 'Z';
		t1.first_node_ = NULL;
	}
	else if (absCompare(this->first_node_, o.first_node_) > 0){
		t1.sign_ = this->sign_;
		t1.first_node_ = absSubtract(this->first_node_, o.first_node_);
	}
	else {
		if (this->sign_ == '+') t1.sign_ = '-';
		else t1.sign_ = '+';
		t1.first_node_ = absSubtract(o.first_node_, this->first_node_);
	}
	
	return t1;
}



BigInt BigInt::operator*(const BigInt &o) const {
	const BigInt *small, *big;
	BigInt sum, adding;
	DigitNode *t;
	int n, count, numOfNode = 0;
	string number;

	if (sign_ == 'Z' || o.sign_ == 'Z') return sum;


	if (absCompare(first_node_, o.first_node_) > 0) {
		small = &o;
		big = this;
	}
	else {
		small = this;
		big = &o;
	}

	t = small->first_node_;
	for (int i = 0; t; i++) {
		n = t->int_node;
		count = 0;
		while (n) {

			//The (9i+count th digit) * (larger number) * 10^(9i+count)
			adding = 0;
			for (int j = n % 10; j > 0; j--) 
				adding += *big;
			
			number=toString(adding.first_node_);
			number.append(i * 9 + count, '0');

			sum += BigInt(number);

			count++;
			n /= 10;
		}


		t = t->nextnode;
	}



	if (sign_ == o.sign_) sum.sign_ = '+';
	else sum.sign_ = '-';



	return sum;
}


	// six relational operators (this always on the left)
bool BigInt::operator==(const BigInt &o) const {
	return (sign_ == o.sign_ && !absCompare(this->first_node_,o.first_node_));
}

bool BigInt::operator!=(const BigInt & o) const {
	return (sign_ != o.sign_ || absCompare(this->first_node_, o.first_node_));
}

bool BigInt::operator<(const BigInt &o) const {

	return (compare(this->sign_,this->first_node_,o.sign_,o.first_node_) < 0);
}

bool BigInt::operator>(const BigInt &o) const {
	return (compare(this->sign_, this->first_node_, o.sign_, o.first_node_) > 0);
}
bool BigInt::operator<=(const BigInt &o) const {
	return !(compare(this->sign_, this->first_node_, o.sign_, o.first_node_) > 0);
}
bool BigInt::operator>=(const BigInt &o) const {
	return !(compare(this->sign_, this->first_node_, o.sign_, o.first_node_) < 0);
}


	// three compound arithmetic/assignment operators
BigInt& BigInt::operator+=(const BigInt &o) {
	*this = *this + o;
	return *this;
}

BigInt& BigInt::operator-=(const BigInt &o) {
	*this = *this - o;
	return *this;
}


BigInt& BigInt::operator*=(const BigInt &o) {
	*this = *this * o;
	return *this;
}

	// pre- and post- increment and decrement operators
BigInt& BigInt::operator++() {
	*this = *this + BigInt(1);
	return *this;
}

BigInt BigInt::operator++(int) {
	BigInt t = *this;
	*this = *this + BigInt(1);
	return t;
}

BigInt& BigInt::operator--()  {
	*this = *this + BigInt(-1);
	return *this;
}
BigInt BigInt::operator--(int) {
	BigInt t = *this;
	*this = *this + BigInt(-1);
	return t;
}


DigitNode* sameSignAdd(const DigitNode *o1, const DigitNode *o2) {

	int carry = 0;
	const DigitNode *t1, *t2;
	DigitNode *t, *rt;

	//same as positive - negtive and negtive - posiitive

	rt = t = new DigitNode;
	t1 = o1;
	t2 = o2;

	t->int_node = (t1->int_node + t2->int_node) % 1000000000;
	carry = (t1->int_node + t2->int_node) / 1000000000;
	
	while (t1->nextnode && t2->nextnode) {
		t->nextnode = new DigitNode;
		t = t->nextnode;
		t1 = t1->nextnode;
		t2 = t2->nextnode;
		t->int_node = (t1->int_node + t2->int_node + carry) % 1000000000;
		carry = (t1->int_node + t2->int_node + carry) / 1000000000;


		/*
		std::cout << t1->int_node << std::endl;
		std::cout << t2->int_node << std::endl;
		std::cout << t->int_node << std::endl;
		std::cout << carry << std::endl;
		std::cout << std::endl;
		*/




	}

	if (carry && !t1->nextnode && !t2->nextnode) {
		t->nextnode = new DigitNode;
		t = t->nextnode;
		t->int_node = 1;		
	}

	while (t1->nextnode) {
		t->nextnode = new DigitNode;
		t = t->nextnode;
		t1 = t1->nextnode;
		t->int_node = (t1->int_node + carry) % 1000000000;
		carry = (t1->int_node + carry) / 1000000000;
	}

	while (t2->nextnode) {
		t->nextnode = new DigitNode;
		t = t->nextnode;
		t2 = t2->nextnode;
		t->int_node = (t2->int_node + carry) % 1000000000;
		carry = (t2->int_node + carry) / 1000000000;
	}

	t->nextnode = NULL;

	return rt;
}

int absCompare(const DigitNode *o1, const DigitNode *o2) {
	int compare = 0;
	const DigitNode *t1, *t2;
	t1 = o1;
	t2 = o2;
	while (t1 && t2) {
		if (t1->int_node > t2->int_node)
			compare = 1;
		if (t1->int_node < t2->int_node)
			compare = -1;
		t1 = t1->nextnode;
		t2 = t2->nextnode;
	}
	if (t1)
		return 1;
	if (t2)
		return -1;
	return compare;
}


int compare(char c1, const DigitNode *o1, char c2, const DigitNode *o2) {
	int n1, n2;
	switch (c1){
	case '+':
		n1 = 1;
		break;
	case 'Z':
		n1 = 0;
		break;
	case '-':
		n1 = -1;
		break;
	}

	switch (c2){
	case '+':
		n2 = 1;
		break;
	case 'Z':
		n2 = 0;
		break;
	case '-':
		n2 = -1;
		break;
	}

	if (n1 != n2)
		return n1 - n2;
	if (!n1)
		return 0;
	if (n1 == 1)
		return absCompare(o1, o2);
	return -absCompare(o1, o2);

}


DigitNode* absSubtract(const DigitNode *o1, const DigitNode *o2) {
	int carry = 0;
	const DigitNode *t1, *t2;
	DigitNode *t, *rt;
	rt = t = new DigitNode;
	t1 = o1;
	t2 = o2;
	if (t1->int_node < t2->int_node){
		t->int_node = t1->int_node + 1000000000 - t2->int_node;
		carry = 1;
	}
	else
		t->int_node = t1->int_node - t2->int_node;


	while (t2->nextnode) {
		t->nextnode = new DigitNode;
		t = t->nextnode;
		t1 = t1->nextnode;
		t2 = t2->nextnode;

		if (t1->int_node - carry < t2->int_node){
			t->int_node = t1->int_node + 1000000000 - t2->int_node - carry;
			carry = 1;
		}
		else {
			t->int_node = t1->int_node - t2->int_node - carry;
			carry = 0;
		}
	}

	while (carry) {
		t->nextnode = new DigitNode;
		t = t->nextnode;
		t1 = t1->nextnode;
		if (t1->int_node == 0) t->int_node = 999999999;
		else {
			carry = 0;
			t->int_node = t1->int_node - 1;
		}
	}

	while (t1->nextnode) {
		t->nextnode = new DigitNode;
		t = t->nextnode;
		t1 = t1->nextnode;
		t->int_node = t1->int_node;
	}
	t->nextnode = NULL;

	getRidOfZero(rt);
	
	return rt;

}

void getRidOfZero(DigitNode* o) {
	DigitNode *t = o, *t2;
	int position = 0, markedPosition = 0;

	while (t->nextnode) {
		++position;
		t = t->nextnode;
		if (!t->int_node && !markedPosition)
			markedPosition = position;
		if (t->int_node)
			markedPosition = 0;
	}


	if (markedPosition--) {
		//goto the node before 0;

		t = o;
		while (markedPosition-- > 0)
			t = t->nextnode;

		t2 = t;
		t = t->nextnode;
		t2->nextnode = NULL;

		while (t) {
			t2 = t;
			t = t->nextnode;
			delete t2;
		}
	}

}

string toString(const DigitNode *o) {
	int i = 0, n;
	const DigitNode *t;
	string str, tmp;
	if (o == NULL) {
		return string("0");
	}

	t = o;
	while (t->nextnode != NULL) {
		i++;
		t = t->nextnode;
	}
	str.append(std::to_string(t->int_node));

	while (i) {
		n = i - 1;
		t = o;
		while (n) {
			t = t->nextnode;
			n--;
		}
		tmp = std::to_string(t->int_node);
		str.append(9 - tmp.size(), '0');
		str.append(std::to_string(t->int_node));
		i--;
	}
	return str;
}



