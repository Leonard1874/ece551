#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int countmax(FILE * f) {
  int res = 0;
  int max = 0;
  int i = 0;
  int j = 0;

  int flist[26] = {0};

  while ((i = fgetc(f)) != EOF) {
    if (isalpha(i)) {
      flist[i - 97] += 1;
    }
  }

  for (j = 0; j < 26; j++) {
    if (flist[j] > max) {
      max = flist[j];
      res = j + 97;
    }
  }
  return res;
}

int countkey(int m) {
  int res = m - 'e';
  if (res >= 0) {
    return res;
  }
  else {
    res += 26;
    return res;
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "wrong number of command line arguments!");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "cannot open file!");
    return EXIT_FAILURE;
  }

  int m = 0;
  m = countmax(f);

  int key = 0;
  key = countkey(m);

  if (fclose(f) != 0) {
    fprintf(stderr, "cannot close file!");
    return EXIT_FAILURE;
  }

  printf("%d\n", key);

  return EXIT_SUCCESS;
}
