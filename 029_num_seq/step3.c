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

//genrate seqence3
int seq3(int x, int y) {
  //pattern : -3x+2y+xy
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

//testing
int main(void) {
  // test seq3 with numbers in x [-10,10], y [-10,10]
  int res = 0;
  for (int y = -10; y <= 10; y++) {
    for (int x = -10; x <= 10; x++) {
      res = seq3(x, y);
      printf("seq3(%d, %d) = %d\n", x, y, res);
      res = 0;
    }
  }

  //test seq3 with large numbers
  printf("seq3(%d, %d) = %d\n", -1000, 1000, seq3(-1000, 1000));
  printf("seq3(%d, %d) = %d\n", -2000, -1000, seq3(-2000, -1000));
  printf("seq3(%d, %d) = %d\n", 2000, 2000, seq3(2000, 2000));
  printf("seq3(%d, %d) = %d\n", 2000, -2000, seq3(2000, -2000));

  //test counteveninseq3range with numbers in [-5,5]
  for (int yL = -5; yL <= 5; yL++) {
    for (int yH = -5; yH <= 5; yH++) {
      for (int xL = -5; xL <= 5; xL++) {
        for (int xH = -5; xH <= 5; xH++) {
          printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
                 xL,
                 xH,
                 yL,
                 yH,
                 countEvenInSeq3Range(xL, xH, yL, yH));
        }
      }
    }
  }

  //provided test case
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         0,
         2,
         0,
         3,
         countEvenInSeq3Range(0, 2, 0, 3));

  //test counteveninseq3range with large numbers
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         1000,
         2000,
         5,
         10,
         countEvenInSeq3Range(1000, 2000, 5, 10));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         5,
         10,
         1000,
         2500,
         countEvenInSeq3Range(5, 10, 1000, 2500));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         1000,
         2500,
         1000,
         2500,
         countEvenInSeq3Range(1000, 2500, 1000, 2500));

  return 0;
}
