#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c = malloc(sizeof(*c));
  c->sz = 1;
  c->onearray = malloc(c->sz * sizeof(*c->onearray));
  c->onearray[0].strname = strdup("unknown");
  c->onearray[0].n = 0;
  //printf("1\n");
  return c;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int found = 0;
  if (name == NULL) {
    c->onearray[0].n += 1;
  }
  else {
    for (int i = 0; i < c->sz; i++) {
      if (!strcmp(c->onearray[i].strname, name)) {
        c->onearray[i].n += 1;
        found = 1;
      }
    }
    if (found == 0) {
      c->sz += 1;
      c->onearray = realloc(c->onearray, c->sz * sizeof(*c->onearray));
      c->onearray[c->sz - 1].strname = strdup(name);
      c->onearray[c->sz - 1].n = 1;
    }
    //printf("%d", numnull);
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (c->sz > 1) {
    for (int i = 1; i < c->sz; i++) {
      fprintf(outFile, "%s : %d\n", c->onearray[i].strname, c->onearray[i].n);
    }
  }
  if (c->onearray[0].n != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->onearray[0].n);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->sz; i++) {
    free(c->onearray[i].strname);
  }
  free(c->onearray);
  free(c);
}
