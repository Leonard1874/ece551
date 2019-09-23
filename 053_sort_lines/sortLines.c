#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int rsp(FILE * f) {
  char ** lines = NULL;
  char * temp = NULL;
  size_t sz;
  size_t i = 0;
  while (getline(&temp, &sz, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = temp;
    temp = NULL;
    i += 1;
  }

  free(temp);

  sortData(lines, i);

  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }

  free(lines);
  return 0;
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!

  if (argc < 1) {
    fprintf(stderr, "invalid argument number!");
    return EXIT_FAILURE;
  }

  if (argc == 1) {
    if (rsp(stdin) != 0) {
      return EXIT_FAILURE;
    }
  }

  if (argc > 1) {
    int i = 1;
    while (argv[i] != NULL) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "cannot open file!");
        return EXIT_FAILURE;
      }
      if (rsp(f) != 0) {
        return EXIT_FAILURE;
      }
      if (fclose(f) != 0) {
        fprintf(stderr, "cannot close file!");
        return EXIT_FAILURE;
      }
      i += 1;
    }
  }
  return EXIT_SUCCESS;
}
