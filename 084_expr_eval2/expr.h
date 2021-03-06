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
  long num;

 public:
  NumExpression(long a) : num(a) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << num;
    std::string s(ss.str());
    return s;
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    std::string s(ss.str());
    return s;
  }
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    std::string s(ss.str());
    return s;
  }
  virtual ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
};

class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    std::string s(ss.str());
    return s;
  }
  virtual ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
};

class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    std::string s(ss.str());
    return s;
  }
  virtual ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};
