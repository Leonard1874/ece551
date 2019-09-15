// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  int res = -3 * x + 2 * y + x * y;
  return res;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int num_even = 0;
  for (int y = yLow; y < yHi; y++) {
    for (int x = xLow; x < xHi; x++) {
      if (seq3(x, y) % 2 == 0) {
        num_even += 1;
      }
    }
  }
  return num_even;
}

int main(void) {
  int res = 0;
  for (int y = -10; y <= 10; y++) {
    for (int x = -10; x <= 10; x++) {
      res = seq3(x, y);
      printf("seq3(%d,%d) = %d\n", x, y, res);
      res = 0;
    }
  }

  printf("seq3(%d,%d) = %d\n", -1000, 1000, seq3(-1000, 1000));
  printf("seq3(%d,%d) = %d\n", -2000, -1000, seq3(-2000, -1000));
  printf("seq3(%d,%d) = %d\n", 2000, 2000, seq3(2000, 2000));
  printf("seq3(%d,%d) = %d\n", 2000, -2000, seq3(2000, -2000));

  for (int yL = 0; yL <= 5; yL++) {
    for (int yH = -5; yH <= 2; yH++) {
      for (int xL = 0; xL <= 5; xL++) {
        for (int xH = -2; xH <= 5; xH++) {
          printf("countEvenInSeq3Range(%d,%d,%d,%d) = %d\n",
                 xL,
                 xH,
                 yL,
                 yH,
                 countEvenInSeq3Range(xL, xH, yL, yH));
        }
      }
    }
  }

  printf("countEvenInSeq3Range(%d,%d,%d,%d) = %d\n",
         1000,
         2000,
         5,
         10,
         countEvenInSeq3Range(1000, 2000, 5, 10));
  printf("countEvenInSeq3Range(%d,%d,%d,%d) = %d\n",
         5,
         10,
         1000,
         2500,
         countEvenInSeq3Range(5, 10, 1000, 2500));
  printf("countEvenInSeq3Range(%d,%d,%d,%d) = %d\n",
         1000,
         2500,
         1000,
         2500,
         countEvenInSeq3Range(1000, 2500, 1000, 2500));

  return 0;
}
