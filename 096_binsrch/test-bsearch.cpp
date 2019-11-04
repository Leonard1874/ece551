#include <assert.h>

#include <iostream>

#include "function.h"
/*
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high){
    return low;
  }
  int l = low;
  int r = high;
  int res = 0;
  while (l < r) {
    if (l == r) {
      if (l == low) {
        int t = f->invoke(l);
        if (t >= 0) {
          res = low;
          break;
        }
      }
      if (r == high - 1) {
        int t = f->invoke(r);
        if (t <= 0) {
          res = high - 1;
          break;
        }
      }
      if (r != low && l != high - 1) {
        int t = f->invoke(r + 1);
        int t1 = f->invoke(r - 1);
        if (t > 0) {
          res = r;
          break;
        }
        if (t1 < 0) {
          res = r - 1;
          break;
        }
      }
    }
    int m = r + (l - r) / 2;
    std::cout << l << ", " << m << ", " << r << std::endl;
    int tmp = f->invoke(m);
    if (tmp == 0) {
      res = m;
      break;
    }
    if (tmp < 0) {
      l = m + 1;
    }
    if (tmp > 0) {
      r = m - 1;
    }
  }
  return res;
}
*/
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high) {
    return low;
  }
  high -= 1;
  int res = low;
  while (low <= high) {
    int mid = (low + high) / 2;
    int tmp = f->invoke(mid);
    //std::cout << low << ", " << mid << ", " << high << std::endl;
    if (tmp > 0) {
      high = mid - 1;
    }
    if (tmp <= 0) {
      res = mid;
      low = mid + 1;
    }
    //std::cout << res << std::endl;
  }
  return res;
}
//extern int binarySearchForZero(Function<int, int> * f, int low, int high);
void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  //test runtime h > l
  //std::cout << log2(high - low) + 1 << std::endl;
  CountedIntFn c1(log2(high - low) + 1, f, mesg);
  Function<int, int> * fc1 = &c1;
  int ans = binarySearchForZero(fc1, low, high);
  //std::cout << ans << std::endl;
  //test correctness
  assert(ans == expected_ans);
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
  check(f4, -1, 4, 0, "testodd");
  check(f4, -1, 3, 0, "testeven");    //6
  check(f4, -3, 0, -1, "testright");  //5
  check(f4, 0, 6, 0, "testleft");
  //test non-linear range
  NLinFunction nlin1;
  Function<int, int> * f5 = &nlin1;
  check(f5, -1, 5, 1, "testnonlinear");
  return EXIT_SUCCESS;
}
