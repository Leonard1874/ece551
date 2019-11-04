#include "function.h"
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
