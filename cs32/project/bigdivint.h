// bigdivint.h - DO NOT CHANGE

#ifndef BIGDIVINT_H
#define BIGDIVINT_H

#include "bigint.h"

class BigDivInt : public BigInt {
 public:
  BigDivInt(const std::string &);
  BigDivInt(const BigInt &);
  BigDivInt(int=0);
  virtual ~BigDivInt();
  BigDivInt operator/(const BigDivInt &) const; // this / other (truncates)
  BigDivInt operator%(const BigDivInt &) const; // this % other
  BigDivInt &operator/=(const BigDivInt &);
  BigDivInt &operator%=(const BigDivInt &);
};

#endif /* BIGDIVINT_H */
