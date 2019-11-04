#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int l = low;
  int r = high - 1;
  int res = 0;
  while (l <= r) {
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
        if (t > 0) {
          res = r;
          break;
        }
      }
    }
    int m = r + (l - r) / 2;
    //std::cout << l << ", " << m << ", " << r << std::endl;
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
