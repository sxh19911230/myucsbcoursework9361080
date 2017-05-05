// bigint.h - DO NOT CHANGE

#ifndef BIG_INT
#define BIG_INT

#include <iosfwd>
#include <string>
using std::ostream;
using std::istream;
using std::string;

class BigException { };  // completely defined here

struct DigitNode;  // to be defined in bigint.cpp (hidden to BigInt clients)

class BigInt {

  // two friends for output and input of BigInt objects
  friend ostream &operator<<(ostream &, const BigInt &);
  friend istream &operator>>(istream &, BigInt &);

 public:
    
  // four constructors and a destructor
  BigInt(const string &) throw(BigException); // new value defined by string
      // throw BigException() if non-digit in string (ok if 1st is '+' or '-')
  BigInt(int=0); // new value equals value of int (also a default ctor)
  BigInt(const BigInt &); // deep copy
  virtual ~BigInt(); // dtor is virtual, just in case
    
  // assignment operator
  BigInt &operator=(const BigInt &);
    
  // three binary arithmetic operators (this always on the left)
  BigInt operator+(const BigInt &) const;
  BigInt operator-(const BigInt &) const; // this - other
  BigInt operator*(const BigInt &) const;
    
  // six relational operators (this always on the left)
  bool operator==(const BigInt &) const;
  bool operator!=(const BigInt &) const;
  bool operator<(const BigInt &) const; // this < other
  bool operator>(const BigInt &) const;
  bool operator<=(const BigInt &) const;
  bool operator>=(const BigInt &) const;
    
  // three compound arithmetic/assignment operators
  BigInt &operator+=(const BigInt &);
  BigInt &operator-=(const BigInt &);
  BigInt &operator*=(const BigInt &);
    
  // pre- and post- increment and decrement operators
  BigInt &operator++(); // pre-inc
  BigInt operator++(int); // post-inc
  BigInt &operator--(); // pre-dec
  BigInt operator--(int); // post-dec


  

 protected:
    
  DigitNode *first_node_; // suggest pointer to first list node
  char sign_; // suggest use to store '+', 'Z' or '-'


};

#endif
