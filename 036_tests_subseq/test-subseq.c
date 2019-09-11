#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  int testarray[7][10] = {{1, 2, 1, 3, 5, 7, 2, 4, 6, 9},
                          {0},
                          {1, 2, 3, 4, 3, 6, 7, 8, 9, 10},
                          {1, 2, 3, 4, 5, 2, 3, 4, 5, 6},
                          {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
                          {1, 2, 3, 4, 5, 4, 3, 4, 5, 6},
                          {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  int testarray2[5][5] = {{-1, -1, -1, -1, -1},
                          {-5, -4, -3, -2, -1},
                          {-1, 0, 1, 2, 3},
                          {-1, 0, 0, 0, 0},
                          {-2, -1, -1, 0, 1}};
  int testarray3[] = {};
  int testarray4[1] = {1};

  size_t res[14] = {4, 1, 6, 5, 1, 5, 10, 1, 5, 5, 2, 3, 0, 1};
  size_t ress;

  for (int i = 0; i < 7; i++) {
    // printf("%d", i);
    ress = maxSeq(testarray[i], 10);
    if (ress != res[i]) {
      return EXIT_FAILURE;
    }
  }
  for (int j = 0; j < 5; j++) {
    ress = maxSeq(testarray2[j], 5);
    if (ress != res[j + 7]) {
      return EXIT_FAILURE;
    }
  }
  ress = maxSeq(testarray3, 0);
  if (ress != res[12]) {
    return EXIT_FAILURE;
  }
  ress = maxSeq(testarray4, 1);
  if (ress != res[13]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
