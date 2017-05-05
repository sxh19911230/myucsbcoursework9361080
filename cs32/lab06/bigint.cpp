#include <iosfwd>
#include <string>
#include "bigint.h"
using std::ostream;
using std::istream;
using std::string;


ostream &operator<<(ostream &, const BigInt &);
istream &operator>>(istream &, BigInt &);



	// four constructors and a destructor
BigInt::BigInt(const string &) throw(BigException) {}
BigInt::BigInt(int = 0) {}
BigInt::BigInt(const BigInt &) {}
BigInt::~BigInt() {}

	// assignment operator
BigInt& BigInt::operator=(const BigInt &) {}

	// three binary arithmetic operators (this always on the left)
BigInt BigInt::operator+(const BigInt &) const {}
BigInt BigInt::operator-(const BigInt &) const {}
BigInt BigInt::operator*(const BigInt &) const {}

	// six relational operators (this always on the left)
bool BigInt::operator==(const BigInt &) const {}
bool BigInt::operator!=(const BigInt &) const {}
bool BigInt::operator<(const BigInt &) const {}
bool BigInt::operator>(const BigInt &) const {}
bool BigInt::operator<=(const BigInt &) const {}
bool BigInt::operator>=(const BigInt &) const {}

	// three compound arithmetic/assignment operators
BigInt& BigInt::operator+=(const BigInt &) {}
BigInt& BigInt::operator-=(const BigInt &) {}
BigInt& BigInt::operator*=(const BigInt &) {}

	// pre- and post- increment and decrement operators
BigInt& BigInt::operator++() {}
BigInt BigInt::operator++(int) {}
BigInt& BigInt::operator--() {}
BigInt BigInt::operator--(int) {}

