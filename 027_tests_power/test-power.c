#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

unsigned powing(unsigned x, unsigned y, unsigned ans) {
  if (x < 0 || y < 0) {
    return -1;
  }
  if (y == 0) {
    return 1;
  }
  if (y == 1) {
    return ans;
  }
  if (x == 0 && y != 0) {
    return 0;
  }
  return powing(x, y - 1, ans * x);
}

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans)
    exit(EXIT_FAILURE);
  else
    return;
}

int main(void) {
  unsigned expected_ans = 0;
  for (unsigned x = 0; x <= 10; x++) {
    for (unsigned y = 0; y <= 10; y++) {
      unsigned ans = x;
      expected_ans = powing(x, y, ans);
      run_check(x, y, expected_ans);
    }
  }
  return EXIT_SUCCESS;
}
