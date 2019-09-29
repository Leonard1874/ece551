#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseline(char * line, kvarray_t * array) {
  size_t i = 0;
  while (i <= strlen(line) - 1) {
    if (line[i] == '=') {
      break;
    }
    i++;
  }
  if (i == strlen(line)) {
    printf("there is no =\n");
    exit(EXIT_FAILURE);
  }
  if (array->sz == 0) {
    array->kvarray = malloc(sizeof(*array->kvarray));
    array->sz += 1;
  }
  else {
    array->kvarray = realloc(array->kvarray, (array->sz + 1) * sizeof(*array->kvarray));
    array->sz += 1;
  }
  array->kvarray[array->sz - 1].key = strndup(line, i);
  array->kvarray[array->sz - 1].value = strdup(line + i + 1);
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "cannot open file!");
    exit(EXIT_FAILURE);
  }
  kvarray_t * array = malloc(sizeof(*array));
  array->sz = 0;
  char ** lines = NULL;
  char * cur = NULL;
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
    parseline(lines[j], array);
    free(lines[j]);
  }
  free(lines);
  if (fclose(f) != 0) {
    printf("cannot close file\n");
    exit(EXIT_FAILURE);
  }
  return array;
}
void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->sz; i++) {
    free(pairs->kvarray[i].key);
    free(pairs->kvarray[i].value);
  }
  free(pairs->kvarray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->sz; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvarray[i].key, pairs->kvarray[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->sz; i++) {
    if (!strcmp(pairs->kvarray[i].key, key)) {
      return pairs->kvarray[i].value;
    }
  }
  return NULL;
}
