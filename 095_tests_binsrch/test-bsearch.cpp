#include <assert.h>

#include "function.h"
extern int binarySearchForZero(Function<int, int> * f, int low, int high);
void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  //test runtime h > l
  CountedIntFn c1(log2(high - low) + 1, f, mesg);
  Function<int, int> * fc1 = &c1;
  int ans = binarySearchForZero(fc1, low, high);

  //test correctness
  assert(ans == expected_ans);

  //test h < l ---X
  CountedIntFn c2(1, f, "testrev");
  Function<int, int> * fc2 = &c2;
  binarySearchForZero(fc2, high, low);
}

int main(void) {
  //test with sinfunction
  SinFunction sin1;
  Function<int, int> * f1 = &sin1;
  check(f1, 0, 150000, 52359, "testsin1");
  //test all pos/neg
  SigFunction sigp;
  SigFunction sign;
  Function<int, int> * f2 = &sigp;
  Function<int, int> * f3 = &sign;
  check(f2, 8, 16, 8, "testsigp");
  check(f3, -20, -10, -11, "testsign");
  //test linear range
  LinFunction lin1;
  Function<int, int> * f4 = &lin1;
  check(f4, 5, 5, 5, "testh=l");
  check(f4, -1, 4, 0, "testodd");
  check(f4, -1, 3, 0, "testeven");    //6
  check(f4, -3, 0, -1, "testright");  //5
  check(f4, 0, 6, 0, "testleft");

  return EXIT_SUCCESS;
}
