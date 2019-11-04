#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <cmath>
#include <cstdio>
#include <cstdlib>
template<typename R, typename A>
class Function {
 public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class SigFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) {
    if (arg > 0) {
      return 1;
    }
    return -1;
  }
};

class LinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 2 * arg; }
};

class NLinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg * arg - 2; }
};

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

#endif
