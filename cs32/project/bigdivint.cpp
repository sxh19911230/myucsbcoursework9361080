// bigdivint.cpp
// Xianghong Sun, 11/16/2014

#include "bigint.h"
#include "bigdivint.h"
#include <iostream>
#include <string>
#include <sstream>
using std::string;


BigDivInt::BigDivInt(const std::string & str) : BigInt(str){}

BigDivInt::BigDivInt(const BigInt &o) : BigInt(o){}

BigDivInt::BigDivInt(int n) : BigInt(n){}

BigDivInt::~BigDivInt() {

}

BigDivInt BigDivInt::operator/(const BigDivInt &o) const {

	if (o.sign_ == 'Z') throw BigException();
	if (sign_ == 'Z') return 0;


	std::stringstream ss;
	string str, dividend, result = "";
	BigDivInt tmp = *this, subtracting, rv;
	int digit;

	tmp.sign_ = '+';

	ss << o;

	dividend = ss.str();

	if (dividend[0] == '-')
		dividend = dividend.substr(1, dividend.size() - 1);

	ss.str("");

	ss << tmp;


	for (int n = ss.str().size() - dividend.size(); n >= 0; n--) {

		str = dividend;
		str.append(n, '0');

		subtracting = BigDivInt(str);
		digit = 0;

		while (tmp - subtracting > 0) {
			tmp -= subtracting;
			++digit;
		}
		

		result.append(std::to_string(digit));
	}

	if (result != "") rv = BigDivInt(result);
	else rv = BigDivInt();

	if (sign_ != o.sign_) {
		++rv;
		rv.sign_ = '-';
	}
	else if (rv.sign_ != 'Z')
		rv.sign_ = '+';

	

	return rv;
}


BigDivInt BigDivInt::operator%(const BigDivInt &o) const{
	if (o.sign_ == 'Z') throw BigException();
	if (sign_ == 'Z') return 0;


	std::stringstream ss;
	string str, dividend;
	BigDivInt tmp = *this, subtracting;


	tmp.sign_ = '+';

	ss << o;

	dividend = ss.str();

	if (dividend[0] == '-')
		dividend = dividend.substr(1, dividend.size() - 1);

	subtracting = BigDivInt(dividend);

	ss.str("");

	ss << tmp;

	for (int n = ss.str().size() - dividend.size(); n >= 0; n--) {
		str = dividend;
		str.append(n, '0');

		subtracting = BigDivInt(str);


		while (tmp - subtracting > 0)
			tmp -= subtracting;

	}

	if (sign_ != o.sign_) tmp -= subtracting;

	tmp.sign_ = o.sign_;

	return tmp;
}



BigDivInt &BigDivInt::operator/=(const BigDivInt &o){
	*this = *this / o;
	return *this;
}
BigDivInt &BigDivInt::operator%=(const BigDivInt & o){
	*this = *this % o;
	return *this;
}


