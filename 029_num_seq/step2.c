// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

//generate seqence2
int seq2(int x) {
  int y = x + 3;
  if (y % 4 == 1 || y % 4 == -3) {
    x *= 2;
  }
  else {
    x = x * y + 1;
  }
  return x;
}

//calculate the sum numbers in seqence2[low,high)
int sumSeq2(int low, int high) {
  int sum = 0;
  for (int i = low; i < high; i++) {
    sum += seq2(i);
  }
  return sum;
}

//testing
int main(void) {
  int x = 0;  //save the return value of seq2 in x for printing

  //test seq2 with numbers in [-20,20]
  for (int i = -20; i <= 20; i++) {
    x = seq2(i);
    printf("seq2(%d) = %d\n", i, x);
    x = 0;
  }

  //test seq2 with large numbers
  printf("seq2(%d) = %d\n", 1000, seq2(1000));
  printf("seq2(%d) = %d\n", -1000, seq2(-1000));
  printf("seq2(%d) = %d\n", 1002, seq2(1002));
  printf("seq2(%d) = %d\n", -1202, seq2(-1202));

  //test sumSeq2 with numbers low [-10,10], high [-10,10]
  for (int k = -10; k <= 10; k++) {
    for (int j = -10; j <= 10; j++) {
      printf("sumSeq2(%d, %d) = %d\n", k, j, sumSeq2(k, j));
    }
  }

  //provided test cases
  printf("sumSeq2(%d,%d) = %d\n", 0, 2, sumSeq2(0, 2));
  printf("sumSeq2(%d,%d) = %d\n", 3, 6, sumSeq2(3, 6));
  printf("sumSeq2(%d,%d) = %d\n", 9, 7, sumSeq2(9, 7));

  //test sumSeq2 with large numbers
  printf("sumSeq2(%d,%d) = %d\n", 100, 100, sumSeq2(100, 100));
  printf("sumSeq2(%d, %d) = %d\n", 0, 1000, sumSeq2(0, 1000));
  printf("sumSeq2(%d, %d) = %d\n", -1000, 1000, sumSeq2(-1000, 1000));
  printf("sumSeq2(%d, %d) = %d\n", -1000, 0, sumSeq2(-1000, 0));

  return 0;
}
