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

// to generate seqence 1
int seq1(int x) {
  // pattern : x = x*4 -3
  x *= 4;
  x -= 3;
  return x;
}

//to print seqence 1, [low,high)
void printSeq1Range(int low, int high) {
  int x = 0;  //each result of seq1 will be saved in x for printing
  for (int i = low; i < high; i++) {
    x = seq1(i);
    if (i == high - 1) {
      printf("%d",
             x);  //if current is the last number to print, pirnt without comma and space
    }
    else {
      printf("%d, ", x);
    }
    x = 0;
  }
  printf("\n");  //at last, print a newline
  return;
}

//testing
int main(void) {
  int x = 0;

  //test seq1 with [-10,10]
  for (int i = -10; i <= 10; i++) {
    x = seq1(i);
    printf("seq1(%d) = %d\n", i, x);
    x = 0;
  }

  //test seq1 with large numbers
  printf("seq1(%d) = %d\n", 100000, seq1(100000));
  printf("seq1(%d) = %d\n", -100000, seq1(-100000));

  //test printSeq1range with low [-10,10], high [-10,10]
  for (int k = -10; k <= 10; k++) {
    for (int j = -10; j <= 10; j++) {
      printf("printSeq1range(%d,%d)\n", k, j);
      printSeq1Range(k, j);
    }
  }

  //test printSeq1range with large numbers
  printf("printSeq1range(%d,%d)\n", -1000, -200);
  printSeq1Range(-1000, -200);
  printf("printSeq1range(%d,%d)\n", 200, 1200);
  printSeq1Range(200, 1200);
  printf("printSeq1range(%d,%d)\n", -1000, 1000);
  printSeq1Range(-1000, 1000);

  return 0;
}
