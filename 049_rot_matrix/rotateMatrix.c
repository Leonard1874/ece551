#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readlines(char ** l, size_t size, size_t lsize, FILE * f) {
  size_t i = 0;
  while (i < size) {
    /*
    while ((fgets(l[i], lsize - 1, f)) != NULL) {
      // fprintf(stdout, "i = %zu", i);
      if (strchr(l[i], '\n') == NULL) {
        fprintf(stderr, "line is too long!");
        return 0;
      }
      else {
        if (l[i][lsize - 1] != '\n') {
          fprintf(stderr, "line is too short!");
          return 0;
        }
      }
      i++;
    }*/

    fgets(l[i], lsize, f);
    if (strchr(l[i], '\n') == NULL) {
      // int t = 0;

      fprintf(stderr, "line is too long!");
      return 0;
    }
    else {
      if (l[i][lsize - 2] != '\n') {
        fprintf(stderr, "line is too short!");
        return 0;
      }
    }
    i++;
  }

  int c = 1;

  if ((c = fgetc(f)) != EOF) {
    fprintf(stderr, "too many lines!");
    return 0;
  }

  return 1;
}

void printlines(char ** l, size_t lsize, size_t csize) {
  for (size_t i = 0; i < csize; i++) {
    for (size_t j = 0; j < lsize - 2; j++) {
      fprintf(stdout, "%c", l[csize - 1 - j][i]);
    }
    fprintf(stdout, "\n");
  }

  // fprintf(stdout, "%c", l[csize - 1][0]);
  return;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "wrong number of input!");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    fprintf(stderr, "cannot open input!");
    return EXIT_FAILURE;
  }

  size_t lsize = 12;
  size_t csize = 10;
  char lines[csize][lsize];
  char * plines[] = {
      lines[0],
      lines[1],
      lines[2],
      lines[3],
      lines[4],
      lines[5],
      lines[6],
      lines[7],
      lines[8],
      lines[9],
  };

  if (!(readlines(plines, csize, lsize, f))) {
    return EXIT_FAILURE;
  }

  printlines(plines, lsize, csize);

  if (fclose(f) != 0) {
    fprintf(stderr, "cannot close input!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
