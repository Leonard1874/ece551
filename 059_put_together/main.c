#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  if (filename == NULL) {
    printf("filename cannot be NULL!\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    printf("cannot open file!\n");
    exit(EXIT_FAILURE);
  }
  counts_t * c = createCounts();
  counts_t * cans = createCounts();
  char ** lines = NULL;
  char * cur = NULL;
  char * strname = NULL;
  size_t linecap;
  size_t i = 0;
  while (getline(&cur, &linecap, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = cur;
    cur = NULL;
    i++;
  }
  free(cur);
  for (size_t j = 0; j < i; j++) {
    addCount(c, lines[j]);
    free(lines[j]);
  }
  free(lines);
  for (int i = 1; i < c->sz; i++) {
    strname = strndup(c->onearray[i].strname, strlen(c->onearray[i].strname) - 1);
    addCount(cans, lookupValue(kvPairs, strname));
    free(strname);
  }
  cans->onearray[0].n += c->onearray[0].n;
  freeCounts(c);
  fclose(f);
  return cans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "wrong number of arguments!\n");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }
  //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}
