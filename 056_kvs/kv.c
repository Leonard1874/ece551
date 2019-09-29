#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseline(char * line, kvarray_t * array) {
  if (strlen(line) == 0) {
    printf("empty!\n");
    exit(EXIT_FAILURE);
  }
  size_t i = 0;
  while (i < strlen(line)) {
    if (line[i] == '=') {
      break;
    }
    i++;
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
  array->kvarray[array->sz - 1].value = strndup(line + i + 1, strlen(line + i + 1) - 1);
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

  if (i == 1) {
    printf("the file is empty!\n");
    free(cur);
    free(lines[0]);
    free(lines);
    fclose(f);
    free(array);
    exit(EXIT_FAILURE);
  }

  free(cur);
  for (size_t j = 0; j < i; j++) {
    if (lines[j][0] == '\n') {
      //printf("empty line\n");
      free(lines[j]);
    }
    else {
      parseline(lines[j], array);
      free(lines[j]);
    }
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
