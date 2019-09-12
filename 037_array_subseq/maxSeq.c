#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  size_t l = 0;
  size_t max_l = 0;
  size_t left = 0;
  size_t right = 0;
  l = right - left;
  while (right + 1 <= n - 1) {
    if (array[right + 1] > array[right]) {
      right += 1;
      l = right - left + 1;
    }
    else {
      right++;
      left = right;
      l = 1;
    }
    if (max_l < l) {
      max_l = l;
    }
  }
  return max_l;
}
