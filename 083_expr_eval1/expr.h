#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long a) : num(a) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << num;
    std::string s(ss.str());
    return s;
  }
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << lhs << " + " << rhs;
    std::string s(ss.str());
    return s;
  }
};
