// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  x *= 4;
  x -= 3;
  return x;
}

void printSeq1Range(int low, int high) {
  int x = 0;
  for (int i = low; i < high; i++) {
    x = seq1(i);
    if (i == high - 1) {
      printf("%d", x);
    }
    else {
      printf("%d, ", x);
    }
    x = 0;
  }
  printf("\n");
  return;
}

int main(void) {
  int x = 0;
  for (int i = -10; i <= 10; i++) {
    x = seq1(i);
    printf("seq1(%d) = %d\n", i, x);
    x = 0;
  }
  printf("seq1(%d) = %d\n", 100000, seq1(100000));
  printf("seq1(%d) = %d\n", -100000, seq1(-100000));
  /*
    printf("seq1(%d) = %d\n", 0.1, seq1(0.1));
    printf("seq1(%d) = %d\n", -0.1, seq1(-0.1));
    printf("seq1(%d) = %d\n", 'a', seq1('a'));
    */
  for (int k = -10; k <= 10; k++) {
    for (int j = -10; j <= 10; j++) {
      printf("printSeq1range(%d,%d)\n", k, j);
      printSeq1Range(k, j);
    }
  }

  printf("printSeq1range(%d,%d)\n", -1000, -200);
  printSeq1Range(-1000, -200);
  printf("printSeq1range(%d,%d)\n", 200, 1200);
  printSeq1Range(200, 1200);
  printf("printSeq1range(%d,%d)\n", -1000, 1000);
  printSeq1Range(-1000, 1000);
  /*
   printf("printSeq1range(%d,%d)\n", 'a', 'e');
   printSeq1Range('a', 'e');
   printf("printSeq1range(%d,%d)\n", 0, 0.3);
   printSeq1Range(0, 0.3);
   printf("printSeq1range(%d,%d)\n", -0.2, 0);
   printSeq1Range(-0.2,0);
   printf("printSeq1range(%d,%d)\n", -1.2, 3.5);
   printSeq1Range(-1.2, 3.5);
   */
  return 0;
}
